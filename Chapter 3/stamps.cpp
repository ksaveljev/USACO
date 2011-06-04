/*
ID: faorien2
PROG: stamps
LANG: C++
 */
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main() {
  int k, n;
  int stamps[50];
  int dp[2000010];
  int INF = 1000000000;
  ofstream fout("stamps.out");
  ifstream fin("stamps.in");

  fill (dp, dp + 2000010, INF);
  dp[0] = 0;

  fin >> k >> n;

  for (int i = 0; i < n; i++)
    fin >> stamps[i];

  int cur = 1;
  while (true) {
    for (int i = 0; i < n; i++) {
      if (stamps[i] > cur) continue;

      dp[cur] = min(dp[cur], 1 + dp[cur - stamps[i]]);
    }

    if (dp[cur] > k)
      break;

    cur++;
  }

  fout << cur - 1 << endl;

  return 0;
}
