#include "graph.h"

int Graph::overlap(string a, string b){
    int res = -1;
    for (int i = 0; i < a.length(); i++)
    {
        if(a.substr(i)== b.substr(0,a.length()-i)){
            res = a.length()- i;
            break;
        }
    }
    return res;
}
 
 Graph::Graph(const char* name)
 {
    std::ifstream in(name);
    std::string a;
   
    std::string b(name);

    b = b.substr(0,b.size()-4);

    std::string target = b.substr(b.rfind('.')+1,3);

    perfectNodeNum = stoi(target);
    length = perfectNodeNum+9;

    while (!in.eof())
    {
        in>> a;
        if(a == "")
            continue;
        uniqueNames.insert(a);
    }
    in.close();


    for(auto i = uniqueNames.begin();i != uniqueNames.end();i++){
        names.push_back(*i);
    }
    
    size = names.size();
    extras = perfectNodeNum*1.2;

    aMatrix.resize(extras,vector<int>(extras, 0));

    extrasCount.reserve(extras - names.size());

    word = names[0].length();

    for (int i = 0; i < names.size(); i++)
    {
        for (int j = 0; j < names.size(); j++)
        {
            int over = overlap(names[i],names[j]);
            if(i != j && over!=-1){
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
            if(aMatrix[i][j]!= 0){
                aList[i].push_back(j);
            }
            if(aMatrix[j][i]!= 0){
                aListRev[i].push_back(j);
            }
        }   
    }
    cout<<"Done loading\n";
 }

void Graph::printMatrix(){
   for (int i = 0; i < aMatrix.size(); i++)
   {
       for (int j = 0; j < aMatrix.size(); j++)
       {
           cout<< aMatrix[i][j]<<" ";
       }
       cout <<"\n";
   }
}

void printSpaces(int n){
    for (int i = 0; i < n; i++)
    {
        cout<<" ";
    }
}

void Graph::printPath(const vector<int>& p){
    for (int i = 0; i < p.size(); i++)
    {
        cout<<p[i]<<",";
    }
    cout<<"\n";
    
    cout<<names[p[0]]<<" "<<aMatrix[p[0]][p[1]]<<" : "<<p[0] <<"\n";
    int offset=names[0].length() -aMatrix[p[0]][p[1]];
    printSpaces(offset);

    for (int i = 1; i < p.size() -1 ; i++)
    {
        cout<<names[p[i]]<<" "<<aMatrix[p[i]][p[i+1]]<<" : "<<p[i] <<'\n';
        offset+= (names[0].length() - aMatrix[p[i]][p[i+1]]);
        printSpaces(offset);
    }
    cout<<names[p[p.size() -1]]<<" "<<0<<" : "<<p[p.size() -1] <<'\n';
    cout<<"Length:"<< offset+names[0].length()<<'\n';
}


int Graph::wordLength(const vector<int>& p){
    int out = names[p[0]].length();
    for (int i = 0; i < p.size()-1; i++)
    {
        out+= (names[0].length() - aMatrix[p[i]][p[i+1]]);
    }
    return out;
}

 Graph::~Graph()
 {
 }
 