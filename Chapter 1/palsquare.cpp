/*
ID: faorien2
PROG: palsquare
LANG: C++
 */
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string convert(int n, int base) {
  if (n == 0)
    return "0";

  char NUMS[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  string result = "";

  do {
    result.push_back(NUMS[n % base]);
    n /= base;
  } while (n);

  return string(result.rbegin(), result.rend());
}

bool is_palindrome(const string &s) {
  string r(s.rbegin(), s.rend());

  return r == s;
}

int main() {
  int base;
  ofstream fout("palsquare.out");
  ifstream fin("palsquare.in");

  fin >> base;

  for (int i = 1; i < 301; i++) {
    string square = convert(i * i, base);
    if (is_palindrome(square)) {
      fout << convert(i, base) << " " << square << endl;
    }
  }

  return 0;
}
