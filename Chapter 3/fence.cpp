/*
ID: faorien2
PROG: fence
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> result;
vector<int> graph[500];

int find_starting_point() {
    int starting_point = -1;

    for (int i = 0; i < 500; i++) {
        if (graph[i].empty())
            continue;

        if (graph[i].size() % 2 == 0) {
            if (starting_point == -1)
                starting_point = i;
        } else {
            starting_point = i;
            break;
        }
    }

    return starting_point;
}

void find_path(int node) {
    if (graph[node].empty()) {
        result.push_back(node+1);
        return;
    }

    while (true) {
        if (graph[node].empty()) {
            result.push_back(node+1);
            return;
        }

        int neighbor = graph[node][0];
        vector<int>::iterator it = find(graph[neighbor].begin(), graph[neighbor].end(), node);
        graph[neighbor].erase(it);
        graph[node].erase(graph[node].begin());
        find_path(neighbor);
    }
}

bool should_print_reverse() {
    for (int i = 0, sz = result.size(); i < sz; i++) {
        if (result[i] < result[sz-1-i])
            return false;
        else if (result[i] > result[sz-1-i])
            return true;
    }

    return false;
}

int main() {
    int number_of_fences, a, b;
    ofstream fout("fence.out");
    ifstream fin("fence.in");

    fin >> number_of_fences;

    while (number_of_fences--) {
        fin >> a >> b;
        a--, b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for (int i = 0; i < 500; i++) {
        sort(graph[i].begin(), graph[i].end());
    }

    int start = find_starting_point();
    find_path(start);

    if (should_print_reverse()) {
        for (int i = result.size() - 1; i >= 0; i--)
            fout << result[i] << endl;
    } else {
        for (int i = 0, sz = result.size(); i < sz; i++)
            fout << result[i] << endl;
    }

    return 0;
}
