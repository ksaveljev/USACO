/*
ID: faorien2
PROG: inflate
LANG: C++
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
  int m, n;
  int a, b;
  int *dp;
  vector< pair<int,int> > problems;

  ofstream fout("inflate.out");
  ifstream fin("inflate.in");

  fin >> m >> n;

  dp = new int[m+1];
  dp[0] = 0;

  for (int i = 0; i < n; i++) {
    fin >> a >> b;
    problems.push_back(make_pair(a,b));
  }

  for (int i = 1; i <= m; i++) {
    int best = 0;
    for (int j = 0; j < n; j++) {
      if (problems[j].second <= i) {
        best = max(best, dp[i-problems[j].second] + problems[j].first);
      }
    }
    dp[i] = max(dp[i-1], best);
  }

  fout << dp[m] << endl;

  delete [] dp;

  return 0;
}
