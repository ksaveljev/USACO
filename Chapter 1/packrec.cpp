/*
ID: faorien2
PROG: packrec
LANG: C++
 */
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

struct rectangle {
  int a;
  int b;
};

int seq[4] = {0, 1, 2, 3};
int best = 2000000000;
rectangle tmp[4];
rectangle rectangles[4];
set< pair<int,int> > result;

pair<int,int> build_rectangle(int rect) {
  pair<int,int> r;

  switch(rect) {
    case 1:
      r.first = tmp[0].a + tmp[1].a + tmp[2].a + tmp[3].a;
      r.second = max(max(tmp[0].b, tmp[1].b), max(tmp[2].b, tmp[3].b));
      break;
    case 2:
      r.first = max(tmp[0].a, tmp[1].a + tmp[2].a + tmp[3].a);
      r.second = tmp[0].b + max(tmp[1].b, max(tmp[2].b, tmp[3].b));
      break;
    case 3:
      r.first = tmp[0].a + max(tmp[1].a, tmp[2].a + tmp[3].a);
      r.second = max(tmp[0].b, tmp[1].b + max(tmp[2].b, tmp[3].b));
      break;
    case 4:
      r.first = tmp[0].a + tmp[3].a + max(tmp[1].a, tmp[2].a);
      r.second = max(max(tmp[0].b, tmp[3].b), tmp[1].b + tmp[2].b);
      break;
    case 5:
      r.first = tmp[0].a + tmp[1].a + max(tmp[2].a, tmp[3].a);
      r.second = max(max(tmp[0].b, tmp[1].b), tmp[2].b + tmp[3].b);
      break;
    case 6:
      r.first = max(tmp[0].a + tmp[1].a, tmp[2].a + tmp[3].a);
      r.second = max(tmp[0].b + tmp[2].b, tmp[1].b + tmp[3].b);

      if (r.first < tmp[0].a + tmp[3].a && r.second < tmp[0].b + tmp[3].b)
        r.first = tmp[0].a + tmp[3].a;
      if (r.first < tmp[1].a + tmp[2].a && r.second < tmp[1].b + tmp[2].b)
        r.first = tmp[1].a + tmp[2].a;

      break;
  }
  
  return r;
}

void solve(int depth) {
  if (depth == 4) {
    pair<int,int> r;
    for (int i = 1; i < 7; i++) {
      r = build_rectangle(i);

      if (r.first * r.second < best) {
        result.clear();
        best = r.first * r.second;
        result.insert(make_pair(min(r.first, r.second), max(r.first, r.second)));
      } else if (r.first * r.second == best) {
        result.insert(make_pair(min(r.first, r.second), max(r.first, r.second)));
      }
    }
    return;
  }
  tmp[depth].a = rectangles[seq[depth]].a;
  tmp[depth].b = rectangles[seq[depth]].b;
  solve(depth + 1);

  tmp[depth].a = rectangles[seq[depth]].b;
  tmp[depth].b = rectangles[seq[depth]].a;
  solve(depth + 1);
}

int main() {
  ofstream fout("packrec.out");
  ifstream fin("packrec.in");

  for (int i = 0; i < 4; i++)
    fin >> rectangles[i].a >> rectangles[i].b;

  do {
    solve(0);
  } while (next_permutation(seq, seq+4));

  fout << best << endl;

  for (set< pair<int,int> >::iterator it = result.begin(); it != result.end(); it++)
    fout << it->first << " " << it->second << endl;

  return 0;
}
