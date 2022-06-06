#pragma once
#include "graph.h"
#include <limits.h>
#include <unordered_set>

using namespace std;

class Sequence
{
    public:
    vector<int> val;
    float score;
    float len;
    float cov;
    float density;
    bool operator==(const Sequence& s) const{
        return this->val == s.val;
    }
};

class SequenceHash
{
public:
    size_t operator()(const Sequence& s) const
    {
        size_t hash = 0; 
        for (int i = 0; i < s.val.size(); i++)
        {
            hash += s.val[i] % 100000;
        }
        hash *= s.score;
        hash %= 100000;
        return hash;
    }
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
    float goodPreset[4] = {6.5625,3.1995,0.55,0.15};
    float betterPreset[4] = {6.5625,3.1995,0.55,0.25};
    float testPreset[4] = {0.f,3.f,1.f,0.f};

    //Parameters
    float* scoringWeights = testPreset;//goodPreset;
    int maxSize = 2000; //
    int population_culled = 500;
    Sequence population[5005]; // At least maxSize + 2
    int opWeights[5]={70,10,50,10,0};

    int opTotalWeight=0;
    int population_size = 0;

    vector<Operation> opHelper={MUTATE,GROW,CROSS,CONNECT,INSERT};

    unordered_set<Sequence,SequenceHash> set;
    Graph* graph;
    Generation(Graph*);

    void score(Sequence& s);
    void combine(const Sequence& a,const Sequence& b);
    void mutate(const Sequence& a);
    void grow(const vector<int>& s);
    void connect(const Sequence& a,const Sequence& b);
    void cross(const Sequence&a , const Sequence& b);
    void insert();
    
    void addSeq(Sequence);
    void showResults();
    void step();

};