/*
ID: faorien2
PROG: beads
LANG: C++
 */
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
  char tmp;
  int counter;
  int N, best;
  string beads;
  ofstream fout("beads.out");
  ifstream fin("beads.in");

  fin >> N >> beads;

  while (N--) {
    tmp = 'w';
    bool first = true;
    counter = 0;
    rotate(beads.begin(), beads.begin() + 1, beads.end());
    for (int i = 0, sz = beads.size(); i < sz; i++) {
      if (beads[i] == 'w') {
        counter++;
        continue;
      }

      if (tmp == 'w') {
        tmp = beads[i];
        counter++;
        continue;
      }

      if (tmp == beads[i]) {
        counter++;
        continue;
      }

      if (first) {
        first = false;
        tmp = beads[i];
        counter++;
        continue;
      }

      break;
    }

    if (counter > best)
      best = counter;
  }

  fout << best << endl;

  return 0;
}
