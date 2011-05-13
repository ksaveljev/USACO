/*
ID: faorien2
PROG: money
LANG: C++
 */
#include <iostream>
#include <fstream>
using namespace std;

int main() {
  int v, n;
  int coins[26];
  unsigned long long dp[10001][26];

  ofstream fout("money.out");
  ifstream fin("money.in");

  fin >> v >> n;

  for (int i = 0; i < v; i++)
    fin >> coins[i];

  for (int i = 0; i <= v; i++)
    dp[0][i] = 1;
    
  for (int i = 0; i <= n; i++)
    dp[i][0] = 0;

  for (int i = 1; i <= v; i++) {
    for (int j = 1; j <= n; j++) {
      dp[j][i] = dp[j][i-1] + (j - coins[i-1] >= 0 ? dp[j-coins[i-1]][i] : 0);
    }
  }

  fout << dp[n][v] << endl;

  return 0;
}
