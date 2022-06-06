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
    g.length = 209; //TODO hardcoded
    Generation gen(&g);
    float lastScore =0;
    int counter = 50;

    for (int i = 0; i < 1000; i++)
    {
        if(i < 99){
            std::cout<<"Gen: "<< i << " \tlen: "<< gen.population[0].len<<" \tcov: " << gen.population[0].cov <<" \tdensity: "<<gen.population[0].density << " \tscore:  " << gen.population[0].score<< '\n' ;  
            // printvec(gen.population[0].val);
        }
        if(i%100 == 99){
            std::cout<<"Gen: "<< i << " len: "<< gen.population[0].len<<" cov: " << gen.population[0].cov <<" density: "<<gen.population[0].density << " score:  " << gen.population[0].score<< '\n' ;  
            // printvec(gen.population[0].val);
        }
        gen.step();
        
        if(lastScore == gen.population[0].score){
            if(--counter <=0){
                break;
            }
        }else{
            lastScore = gen.population[0].score;
            counter=150;
        }
    }
    gen.showResults();
    //g.printPath(gen.population[0].val);
    return 0;
}
