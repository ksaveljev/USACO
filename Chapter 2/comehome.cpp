/*
ID: faorien2
PROG: comehome
LANG: C++
 */
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
using namespace std;

typedef char vdata;

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
    pair<vdata,int> dijkstra (vdata start);
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

pair<char,int> WGraph::dijkstra (vdata start) {
  int MAXIMUM = 2000000000;
  Vertex* v;
  pair<vdata,int> result;
  int dist; // best current distance from start
  vdata current_vertex; // current vertex id to process
  map<vdata,int> distance; // distance from source to all other vertexes
  map<vdata,bool> visited; // list of visited vertexes

  current_vertex = start;

  for (int i = 0, sz = allVertexes.size(); i < sz; i++) {
    // currently all distances from source to all other vertixes is uknown
    distance[allVertexes[i]->id] = MAXIMUM;
    // none of the vertexes has been visited yet
    visited[allVertexes[i]->id] = false;
  }

  distance[start] = 0; // distance from source to source

  while (visited[current_vertex] == false) {
    // visit vertex
    visited[current_vertex] = true;
    v = getVertex(current_vertex);

    // for every single vertex we have an edge with
    for (int i = 0, sz = v->adj.size(); i < sz; i++) {
      if (distance[v->adj[i].first->id] > (distance[current_vertex] + v->adj[i].second)) {
        distance[v->adj[i].first->id] = distance[current_vertex] + v->adj[i].second;
      }   
    }   

    dist = MAXIMUM;
    current_vertex = start;
    for (int i = 0, sz = allVertexes.size(); i < sz; i++) {
      if (visited[allVertexes[i]->id] == false && dist > distance[allVertexes[i]->id]) {
        dist = distance[allVertexes[i]->id];
        current_vertex = allVertexes[i]->id;
      }   
    }   
  }

  result.second = MAXIMUM;
  for (char c = 'A'; c < 'Z'; c++) {
    if (distance.find(c) == distance.end())
      continue;

    if (distance[c] < result.second) {
      result.first = c;
      result.second = distance[c];
    }
  }

  return result;
}

int main() {
  int p;
  WGraph g;
  char start, end;
  int weight;

  ofstream fout("comehome.out");
  ifstream fin("comehome.in");

  fin >> p;

  for (int i = 0; i < p; i++) {
    fin >> start >> end >> weight;
    g.addEdge(start, end, weight);
  }

  pair<char,int> result = g.dijkstra('Z');

  fout << result.first << " " << result.second << endl;

  return 0;
}
