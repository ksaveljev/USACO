/*
ID: faorien2
PROG: pprime
LANG: C++
 */
#include <iostream>
#include <fstream>
#include <set>
#include <cmath>
using namespace std;

set<int> pprimes;

bool is_prime(int n) {
  if (n % 2 == 0)
    return false;

  for (int i = 3, sq = sqrt(n); i <= sq; i += 2) {
    if (n % i == 0)
      return false;
  }

  return true;
}

void generate_pprimes(int num, int depth, int len) {
  if (depth == (len + 1) / 2) {
    int tmp;
    if (len % 2 == 0) {
      tmp = num;
    } else {
      tmp = num / 10; 
    }

    while (tmp) {
      num = num * 10 + tmp % 10;
      tmp /= 10;
    }

    if (is_prime(num))
      pprimes.insert(num);

    return;
  }

  if (depth == 0) {
    for (int i = 1; i < 10; i += 2)
      generate_pprimes(num * 10 + i, depth + 1, len);
  } else {
    for (int i = 0; i < 10; i++) {
      generate_pprimes(num * 10 + i, depth + 1, len);
    }
  }
}

int main() {
  int start, end;

  ofstream fout("pprime.out");
  ifstream fin("pprime.in");

  fin >> start >> end;

  pprimes.insert(2);
  pprimes.insert(3);
  pprimes.insert(5);
  pprimes.insert(7);

  for (int i = 2; i < 9; i++) {
    generate_pprimes(0, 0, i);
  }

  for (set<int>::iterator it = pprimes.begin(); it != pprimes.end(); it++) {
    if (*it >= start && *it <= end)
      fout << *it << endl;
  }

  return 0;
}
