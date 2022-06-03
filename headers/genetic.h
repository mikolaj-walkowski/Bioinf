#pragma once

#include "graph.h"
#include <limits.h>

using namespace std;

class Sequence
{
    public:
    vector<int> val;
    float score;
    float len;
    float cov;
    float density;
};

enum Operation{
    MUTATE,
    GROW,
    CROSS,
    CONNECT,
    INSERT
};

class Generation{
public:
    /* d,cov,len,bonus*/
    float goodPreset[4] = {6.5625,3,0.55,0.15};
    //Parameters
    float* scoringWeights = goodPreset;
    int maxSize = 5000; //
    int population_culled = 300;
    Sequence population[5005]; // At least maxSize + 2
    int opWeights[5]={4,2,2,2,0};

    int opTotalWeight=0;
    int population_size = 0;
    vector<Operation> opHelper={MUTATE,GROW,CROSS,CONNECT,INSERT};

    Graph* graph;
    Generation(Graph*);

    void score(Sequence& s);
    void combine(const Sequence& a,const Sequence& b);
    void mutate(const Sequence& a);
    void grow(const vector<int>& s);
    void connect(const Sequence& a,const Sequence& b);
    void cross(const Sequence&a , const Sequence& b);
    
    void addSeq(Sequence);
    void showResults();
    void step();

};