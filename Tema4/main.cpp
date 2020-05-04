#include <iostream>
#include "graph.hpp"

using namespace std;

int main() {
    DirectedGraph<int> g({1, 2, 3, 4, 5, 6}, {
        {1, 2},
        {1, 4},
        {3, 5},
        {5, 3},
        {0, 1},
        {0, 5},
    });

    g.BFSPrint(0, cout);
    g.DFSPrint(0, cout);
    cout << g.hasEdge(1, 2) << " " << g.hasEdge(0, 3) << endl;
    cout << g.twoCycles() << endl;

    return 0;
}