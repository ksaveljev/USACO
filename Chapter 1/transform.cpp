/*
ID: faorien2
PROG: transform
LANG: C++
 */
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void copy_pattern(const char p[][15], char target[][15], int N) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      target[i][j] = p[i][j];
    }
  }
}

void rotate(const char p[][15], char target[][15], int N, int count) {
  char tmp[15][15];

  copy_pattern(p, target, N);

  for (int i = 0; i < count; i++) {
    copy_pattern(target, tmp, N);

    for (int a = 0; a < N; a++) {
      for (int b = 0; b < N; b++) {
        target[a][b] = tmp[N-b-1][a];
      }
    }
  }
}

void reflect(const char p[][15], char target[][15], int N) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      target[i][j] = p[i][N-j-1];
    }
  }
}

void read_pattern(ifstream &fin, char p[][15], int N) {
  string input;
  for (int i = 0; i < N; i++) {
    fin >> input;
    for (int j = 0; j < N; j++) {
      p[i][j] = input[j];
    }
  }
}

bool compare_pattern(const char a[][15], const char b[][15], int N) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (a[i][j] != b[i][j])
        return false;
    }
  }

  return true;
}

int main() {
  int N;
  int result = 7;
  char pattern[15][15];
  char target[15][15];
  char tmp[15][15];
  ofstream fout("transform.out");
  ifstream fin("transform.in");

  fin >> N;

  read_pattern(fin, pattern, N);
  read_pattern(fin, target, N);

  while (true) {
    rotate(pattern, tmp, N, 1);
    if (compare_pattern(tmp, target, N)) {
      result = 1;
      break;
    }

    rotate(pattern, tmp, N, 2);
    if (compare_pattern(tmp, target, N)) {
      result = 2;
      break;
    }

    rotate(pattern, tmp, N, 3);
    if (compare_pattern(tmp, target, N)) {
      result = 3;
      break;
    }

    reflect(pattern, tmp, N);
    if (compare_pattern(tmp, target, N)) {
      result = 4;
      break;
    }

    reflect(pattern, tmp, N);
    copy_pattern(tmp, pattern, N);
    rotate(pattern, tmp, N, 1);
    if (compare_pattern(tmp, target, N)) {
      result = 5;
      break;
    }

    rotate(pattern, tmp, N, 2);
    if (compare_pattern(tmp, target, N)) {
      result = 5;
      break;
    }

    rotate(pattern, tmp, N, 3);
    if (compare_pattern(tmp, target, N)) {
      result = 5;
      break;
    }
    
    if (compare_pattern(pattern, target, N)) {
      result = 6;
      break;
    }

    break;
  }

  fout << result << endl;

  return 0;
}
