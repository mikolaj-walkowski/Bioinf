#include "genetic.h"
void printvec(const vector<int> a){
    for (int i = 0; i < a.size(); i++)
    {
        cout<<a[i]<<" ";
    }
    cout<<"\n";
}
Generation::Generation(Graph *a) : graph(a)
{
    for (int i = 0; i < 100; i++)
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
        sequences.push_back(s);
        //printvec(s.val);
    }
}

void Generation::score(Sequence &s)
{
    int wL = graph->wordLength(s.val);
    //int len = graph->length - wL > 0 ? wL - graph->length : graph->length - wL;
    int len = abs(graph->length - wL)*-1;
    s.len = len;
    //len*=len*-1;
    //len*=10;
    int cov = s.val.size() - graph->size;
    s.cov = cov;
    //cov*=10;
    s.score = (((float)s.val.size())/((float)wL))*400 + cov + len;
}

void Generation::grow(vector<int>& core){
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
        if (find(core.begin(),core.end(), Con[e]) == core.end())
        {
            seq.val.push_back(Con[e]);
        }
        
        if(seq.val.size() > 2 ){
        score(seq);
        sequences.push_back(seq);
        }
        //printvec(seq.val);
}
void Generation::mutate(const Sequence& s)
{
    int i = (rand() % (s.val.size()- 2))+ 1;
    vector<int> core1(s.val.begin(),s.val.begin()+i);
    vector<int> core2(s.val.begin() + i,s.val.end());
    
    Sequence s1, s2;
    
    s1.val = core1;
    s2.val = core2;
    
    score(s1);
    score(s2);

    sequences.push_back(s1);
    sequences.push_back(s2);

    //grow(core1);
    //grow(core2);
}

void Generation::combine(const Sequence &a, const Sequence &b)
{
}

bool SeqCmp(const Sequence &a, const Sequence &b)
{
    return a.score > b.score;
}

void Generation::step()
{
    int size = sequences.size();
    oldSequences = sequences;

    while (sequences.size()<maxSize)
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
            int i = rand()%oldSequences.size();
            mutate(oldSequences[i]);
            break;
        }   
        case GROW:{
            int i = rand()%oldSequences.size();
            grow(oldSequences[i].val);
            break;
        }   
        case CROSS:{
            //TODO
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
    
    sort(sequences.begin(), sequences.end(), SeqCmp);
    sequences = vector<Sequence>(sequences.begin(), sequences.begin() + 100);
}
void Generation::showResults(){
    for (int i = 0; i < sequences.size() && i < 20; i++)
    {
        cout<<"Rank: "<<i+1<<" \tLen: "<< sequences[i].len << "\tCov: "<< sequences[i].cov<<"\tScore: "<< sequences[i].score<<"\n";
    }
}
