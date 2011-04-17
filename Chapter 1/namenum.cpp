/*
ID: faorien2
PROG: namenum
LANG: C++
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

bool theTruthIsOutThere(const string &a, const string &b) {
  return a.size() == b.size() ? a < b : a.size() < b.size();
}

int main() {
  bool good, found;
  string input;
  vector<string> dict;
  set< pair<char,char> > s;
  ofstream fout("namenum.out");
  ifstream fin("namenum.in");

  ifstream dic("dict.txt");

  while (dic >> input) {
    dict.push_back(input);
  }

  sort(dict.begin(), dict.end(), theTruthIsOutThere);

  s.insert(make_pair('A', '2'));
  s.insert(make_pair('B', '2'));
  s.insert(make_pair('C', '2'));
  s.insert(make_pair('D', '3'));
  s.insert(make_pair('E', '3'));
  s.insert(make_pair('F', '3'));
  s.insert(make_pair('G', '4'));
  s.insert(make_pair('H', '4'));
  s.insert(make_pair('I', '4'));
  s.insert(make_pair('J', '5'));
  s.insert(make_pair('K', '5'));
  s.insert(make_pair('L', '5'));
  s.insert(make_pair('M', '6'));
  s.insert(make_pair('N', '6'));
  s.insert(make_pair('O', '6'));
  s.insert(make_pair('P', '7'));
  s.insert(make_pair('R', '7'));
  s.insert(make_pair('S', '7'));
  s.insert(make_pair('T', '8'));
  s.insert(make_pair('U', '8'));
  s.insert(make_pair('V', '8'));
  s.insert(make_pair('W', '9'));
  s.insert(make_pair('X', '9'));
  s.insert(make_pair('Y', '9'));

  fin >> input;

  found = false;

  for (int i = 0, sz = dict.size(), len = input.size(); i < sz; i++) {
    if (dict[i].size() < len)
      continue;

    if (dict[i].size() > len)
      break;

    good = true;
    for (int j = 0; j < len; j++) {
      if (s.find(make_pair(dict[i][j], input[j])) == s.end()) {
        good = false;
        break;
      }
    }

    if (good) {
      fout << dict[i] << endl;
      found = true;
    }
  }

  if (!found)
    fout << "NONE" << endl;

  return 0;
}
