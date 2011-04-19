/*
ID: faorien2
PROG: crypt1
LANG: C++
 */
#include <iostream>
#include <fstream>
#include <set>
using namespace std;

set<int> digits;

bool allowed(int num) {
  while (num) {
    if (digits.find(num % 10) == digits.end())
      return false;

    num /= 10;
  }

  return true;
}

int main() {
  int n;
  int tmp;
  int p1, p2;
  int counter = 0;
  ofstream fout("crypt1.out");
  ifstream fin("crypt1.in");

  fin >> n;

  for (int i = 0; i < n; i++) {
    fin >> tmp;
    digits.insert(tmp);
  }

  for (int i = 100; i < 1000; i++) {
    for (int j = 10; j < 100; j++) {
      if (!allowed(i) || !allowed(j))
        continue;

      p1 = i * (j % 10);
      p2 = i * (j / 10);

      if (p1 < 100 || p1 > 999 || !allowed(p1))
        continue;
      if (p2 < 100 || p2 > 999 || !allowed(p2))
        continue;

      tmp = i * j;

      if (tmp < 1000 || tmp > 9999 || !allowed(tmp))
        continue;

      counter++;
    }
  }

  fout << counter << endl;

  return 0;
}
