/*
ID: faorien2
PROG: holstein
LANG: C++
 */
#include <iostream>
#include <fstream>
using namespace std;

struct result {
  int feeds;
  bool taken[20];
};

int v, g;
int counter;
int requirements[30];
int feeds[20][30];
bool taken[20];
int tmp[30];
result best;

void solve(int depth) {
  if (depth == g) {
    counter = 0;

    for (int i = 0; i < 30; i++)
      tmp[i] = 0;

    for (int i = 0; i < g; i++) {
      if (taken[i] == true) {
        counter++;
        for (int j = 0; j < v; j++)
          tmp[j] += feeds[i][j];
      }
    }

    bool ok = true;
    for (int i = 0; i < v; i++) {
      if (tmp[i] < requirements[i]) {
        ok = false;
        break;
      }
    }

    if (ok) {
      if (counter > best.feeds)
        return;
      else if (counter == best.feeds) {
        ok = true;
        for (int i = 0; i < g; i++) {
          if (taken[i] == best.taken[i])
            continue;
          if (taken[i] == false && best.taken[i] == true) {
            ok = false;
            break;
          }
          if (taken[i] == true && best.taken[i] == false) {
            break;
          }
        }

        if (ok) {
          for (int i = 0; i < g; i++)
            best.taken[i] = taken[i];
        }
      } else {
        best.feeds = counter;
        for (int i = 0; i < g; i++)
          best.taken[i] = taken[i];
      }
    }

    return;
  }

  taken[depth] = true;
  solve(depth + 1);
  taken[depth] = false;
  solve(depth + 1);
}

int main() {
  ofstream fout("holstein.out");
  ifstream fin("holstein.in");

  best.feeds = 1000000;
  for (int i = 0; i < 20; i++)
    best.taken[i] = false;

  for (int i = 0; i < 20; i++)
    taken[i] = false;

  fin >> v;

  for (int i = 0; i < v; i++)
    fin >> requirements[i];

  fin >> g;

  for (int i = 0; i < g; i++)
    for (int j = 0; j < v; j++)
      fin >> feeds[i][j];

  solve(0);

  fout << best.feeds;

  for (int i = 0; i < g; i++) {
    if (best.taken[i]) {
      fout << " " << i + 1;
    }
  }
  fout << endl;

  return 0;
}
