/*
ID: faorien2
PROG: ttwo
LANG: C++
 */
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

char field[10][10];

enum dir { NORTH, SOUTH, WEST, EAST };

struct position {
  int r;
  int c;
  dir direction;
  position() : direction(NORTH) {}
};

void make_move(position &p) {
  switch (p.direction) {
    case NORTH:
      if (p.r > 0 && field[p.r-1][p.c] == '.') {
        p.r -= 1;
      } else {
        p.direction = EAST;
      }
      break;
    case SOUTH:
      if (p.r < 9 && field[p.r+1][p.c] == '.') {
        p.r += 1;
      } else {
        p.direction = WEST;
      }
      break;
    case WEST:
      if (p.c > 0 && field[p.r][p.c-1] == '.') {
        p.c -= 1;
      } else {
        p.direction = NORTH;
      }
      break;
    case EAST:
      if (p.c < 9 && field[p.r][p.c+1] == '.') {
        p.c += 1;
      } else {
        p.direction = SOUTH;
      }
      break;
  }
}

int main() {
  bool found;
  int result = 0;
  position cows, farmer;
  vector< pair<position,position> > states;

  ofstream fout("ttwo.out");
  ifstream fin("ttwo.in");

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      fin >> field[i][j];

      if (field[i][j] == 'C') {
        field[i][j] = '.';
        cows.r = i;
        cows.c = j;
      } else if (field[i][j] == 'F') {
        field[i][j] = '.';
        farmer.r = i;
        farmer.c = j;
      }
    }
  }

  states.push_back(make_pair(cows, farmer));

  while (true) {
    make_move(cows);
    make_move(farmer);

    result++;

    if (cows.r == farmer.r && cows.c == farmer.c)
      break;

    found = false;
    for (int i = 0, sz = states.size(); i < sz; i++) {
      if (states[i].first.r == cows.r && states[i].first.c == cows.c && states[i].first.direction == cows.direction && states[i].second.r == farmer.r && states[i].second.c == farmer.c && states[i].second.direction == farmer.direction) {
        found = true;
        break;
      }
    }

    if (found) {
      result = 0;
      break;
    } else {
      states.push_back(make_pair(cows, farmer));
    }
  }

  fout << result << endl;

  return 0;
}
