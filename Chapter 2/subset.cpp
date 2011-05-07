/*
ID: faorien2
PROG: subset
LANG: C++
 */
#include <iostream>
#include <fstream>
using namespace std;

int main() {
  int n;
  // Sum = n * (n + 1) / 2
  // max(n) = 39
  unsigned long long dp[1500][40];

  ofstream fout("subset.out");
  ifstream fin("subset.in");

  fin >> n;

  if ((n * (n + 1) / 2) & 1) {
    fout << 0 << endl;
    return 0;
  }

  for (int i = 0; i < 750; i++)
    for (int j = 0; j < 40; j++)
      dp[i][j] = 0;

  for (int j = 0; j < 40; j++)
    dp[0][j] = 1;

  for (int sum = 1; sum <= n*(n+1)/2; sum++) {
    for (int i = 1; i <= n; i++) {
      dp[sum][i] = dp[sum][i-1] + (sum - i >= 0 ? dp[sum-i][i-1] : 0);
    }
  }

  fout << dp[n*(n+1)/4][n] / 2 << endl;

  return 0;
}
