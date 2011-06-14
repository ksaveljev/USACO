/*
ID: faorien2
PROG: agrinet
LANG: C++
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <fstream>
using namespace std;

class UnionFindDisjointSets {
  public:
    UnionFindDisjointSets(int size);
    int findSet(int a);
    bool isSameSet(int a, int b);
    void unionSet(int a, int b);
    int numDisjointSets();
    int sizeOfSet(int a);
  private:
    int size;
    vector<int> pset;
    vector<int> set_size;
};

UnionFindDisjointSets::UnionFindDisjointSets(int size) {
  this->size = size;

  set_size.assign(size, 1);
  pset.assign(size, 0);

  for (int i = 0; i < size; i++)
    pset[i] = i;
}

int UnionFindDisjointSets::findSet(int a) {
  return pset[a] == a ? a : (pset[a] = findSet(pset[a]));
}

bool UnionFindDisjointSets::isSameSet(int a, int b) {
  return findSet(a) == findSet(b);
}

void UnionFindDisjointSets::unionSet(int a, int b) {
  if (isSameSet(a, b)) return;

  size--;
  set_size[findSet(b)] += set_size[findSet(a)];
  pset[findSet(a)] = findSet(b);
}

int UnionFindDisjointSets::numDisjointSets() {
  return size;
}

int UnionFindDisjointSets::sizeOfSet(int a) {
  return set_size[findSet(a)];
}

int main() {
  int n, w;

  ofstream fout("agrinet.out");
  ifstream fin("agrinet.in");

  fin >> n;

  priority_queue< pair<int, pair<int,int> > > edgeList;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      fin >> w;

      if (i == j) continue;

      edgeList.push(make_pair(-w, make_pair(i,j)));
    }
  }

  int mst_cost = 0;
  UnionFindDisjointSets ds(n);

  while (!edgeList.empty()) {
    pair< int, pair<int,int> > front = edgeList.top();
    edgeList.pop();

    if (!ds.isSameSet(front.second.first, front.second.second)) {
      mst_cost += (-front.first);
      ds.unionSet(front.second.first, front.second.second);
    }
  }

  fout << mst_cost << endl;

  return 0;
}

