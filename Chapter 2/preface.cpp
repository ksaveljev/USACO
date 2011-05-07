/*
ID: faorien2
PROG: preface
LANG: C++
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string int2roman(int n) {
  string roman;
  string ones[] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
  string tens[] = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
  string hundreds[] = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
  string thousands[] = {"", "M", "MM", "MMM"};

  int o = n % 10; 
  n /= 10; 
  int t = n % 10; 
  n /= 10; 
  int h = n % 10; 
  n /= 10; 
  int th = n % 10; 

  roman += thousands[th] + hundreds[h] + tens[t] + ones[o];

  return roman;
}

int get_value(char c) {
  if (c == 'I')
    return 1;
  if (c == 'V')
    return 2;
  if (c == 'X')
    return 3;
  if (c == 'L')
    return 4;
  if (c == 'C')
    return 5;
  if (c == 'D')
    return 6;
  if (c == 'M')
    return 7;
}

bool theTruthIsOutThere(const pair<char,int> &a, const pair<char,int> &b) {
  int acost, bcost;
  acost = get_value(a.first);
  bcost = get_value(b.first);

  return acost < bcost;
}

int main() {
  int n;
  string s;
  bool found;
  vector< pair<char,int> > result;

  ofstream fout("preface.out");
  ifstream fin("preface.in");

  fin >> n;

  for (int i = 1; i <= n; i++) {
    s = int2roman(i);

    for (int i = 0, sz = s.size(); i < sz; i++) {
      found = false;

      for (int j = 0, sz2 = result.size(); j < sz2; j++) {
        if (result[j].first == s[i]) {
          result[j].second += 1;
          found = true;
          break;
        }
      }

      if (!found) {
        result.push_back(make_pair(s[i], 1));
      }
    }
  }

  sort(result.begin(), result.end(), theTruthIsOutThere);

  for (int i = 0, sz = result.size(); i < sz; i++)
    fout << result[i].first << " " << result[i].second << endl;

  return 0;
}
