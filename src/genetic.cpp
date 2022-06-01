#include "genetic.h"
#include <set>
#include <limits>


float epsilon = 0;

// void printvec(const vector<int> a){
//     for (int i = 0; i < a.size(); i++)
//     {
//         cout<<a[i]<<" ";
//     }
//     cout<<"\n";
// }

Generation::Generation(Graph *a) : graph(a)
{
    epsilon = ((float)a->names[0].length())/((float)a->length);
    for (int i = 0; i < opHelper.size(); i++)
    {
        opTotalWeight+= opWeights[i];
    }
    
    for (int i = 0; i < population_culled; i++)
    {
        Sequence s;
        int j = rand();
        do
        {
            j = (j + 1) % graph->size;
        } while (graph->aList[j].size() == 0 && graph->aListRev[j].size() == 0 );
        
        int l = rand() % graph->aListRev[j].size();
        s.val.push_back(graph->aListRev[j][l]);

        s.val.push_back(j);

        int k = rand() % graph->aList[j].size();
        s.val.push_back(graph->aList[j][k]);

        score(s);
        addSeq(s);
    }
}

bool validate(const vector<int>& a){
    set<int> b(a.begin(),a.end());
    return a.size()==b.size();
}

void Generation::connect(const Sequence& a, const Sequence& b){
    
}

void Generation::score(Sequence &s)
{
    float wL = graph->wordLength(s.val);
    //int len = graph->length - wL > 0 ? wL - graph->length : graph->length - wL;
    
    // if(wL > graph->length + 10) {s.cov = numeric_limits<float>::lowest(); s.density = numeric_limits<float>::lowest(); s.len=numeric_limits<float>::lowest();s.score=numeric_limits<float>::lowest();return;}
    // dla idealnej 1 
    float len = (-1.f/((float)graph->length))*abs(wL-graph->length) + 1.f;
    s.len = len;

    float cov = ((float)s.val.size())/120.f;//(float)this->graph->size);
    s.cov = cov;

    float d = (((float)s.val.size())/wL);
    s.density = d;

    int bonus = abs(wL - graph->length ) <= 10 ? 1 : 0;
    
    s.score = cov + d + bonus;//d + 4*cov + len + bonus*2;
}

void Generation::grow(const vector<int>& core){
        auto Con = graph->aListRev[core[0]];
        int e = rand() % Con.size();
        Sequence seq;
        if (find(core.begin(),core.end(), Con[e]) == core.end())
        {
            seq.val.push_back(Con[e]);
        }
        seq.val.insert(seq.val.end(), core.begin(),core.end());
        
        Con = graph->aList[core[core.size()-1]];

        e = rand() % Con.size();

        if (find(seq.val.begin(),seq.val.end(), Con[e]) == seq.val.end())
        {
            seq.val.push_back(Con[e]);
        }
        
        if(seq.val.size() > 2 ){
        score(seq);
        addSeq(seq);
        }
}
void Generation::mutate(const Sequence& s)
{
    if(s.val.size()<3)
        return;
    int i = (rand() % (s.val.size()- 2))+ 1;
    vector<int> core1(s.val.begin(),s.val.begin()+i);
    vector<int> core2(s.val.begin() + i,s.val.end());
    
    Sequence s1, s2;
    
    s1.val = core1;
    s2.val = core2;
    
    score(s1);
    score(s2);

    addSeq(s1);
    addSeq(s2);
}

void Generation::combine(const Sequence &a, const Sequence &b)
{
    for (int i = 0; i < a.len; i++)
    {
    }
    
}

bool SeqCmp(const Sequence &a, const Sequence &b)
{
    // if (abs(a.len - b.len) <= 10 ){
    //     return a.cov> b.cov;
    // }

    // return a.cov + a.len/a.len +b.len*3 > b.cov/b.len + b.len*3;
    return a.score > b.score; 
}

bool isConnected(int a) {
    return a > 0;
}

void Generation::cross(const Sequence& a, const Sequence& b) {
    int aRandPos = rand()%a.val.size();
    unsigned int rand_n1 = a.val[aRandPos];
    std::vector<int> availableVertex = this->graph->aMatrix[rand_n1];
    std::vector<int>::iterator iter = availableVertex.begin();

    std::vector<int> legalConnections = {};

    while ((iter = std::find_if(iter, availableVertex.end(), isConnected)) != availableVertex.end())
    {
        legalConnections.push_back(iter - availableVertex.begin());
        iter++;
    }

    std::vector<int> availableConnections(legalConnections.size() + b.val.size(), -1);
    set_intersection(legalConnections.begin(), legalConnections.end(), b.val.begin(), b.val.end(), availableConnections.begin());
    availableConnections.erase(remove(availableConnections.begin(), availableConnections.end(), -1), availableConnections.end());

    if(availableConnections.size() == 0) return;

    unsigned int chosenOne = availableConnections[rand()%availableConnections.size()];

    std::vector<int> combined(aRandPos);
    copy(a.val.begin(), a.val.begin() + aRandPos, combined.begin());
    combined.insert(combined.end(), find(b.val.begin(), b.val.end(), chosenOne), b.val.end());
    
    Sequence newSeq;

    newSeq.val = combined;
    
    score(newSeq);

    this->addSeq(newSeq);

    return;
};

void Generation::step()
{

    while (population_size < maxSize)
    {
        int operation = rand()%opTotalWeight;
        int currSum=0;
        
        Operation e;

        for (int i = 0; i < opHelper.size(); i++)
        {
            currSum+= opWeights[opHelper[i]];
            if(operation < currSum){
                e = opHelper[i];
                break;
            }
        }
        switch (e)
        {
        case MUTATE:{
            int i = rand()%population_culled;
            mutate(population[i]);
            break;
        }   
        case GROW:{
            int i = rand()%population_culled;
            grow(population[i].val);
            break;
        }   
        case CROSS:{
            int a = rand()%population_culled, b;
            do {
                b = rand()%population_culled;
            }while(b == a);

            cross(population[a], population[b]);
            break;
        }   
        case CONNECT:{
            //TODO
            break;
        }   
        case INSERT:{
            //TODO
            break;
        }   
        default:{
            break;
        }   
        }
        
    }
    
    std::sort(population, population+population_size, SeqCmp);
    population_size=population_culled;
}
void Generation::showResults(){
    for (int i = 0; i < population_size && i < 20; i++)
    {
        cout<<"Rank: "<<i+1<<" \tLen: "<< population[i].len << "\tCov: "<< population[i].cov<<"\tScore: "<< population[i].score<<"\n";
    }
}

void Generation::addSeq(Sequence a){
    population[population_size++]  = a;
}
