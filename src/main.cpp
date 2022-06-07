#include <iostream>
#include <fstream> 
#include <string.h>
#include "graph.h"
#include "genetic.h"

void printvec(const vector<int> a){
    for (int i = 0; i < a.size(); i++)
    {
        cout<<a[i]<<" ";
    }
    cout<<"\n";
}

int main(int argc, char** argv) {

    char* filename = argv[1];
    
    Graph g(filename);
   
    Generation gen(&g);
    
    float lastScore =0;
    int counter = 150;

    for (int i = 0; i < 2300; i++)
    {
        std::cout<<"Gen: "<< i << " \tlen: "<< gen.population[0].len<<" \tcov: " << gen.population[0].cov <<" \tdensity: "<<gen.population[0].density << " \tscore:  " << gen.population[0].score<< '\n' ;  
        gen.step();
    }
    gen.showResults();
    //g.printPath(gen.population[0].val);
    cout<< "Total Searches: "<< gen.set.size() << '\n';
    return 0;
}
