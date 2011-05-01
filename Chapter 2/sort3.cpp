/*
ID: faorien2
PROG: sort3
LANG: C++
 */
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main() {
  int n;
  int nums[1005];
  int sorted[1005];
  int count[5];
  int result = 0;
  bool ok;
  bool final = false;

  ofstream fout("sort3.out");
  ifstream fin("sort3.in");

  for (int i = 0; i < 5; i++)
    count[i] = 0;

  fin >> n;

  for (int i = 0; i < n; i++) {
    fin >> nums[i];
    sorted[i] = nums[i];
    count[nums[i]]++;
  }

  sort(sorted, sorted + n);

  while (true) {
    if (final)
      break;

    final = true;
    for (int i = 0; i < n; i++) {
      if (nums[i] != sorted[i]) {
        final = false;
        ok = false;
        for (int j = i + 1; j < n; j++) {
          if (nums[j] != sorted[j] && nums[j] == sorted[i] && nums[i] == sorted[j]) {
            ok = true;
            swap(nums[i], nums[j]);
            break;
          }
        }
        if (ok) {
          result++;
          break;
        } else {
          for (int j = i + 1; j < n; j++) {
            if (nums[j] != sorted[j] && nums[j] == sorted[i]) {
              result++;
              swap(nums[j], nums[i]);
              break;
            }
          }
        }
      }
    }
  }

  fout << result << endl;

  return 0;
}
