/*
ID: faorien2
PROG: sprime
LANG: C++
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

bool is_prime(int n) {
  if (n == 2)
    return true;

  if (n % 2 == 0)
    return false;

  for (int i = 3, sq = sqrt(n); i <= sq; i += 2) 
    if (n % i == 0)
      return false;

  return true;
}

int main() {
  int n;
  vector<int> primes[10];

  ofstream fout("sprime.out");
  ifstream fin("sprime.in");

  for (int i = 2; i < 10; i++)
    if (is_prime(i))
      primes[1].push_back(i);

  for (int i = 2; i < 9; i++) {
    for (int j = 0, sz = primes[i-1].size(); j < sz; j++) {
      for (int k = 0; k < 10; k++) {
        if (is_prime(primes[i-1][j] * 10 + k))
          primes[i].push_back(primes[i-1][j] * 10 +k);
      }
    }
  }

  fin >> n;

  for (int i = 0, sz = primes[n].size(); i < sz; i++)
    fout << primes[n][i] << endl;

  return 0;
}
