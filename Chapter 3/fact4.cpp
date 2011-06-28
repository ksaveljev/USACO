/*
ID: faorien2
PROG: fact4
LANG: C++
 */
#include <iostream>
#include <fstream>
using namespace std;

int main() {
  int n;

  ofstream fout("fact4.out");
  ifstream fin("fact4.in");

  fin >> n;

  unsigned long long result = 1;

  for (int i = 2; i <= n; i++) {
    result *= i;

    while (result % 10 == 0) {
      result /= 10;
    }

    result %= 1000000000;
  }

  fout << result % 10 << endl;

  return 0;
}
