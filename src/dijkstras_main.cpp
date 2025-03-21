#include "dijkstras.h"
#include <iostream>

int main() {
    Graph G;
    file_to_graph("src/small.txt", G);

    int source = 0;
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, source, previous);

    int destination = 3;
    vector<int> path = extract_shortest_path(distances, previous, destination);

    print_path(path, distances[destination]);


    return 0;
}