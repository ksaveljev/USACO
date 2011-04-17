/*
ID: faorien2
PROG: dualpal
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
  int n, s;
  int pal_num;
  ofstream fout("dualpal.out");
  ifstream fin("dualpal.in");

  fin >> n >> s;

  for (int i = s + 1; ; i++) {
    pal_num = 0;
    for (int j = 2; j < 11; j++) {
      if (is_palindrome(convert(i, j))) {
        pal_num++;
        if (pal_num == 2)
          break;
      }
    }

    if (pal_num == 2) {
      fout << i << endl;
      n--;
      if (!n)
        break;
    }
  }

  return 0;
}
