#include <iostream>
#include <fstream> 
#include "headers/graph.h"

int main(int, char**) {
    Graph g("../data/18.200-40.txt");
    //g.printMatrix();
    g.printPath(g.longestP());

    return 0;
}
