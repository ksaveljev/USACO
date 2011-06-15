/*
ID: faorien2
PROG: contact
LANG: C++
 */
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

unsigned int jenkins_one_at_a_time_hash(const string &input, int start, int n) {
  unsigned int hash = 0;

  for (int i = 0; i < n; i++) {
    hash += input[start+i];
    hash += (hash << 10);
    hash ^= (hash >> 6);
  }

  hash += (hash << 3);
  hash ^= (hash >> 11);
  hash += (hash << 15);

  return hash;
}

struct pattern {
  string s;
  int freq;
  int dec;
  pattern() : freq(0) {}
};

int str2bin(const string &s) {
  int result = 0;
  int tmp = 1;

  for (int i = s.size() - 1; i >= 0; i--) {
    result += int(s[i]-'0') * tmp;
    tmp <<= 1;
  }

  return result;
}

bool theTruthIsOutThere(const pattern &a, const pattern &b) {
  if (a.freq == b.freq) {
    if (a.s.size() == b.s.size()) {
      return a.dec < b.dec;
    }

    return a.s.size() < b.s.size();
  }

  return a.freq > b.freq;
}

int main() {
  int a, b, n;
  string s;
  string input;
  unsigned int hash;
  map<int,string> m;
  map<int,int> count;

  ofstream fout("contact.out");
  ifstream fin("contact.in");

  fin >> a >> b >> n;

  while (fin >> input) {
    s+= input;
  }

  for (int i = 0, sz = s.size(); i < sz; i++) {
    for (int j = a; j <= b; j++) {
      if (i + j > sz) break;

      hash = jenkins_one_at_a_time_hash(s, i, j);

      if (m.find(hash) == m.end()) {
        m[hash] = string(s.begin() + i, s.begin() + i + j);
        count[hash] = 1;
      } else {
        count[hash] += 1;
      }
    }
  }

  pattern tmp;
  vector<pattern> v;

  for (typeof(count.begin()) it = count.begin(); it != count.end(); it++) {
    tmp.s = m[it->first];
    tmp.freq = it->second;
    tmp.dec = str2bin(tmp.s);
    v.push_back(tmp);
  }

  sort(v.begin(), v.end(), theTruthIsOutThere);

  bool first = true;
  int c = 0;
  int rep = 0;
  int prev = -1;
  for (int i = 0, sz = v.size(); i < sz; i++) {
    if (v[i].freq != prev) {
      if (c == n)
        break;

      if (!first)
        fout << endl;

      fout << v[i].freq << endl;
      fout << v[i].s;

      c++;
      rep = 1;
      prev = v[i].freq;
      first = false;
    } else {
      rep++;
      if (rep > 6) {
        rep = 1;
        fout << endl << v[i].s;
      } else {
        fout << " " << v[i].s;
      }
    }
  }
  fout << endl;

  return 0;
}
