/*
ID: faorien2
PROG: barn1
LANG: C++
 */
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct gap {
  int start;
  int end;
};

int main() {
  int tmp;
  int count;
  bool counting;
  gap current, best;
  int blocked;
  int m, s, c;
  int start = 100000, end = 1;
  bool stalls[210];

  memset(stalls, false, sizeof stalls);

  ofstream fout("barn1.out");
  ifstream fin("barn1.in");

  fin >> m >> s >> c;

  for (int i = 0; i < c; i++) {
    fin >> tmp;
    stalls[tmp] = true;

    if (tmp < start)
      start = tmp;

    if (tmp > end)
      end = tmp;
  }

  if (m >= c) {
    blocked = c;
    m = 0;
  } else {
    blocked = end - start + 1;
    m--;
  }

  while (m > 0) {
    counting = false;
    best.start = 0;
    best.end = 0;
    current.start = 0;
    current.end = 0;

    for (int i = start + 1; i <= end; i++) {
      if (stalls[i] == false) {
        if (counting) {
          current.end = i;
        } else {
          counting = true;
          current.start = i;
          current.end = i;
        }
      } else {
        if (counting) {
          counting = false;
          if (current.end - current.start > best.end - best.start) {
            best.start = current.start;
            best.end = current.end;
          }
        }
      }
    }

    for (int i = best.start; i <= best.end; i++)
      stalls[i] = true;

    blocked = blocked - (best.end - best.start + 1);
    m--;
  }

  fout << blocked << endl;

  return 0;
}
