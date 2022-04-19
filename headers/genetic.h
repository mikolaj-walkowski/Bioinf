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


using namespace std;

class Generation{
public:
    vector<Sequence> sequences;
    Graph* graph;

    Generation(Graph*);

    void score(Sequence& s);
    void combine(const Sequence& a,const Sequence& b);
    void mutate(const Sequence& a);
    void grow(vector<int>& s);
    void showResults();
    void step();

};