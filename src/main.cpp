#include <iostream>
#include <fstream> 
#include "graph.h"
#include "genetic.h"

void printvec(const vector<int> a){
    for (int i = 0; i < a.size(); i++)
    {
        cout<<a[i]<<" ";
    }
    cout<<"\n";
}

int main(int, char**) {
    Graph g("../data/9.200-80.txt");
    g.length = 200;
    
    Generation gen(&g);

    for (int i = 0; i < 500; i++)
    {
        // if(i < 99){
        //     std::cout<<"Gen: "<< i << " \tlen: "<< gen.population[0].len<<" \tcov: " << gen.population[0].cov <<" \tdensity: "<<gen.population[0].density << " \tscore:  " << gen.population[0].score<< '\n' ;  
        //     // printvec(gen.population[0].val);
        // }
        if(i%100 == 99){
            std::cout<<"Gen: "<< i << " len: "<< gen.population[0].len<<" cov: " << gen.population[0].cov <<" density: "<<gen.population[0].density << " score:  " << gen.population[0].score<< '\n' ;  
            // printvec(gen.population[0].val);
        }
        gen.step();
    }
    gen.showResults();
    //g.printPath(gen.sequences[0].val);
    return 0;
}
