/*
ID: faorien2
PROG: castle
LANG: C++
 */
#include <iostream>
#include <fstream>
#include <queue>
#include <map>
using namespace std;

int m, n;

struct room {
  bool west;
  bool north;
  bool east;
  bool south;
  int v;
  room() : v(0), west(true), north(true), east(true), south(true) {}
};

struct result {
  int a;
  int b;
  char way;
  int size;
  result() : size(0) {}
};

room castle[51][51];

int fill(int a, int b, int num) {
  int count = 0;
  pair<int,int> tmp;
  queue< pair<int,int> > q;

  tmp.first = a;
  tmp.second = b;
  castle[a][b].v = num;
  count++;

  q.push(tmp);

  while (!q.empty()) {
    tmp = q.front();
    q.pop();

    if (castle[tmp.first][tmp.second].north) {
      if (castle[tmp.first-1][tmp.second].v == 0) {
        castle[tmp.first-1][tmp.second].v = num;
        count++;
        q.push(make_pair(tmp.first-1, tmp.second));
      }
    }

    if (castle[tmp.first][tmp.second].south) {
      if (castle[tmp.first+1][tmp.second].v == 0) {
        castle[tmp.first+1][tmp.second].v = num;
        count++;
        q.push(make_pair(tmp.first+1, tmp.second));
      }
    }

    if (castle[tmp.first][tmp.second].east) {
      if (castle[tmp.first][tmp.second+1].v == 0) {
        castle[tmp.first][tmp.second+1].v = num;
        count++;
        q.push(make_pair(tmp.first, tmp.second+1));
      }
    }

    if (castle[tmp.first][tmp.second].west) {
      if (castle[tmp.first][tmp.second-1].v == 0) {
        castle[tmp.first][tmp.second-1].v = num;
        count++;
        q.push(make_pair(tmp.first, tmp.second-1));
      }
    }
  }

  return count;
}

int main() {
  int tmp;
  int num = 1;
  int largest = 0;
  map<int,int> rooms;
  result best;

  ofstream fout("castle.out");
  ifstream fin("castle.in");

  fin >> m >> n;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      fin >> tmp;

      if (tmp > 7) {
        castle[i][j].south = false;
        tmp -= 8;
      }

      if (tmp > 3) {
        castle[i][j].east = false;
        tmp -= 4;
      }

      if (tmp > 1) {
        castle[i][j].north = false;
        tmp -= 2;
      }

      if (tmp > 0) {
        castle[i][j].west = false;
        tmp -= 1;
      }
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (castle[i][j].v == 0) {
        rooms[num] = fill(i, j, num);
        if (rooms[num] > largest)
          largest = rooms[num];
        num++;
      }
    }
  }

  for (int j = 0; j < m; j++) {
    for (int i = n - 1; i >= 0; i--) {
      if (i > 0) { // check NORTH
        if (castle[i][j].v != castle[i-1][j].v) {
          if (rooms[castle[i][j].v] + rooms[castle[i-1][j].v] > best.size) {
            best.size = rooms[castle[i][j].v] + rooms[castle[i-1][j].v];
            best.a = i;
            best.b = j;
            best.way = 'N';
          }
        }
      }

      if (j < m - 1) { // check EAST
        if (castle[i][j].v != castle[i][j+1].v) {
          if (rooms[castle[i][j].v] + rooms[castle[i][j+1].v] > best.size) {
            best.size = rooms[castle[i][j].v] + rooms[castle[i][j+1].v];
            best.a = i;
            best.b = j;
            best.way = 'E';
          }
        }
      }
    }
  }


  fout << num - 1 << endl;
  fout << largest << endl;
  fout << best.size << endl;
  fout << best.a + 1 << " " << best.b + 1 << " " << best.way << endl;

  return 0;
}
