/*
ID: faorien2
PROG: hamming
LANG: C++
 */
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int hamming_distance(int num1, int num2, int b) {
  int result = 0;

  int tmp = num1 ^ num2;

  while (tmp) {
    result++;
    tmp &= tmp - 1;
  }

  return result;
}

int main() {
  int n, b, d;
  bool found;
  vector<int> result;

  ofstream fout("hamming.out");
  ifstream fin("hamming.in");

  fin >> n >> b >> d;

  result.push_back(0);

  for (int i = 1; i <= 1<<b; i++) {
    found = true;
    for (int j = 0, sz = result.size(); j < sz; j++) {
      if (hamming_distance(result[j], i, b) < d) {
        found = false;
        break;
      }
    }
    if (found)
      result.push_back(i);

    if (result.size() == n)
      break;
  }

  for (int i = 0; i < n; i++) {
    if (i == 0) {

    } else if (i % 10 == 0)
      fout << endl;
    else
      fout << " ";

    fout << result[i];
  }
  fout << endl;

  return 0;
}
