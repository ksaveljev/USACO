/*
ID: faorien2
PROG: ride
LANG: C++
 */
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int count(const string &s) {
  int tmp = 1;
  for (int i = 0, sz = s.size(); i < sz; i++) {
    tmp *= ((int)(s[i] - 'A') + 1);
    tmp %= 47;
  }
  return tmp;
}

int main() {
  string a, b;
  ofstream fout("ride.out");
  ifstream fin("ride.in");

  fin >> a >> b;

  fout << (count(a) == count(b) ? "GO" : "STAY") << endl;

  return 0;
}
