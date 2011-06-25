/*
ID: faorien2
PROG: humble
LANG: C++
 */
#include <iostream>
#include <fstream>
using namespace std;

int main() {
  int k, n;
  int pos = 0;
  int primes[100];
  int index[100] = {0};
  int humble[100010];
  ofstream fout("humble.out");
  ifstream fin("humble.in");

  fin >> k >> n;

  for (int i = 0; i < k; i++) {
    fin >> primes[i];
  }

  humble[pos++] = 1;

  while (pos <= n) {
    unsigned int min = ~0;

    for (int i = 0; i < k; i++) {
      for (int j = index[i]; j < pos; j++) {
        unsigned int cur = primes[i] * humble[j];
        if (cur > humble[pos-1]) {
          if (cur < min) {
            min = cur;
          }
          index[i] = j;
          break;
        }
      }
    }

    humble[pos++] = min;
  }

  fout << humble[pos-1] << endl;

  return 0;
}
