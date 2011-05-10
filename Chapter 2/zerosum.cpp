/*
ID: faorien2
PROG: zerosum
LANG: C++
 */
#include <iostream>
#include <fstream>
using namespace std;

int seq[17];
ofstream fout("zerosum.out");
ifstream fin("zerosum.in");

bool is_zerosum(int n) {
 int action = -1; 
 int a = 0, b = seq[0];

  for (int i = 1; i < 2*n-1; i++) {
    if (i % 2 == 0) {
      b = seq[i];
    } else {
      if (seq[i] == 0) {
        b = b * 10 + seq[i+1];
        i++;
      } else {
        if (action == -1) {
          a = b;
        } else {
          if (action == 1) {
            a += b;
          } else { // action == 2
            a -= b;
          }
        }

        action = seq[i];
        b = 0;
      }
    }
  }

  if (action == -1)
    return false;

  if (action == 1) {
    a += b;
  } else { // action == 2
    a -= b;
  }

  return a == 0;
}

void solve(int n, int depth) {
  if (depth == n - 1) {
    if (is_zerosum(n)) {
      for (int i = 0; i < 2*n - 1; i++) {
        if (i % 2 == 0)
          fout << seq[i];
        else
          switch (seq[i]) {
            case 0:
              fout << " ";
              break;
            case 1:
              fout << "+";
              break;
            case 2:
              fout << "-";
              break;
          }
      }
      fout << endl;
    }

    return;
  }

  for (int i = 0; i < 3; i++) {
    seq[depth*2+1] = i; // 0 - space, 1 - plus, 2 - minus
    solve(n, depth+1);
  }
}

int main() {
  int n;

  fin >> n;

  for (int i = 0; i < 9; i++) {
    seq[i * 2] = i + 1;
  }

  solve(n, 0);

  return 0;
}
