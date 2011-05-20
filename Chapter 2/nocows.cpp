/*
ID: faorien2
PROG: nocows
LANG: C++
 */
#include <iostream>
#include <fstream>
using namespace std;

int dp[201][100];

int solve(int n, int k) {
  if (n % 2 == 0)
    return 0;
  if (2 * k - 1 > n)
    return 0;

  if (k == 1)
    return (n == 1 ? 1 : 0);

  if (dp[n][k] != -1)
    return dp[n][k];

  dp[n][k] = 0;

  for (int i = 1; i < (n+1) / 2; i += 2) {
    int n1 = i;
    int n2 = n - i - 1;
    int sol = 0;

    for (int j = 1; j < k - 1; j++) {
      sol += solve(n1, j) * solve(n2, k - 1);
      sol += solve(n1, k - 1) * solve(n2, j);
      sol %= 9901;
    }

    sol += solve(n1, k - 1) * solve(n2, k - 1);
    sol %= 9901;

    if (n1 != n2)
      dp[n][k] += 2 * sol;
    else
      dp[n][k] += sol;

    dp[n][k] %= 9901;
  }

  return dp[n][k];
}

int main() {
  int n, k;

  ofstream fout("nocows.out");
  ifstream fin("nocows.in");

  fin >> n >> k;

  for (int i = 0; i < 201; i++)
    for (int j = 0; j < 100; j++)
      dp[i][j] = -1;

  fin >> n >> k;

  fout << solve(n, k) << endl;

  return 0;
}
