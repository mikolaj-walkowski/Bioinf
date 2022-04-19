#include <iostream>
#include <fstream> 
#include "graph.h"
#include "genetic.h"

int main(int, char**) {
    Graph g("../data/9.200-40.txt");
    g.length = 200;
    
    Generation gen(&g);

    for (int i = 0; i < 500; i++)
    {
        gen.step();
    }
    gen.showResults();
    return 0;
}
