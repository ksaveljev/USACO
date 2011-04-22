/*
ID: faorien2
PROG: milk3
LANG: C++
 */
#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

int result[25];
int visited[25][25][25];

int A, B, C;

struct snapshot {
  int a, b, c;
};

void solve(int a, int b, int c) {
  int transfer;
  snapshot s;
  snapshot tmp;
  queue<snapshot> q;

  tmp.a = a;
  tmp.b = b;
  tmp.c = c;

  q.push(tmp);

  while (!q.empty()) {
    s = q.front();
    q.pop();

    if (s.a == 0) {
      result[s.c] = 1;
    }

    // A -> B
    tmp.a = s.a;
    tmp.b = s.b;
    tmp.c = s.c;

    transfer = min(tmp.a, B - tmp.b);

    tmp.a -= transfer;
    tmp.b += transfer;

    if (visited[tmp.a][tmp.b][tmp.c] == -1) {
      q.push(tmp);
      visited[tmp.a][tmp.b][tmp.c] = 1;
    }

    // A -> C
    tmp.a = s.a;
    tmp.b = s.b;
    tmp.c = s.c;

    transfer = min(tmp.a, C - tmp.c);

    tmp.a -= transfer;
    tmp.c += transfer;

    if (visited[tmp.a][tmp.b][tmp.c] == -1) {
      q.push(tmp);
      visited[tmp.a][tmp.b][tmp.c] = 1;
    }

    // B -> A
    tmp.a = s.a;
    tmp.b = s.b;
    tmp.c = s.c;

    transfer = min(tmp.b, A - tmp.a);

    tmp.b -= transfer;
    tmp.a += transfer;

    if (visited[tmp.a][tmp.b][tmp.c] == -1) {
      q.push(tmp);
      visited[tmp.a][tmp.b][tmp.c] = 1;
    }

    // B -> C
    tmp.a = s.a;
    tmp.b = s.b;
    tmp.c = s.c;

    transfer = min(tmp.b, C - tmp.c);

    tmp.b -= transfer;
    tmp.c += transfer;

    if (visited[tmp.a][tmp.b][tmp.c] == -1) {
      q.push(tmp);
      visited[tmp.a][tmp.b][tmp.c] = 1;
    }

    // C -> A
    tmp.a = s.a;
    tmp.b = s.b;
    tmp.c = s.c;

    transfer = min(tmp.c, A - tmp.a);

    tmp.c -= transfer;
    tmp.a += transfer;

    if (visited[tmp.a][tmp.b][tmp.c] == -1) {
      q.push(tmp);
      visited[tmp.a][tmp.b][tmp.c] = 1;
    }

    // C -> B
    tmp.a = s.a;
    tmp.b = s.b;
    tmp.c = s.c;

    transfer = min(tmp.c, B - tmp.b);

    tmp.c -= transfer;
    tmp.b += transfer;

    if (visited[tmp.a][tmp.b][tmp.c] == -1) {
      q.push(tmp);
      visited[tmp.a][tmp.b][tmp.c] = 1;
    }
  }
}

int main() {
  bool first = true;

  ofstream fout("milk3.out");
  ifstream fin("milk3.in");

  fin >> A >> B >> C;

  for (int i = 0; i < 25; i++)
    result[i] = -1;

  for (int i = 0; i < 25; i++)
    for (int j = 0; j < 25; j++)
      for (int k = 0; k < 25; k++)
        visited[i][j][k] = -1;

  solve(0, 0, C);

  for (int i = 0; i < 25; i++) {
    if (result[i] != -1) {
      if (!first)
        fout << " ";
      fout << i;
      first = false;
    }
  }
  fout << endl;

  return 0;
}
