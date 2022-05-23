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
    // vector<Sequence> oldSequences;
    // vector<Sequence> sequences;

    Graph* graph;

    int opWeights[5]={7,2,0,0,0};
    int opTotalWeight=0;

    int maxSize = 5000;
    int population_size = 0;
    int population_culled = 200;
    Sequence population[5005];

    vector<Operation> opHelper={MUTATE,GROW,CROSS,CONNECT,INSERT};

    Generation(Graph*);

    void score(Sequence& s);
    void combine(const Sequence& a,const Sequence& b);
    void mutate(const Sequence& a);
    void grow(const vector<int>& s);
    void connect(const Sequence& a,const Sequence& b);

    // void erase(Sequence&); 
    void addSeq(Sequence);
    void showResults();
    void step();

};