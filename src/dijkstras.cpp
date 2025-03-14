#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>
#include <cassert>

#include "dijkstras.h"
using namespace std;


vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.size();
    vector<int> distance(n, INF);
    previous.assign(n, -1);
    vector<bool> visited(n, false);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pQ;
    distance[source] = 0;
    pQ.push({0, source});

    while (!pQ.empty()) {
        // cout << "pq size: " << pQ.size() << endl;
        int u = pQ.top().second;
        pQ.pop();
        // cout << u << endl;
        if (visited[u]) {
            continue;
        }
        visited[u] = true;
        
        for (const Edge& e : G[u]) {
            int v = e.dst;
            int weight = e.weight;

            // cout << v << " " << weight << endl;
            if (distance[u] + weight < distance[v]) {
                // cout << "HIT" << endl;
                distance[v] = distance[u] + weight;
                previous[v] = u;
                pQ.push({distance[v], v});
            }
        }
    }
    return distance;
}
vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> shortest;
    for (int v = destination; v != -1; v = previous[v]) {
        shortest.push_back(v);
    }
    vector<int> revShortest;
    for (int i = shortest.size() - 1; i >= 0; --i) {
        revShortest.push_back(shortest[i]);
    }
    return revShortest;
}
void print_path(const vector<int>& v, int total) {
    for (int vx : v) {
        cout << vx << " ";
    }
    cout << endl;
    cout << "Total cost is " << total << endl;
}
