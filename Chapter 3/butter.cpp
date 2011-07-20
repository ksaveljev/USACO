/*
ID: faorien2
PROG: butter
LANG: C++
 */
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <set>
using namespace std;

unsigned int INF = 4000000000;

typedef int vdata;

struct Vertex {
  vdata id;
  vector< pair<Vertex*, int> > adj;
  Vertex (vdata id) : id(id) {}
};

typedef map<vdata, Vertex*> vmap;
typedef pair<vdata, Vertex*> vpair;


class WGraph {
  public:
    WGraph() {}
    ~WGraph();
    Vertex* addVertex (vdata v);
    void addEdge (vdata begin, vdata end, int weight, bool directed);
    Vertex* getVertex (vdata v);
    void dijkstra(vdata begin, int dist[800]);
  private:
    vmap vertexMap;
    vmap::iterator it;
    vector<Vertex*> allVertexes;
};

WGraph::~WGraph() {
  for (int i = 0, sz = allVertexes.size(); i < sz; i++)
    delete allVertexes[i];
}

Vertex* WGraph::addVertex (vdata v) {
  Vertex* newv = new Vertex (v);
  allVertexes.push_back (newv);
  vertexMap.insert (vpair (v, newv));
  return newv;
}

Vertex* WGraph::getVertex (vdata v) {
  it = vertexMap.find (v);

  if (it == vertexMap.end())
    return addVertex (v);

  return it->second;
}

void WGraph::addEdge (vdata begin, vdata end, int weight, bool directed = false) {
  Vertex* a = getVertex (begin);
  Vertex* b = getVertex (end);
  a->adj.push_back (make_pair (b, weight));
  if (!directed)
    b->adj.push_back (make_pair (a, weight));
}

void WGraph::dijkstra(vdata begin, int dist[800]) {
  set< pair<int,vdata> > q;

  for (int i = 0, sz = allVertexes.size(); i < sz; i++) {
    dist[allVertexes[i]->id] = INF;
  }
  
  dist[begin] = 0;
  q.insert(make_pair(dist[begin], begin));
  while (!q.empty()) {
    vdata v = q.begin()->second;
    q.erase(q.begin());

    Vertex* node = getVertex(v);

    for (int i = 0, sz = node->adj.size(); i < sz; i++) {
      vdata to = node->adj[i].first->id;
      unsigned int len = node->adj[i].second;

      if (dist[v] + len < dist[to]) {
        q.erase(make_pair(dist[to], to));
        dist[to] = dist[v] + len;
        q.insert(make_pair(dist[to], to));
      }
    }
  }
}

int main(void)
{
  int n, p, c;
  int a, b, v, cow_position;
  WGraph g;
  vector<int> cows;
  //map<vdata, unsigned int> m[500];
  int m[500][800];

  ofstream fout("butter.out");
  ifstream fin("butter.in");

  fin >> n >> p >> c;

  for (int i = 0; i < p; i++) {
    g.addVertex(i);
  }

  for (int i = 0; i < n; i++) {
    fin >> cow_position;
    cows.push_back(cow_position-1);
  }

  while (c--) {
    fin >> a >> b >> v;
    g.addEdge(a-1, b-1, v);
  }

  unsigned int result = INF;

  for (int i = 0; i < n; i++) {
    g.dijkstra(cows[i], m[i]);
  }

  for (int i = 0; i < p; i++) {
    unsigned int dist = 0;
    for (int j = 0; j < n; j++) {
      dist += m[j][i];
    }
    result = min(result, dist);
  }

  fout << result << endl;
  
  return 0;
}
