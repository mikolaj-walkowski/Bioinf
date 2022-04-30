#pragma once

#include "graph.h"
#include <limits.h>

struct Sequence
{
    vector<int> val = vector<int>();
    int score=INT_MIN;
    int len;
    int cov;
};
enum Operation{
    MUTATE,
    GROW,
    CROSS,
    CONNECT,
    INSERT
};

using namespace std;

class Generation{
public:
    vector<Sequence> oldSequences;
    vector<Sequence> sequences;

    Graph* graph;

    int maxSize = 1000;
    int opWeights[5]={4,1,0,0,0};
    int opTotalWeight=5;
    vector<Operation> opHelper={MUTATE,GROW,CROSS,CONNECT,INSERT};

    Generation(Graph*);

    void score(Sequence& s);
    void combine(const Sequence& a,const Sequence& b);
    void mutate(const Sequence& a);
    void grow(vector<int>& s);
    void showResults();
    void step();

};