/*
ID: faorien2
PROG: lamps
LANG: C++
 */
#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>
#include <sstream>
using namespace std;

bool fits(int comb, int c) {
  int count = 0;

  for (int i = 0; i < 4; i++) {
    if (comb & (1<<i))
      count++;
  }

  switch (c) {
    case 0:
      if (count != 0)
        return false;
      break;
    case 1:
      if (count != 1)
        return false;
      break;
    case 2:
      if (count != 0 && count != 2)
        return false;
      break;
    default:
      if (c % 2 == 0) {
        if (count != 0 && count != 2 && count != 4)
          return false;
      } else {
        if (count != 1 && count != 3)
          return false;
      }
      break;
  }

  return true;
}

void push_button(int lamps[101], int button) {
  switch (button) {
    case 1:
      for (int i = 0; i < 101; i++)
        lamps[i] = (lamps[i] == 1 ? 0 : 1);
      break;
    case 2:
      for (int i = 1; i < 101; i += 2)
        lamps[i] = (lamps[i] == 1 ? 0 : 1);
      break;
    case 3:
      for (int i = 0; i < 101; i += 2)
        lamps[i] = (lamps[i] == 1 ? 0 : 1);
      break;
    case 4:
      for (int i = 1; i < 101; i += 3)
        lamps[i] = (lamps[i] == 1 ? 0 : 1);
      break;
  }
}

bool ok(int lamps[101], int on[101], int off[101]) {
  for (int i = 0; i < 101; i++) {
    if (on[i] != -1 && lamps[i] != on[i]) {
      return false;
    }

    if (off[i] != -1 && lamps[i] != off[i]) {
      return false;
    }
  }

  return true;
}

int main() {
  int n, c, tmp;
  int lamps[101];
  int on[101], off[101];
  set<string> result;

  ofstream fout("lamps.out");
  ifstream fin("lamps.in");

  fin >> n >> c;

  fill (on, on + 101, -1);
  fill (off, off + 101, -1);

  while (fin >> tmp) {
    if (tmp == -1)
      break;

    on[tmp] = 1;
  }

  while (fin >> tmp) {
    if (tmp == -1)
      break;

    off[tmp] = 0;
  }

  for (int i = 0; i < 16; i++) {
    if (!fits(i, c))
      continue;

    fill (lamps, lamps + n + 1, 1);

    for (int j = 0; j < 4; j++) {
      if (i & (1<<j))
        push_button(lamps, j + 1);
    }

    if (ok(lamps, on, off)) {
      stringstream ss;
      for (int j = 1; j <= n; j++)
        ss << lamps[j];

      result.insert(ss.str());
    }
  }

  if (result.size() == 0) {
    fout << "IMPOSSIBLE" << endl;
  } else {
    for (typeof(result.begin()) it = result.begin(); it != result.end(); it++) {
      fout << *it << endl;
    }
  }

  return 0;
}
