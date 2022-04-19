#include "graph.h"

int overlap(string a, string b){
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
    while (!in.eof())
    {
        in>> a;
        names.push_back(a);
    }
    in.close();
    aMatrix.resize(names.size(),vector<int>(names.size(), 0));
    size = names.size();
    
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

vector<int> Graph::longestP(){
    int longest = 0, longestVal = 0;
    int curr = 0;
    queue<int> bfsQ;
    vector<int> val(names.size(),0);
    vector<vector<int>> path(names.size());

    bfsQ.push(curr);
    path[curr].push_back(curr);

    while (!bfsQ.empty())
    {
        curr = bfsQ.front();
        bfsQ.pop();
        for(int i =0 ; i< names.size(); ++i){
            //cout << aMatrix[curr][i]  <<" " << *find(path[curr].begin(),path[curr].end(),i) << "==" << i <<" "<< val[i] << "<"<< val[curr] + aMatrix[curr][i]<<'\n';
            if(aMatrix[curr][i] > 0 && *find(path[curr].begin(),path[curr].end(),i) != i && val[i]< val[curr] + aMatrix[curr][i]){
                val[i] = val[curr]+aMatrix[curr][i];
                path[i] = path[curr];
                path[i].push_back(i);
                bfsQ.push(i);
                if (val[i]> longestVal)
                {
                    longest=i;
                    longestVal=val[i];
                }
            }
        }
    }
    curr = longest, longestVal = 0;
    val = vector<int>(names.size(),0);
    path = vector<vector<int>>(names.size());
    //cout<< longest <<'\n';
    bfsQ.push(curr);
    path[curr].push_back(curr);

    while (!bfsQ.empty())
    {
        curr = bfsQ.front();
        bfsQ.pop();
        for(int i =0 ; i< names.size(); ++i){
            //cout << aMatrix[curr][i]  <<" " << *find(path[curr].begin(),path[curr].end(),i) << "==" << i <<" "<< val[i] << "<"<< val[curr] + aMatrix[curr][i]<<'\n';
            if(aMatrix[curr][i] > 0 && *find(path[curr].begin(),path[curr].end(),i) != i && val[i]< val[curr]+aMatrix[curr][i]){
                val[i] = val[curr]+aMatrix[curr][i];
                path[i] = path[curr];
                path[i].push_back(i);
                bfsQ.push(i);
                if (val[i]> longestVal)
                {
                    longest=i;
                    longestVal=val[i];
                }
            }
        }
    }
    return path[longest];
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
    
    cout<<names[p[0]]<<" "<<aMatrix[p[0]][p[1]]<<"\n";
    int offset=names[0].length() -aMatrix[p[0]][p[1]];
    printSpaces(offset);

    for (int i = 1; i < p.size() -1 ; i++)
    {
        cout<<names[p[i]]<<" "<<aMatrix[p[i]][p[i+1]]<<'\n';
        offset+= (names[0].length() - aMatrix[p[i]][p[i+1]]);
        printSpaces(offset);
    }
    cout<<names[p[p.size() -1]];
    cout<<'\n';
    cout<<"Longest Path Val:"<< offset+names[0].length()<<'\n';
}

int Graph::wordLength(const vector<int>& p){
    int out = names[p[0]].length();
    for (int i = 1; i < p.size() -1 ; i++)
    {
        out+= (names[0].length() - aMatrix[p[i]][p[i+1]]);
    }
    return out;
}

// bool Graph::repeats(const vector<int>&p){
//     for (int i = 0; i < p.size(); ++i){
//         if 
//     }
// }

 Graph::~Graph()
 {
 }
 