/*
ID: faorien2
PROG: test
LANG: C++
 */
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
  int a, b;
  ofstream fout("test.out");
  ifstream fin("test.in");

  fin >> a >> b;
  fout << a + b << endl;

  return 0;
}
