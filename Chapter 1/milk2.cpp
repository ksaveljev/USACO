/*
ID: faorien2
PROG: milk2
LANG: C++
 */
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main() {
  int N;
  int best_milking = 0, best_nomilking = 0;
  int current_milking = 0, current_nomilking = 0;
  int start, end;
  int highest = 0, lowest = 2000000000;
  char *timeline = new char[1000000];

  memset(timeline, '.', 1000000*sizeof(char));

  ofstream fout("milk2.out");
  ifstream fin("milk2.in");

  fin >> N;

  while (N--) {
    fin >> start >> end;
    if (start + 1 < lowest)
      lowest = start + 1;
    if (end > highest)
      highest = end;

    memset(timeline + start + 1, '*', (end - start) * sizeof(char));
  }

  bool milking = true;
  for (int i = lowest; i <= highest; i++) {
    if (timeline[i] == '*') {
      if (milking) {
        current_milking++;
      } else {
        milking = true;
        current_milking = 1;
        if (current_nomilking > best_nomilking)
          best_nomilking = current_nomilking;
      }
    } else {
      if (!milking) {
        current_nomilking++;
      } else {
        milking = false;
        current_nomilking = 1;
        if (current_milking > best_milking)
          best_milking = current_milking;
      }
    }
  }

  // always end with milking interval
  if (current_milking > best_milking)
    best_milking = current_milking;

  fout << best_milking << " " << best_nomilking << endl;

  return 0;
}
