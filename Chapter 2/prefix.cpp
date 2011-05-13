/*
ID: faorien2
PROG: prefix
LANG: C++
 */
#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

int jenkins(const string &s, int start, int len) {
  int hash, i;

  for (hash = i = 0; i < len; i++) {
    hash += s[start + i];
    hash += (hash << 10);
    hash ^= (hash >> 6);
  }

  hash += (hash << 3);
  hash ^= (hash >> 11);
  hash += (hash << 15);

  return hash;
}

int main() {
  string input = "", tmp;
  map<int,int> m;
  int result = 0;
  int hash;

  ofstream fout("prefix.out");
  ifstream fin("prefix.in");

  while (fin >> tmp) {
    if (tmp == ".")
      break;

    m.insert(make_pair(jenkins(tmp, 0, tmp.size()), tmp.size()));
  }

  while (fin >> tmp) {
    input += tmp;
  }

  int sz = input.size();
  bool *reachable = new bool[sz + 1];

  fill (reachable, reachable + sz + 1, false);

  reachable[0] = true;
  for (int i = 0; i < sz + 1; i++) {
    if (!reachable[i])
      continue;

    if (i > result)
      result = i;

    if (i == sz)
      continue;

    for (int j = 0; j < 10; j++) {
      hash = jenkins(input, i, j + 1);
      if (m.find(hash) == m.end())
        continue;

      reachable[i+m[hash]] = true;
    }
  }

  fout << result << endl;

  delete [] reachable;

  return 0;
}
