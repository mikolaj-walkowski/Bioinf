#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Graph
{
public:
   vector<vector<int>> aMatrix;
   vector<vector<int>> aList;
   vector<vector<int>> aListRev;

   unordered_set<string> uniqueNames;
   vector<string> names;
   vector<int> path;

   float size;
   int extras; 

   vector<int> extrasCount;

   int length;
   int word;

   void printMatrix();
   void printPath(const vector<int> &);
   int wordLength(const vector<int> &);
   int overlap(string a, string b);

   Graph(const char *name);
   ~Graph();
};
