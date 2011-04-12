/*
ID: faorien2
PROG: gift1
LANG: C++
 */
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

int main() {
  int NP;
  int money, people;
  string name;
  vector<string> names;
  map<string,int> result;

  ofstream fout("gift1.out");
  ifstream fin("gift1.in");

  fin >> NP;

  for (int i = 0; i < NP; i++) {
    fin >> name;
    names.push_back(name);
    result[name] = 0;
  }

  while (NP--) {
    fin >> name;
    fin >> money >> people;

    if (people == 0)
      continue;

    result[name] = result[name] - money + money % people;

    for (int i = 0; i < people; i++) {
      fin >> name;
      result[name] += money / people;
    }
  }

  for (int i = 0, sz = names.size(); i < sz; i++) {
    fout << names[i] << " " << result[names[i]] << endl;
  }
  

  return 0;
}
