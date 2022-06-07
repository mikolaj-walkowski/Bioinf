#include "graph.h"

<<<<<<< Updated upstream
int overlap(string a, string b)
=======
int Graph::overlap(string a, string b)
>>>>>>> Stashed changes
{
    int res = -1;
    for (int i = 0; i < a.length(); i++)
    {
        if (a.substr(i) == b.substr(0, a.length() - i))
        {
            res = a.length() - i;
            break;
        }
    }
    return res;
}
<<<<<<< Updated upstream
=======

Graph::Graph(const char *name)
{
    std::ifstream in(name);
    std::string a;
    while (!in.eof())
    {
        in >> a;
        if (a == "")
            continue;
        uniqueNames.insert(a);
    }
    in.close();
    for (auto i = uniqueNames.begin(); i != uniqueNames.end(); i++)
    {
        names.push_back(*i);
    }

    aMatrix.resize(names.size() * 1.4, vector<int>(names.size() * 1.4, 0));
>>>>>>> Stashed changes

void Graph::update()
{
    aMatrix.resize(names.size(), vector<int>(names.size(), 0));
    size = names.size();
<<<<<<< Updated upstream
=======
    extras = names.size() * 1.4;

    extrasCount.reserve(extras - names.size());

    word = names[0].length();
>>>>>>> Stashed changes

    for (int i = 0; i < names.size(); i++)
    {
        for (int j = 0; j < names.size(); j++)
        {
            int over = overlap(names[i], names[j]);
            if (i != j && over != -1)
            {
                aMatrix[i][j] = over;
            }
        }
    }
    for (int i = 0; i < names.size(); i++)
    {
        aList.push_back(vector<int>());
        aListRev.push_back(vector<int>());
        for (int j = 0; j < names.size(); j++)
        {
            if (aMatrix[i][j] != 0)
            {
                aList[i].push_back(j);
            }
            if (aMatrix[j][i] != 0)
            {
                aListRev[i].push_back(j);
            }
        }
<<<<<<< Updated upstream
    }
}

Graph::Graph(const char *name)
{
    std::ifstream in(name);
    std::string a;
    while (!in.eof())
    {
        in >> a;
        names.push_back(a);
    }
    in.close();
    update();
    cout << "Done loading\n";
=======
    }
    // cout<<"Done loading\n";
>>>>>>> Stashed changes
}

void Graph::printMatrix()
{
    for (int i = 0; i < aMatrix.size(); i++)
    {
        for (int j = 0; j < aMatrix.size(); j++)
        {
            cout << aMatrix[i][j] << " ";
        }
        cout << "\n";
    }
}

void printSpaces(int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << " ";
    }
}

void Graph::printPath(const vector<int> &p)
{
    for (int i = 0; i < p.size(); i++)
    {
        cout << p[i] << ",";
    }
    cout << "\n";

    cout << names[p[0]] << " " << aMatrix[p[0]][p[1]] << " : " << p[0] << "\n";
    int offset = names[0].length() - aMatrix[p[0]][p[1]];
    printSpaces(offset);

    for (int i = 1; i < p.size() - 1; i++)
    {
        cout << names[p[i]] << " " << aMatrix[p[i]][p[i + 1]] << " : " << p[i] << '\n';
        offset += (names[0].length() - aMatrix[p[i]][p[i + 1]]);
        printSpaces(offset);
    }
    cout << names[p[p.size() - 1]] << " " << 0 << " : " << p[p.size() - 1] << '\n';
    cout << "Length:" << offset + names[0].length() << '\n';
}

int Graph::wordLength(const vector<int> &p)
{
    int out = names[p[0]].length();
    for (int i = 0; i < p.size() - 1; i++)
    {
        out += (names[0].length() - aMatrix[p[i]][p[i + 1]]);
    }
    return out;
}

Graph::~Graph()
{
}
