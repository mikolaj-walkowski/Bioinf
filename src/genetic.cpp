#include "genetic.h"
#include <map>
#include <limits>
#include <random>

float epsilon = 0;

// void printvec(const vector<int> a){
//     for (int i = 0; i < a.size(); i++)
//     {
//         cout<<a[i]<<" ";
//     }
//     cout<<"\n";
// }

bool SeqCmp(const Sequence &a, const Sequence &b)
{
    return a.score > b.score;
}

string GenerateRandomSequence(unsigned int len = 10)
{
    std::random_device rng;
    std::mt19937 gen(rng());
    char letters[4] = {'A', 'C', 'T', 'G'};
    std::uniform_int_distribution<> distr(0, 3);

    string sequence = "";
    for (int i = 0; i < len; ++i)
    {
        sequence += letters[distr(gen)];
    }

    return sequence;
}

template <typename Iterator>
bool has_duplicates(Iterator first, Iterator last)
{
    std::map<typename std::iterator_traits<Iterator>::value_type, std::size_t> histogram;

    while (first != last)
        if (++histogram[*first++] > 1)
            return true;

    return false;
}

Generation::Generation(Graph *a) : graph(a)
{
    epsilon = ((float)a->word) / ((float)a->length);
    for (int i = 0; i < opHelper.size(); i++)
    {
        opTotalWeight += opWeights[i];
    }

    for (int i = 0; i < population_culled; i++)
    {
        Sequence s;
        int j = rand();
        do
        {
            j = (j + 1) % ((int)graph->size);
        } while (graph->aList[j].size() == 0 && graph->aListRev[j].size() == 0);

        int l = rand() % graph->aListRev[j].size();
        s.val.push_back(graph->aListRev[j][l]);

        s.val.push_back(j);

        int k = rand() % graph->aList[j].size();
        s.val.push_back(graph->aList[j][k]);

        score(s);
        population[population_size++] = s;
    }
    set = unordered_set<Sequence, SequenceHash>(population, population + population_culled);

    for (int i = graph->size; i < graph->extras; i++)
    {
        string word;
        do
        {
            word = GenerateRandomSequence(graph->word);
        } while (!graph->uniqueNames.insert(word).second);

        graph->names.push_back(word);

        for (int j = 0; j < graph->names.size(); j++)
        {
            if (i != j)
            {
                int over = graph->overlap(graph->names[i], graph->names[j]);
                if (over != -1)
                {
                    graph->aMatrix[i][j] = over;
                }
                over = graph->overlap(graph->names[j], graph->names[i]);
                if (over != -1)
                {
                    graph->aMatrix[j][i] = over;
                }
            }
        }

        graph->aList[i].clear();
        graph->aListRev[i].clear();

        for (int j = 0; j < graph->names.size(); j++)
        {
            if (graph->aMatrix[i][j] != 0)
            {
                graph->aList[i].push_back(j);
            }
            if (graph->aMatrix[j][i] != 0)
            {
                graph->aListRev[i].push_back(j);
            }
            auto it = find(graph->aList[j].begin(), graph->aList[j].end(), i);
            if(it!=graph->aList[j].end()){
                graph->aList[j].erase(it);
            }
            it = find(graph->aListRev[j].begin(), graph->aListRev[j].end(), i);
            if (it != graph->aListRev[j].end())
            {
                graph->aListRev[j].erase(it);   
            }
        
            if (graph->aMatrix[i][j] != 0)
            {
                graph->aListRev[j].push_back(i);
            }
            if (graph->aMatrix[j][i] != 0)
            {
                graph->aList[j].push_back(i);
            }
        }
    }
}

void Generation::score(Sequence &s)
{
    float wL = graph->wordLength(s.val);

    float len = (1.f / ((float)graph->length)) * wL;
    len = len <= 1 ? len : 0;
    s.len = len;

    float cov = ((float)s.val.size()) / graph->size;
    s.cov = cov;

    float d = (((float)s.val.size()) / wL);
    s.density = d;

    int bonus = wL - graph->length <= graph->word && wL - graph->length > 0 ? 1 : 0;

    s.score = scoringWeights[0] * d + scoringWeights[1] * cov + scoringWeights[2] * len + scoringWeights[3] * bonus;
}

void Generation::grow(const vector<int> &core)
{
    auto Con = graph->aListRev[core[0]];
    int e = rand() % Con.size();
    Sequence seq;
    if (find(core.begin(), core.end(), Con[e]) == core.end())
    {
        seq.val.push_back(Con[e]);
    }
    seq.val.insert(seq.val.end(), core.begin(), core.end());

    Con = graph->aList[core[core.size() - 1]];

    e = rand() % Con.size();

    if (find(seq.val.begin(), seq.val.end(), Con[e]) == seq.val.end())
    {
        seq.val.push_back(Con[e]);
    }

    if (seq.val.size() > 2)
    {
        addSeq(seq);
    }
}

void Generation::mutate(const Sequence &s)
{
    if (s.val.size() < 3)
        return;
    int i = (rand() % (s.val.size() - 2)) + 1;
    vector<int> core1(s.val.begin(), s.val.begin() + i);
    vector<int> core2(s.val.begin() + i, s.val.end());

    Sequence s1, s2;

    s1.val = core1;
    s2.val = core2;

    addSeq(s1);
    addSeq(s2);
}

void Generation::connect(const Sequence &a, const Sequence &b)
{
    auto i = a.val.begin();
    for (; i != a.val.end(); i++)
    {
        if (equal(i, a.val.end(), b.val.begin()))
        {
            vector<int> core(i, a.val.end());
            core.insert(core.end(), b.val.begin(), b.val.begin() + core.size());
            if (has_duplicates(core.begin(), core.end()))
            {
                continue;
            }
            else
            {
                Sequence newSeq;
                newSeq.val = core;
                addSeq(newSeq);
                break;
            }
        }
    }

    i = b.val.begin();

    for (; i != b.val.end(); i++)
    {
        if (equal(i, b.val.end(), a.val.begin()))
        {
            vector<int> core(i, b.val.end());
            core.insert(core.end(), a.val.begin(), a.val.begin() + core.size());
            if (has_duplicates(core.begin(), core.end()))
            {
                continue;
            }
            else
            {
                Sequence newSeq;
                newSeq.val = core;
                addSeq(newSeq);
                break;
            }
        }
    }
}

void Generation::cross(const Sequence &a, const Sequence &b)
{
    int aRandPos = rand() % a.val.size();
    unsigned int rand_n1 = a.val[aRandPos];
    std::vector<int> legalConnections = this->graph->aList[rand_n1];

    std::vector<int> availableConnections(legalConnections.size() + b.val.size(), -1);

    set_intersection(legalConnections.begin(), legalConnections.end(), b.val.begin(), b.val.end(), availableConnections.begin());
    availableConnections.erase(remove(availableConnections.begin(), availableConnections.end(), -1), availableConnections.end());

    if (availableConnections.size() == 0)
        return;

    unsigned int chosenOne = availableConnections[rand() % availableConnections.size()];

    std::vector<int> combined(aRandPos);
    copy(a.val.begin(), a.val.begin() + aRandPos, combined.begin());
    combined.insert(combined.end(), find(b.val.begin(), b.val.end(), chosenOne), b.val.end());

    if (has_duplicates(combined.begin(), combined.end()))
        return;

    Sequence newSeq;

    newSeq.val = combined;

    this->addSeq(newSeq);

    return;
};


void Generation::insert()
{
    fill(graph->extrasCount.begin(), graph->extrasCount.end(), 0);

    for (int j = 0; j < population_culled; j++)
    {
        for (int k = 0; k < population[j].val.size(); k++)
        {
            if (population[j].val[k] >= graph->size)
            {
                graph->extrasCount[population[j].val[k] - graph->size]++;
            }
        }
    }
    for (int i = graph->size; i < graph->extras; i++)
    {
        if (graph->extrasCount[i - graph->size] == 0)
        {
            string word;
            do
            {
                word = GenerateRandomSequence(graph->word);
            } while (!graph->uniqueNames.insert(word).second);

            graph->names.push_back(word);

            for (int j = 0; j < graph->extras; j++)
            {

                if (i != j)
                {
                    int over = graph->overlap(graph->names[i], graph->names[j]);
                    if (over != -1)
                    {
                        graph->aMatrix[i][j] = over;
                    }
                    over = graph->overlap(graph->names[j], graph->names[i]);
                    if (over != -1)
                    {
                        graph->aMatrix[j][i] = over;
                    }
                }
            }

            graph->aList[i].clear();
            graph->aListRev[i].clear();

            for (int j = 0; j < graph->extras; j++)
            {
                if (graph->aMatrix[i][j] != 0)
                {
                    graph->aList[i].push_back(j);
                }
                if (graph->aMatrix[j][i] != 0)
                {
                    graph->aListRev[i].push_back(j);
                }
                
                auto it = find(graph->aList[j].begin(), graph->aList[j].end(), i);
                
                if(it!=graph->aList[j].end()){
                    graph->aList[j].erase(it);
                }
                
                it = find(graph->aListRev[j].begin(), graph->aListRev[j].end(), i);
                
                if (it != graph->aListRev[j].end())
                {
                    graph->aListRev[j].erase(it);   
                }

                if (graph->aMatrix[i][j] != 0)
                {
                    graph->aListRev[j].push_back(i);
                }
                if (graph->aMatrix[j][i] != 0)
                {
                    graph->aList[j].push_back(i);
                }
            }
        }
    }
}

void Generation::step()
{

    while (population_size < maxSize)
    {
        int operation = rand() % opTotalWeight;
        int currSum = 0;

        Operation e;

        for (int i = 0; i < opHelper.size(); i++)
        {
            currSum += opWeights[opHelper[i]];
            if (operation < currSum)
            {
                e = opHelper[i];
                break;
            }
        }
        switch (e)
        {
        case MUTATE:
        {
            int i = rand() % population_culled;
            mutate(population[i]);
            break;
        }
        case GROW:
        {
            int i = rand() % population_culled;
            grow(population[i].val);
            break;
        }
        case CROSS:
        {
            int a = rand() % population_culled, b;
            do
            {
                b = rand() % population_culled;
            } while (b == a);

            cross(population[a], population[b]);
            break;
        }
        case CONNECT:
        {
            int a = rand() % population_culled, b = rand() % population_culled;
            if (a == b)
                b = (b + 1) % population_culled;
            connect(population[a], population[b]);
            break;
        }
        default:
        {
            break;
        }
        }
    }

    std::sort(population, population + population_size, SeqCmp);
    population_size = population_culled;
    insertCtr--;
    if(insertCtr <= 0 ){
        insert();
        insertCtr = maxInsertCtr;
    }
}
void Generation::showResults()
{
    for (int i = 0; i < population_size && i < 20; i++)
    {
        cout << "Rank: " << i + 1 << "\tLen: " << population[i].len << "\tCov: " << population[i].cov << "\tdensity: " << population[i].density << "\tScore: " << population[i].score << "\n";
    }
}

void Generation::addSeq(Sequence a)
{
    score(a);
    if (set.insert(a).second)
    {
        population[population_size++] = a;
    }
}
