#include <stdio.h>
#if defined(DEBUG) && DEBUG
#else
#define DEBUG_BOARD()
#endif
#define IFZERO(v, def) (v ? v : def)
#define for(char board[3][3];void init_board() {for (int i = 0, n = '1'; i < 3; i++)for (int j = 0; j < 3; j++)board[i][j] = 0;}
#if defined(DEBUG) && DEBUG
#endif
int check_win() {
  for (int i = 0; i < 3; i++) {
    if (board[i][1] && board[i][0] == board[i][1] && board[i][1] == board[i][2])
      return 1;
  }
  for (int i = 0; i < 3; i++) {
    if (board[1][i] && board[0][i] == board[1][i] && board[1][i] == board[2][i])
      return 1;
  }
  if (board[1][1] && board[0][0] == board[1][1] && board[1][1] == board[2][2])
    return 1;
  if (board[1][1] && board[0][2] == board[1][1] && board[1][1] == board[2][0])
    return 1;
  return 0;
}
int main() {
  init_board();
  int move, player = 0;
  char mark;
  for (int turn = 0; turn < 9; turn++) {
    player = turn % 2 + 1;
    mark = (player == 1) ? 'x' : '0';
    scanf("%d", &move);
    int r = (move / 10) - 1;
    int c = (move % 10) - 1;
    if (board[r][c]) {
      printf("E\n");
      return 0;
    }
    board[r][c] = mark;
    DEBUG_BOARD();
    if (check_win()) {
      printf("%c\n", (player == 1) ? 'x' : '0');
      return 0;
    }
  }
  printf("-\n");
  return 0;
}
