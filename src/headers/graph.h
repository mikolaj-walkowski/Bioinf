#pragma once

#include <iostream> 
#include <fstream> 
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

 class Graph
 {
 public:
    vector<vector<int>> aMatrix;
    vector<string> names;
    vector<int> path;
    
    vector<int> longestP();
    
    void printMatrix();
    void printPath(const vector<int> &p);

    Graph(const char* name);
    ~Graph();
 };
