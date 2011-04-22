/*
ID: faorien2
PROG: ariprog
LANG: C++
 */
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

bool theTruthIsOutThere(const pair<int,int> &a, const pair<int,int> &b) {
  return a.second == b.second ? a.first < b.first : a.second < b.second;
}

int main() {
  int N;
  int n, m;
  int a, b;
  bool found;
  int *bisq = new int[125001];
  vector< pair<int,int> > result;
  
  memset(bisq, -1, sizeof(int) * 125001);

  ofstream fout("ariprog.out");
  ifstream fin("ariprog.in");

  fin >> N >> m;

  for (int i = 0; i <= m; i++) {
    for (int j = 0; j <= m; j++) {
      bisq[i*i + j*j] = i*i + j*j;
    }
  }

  for (int i = 0; i < 125000; i++) {
    if (bisq[i] == -1)
      continue;

    a = bisq[i];

    b = (125000 - i) / (N - 1);

    for (b = b; b > 0; b--) {
      found = true;

      for (n = 1; n < N; n++) {
        if (bisq[a + b * n] == -1) {
          found = false;
          break;
        }
      }

      if (found)
        result.push_back(make_pair(a, b));
    }
  }

  sort(result.begin(), result.end(), theTruthIsOutThere);

  for (int i = 0, sz = result.size(); i < sz; i++)
    fout << result[i].first << " " << result[i].second << endl;

  if (result.size() == 0)
    fout << "NONE" << endl;

  delete [] bisq;

  return 0;
}
