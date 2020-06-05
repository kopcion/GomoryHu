//
// Created by kopcion on 02.06.2020.
//

#ifndef GOMORYHU_DINICS_H
#define GOMORYHU_DINICS_H

#include "MinCutFunc.h"
#include <queue>
#include <iostream>
#include <unordered_map>

using namespace std;

class Dinics : public MinCutFunc{
public:
    int minCut(vector<unordered_map<int,int> > &graph, int s, int t) override;

private:
    int dfs(vector<int>& dist, vector<bool> &visited, int current, int currentFlow);
    bool bfs(vector<int> &dist);
};

#endif //GOMORYHU_DINICS_H
