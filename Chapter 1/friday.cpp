/*
ID: faorien2
PROG: friday
LANG: C++
 */
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

bool is_leap(int year) {
  bool leap = false;

  if (year % 4 == 0) {
    if (year % 100 == 0) {
      if ( year % 400 == 0) {
        leap = true;
      }
    } else {
      leap = true;
    }
  }

  return leap;
}

int main() {
  int N;
  int days = 0;
  int cur_day = 0;
  int result[8];

  memset(result, 0, sizeof result);

  ofstream fout("friday.out");
  ifstream fin("friday.in");

  int months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  fin >> N;

  for (int year = 1900; year < 1900 + N; year++) {
    for (int i = 0; i < 12; i++) {
      days = months[i];
      if (i == 1) { // february
        if (is_leap(year))
          days++;
      }
      for (int j = 1; j <= days; j++) {
        cur_day++;
        if (cur_day == 8)
          cur_day = 1;

        if (j == 13) {
          result[cur_day]++;
        }
      }
    }
  }

  fout << result[6] << " " << result[7] << " " << result[1] << " " << result[2] << " " << result[3] << " " << result[4] << " " << result[5] << endl;


  return 0;
}
