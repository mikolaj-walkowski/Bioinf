#include <iostream>
<<<<<<< Updated upstream
#include <fstream> 
=======
#include <fstream>
#include <string.h>
>>>>>>> Stashed changes
#include "graph.h"
#include "genetic.h"
#include <chrono>

void printvec(const vector<int> a)
{
    for (int i = 0; i < a.size(); i++)
    {
        cout << a[i] << " ";
    }
    cout << "\n";
}

<<<<<<< Updated upstream
int main(int, char**) {
    Graph g("../data/9.200-80.txt");
    g.length = 209; //TODO hardcoded
    
    Generation gen(&g);

    for (int i = 0; i < 500; i++)
    {
        if(i < 99){
            std::cout<<"Gen: "<< i << " \tlen: "<< gen.population[0].len<<" \tcov: " << gen.population[0].cov <<" \tdensity: "<<gen.population[0].density << " \tscore:  " << gen.population[0].score<< '\n' ;  
            // printvec(gen.population[0].val);
        }
        if(i%100 == 99){
            std::cout<<"Gen: "<< i << " len: "<< gen.population[0].len<<" cov: " << gen.population[0].cov <<" density: "<<gen.population[0].density << " score:  " << gen.population[0].score<< '\n' ;  
            // printvec(gen.population[0].val);
        }
=======
int main(int argc, char **argv)
{

    char *filename = argv[1];
    int maxTime = stoi(argv[2]);

    Graph g(filename);
    int len = strlen(filename);
    char *numStart = strchr(strchr(filename, '/'), '.') + 1;

    numStart[3] = '\0';
    g.length = atoi(numStart) + 9;

    // cout << g.length << "num\n";

    Generation gen(&g);

    float lastScore = 0;
    int counter = 150;

    auto start = chrono::high_resolution_clock::now();
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    for (int i = 0; i < 3000; i++)
    {
        // std::cout << "Gen: " << i << " \tlen: " << gen.population[0].len << " \tcov: " << gen.population[0].cov << " \tdensity: " << gen.population[0].density << " \tscore:  " << gen.population[0].score << "\tAditional: " << gen.maxInsertCtr - gen.insertCtr << '\n';
>>>>>>> Stashed changes
        gen.step();
        stop = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
        if (duration.count() > maxTime)
            break;
    }
    gen.showResults();
<<<<<<< Updated upstream
    //g.printPath(gen.population[0].val);
=======
    // g.printPath(gen.population[0].val);
    // cout << "Total Searches: " << gen.set.size() << '\n';
    cout << "Total Searches: " << gen.set.size() << "\tElapsed time: " << duration.count() << "ms" << '\n';
>>>>>>> Stashed changes
    return 0;
}
