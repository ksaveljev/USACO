/*
ID: faorien2
PROG: maze1
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <map>
using namespace std;

// helper to identify which exit we have found: either first or second
bool first = true;
int result = 0;
map<int,int> dist;
int w, h;
string maze[250];

void add_exit(pair<int,int> *exits, int i, int j) {
  if (first) {
    first = false;
    exits[0].first = i;
    exits[0].second = j;
  } else {
    exits[1].first = i;
    exits[1].second = j;
  }
}

void fill(pair<int,int> start) {
  pair<int,int> pos;
  pair<pair<int,int>,int> tmp;
  queue< pair<pair<int,int>,int> > q;
  map<int,bool> visited;

  tmp = make_pair(start, 1);
  q.push(tmp);

  visited[start.first * 10000 + start.second] = true;

  while (!q.empty()) {
    tmp = q.front();
    q.pop();

    pos = tmp.first;
    // if is true during the first fill
    if (dist.find(pos.first*10000 + pos.second) == dist.end()) {
      dist[pos.first * 10000 + pos.second] = tmp.second;
    } else { // else is true during the second fill
      dist[pos.first*10000 + pos.second] = min(dist[pos.first*10000 + pos.second], tmp.second);
      if (dist[pos.first*10000 + pos.second] > result) {
        result = dist[pos.first*10000 + pos.second];
      }
    }

    if (pos.first > 1 && maze[pos.first-1][pos.second] == ' ' && !visited[(pos.first-2)*10000 + pos.second]) {
      visited[(pos.first-2)*10000 + pos.second] = true;
      q.push(make_pair(make_pair(pos.first-2,pos.second), tmp.second+1));
    }

    if (pos.first + 2 < 2 * h + 1 && maze[pos.first+1][pos.second] == ' ' && !visited[(pos.first+2)*10000 + pos.second]) {
      visited[(pos.first+2)*10000 + pos.second] = true;
      q.push(make_pair(make_pair(pos.first+2, pos.second), tmp.second+1));
    }

    if (pos.second > 1 && maze[pos.first][pos.second-1] == ' ' && !visited[pos.first * 10000 + pos.second-2]) {
      visited[pos.first*10000 + pos.second-2] = true;
      q.push(make_pair(make_pair(pos.first, pos.second-2), tmp.second+1));
    }

    if (pos.second + 2 < 2 * w + 1 && maze[pos.first][pos.second+1] == ' ' && !visited[pos.first*10000 + pos.second+2]) {
      visited[pos.first*10000 + pos.second+2] = true;
      q.push(make_pair(make_pair(pos.first, pos.second+2), tmp.second+1));
    }
  }
}

int main(void) {
  pair<int,int> exits[2];
  string input;

  ofstream fout("maze1.out");
  ifstream fin("maze1.in");

  fin >> w >> h;
  fin.ignore(100, '\n');

  for (int i = 0; i < 2*h+1; i++) {
    getline(fin, maze[i]);
  }

  for (int j = 1; j < 2*w+1; j += 2) {
    if (maze[0][j] == ' ') {
      add_exit(exits, 1, j);
    }

    if (maze[2*h][j] == ' ') {
      add_exit(exits, 2*h-1, j);
    }
  }

  for (int i = 1; i < 2*h+1; i += 2) {
    if (maze[i][0] == ' ') {
      add_exit(exits, i, 1);
    }

    if (maze[i][2*w] == ' ') {
      add_exit(exits, i, 2*w-1);
    }
  }

  fill(exits[0]);
  fill(exits[1]);

  fout << result << endl;

  return 0;
}
