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
    Graph g(argv[1]);
    int len = strlen(argv[1]);
    char* numStart = strchr(strchr(argv[1],'/'),'.') + 1;
    cout<< numStart <<'\n';
    numStart[3] = '\0';
    g.length = atoi(numStart)+ 9; 
    
    cout << g.length <<"num\n";

    Generation gen(&g);
    float lastScore =0;
    int counter = 150;

    for (int i = 0; i < 1000; i++)
    {
        std::cout<<"Gen: "<< i << " \tlen: "<< gen.population[0].len<<" \tcov: " << gen.population[0].cov <<" \tdensity: "<<gen.population[0].density << " \tscore:  " << gen.population[0].score<< '\n' ;  
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
    cout<< "Total Searches: "<< gen.set.size() << '\n';
    return 0;
}
