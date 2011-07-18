/*
ID: faorien2
PROG: msquare
LANG: C++
 */
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <map>
using namespace std;

int target[8];

struct result {
  int moves;
  int current[8];
  string transformations;
};


result solve() {
  result tmp, next;
  bool found;
  queue<result> q;
  map<int,bool> visited;

  tmp.moves = 0;
  for (int i = 0; i < 4; i++)
    tmp.current[i] = i + 1;
  tmp.current[4] = 8;
  tmp.current[5] = 7;
  tmp.current[6] = 6;
  tmp.current[7] = 5;
  tmp.transformations = "";
  q.push(tmp);

  visited[12348765] = true;

  while (!q.empty()) {
    tmp = q.front();
    q.pop();

    found = true;
    for (int i = 0; i < 8; i++) {
      if (tmp.current[i] != target[i]) {
        found = false;
        break;
      }
    }

    if (found) {
      return tmp;
    }

    next.moves = tmp.moves + 1;

    // A: exchange the top and bottom row
    int r = 0;
    for (int i = 0; i < 8; i++) {
      next.current[i] = tmp.current[(i + 4) % 8];
      r = r * 10 + next.current[i];
    }

    if (!visited[r]) {
      visited[r] = true;
      next.transformations = tmp.transformations + "A";
      q.push(next);
    }

    // B: single right circular shifting of the rectangle
    r = 0;
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 4; j++) {
        next.current[j + 4*i] = tmp.current[4*i + (3 + j) % 4];
      }
    }

    for (int i = 0; i < 8; i++) {
      r = r * 10 + next.current[i];
    }

    if (!visited[r]) {
      visited[r] = true;
      next.transformations = tmp.transformations + "B";
      q.push(next);
    }

    // C: single clockwise rotation of the middle four squares
    next.current[0] = tmp.current[0];
    next.current[3] = tmp.current[3];
    next.current[4] = tmp.current[4];
    next.current[7] = tmp.current[7];
    next.current[1] = tmp.current[5];
    next.current[2] = tmp.current[1];
    next.current[5] = tmp.current[6];
    next.current[6] = tmp.current[2];

    r = 0;
    for (int i = 0; i < 8; i++) {
      r = r * 10 + next.current[i];
    }

    if (!visited[r]) {
      visited[r] = true;
      next.transformations = tmp.transformations + "C";
      q.push(next);
    }
  }
}

int main() {
  ofstream fout("msquare.out");
  ifstream fin("msquare.in");

  for (int i = 0; i < 4; i++) {
    fin >> target[i];
  }

  for (int i = 0; i < 4; i++) {
    fin >> target[7-i];
  }

  result r = solve();

  fout << r.moves << endl;
  for (int i = 0, sz = r.transformations.size(); i < sz; i++) {
    if (i > 0 && i % 60 == 0) {
      fout << endl;
    }
    fout << r.transformations[i];
  }
  fout << endl;

  return 0;
}
