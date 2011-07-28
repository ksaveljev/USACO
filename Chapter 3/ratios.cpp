/*
ID: faorien2
PROG: ratios
LANG: C++
*/
#include <iostream>
#include <fstream>
using namespace std;

int main() {
  int INF = 200000000;
  int goal[3];
  int input[3][3];
  int tmp[3], result[4];

  result[0] = result[1] = result[2] = INF;

  ofstream fout("ratios.out");
  ifstream fin("ratios.in");

  for (int i = 0; i < 3; i++) {
    fin >> goal[i];
  }

  if (goal[0] == 0 && goal[1] == 0 && goal[2] == 0) {
    fout << "0 0 0 0" << endl;
    return 0;
  }

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      fin >> input[i][j];
    }
  }

  for (int a = 0; a < 100; a++) {
    for (int b = 0; b < 100; b++) {
      for (int c = 0; c < 100; c++) {
        if (a==0 && b==0 && c==0) {
          continue;
        }
        tmp[0] = a * input[0][0] + b * input[1][0] + c * input[2][0];
        tmp[1] = a * input[0][1] + b * input[1][1] + c * input[2][1];
        tmp[2] = a * input[0][2] + b * input[1][2] + c * input[2][2];

        int r = -1;
        for (int i = 0; i < 3; i++) {
          if (goal[i] == 0) {
            continue;
          }

          if (tmp[i] % goal[i] == 0)
            r = tmp[i] / goal[i];
        }

        if (r == -1) {
          continue;
        }

        bool ok = true;
        for (int i = 0; i < 3; i++) {
          if (goal[i] * r != tmp[i]) {
            ok = false;
          }
        }

        if (!ok) {
          continue;
        }

        if (a + b + c < result[0] + result[1] + result[2]) {
          result[0] = a;
          result[1] = b;
          result[2] = c;
          result[3] = r;
        }
      }
    }
  }

  if (result[0] == INF) {
    fout << "NONE" << endl;
  } else {
    fout << result[0] << " " << result[1] << " " << result[2] << " " << result[3] << endl;
  }

  return 0;
}
