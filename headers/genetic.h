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

template <typename T>
T modpow(T base, T exp, T modulus) {
  base %= modulus;
  T result = 1;
  while (exp > 0) {
    if (exp & 1) result = (result * base) % modulus;
    base = (base * base) % modulus;
    exp >>= 1;
  }
  return result;
}

class SequenceHash
{
    unsigned long mod = 100000000000;
    
public:
    size_t operator()(const Sequence& s) const
    {
        size_t hash = 0; 
        for (unsigned long i = 0; i < s.val.size(); i++)
        {
            hash += modpow((unsigned long)s.val[i],i*10, mod);
            hash %= mod;
        }
        hash *= s.score;
        hash %= mod;
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
    float testPreset[4] = {3,4,0.9,0.15};

    //Parameters
    float* scoringWeights = betterPreset;//testPreset;//goodPreset;
    int maxSize = 2000; //
    int population_culled = 500;
    Sequence population[5005]; // At least maxSize + 2
    int opWeights[4]={70,20,50,20};

    int opTotalWeight=0;
    int population_size = 0;

    int maxInsertCtr = 50;
    int insertCtr = maxInsertCtr;

    vector<Operation> opHelper={MUTATE,GROW,CROSS,CONNECT};

    unordered_set<Sequence,SequenceHash> set;
    Graph* graph;
    Generation(Graph*);

    void score(Sequence& s);
    void mutate(const Sequence& a);
    void grow(const vector<int>& s);
    void connect(const Sequence& a,const Sequence& b);
    void cross(const Sequence&a , const Sequence& b);
    void insert();
    
    void addSeq(Sequence);
    void showResults();
    void step();

};