/*
ID: faorien2
PROG: frac1
LANG: C++
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct fraction {
  int a;
  int b;
  double v;
};

bool theTruthIsOutThere(const fraction &a, const fraction &b) {
  return a.v < b.v;
}

int gcd(int a, int b) {
  while (b) {
    a %= b;
    swap(a, b);
  }
  return a;
}

int main() {
  int n;
  fraction tmp;
  vector<fraction> v;

  ofstream fout("frac1.out");
  ifstream fin("frac1.in");

  fin >> n;

  for (int i = 2; i <= n; i++) {
    for (int j = 1; j < i; j++) {
      if (gcd(j, i) > 1)
        continue;

      tmp.a = j;
      tmp.b = i;
      tmp.v = j * 1.0 / i;
      v.push_back(tmp);
    }
  }

  sort(v.begin(), v.end(), theTruthIsOutThere);

  fout << "0/1" << endl;
  for (int i = 0, sz = v.size(); i < sz; i++)
    fout << v[i].a << "/" << v[i].b << endl;
  fout << "1/1" << endl;

  return 0;
}
