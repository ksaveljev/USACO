/*
ID: faorien2
PROG: rect1
LANG: C++
 */
#include <iostream>
#include <fstream>
#include <list>
#include <map>
using namespace std;

struct rectangle {
  int llx, lly, urx, ury, color;
  int size() { return (urx - llx) * (ury - lly); }
};

list<rectangle> rectangles;

void paint_rectangle(const rectangle &r)
{
  list<rectangle>::iterator it;
  list<rectangle>::iterator lp = rectangles.begin();

  while (lp != rectangles.end()) {
    it = lp++;

    // no overlap
    if (it->llx >= r.urx) continue;
    if (it->lly >= r.ury) continue;
    if (r.llx >= it->urx) continue;
    if (r.lly >= it->ury) continue;

    // separate left rectangle
    if (it->llx < r.llx) {
      rectangle tmp = *it;
      tmp.urx = r.llx;
      rectangles.push_back(tmp);
    }

    // separate right rectangle
    if (it->urx > r.urx) {
      rectangle tmp = *it;
      tmp.llx = r.urx;
      rectangles.push_back(tmp);
    }

    // separate bottom rectangle
    if (it->lly < r.lly) {
      rectangle tmp = *it;
      tmp.ury = r.lly;
      tmp.llx = max(tmp.llx, r.llx);
      tmp.urx = min(tmp.urx, r.urx);
      if (tmp.size()) rectangles.push_back(tmp);
    }

    // separate top rectangle
    if (it->ury > r.ury) {
      rectangle tmp = *it;
      tmp.lly = r.ury;
      tmp.llx = max(tmp.llx, r.llx);
      tmp.urx = min(tmp.urx, r.urx);
      if (tmp.size()) rectangles.push_back(tmp);
    }

    // remove current
    rectangles.erase(it);
  }
}

int main() {
  int a, b, n;
  rectangle tmp;
  map<int,int> result;

  ofstream fout("rect1.out");
  ifstream fin("rect1.in");

  fin >> a >> b >> n;

  tmp.llx = 0;
  tmp.lly = 0;
  tmp.urx = a;
  tmp.ury = b;
  tmp.color = 1;

  rectangles.push_back(tmp);

  while (n--) {
    fin >> tmp.llx >> tmp.lly >> tmp.urx >> tmp.ury >> tmp.color;
    paint_rectangle(tmp);
    rectangles.push_back(tmp);
  }

  for (list<rectangle>::iterator it = rectangles.begin(); it != rectangles.end(); it++) {
    if (result.find(it->color) == result.end()) {
      result[it->color] = it->size();
    } else {
      result[it->color] += it->size();
    }
  }

  for (int i = 0; i < 2501; i++) {
    if (result.find(i) == result.end()) {
      continue;
    }
    fout << i << " " << result[i] << endl;
  }

  return 0;
}
