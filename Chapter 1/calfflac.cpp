/*
ID: faorien2
PROG: calfflac
LANG: C++
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct best {
  int start;
  int end;
  int length;
};

int main() {
  string actual_text = "";
  string input;
  best result;
  vector< pair<char,int> > text;
  ofstream fout("calfflac.out");
  ifstream fin("calfflac.in");

  result.start = 0;
  result.end = 0;
  result.length = 0;

  while (getline(fin, input)) {
    actual_text += input + "\n";
  }

  for (int i = 0, sz = actual_text.size(); i < sz; i++) {
    if (actual_text[i] >= 'A' && actual_text[i] <= 'Z' || actual_text[i] >= 'a' && actual_text[i] <= 'z')
      text.push_back(make_pair(toupper(actual_text[i]), i));
  }

  for (int i = 0, sz = text.size(); i < sz; i++) {
    for (int j = 0; i-j-1 >= 0 && i+j+1 < sz && text[i-j-1].first == text[i+j+1].first; j++) {
      if ((i + j + 1) - (i - j - 1) + 1 > result.length) {
        result.start = text[i-j-1].second;
        result.end = text[i+j+1].second;
        result.length = (i+j+1) - (i-j-1) + 1;
      }
    }

    if (i < sz - 1 && text[i].first == text[i+1].first) {
      for (int j = 0; i-j-1 >= 0 && i+j+2 < sz && text[i-j-1].first == text[i+j+2].first; j++) {
        if ((i+j+2) - (i-j-1) + 1 > result.length) {
          result.start = text[i-j-1].second;
          result.end = text[i+j+2].second;
          result.length = (i+j+2) - (i-j-1) + 1;
        }
      }
    }
  }

  fout << result.length << endl;
  fout << string(actual_text.begin() + result.start, actual_text.begin() + result.end + 1) << endl;

  return 0;
}
