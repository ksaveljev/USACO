/*
ID: faorien2
PROG: fracdec
LANG: C++
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <string>
using namespace std;

int main() {
  int n, d;
  int counter = 0;
  vector<int> frac;
  map<int,int> visited;
  ofstream fout("fracdec.out");
  ifstream fin("fracdec.in");

  stringstream ss;

  fin >> n >> d;

  if (n % d == 0) {
    fout << n/d << ".0" << endl;
    return 0;
  }

  if (n > d) {
    ss << n/d << ".";
    //fout << n/d << ".";
    n %= d;
  } else {
    ss << "0.";
    //fout << "0.";
  }

  int repeat = -1;

  while (n) {
    n *= 10;

    if (visited.find(n) != visited.end()) {
      // repeating sequence found
      repeat = visited[n];
      n = 0;
    } else {
      visited[n] = counter;
      frac.push_back(n / d);
      n %= d;
      counter++;
    }
  }

  for (int i = 0, sz = frac.size(); i < sz; i++) {
    if (i == repeat)
      ss << "(";
    ss << frac[i];
  }

  if (repeat != -1)
    ss << ")";

  string result = ss.str();

  for (int i = 0, sz = result.size(); i < sz; i++) {
    if (i > 0 && i % 76 == 0)
      fout << endl;
    fout << result[i];
  }
  fout << endl;

  return 0;
}
