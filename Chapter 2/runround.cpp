/*
ID: faorien2
PROG: runround
LANG: C++
 */
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
using namespace std;

vector<int> runaround_numbers;

bool next_combination (int a[9], int k, int n) {
  for (int i = k - 1; i >= 0; i--) {
    if (a[i] < n - k + i + 1) {
      a[i]++;
      for (int j = i + 1; j < k; j++)
        a[j] = a[j-1] + 1;
      return true;
    }
  }
  return false;
}

bool taken[9];

bool is_runaround(int num, int len) {
  if (len == 1)
    return true;

  int temp = num;

  int n;
  int tmp;
  int count = 0;
  bool visited[10];
  int jumps[10];

  fill(visited, visited+10, false);

  while (num) {
    n = num % 10;
    num /= 10;

    tmp = ((len - count) + n) % len;
    if (tmp == 0)
      tmp = len;
    count++;

    if (visited[tmp])
      return false;

    visited[tmp] = true;

    jumps[len - count] = tmp;
  }

  count = 1;
  int cur = jumps[0];

  while (count < len) {
    cur = jumps[cur - 1];
    count++;

    if (cur == 1 && count != len)
      return false;
  }

  return true;
}

void generate_numbers(int num, int len) {
  int nums[9] = {1,2,3,4,5,6,7,8,9};

  if ((int)log10(num) + 1 == len) {
    if (is_runaround(num, len))
      runaround_numbers.push_back(num);

    return;
  }
  
  for (int i = 0; i < 9; i++) {
    if (taken[i])
      continue;

    taken[i] = true;
    generate_numbers(num * 10 + nums[i], len);
    taken[i] = false;
  }
}

int main() {
  int n;

  ofstream fout("runround.out");
  ifstream fin("runround.in");

  fin >> n;

  fill(taken, taken+9, false);

  for (int i = 1; i < 10; i++)
    runaround_numbers.push_back(i);

  for (int i = 2; i < 10; i++) {
    generate_numbers(0, i);
  }

  for (int i = 0, sz = runaround_numbers.size(); i < sz; i++) {
    if (runaround_numbers[i] > n) {
      fout << runaround_numbers[i] << endl;
      break;
    }
  }

  return 0;
}

