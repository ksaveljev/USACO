/*
ID: faorien2
PROG: checker
LANG: C++
 */
#include <iostream>
#include <fstream>
using namespace std;

int n;
int counter = 0;
int printed = 0;
int field[15][15];
int checkers[15];

ofstream fout("checker.out");
ifstream fin("checker.in");

int col[15];
int updiag[30];
int downdiag[30];

void solve(int depth, int limit) {
  if (depth == n) {
    if (printed < 3) {
      for (int i = 0; i < n; i++) {
        if (i > 0)
          fout << " ";
        fout << checkers[i] + 1;
      }
      fout << endl;
      printed++;
    }

    counter++;

    if (n > 6 && checkers[0] < n/2)
      counter++;

    return;
  }

  for (int i = 0; i < limit; i++) {
    //if (good_spot(depth, i)) {
    if (!col[i] && !updiag[depth+i] && !downdiag[depth-i+15]) {
      col[i]++;
      updiag[depth+i]++;
      downdiag[depth-i+15]++;

      field[depth][i] = 1;
      checkers[depth] = i;
      solve(depth + 1, n);
      field[depth][i] = 0;

      col[i]--;
      updiag[depth+i]--;
      downdiag[depth-i+15]--;
    }
  }
}

int main() {
  fin >> n;

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      field[i][j] = 0;

  for (int i = 0; i < 15; i++)
    col[i] = 0;

  for (int i = 0; i < 30; i++) {
    updiag[i] = 0;
    downdiag[i] = 0;
  }

  solve(0, (n == 6 ? 6 : (n+1)/2));

  fout << counter << endl;

  return 0;
}
