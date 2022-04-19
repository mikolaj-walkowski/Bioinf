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
    vector<vector<int>> aList;
    vector<vector<int>> aListRev;

    vector<string> names;
    vector<int> path;
    int size;
    int length;

    vector<int> longestP();
    
    void printMatrix();
    void printPath(const vector<int> &);
    int wordLength(const vector<int>&);
   //  bool repeats(const vector<int>&);

    Graph(const char* name);
    ~Graph();
 };