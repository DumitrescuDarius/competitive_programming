#include <arpa/inet.h>
#include <cerrno>
#include <chrono>
#include <cstring>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <netinet/in.h>
#include <random>
#include <sys/select.h>
#include <sys/socket.h>
#include <termios.h>
#include <thread>
#include <unistd.h>

using namespace std;

// ===================== ORIGINAL GLOBALS =====================
char a[21][36], x;
int i, j, p = -1, r = -1, scor[2], ps[3] = {0, 8, 12}, pd[3] = {0, 8, 12},
          dificultate, scor_sp, highScore, random_val;
const int n = 35, m = 20;
bool atins, mod, skip, pause_flag;

// ===================== NETWORK GLOBALS (NEW) =====================
int gSock = -1;
sockaddr_in gPeerAddr{};
socklen_t gPeerAddrLen = sizeof(gPeerAddr);
bool gIsHost = false;

// ===================== TERMINAL GLOBALS =====================
struct termios orig_termios;

// ===================== NETWORK PACKETS (NEW) =====================
#pragma pack(push, 1)
struct JoinPacket {
  int magic;   // 'PONG' magic
  int version; // 1
};
struct ConfigPacket {
  int dificultate; // host-selected difficulty
};
struct InputPacket {
  int move; // -1 up, 0 none, 1 down
};
struct StatePacket {
  int i, j, p, r;
  int ps1, ps2;
  int pd1, pd2;
  int scor0, scor1;
};
#pragma pack(pop)

// ===================== TERMINAL FUNCTIONS (replaces Windows console)
// =====================
void disableRawMode() { tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios); }

void enableRawMode() {
  tcgetattr(STDIN_FILENO, &orig_termios);
  atexit(disableRawMode);

  struct termios raw = orig_termios;
  raw.c_lflag &= ~(ECHO | ICANON);
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 0;
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void ShowConsoleCursor(bool showFlag) {
  if (showFlag) {
    cout << "\033[?25h" << flush;
  } else {
    cout << "\033[?25l" << flush;
  }
}

// Non-blocking key check
bool kbhit() {
  struct timeval tv = {0, 0};
  fd_set fds;
  FD_ZERO(&fds);
  FD_SET(STDIN_FILENO, &fds);
  return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) > 0;
}

// Get character without blocking
char getch() {
  char c = 0;
  if (kbhit()) {
    read(STDIN_FILENO, &c, 1);
  }
  return c;
}

// Key state tracking
struct KeyState {
  bool pressed[256] = {false};
  bool justPressed[256] = {false};

  void update() {
    for (int i = 0; i < 256; i++) {
      justPressed[i] = false;
    }

    if (kbhit()) {
      char c = getch();
      if (c == 27) { // ESC or arrow key sequence
        if (kbhit()) {
          char c2 = getch();
          if (c2 == '[' && kbhit()) {
            char c3 = getch();
            if (c3 == 'A') { // Up arrow
              if (!pressed[128])
                justPressed[128] = true;
              pressed[128] = true;
            } else if (c3 == 'B') { // Down arrow
              if (!pressed[129])
                justPressed[129] = true;
              pressed[129] = true;
            }
          } else {
            // Just ESC
            if (!pressed[27])
              justPressed[27] = true;
            pressed[27] = true;
          }
        } else {
          if (!pressed[27])
            justPressed[27] = true;
          pressed[27] = true;
        }
      } else {
        int key = (unsigned char)c;
        if (c >= 'a' && c <= 'z')
          key = c - 32; // Convert to uppercase
        if (!pressed[key])
          justPressed[key] = true;
        pressed[key] = true;
      }
    }

    // Reset pressed states after a short time
    static auto lastReset = chrono::steady_clock::now();
    auto now = chrono::steady_clock::now();
    if (chrono::duration_cast<chrono::milliseconds>(now - lastReset).count() >
        100) {
      for (int i = 0; i < 256; i++) {
        pressed[i] = false;
      }
      lastReset = now;
    }
  }

  bool isPressed(int key) { return pressed[key]; }
  bool wasJustPressed(int key) { return justPressed[key]; }
} keyState;

#define VK_UP 128
#define VK_DOWN 129
#define VK_ESCAPE 27
#define VK_SPACE 32

bool GetAsyncKeyState(int key) {
  keyState.update();

  if (key == VK_UP)
    return keyState.isPressed(128);
  if (key == VK_DOWN)
    return keyState.isPressed(129);
  if (key == VK_ESCAPE)
    return keyState.isPressed(27);
  if (key == VK_SPACE)
    return keyState.isPressed(32);
  if (key == 'W')
    return keyState.isPressed('W');
  if (key == 'S')
    return keyState.isPressed('S');
  if (key == 'H')
    return keyState.isPressed('H');
  if (key == 0x31)
    return keyState.isPressed('1');
  if (key == 0x32)
    return keyState.isPressed('2');
  if (key == 0x33)
    return keyState.isPressed('3');
  if (key == 0x34)
    return keyState.isPressed('4');
  if (key == 0x35)
    return keyState.isPressed('5');
  if (key == 0xBD)
    return keyState.isPressed('-');

  return false;
}

void Sleep(int ms) { this_thread::sleep_for(chrono::milliseconds(ms)); }

// ===================== ORIGINAL FUNCTIONS =====================
void load() {
  ifstream f("save.txt");
  if (f.is_open()) {
    f >> highScore;
    f.close();
  } else {
    highScore = 0;
  }
}

bool select_diff() {
  keyState.update();
  if (keyState.wasJustPressed('1')) {
    dificultate = 200;
    return true;
  }
  if (keyState.wasJustPressed('2')) {
    dificultate = 150;
    return true;
  }
  if (keyState.wasJustPressed('3')) {
    dificultate = 100;
    return true;
  }
  if (keyState.wasJustPressed('4')) {
    dificultate = 50;
    return true;
  }
  if (keyState.wasJustPressed('5')) {
    dificultate = 1;
    return true;
  }
  return false;
}

void help_menu() {
  cout << "W S controleaza peretele din stanga, iar sageata sus si jos cel din "
          "dreapta.\nPentru singleplayer se joaca doar cu W S,\n";
  cout << "iar dificultatea modifica viteza mingii si sansa ca bot-ul sa miste "
          "peretele sau astfel:\n";
  cout << "Incepator: O miscare a mingii la fiecare 200ms + sansa de 20% ca "
          "miscarea bot-ului sa dea fail;\n";
  cout << "Usor: O miscare a mingii la fiecare 150ms + sansa de 15% ca "
          "miscarea bot-ului sa dea fail;\n";
  cout << "Mediu: O miscare a mingii la fiecare 100ms + sansa de 10% ca "
          "miscarea bot-ului sa dea fail;\n";
  cout << "Greu: O miscare a mingii la fiecare 50ms + sansa de 5% ca miscarea "
          "bot-ului sa dea fail;\n";
  cout << "Inuman: O miscare a mingii la fiecare 1ms + bot-ul se va misca "
          "garantat.\n";
  cout << "Pentru multiplayer dificultatea schimba doar viteza jocului la "
          "valorite antementionate.";
  cout << "Apasa SPACE pentru a te intoarce la meniul principal.";
}

void MainMenu() {
  cout << "\033[2J\033[H" << flush; // Clear screen
  while (1) {
    cout << "   P I N G  P O N G\n";
    cout << "|     |\n";
    cout << "|O    |\n";
    cout << "|     |\n";
    cout << "Selecteaza dificultatea: (dificultatea este doar un modificator "
            "de viteza)\n1.Incepator\n2.Usor\n3.Mediu\n4.Greu\n5.Inuman\nApasa "
            "h pentru help menu";

    keyState.update();
    if (keyState.wasJustPressed(VK_ESCAPE))
      exit(0);
    else if (keyState.wasJustPressed('H')) {
      Sleep(1000);
      cout << "\033[2J\033[H" << flush;
      help_menu();
      while (1) {
        keyState.update();
        if (keyState.wasJustPressed(VK_SPACE))
          break;
        Sleep(50);
      }
    }
    if (select_diff())
      break;
    Sleep(400);
    cout << "\033[2J\033[H" << flush;
    cout << "   P I N G  P O N G\n";
    cout << "|     |\n";
    cout << "|  O  |\n";
    cout << "|     |\n";
    cout << "Selecteaza dificultatea: (dificultatea este doar un modificator "
            "de viteza)\n1.Incepator\n2.Usor\n3.Mediu\n4.Greu\n5.Inuman\nApasa "
            "h pentru help menu";

    keyState.update();
    if (keyState.wasJustPressed(VK_ESCAPE))
      exit(0);
    else if (keyState.wasJustPressed('H')) {
      Sleep(1000);
      cout << "\033[2J\033[H" << flush;
      help_menu();
      while (1) {
        keyState.update();
        if (keyState.wasJustPressed(VK_SPACE))
          break;
        Sleep(50);
      }
    }
    if (select_diff())
      break;
    Sleep(400);
    cout << "\033[2J\033[H" << flush;
    cout << "   P I N G  P O N G\n";
    cout << "|     |\n";
    cout << "|    O|\n";
    cout << "|     |\n";
    cout << "Selecteaza dificultatea: (dificultatea este doar un modificator "
            "de viteza)\n1.Incepator\n2.Usor\n3.Mediu\n4.Greu\n5.Inuman\nApasa "
            "h pentru help menu";

    keyState.update();
    if (keyState.wasJustPressed(VK_ESCAPE))
      exit(0);
    else if (keyState.wasJustPressed('H')) {
      Sleep(1000);
      cout << "\033[2J\033[H" << flush;
      help_menu();
      while (1) {
        keyState.update();
        if (keyState.wasJustPressed(VK_SPACE))
          break;
        Sleep(50);
      }
    }
    if (select_diff())
      break;
    Sleep(400);
    cout << "\033[2J\033[H" << flush;
    cout << "   P I N G  P O N G\n";
    cout << "|     |\n";
    cout << "|  O  |\n";
    cout << "|     |\n";
    cout << "Selecteaza dificultatea: (dificultatea este doar un modificator "
            "de viteza)\n1.Incepator\n2.Usor\n3.Mediu\n4.Greu\n5.Inuman\nApasa "
            "h pentru help menu";

    keyState.update();
    if (keyState.wasJustPressed(VK_ESCAPE))
      exit(0);
    else if (keyState.wasJustPressed('H')) {
      Sleep(1000);
      cout << "\033[2J\033[H" << flush;
      help_menu();
      while (1) {
        keyState.update();
        if (keyState.wasJustPressed(VK_SPACE))
          break;
        Sleep(50);
      }
    }
    if (select_diff())
      break;
    Sleep(400);
    cout << "\033[2J\033[H" << flush;
  }
  cout << "\033[2J\033[H" << flush;
}

void setup() {
  load();
  atins = 0;
  x = ' ';
  i = 10;
  j = 20;
  ps[1] = 8;
  ps[2] = 12;
  pd[1] = 8;
  pd[2] = 12;
  p = -1;
  r = 0;
  scor_sp = 0;
  skip = 0;
  int ii, jj;
  for (ii = 1; ii < 8; ii++)
    a[ii][1] = a[ii][n] = ' ';
  for (ii = 13; ii < m; ii++)
    a[ii][1] = a[ii][n] = ' ';
  for (ii = 1; ii <= n; ii++)
    a[0][ii] = '_', a[m][ii] = '_';
  for (ii = 8; ii <= 12; ii++)
    a[ii][1] = a[ii][n] = '|';
  for (ii = 1; ii < m; ii++)
    for (jj = 2; jj < n; jj++)
      a[ii][jj] = ' ';
  a[10][20] = 'O';
}

void afisare() {
  cout << "\033[2J\033[H" << flush; // Clear screen and move to top
  int ii, jj;
  for (ii = 0; ii <= 20; ii++) {
    for (jj = 1; jj <= n; jj++)
      cout << a[ii][jj];
    cout << "\n";
  }
  if (mod)
    cout << "Jucator1  " << scor[0] << "             Jucator2  " << scor[1];
  else
    cout << "Scor: " << scor_sp << "             HighScore:  " << highScore;
  cout << flush;
}

void save() {
  fstream f("save.txt", ios::in | ios::out | ios::trunc);
  f << highScore;
  f.close();
}

void mode_select() {
  cout << "\033[2J\033[H" << flush;
  cout << "Selecteaza modul(1/2):\n1 - singleplayer\n2 - multiplayer\n";
  cout << "Modul singleplayer a fost facut teoretic imposibil de batut, \nasa "
          "ca scorul creste de fiecare daca cand lovesti mingea.";
  cout << "\n\nApasa butonul '-' pentru a sterge highScore-ul (singleplayer)";
  cout << "\nHighScore curent: " << highScore;
  cout << "\n\nTip: Poti apasa ESCAPE oricand pentru a te intoarce la meniul "
          "principal/inchide jocul";
  cout << flush;
}

// ===================== NEW: helper to draw paddles+ball into a[][]
// =====================
void rebuild_board_from_state() {
  // clear inner area
  for (int ii = 1; ii < m; ii++)
    for (int jj = 2; jj < n; jj++)
      a[ii][jj] = ' ';

  // clear paddle columns
  for (int ii = 1; ii < m; ii++) {
    a[ii][1] = ' ';
    a[ii][n] = ' ';
  }

  // draw paddles
  for (int ii = ps[1]; ii <= ps[2]; ii++)
    a[ii][1] = '|';
  for (int ii = pd[1]; ii <= pd[2]; ii++)
    a[ii][n] = '|';

  // draw ball
  if (i >= 1 && i <= m - 1 && j >= 2 && j <= n - 1)
    a[i][j] = 'O';
}

// ===================== NEW: network init/teardown =====================
bool net_init_common() {
  gSock = socket(AF_INET, SOCK_DGRAM, 0);
  if (gSock < 0)
    return false;

  // non-blocking
  int flags = fcntl(gSock, F_GETFL, 0);
  fcntl(gSock, F_SETFL, flags | O_NONBLOCK);
  return true;
}

void net_close() {
  if (gSock >= 0) {
    close(gSock);
    gSock = -1;
  }
}

// ===================== NEW: online setup (host/client) =====================
bool online_setup_host() {
  if (!net_init_common())
    return false;
  gIsHost = true;

  sockaddr_in bindAddr{};
  bindAddr.sin_family = AF_INET;
  bindAddr.sin_port = htons(7777);
  bindAddr.sin_addr.s_addr = INADDR_ANY;

  if (bind(gSock, (sockaddr *)&bindAddr, sizeof(bindAddr)) != 0)
    return false;

  cout << "\033[2J\033[H" << flush;
  cout << "ONLINE HOST\n";
  cout << "Waiting for client... (client must send join)\n";
  cout << flush;

  // wait for join packet (blocking-ish loop, but without freezing gameplay)
  JoinPacket jp{};
  while (true) {
    ssize_t ret = recvfrom(gSock, (char *)&jp, sizeof(jp), 0,
                           (sockaddr *)&gPeerAddr, &gPeerAddrLen);
    if (ret == sizeof(jp) && jp.magic == 0x474E4F50 /*'PONG'*/ &&
        jp.version == 1)
      break;

    keyState.update();
    if (keyState.wasJustPressed(VK_ESCAPE))
      return false;
    Sleep(10);
  }

  // send difficulty config to client (host chosen)
  ConfigPacket cfg{dificultate};
  sendto(gSock, (char *)&cfg, sizeof(cfg), 0, (sockaddr *)&gPeerAddr,
         gPeerAddrLen);

  return true;
}

bool online_setup_client() {
  if (!net_init_common())
    return false;
  gIsHost = false;

  cout << "\033[2J\033[H" << flush;
  cout << "ONLINE CLIENT\n";
  cout << "Enter host IP (LAN): ";
  cout << flush;

  // Temporarily restore normal terminal mode for input
  disableRawMode();
  string ip;
  cin >> ip;
  enableRawMode();

  gPeerAddr = {};
  gPeerAddr.sin_family = AF_INET;
  gPeerAddr.sin_port = htons(7777);
  inet_pton(AF_INET, ip.c_str(), &gPeerAddr.sin_addr);

  // send join
  JoinPacket jp{0x474E4F50 /*'PONG'*/, 1};
  sendto(gSock, (char *)&jp, sizeof(jp), 0, (sockaddr *)&gPeerAddr,
         gPeerAddrLen);

  // wait for difficulty config
  ConfigPacket cfg{};
  while (true) {
    ssize_t ret =
        recvfrom(gSock, (char *)&cfg, sizeof(cfg), 0, nullptr, nullptr);
    if (ret == sizeof(cfg))
      break;

    keyState.update();
    if (keyState.wasJustPressed(VK_ESCAPE))
      return false;
    Sleep(10);
  }
  dificultate = cfg.dificultate;
  return true;
}

// ===================== NEW: online multiplayer loop =====================
void online_multiplayer_loop() {
  mod = 1;
  setup();

  while (1) {
    keyState.update();
    if (keyState.isPressed(VK_ESCAPE)) {
      scor[0] = scor[1] = 0;
      cout << "\033[2J\033[H" << flush;
      break;
    }

    if (gIsHost) {
      // ================= HOST: left paddle local input =================
      if (keyState.isPressed('W') && ps[1] > 1)
        ps[1]--, ps[2]--;
      else if (keyState.isPressed('S') && ps[2] < m - 1)
        ps[1]++, ps[2]++;

      // ================= HOST: receive client input for right paddle
      InputPacket ip{};
      ssize_t ret =
          recvfrom(gSock, (char *)&ip, sizeof(ip), 0, nullptr, nullptr);
      if (ret == sizeof(ip)) {
        if (ip.move == -1 && pd[1] > 1)
          pd[1]--, pd[2]--;
        else if (ip.move == 1 && pd[2] < m - 1)
          pd[1]++, pd[2]++;
      }

      // ================= HOST: ball + score logic =================
      if ((j == 2 || j == n - 1) && !atins)
        r = -1, atins = 1;

      rebuild_board_from_state();
      i += r;
      j += p;

      if (r == 1 && i + r >= m)
        r = -r;
      else if (r == -1 && i + r < 1)
        r = -r;

      // paddle collision
      if ((j == 2 && i >= ps[1] && i <= ps[2]) ||
          (j == n - 1 && i >= pd[1] && i <= pd[2])) {
        p = -p;
      }

      // scoring when ball passes edges
      if (j <= 1) {
        cout << "\n\nJucator2 a primit un punct";
        cout << flush;
        scor[1]++;
        this_thread::sleep_for(chrono::seconds(1));
        x = getch();
        setup();
        x = ' ';
      } else if (j >= n) {
        cout << "\n\nJucator1 a primit un punct";
        cout << flush;
        scor[0]++;
        this_thread::sleep_for(chrono::seconds(1));
        x = getch();
        setup();
        x = ' ';
      }

      rebuild_board_from_state();

      // send state to client
      StatePacket st{i, j, p, r, ps[1], ps[2], pd[1], pd[2], scor[0], scor[1]};
      sendto(gSock, (char *)&st, sizeof(st), 0, (sockaddr *)&gPeerAddr,
             gPeerAddrLen);

      afisare();
    } else {
      // ================= CLIENT: send input only =================
      InputPacket ip{};
      ip.move = 0;
      if (keyState.isPressed(VK_UP))
        ip.move = -1;
      else if (keyState.isPressed(VK_DOWN))
        ip.move = 1;
      sendto(gSock, (char *)&ip, sizeof(ip), 0, (sockaddr *)&gPeerAddr,
             gPeerAddrLen);

      // receive state from host
      StatePacket st{};
      ssize_t ret =
          recvfrom(gSock, (char *)&st, sizeof(st), 0, nullptr, nullptr);
      if (ret == sizeof(st)) {
        i = st.i;
        j = st.j;
        p = st.p;
        r = st.r;
        ps[1] = st.ps1;
        ps[2] = st.ps2;
        pd[1] = st.pd1;
        pd[2] = st.pd2;
        scor[0] = st.scor0;
        scor[1] = st.scor1;

        rebuild_board_from_state();
      }

      afisare();
    }

    this_thread::sleep_for(chrono::milliseconds(dificultate));
  }
}

// ===================== NEW: multiplayer submenu =====================
char multiplayer_submenu() {
  cout << "\033[2J\033[H" << flush;
  cout << "Multiplayer:\n1 - Local (same PC)\n2 - Online (P2P LAN)\nESC - "
          "back\n";
  cout << flush;
  while (true) {
    keyState.update();
    if (keyState.wasJustPressed('1'))
      return '1';
    if (keyState.wasJustPressed('2'))
      return '2';
    if (keyState.wasJustPressed(VK_ESCAPE))
      return 0;
    Sleep(50);
  }
}

int main() {
  enableRawMode();
  mt19937 rng(random_device{}());
  uniform_int_distribution<int> dist(1, 100);
  ShowConsoleCursor(false);

  while (1) {
    setup();
    MainMenu();
    cout << "\033[2J\033[H" << flush;
    x = 0;
    Sleep(1000);
    mode_select();

    while (x != '1' && x != '2') {
      keyState.update();
      if (keyState.wasJustPressed('1'))
        x = '1';
      if (keyState.wasJustPressed('2'))
        x = '2';
      if (keyState.wasJustPressed(VK_ESCAPE)) {
        skip = 1;
        break;
      } else if (keyState.wasJustPressed('-')) {
        Sleep(500);
        cout << "\nEsti sigur? Apasa '-' din nou pentru a confirma sau apasa "
                "SPACE buton pentru a reveni.";
        cout << flush;
        while (1) {
          keyState.update();
          if (keyState.wasJustPressed('-')) {
            highScore = 0;
            save();
            mode_select();
            Sleep(1000);
            break;
          } else if (keyState.wasJustPressed(VK_SPACE)) {
            mode_select();
            break;
          }
          Sleep(50);
        }
      }
      Sleep(50);
    }

    if (x == '1' && !skip) {
      // ===================== SINGLEPLAYER =====================
      while (1) {
        afisare();

        keyState.update();
        if (keyState.wasJustPressed(VK_ESCAPE)) {
          scor[0] = scor[1] = 0;
          cout << "\033[2J\033[H" << flush;
          break;
        }

        if (keyState.isPressed('W') && ps[1] > 1)
          a[ps[1] - 1][1] = '|', a[ps[2]][1] = ' ', ps[1]--, ps[2]--, Sleep(10);
        else if (keyState.isPressed('S') && ps[2] < m - 1)
          a[ps[1]][1] = ' ', ps[1]++, a[ps[2] + 1][1] = '|', ps[2]++, Sleep(10);

        // auto
        random_val = dist(rng);
        if (random_val > dificultate / 10) {
          if (dificultate != 1 || scor_sp < 100) {
            if (i < pd[1] + 2 && pd[1] > 1)
              a[pd[1] - 1][n] = '|', a[pd[2]][n] = ' ', pd[1]--, pd[2]--;
            else if (i > pd[2] - 2 && pd[2] < m - 1)
              a[pd[1]][n] = ' ', pd[1]++, a[pd[2] + 1][n] = '|', pd[2]++;
          }
        }

        if ((j == 2 || j == n - 1) && !atins)
          r = -1, atins = 1;
        swap(a[i][j], a[i + r][j + p]);
        i += r;
        j += p;
        if (r == 1 && i + r >= m)
          r = -r;
        else if (r == -1 && i + r < 1)
          r = -r;
        if (j == 2 && a[i][j + p] == '|') {
          p = -p;
          scor_sp++;
          if (scor_sp > highScore)
            highScore = scor_sp;
          save();
        }
        if (j == n - 1 && a[i][j + p] == '|')
          p = -p;
        if (j == 1) {
          cout << "\n\nCalculatorul a primit un punct";
          cout << flush;
          scor_sp = 0;
          this_thread::sleep_for(chrono::seconds(1));
          x = getch();
          setup();
          x = ' ';
        } else if (j == n) {
          cout << "\n\nBravo baiete!!";
          cout << flush;
          this_thread::sleep_for(chrono::seconds(1));
          x = getch();
          setup();
          x = ' ';
        }
        this_thread::sleep_for(chrono::milliseconds(dificultate));
      }
    } else if (x == '2' && !skip) {
      // ===================== MULTIPLAYER CHOICE =====================
      char mp = multiplayer_submenu();
      if (!mp)
        continue;

      if (mp == '1') {
        // ===================== LOCAL MULTIPLAYER =====================
        mod = 1;
        while (1) {
          afisare();

          keyState.update();
          if (keyState.isPressed(VK_ESCAPE)) {
            scor[0] = scor[1] = 0;
            cout << "\033[2J\033[H" << flush;
            break;
          }

          if (keyState.isPressed('W') && ps[1] > 1)
            a[ps[1] - 1][1] = '|', a[ps[2]][1] = ' ', ps[1]--, ps[2]--;
          else if (keyState.isPressed('S') && ps[2] < m - 1)
            a[ps[1]][1] = ' ', ps[1]++, a[ps[2] + 1][1] = '|', ps[2]++;

          if (keyState.isPressed(VK_UP) && pd[1] > 1)
            a[pd[1] - 1][n] = '|', a[pd[2]][n] = ' ', pd[1]--, pd[2]--;
          else if (keyState.isPressed(VK_DOWN) && pd[2] < m - 1)
            a[pd[1]][n] = ' ', pd[1]++, a[pd[2] + 1][n] = '|', pd[2]++;

          if ((j == 2 || j == n - 1) && !atins)
            r = -1, atins = 1;
          swap(a[i][j], a[i + r][j + p]);
          i += r;
          j += p;
          if (r == 1 && i + r >= m)
            r = -r;
          else if (r == -1 && i + r < 1)
            r = -r;
          if ((j == 2 && a[i][j + p] == '|') ||
              (j == n - 1 && a[i][j + p] == '|'))
            p = -p;
          if (j == 1) {
            cout << "\n\nJucator2 a primit un punct";
            cout << flush;
            scor[1]++;
            this_thread::sleep_for(chrono::seconds(1));
            x = getch();
            setup();
            x = ' ';
          } else if (j == n) {
            cout << "\n\nJucator1 a primit un punct";
            cout << flush;
            scor[0]++;
            this_thread::sleep_for(chrono::seconds(1));
            x = getch();
            setup();
            x = ' ';
          }
          this_thread::sleep_for(chrono::milliseconds(dificultate));
        }
      } else if (mp == '2') {
        // ===================== ONLINE MULTIPLAYER =====================
        cout << "\033[2J\033[H" << flush;
        cout << "Online P2P:\n1 - Host\n2 - Client\nESC - back\n";
        cout << flush;
        char role = 0;
        while (role != '1' && role != '2') {
          keyState.update();
          if (keyState.wasJustPressed('1'))
            role = '1';
          if (keyState.wasJustPressed('2'))
            role = '2';
          if (keyState.wasJustPressed(VK_ESCAPE)) {
            role = 0;
            break;
          }
          Sleep(50);
        }
        if (!role)
          continue;

        bool ok = false;
        if (role == '1')
          ok = online_setup_host();
        else
          ok = online_setup_client();

        if (!ok) {
          net_close();
          continue;
        }

        online_multiplayer_loop();
        net_close();
      }
    }
    save();
  }
  return 0;
}
