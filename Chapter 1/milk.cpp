/*
ID: faorien2
PROG: milk
LANG: C++
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

bool theTruthIsOutThere(const pair<int,int> &a, const pair<int,int> &b) {
  return a.first < b.first;
}

int main() {
  int n, m;
  int result = 0;
  pair<int,int> tmp;
  vector< pair<int,int> > farmers;
  ofstream fout("milk.out");
  ifstream fin("milk.in");

  fin >> n >> m;

  while (m--) {
    fin >> tmp.first >> tmp.second;
    farmers.push_back(tmp);
  }

  sort(farmers.begin(), farmers.end(), theTruthIsOutThere);

  for (int i = 0, sz = farmers.size(); i < sz; i++) {
    if (n > farmers[i].second) {
      result += farmers[i].first * farmers[i].second;
      n -= farmers[i].second;
    } else {
      result += farmers[i].first * n;
      break;
    }
  }

  fout << result << endl;

  return 0;
}
