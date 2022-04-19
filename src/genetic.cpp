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
    int len =graph->length - wL;
    s.len = len;
    len*=len*-1;
    //len*=10;
    int cov = s.val.size() - graph->size;
    s.cov = cov;
    cov*=cov*-1;
    s.score = cov + len;
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
    grow(core1);
    grow(core2);
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
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            grow(sequences[i].val);
            mutate(sequences[i]);
        }
    }
    sort(sequences.begin(), sequences.end(), SeqCmp);
    // for (int i = 0; i < 10; i++)
    // {
    //     cout << "Seq " << i + 1 << ": Score: " << sequences[i].score << "\n";
    // }
    sequences = vector<Sequence>(sequences.begin(), sequences.begin() + 10);
}
void Generation::showResults(){
    for (int i = 0; i < sequences.size(); i++)
    {
        cout<<"Rank: "<<i<<"\tLen: "<< sequences[i].len << "\tCov: "<< sequences[i].cov<<"\n";
    }
}
