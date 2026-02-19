#include <iostream>

using namespace std;

int main() {
  int N;
  if (!(cin >> N))
    return 0;

  // A = index curent (i)
  // B = index urmator (i + 1)
  // C = variabila pentru valoarea V[i]
  // D = variabila pentru valoarea V[i+1]
  // E = counter pentru treceri (pentru a repeta de N ori)

  cout << "0. ASSIGN E Z" << endl; // E = 0 (counter treceri)

  // Inceput loop exterior (treceri prin vector)
  cout << "1. ASSIGN A Z" << endl; // A = 0 (resetam indexul la fiecare trecere)

  // Inceput loop interior (comparatii)
  cout << "2. ASSIGN B A" << endl; // B = A
  cout << "3. INC B" << endl;      // B = A + 1

  // Verificam daca B a ajuns la N (sfarsitul vectorului)
  cout << "4. IF_SAME_GOTO B N 12"
       << endl; // Daca B == N, am terminat o trecere, mergem la incrementare E

  // Incarcam valorile pentru comparatie
  cout << "5. ASSIGN C A" << endl; // C = A (index)
  cout << "6. PLOAD C" << endl;    // C = V[A]
  cout << "7. ASSIGN D B" << endl; // D = B (index)
  cout << "8. PLOAD D" << endl;    // D = V[B]

  // Comparatie: daca V[A] > V[B], facem swap
  cout << "9. IF_LESS_GOTO D C 15"
       << endl; // Daca V[B] < V[A], sari la swap (linia 15)

  // Daca nu am facut swap, mergem la urmatorul element
  cout << "10. INC A" << endl;              // A++
  cout << "11. IF_LESS_GOTO A N 2" << endl; // Daca A < N, repeta loop interior

  // Final de trecere
  cout << "12. INC E" << endl; // E++ (numaram trecerea)
  cout << "13. IF_LESS_GOTO E N 1"
       << endl;              // Daca E < N, reia de la inceput (linia 1)
  cout << "14. END" << endl; // Gata sortarea!

  // Subrutina de SWAP (apelata de la linia 9)
  cout << "15. PSWAP A B" << endl; // Schimba V[A] cu V[B]
  cout << "16. IF_SAME_GOTO Z Z 10"
       << endl; // Salt neconditionat inapoi la incrementare A (linia 10)

  return 0;
}
