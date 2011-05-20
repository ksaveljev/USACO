/*
ID: faorien2
PROG: concom
LANG: C++
 */
#include <iostream>
#include <fstream>
using namespace std;

int owns[101][101];
bool controls[101][101];

void add_new_controller(int a, int b) {
  if (controls[a][b])
    return;

  controls[a][b] = true;

  // everything owned by b is now own by a
  for (int i = 1; i < 101; i++) {
    owns[a][i] += owns[b][i];
    if (owns[a][i] > 100)
      owns[a][i] = 100;
  }

  // everything that controls a also owns b now
  for (int i = 1; i < 101; i++) {
    if (controls[i][a]) {
      add_new_controller(i, b);
    }
  }

  // check if changes made have add more companies to the ownership of a
  for (int i = 1; i < 101; i++) {
    if (owns[a][i] > 50)
      add_new_controller(a, i);
  }
}

void add_more_control(int a, int b, int percent) {
  for (int i = 1; i < 101; i++) {
    if (controls[i][a]) {
      owns[i][b] += percent;
      if (owns[i][b] > 100)
        owns[i][b] = 100;
    }
  }

  for (int i = 1; i < 101; i++) {
    if (owns[i][b] > 50)
      add_new_controller(i, b);
  }
}

int main() {
  int n;
  int a, b, p;

  for (int i = 1; i < 101; i++) {
    for (int j = 1; j < 101; j++) {
      owns[i][j] = 0;
      controls[i][j] = false;
    }

    owns[i][i] = 100;
    controls[i][i] = true;
  }
  
  ofstream fout("concom.out");
  ifstream fin("concom.in");

  fin >> n;

  while (n--) {
    fin >> a >> b >> p;
    add_more_control(a,b,p);
  }

  for (int i = 1; i < 101; i++) {
    for (int j = 1; j < 101; j++) {
      if (i != j && controls[i][j])
        fout << i << " " << j << endl;
    }
  }

  return 0;
}
