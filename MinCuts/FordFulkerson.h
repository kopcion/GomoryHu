//
// Created by kopcion on 08.04.2020.
//

#ifndef GOMORYHU_FORDFULKERSON_H
#define GOMORYHU_FORDFULKERSON_H

#include "MinCutFunc.h"
#include <iostream>
#include <vector>
#include <queue>

class FordFulkerson : public MinCutFunc {
    int minCut(vector<vector<int> > &graph, set<int> &S1, set<int> &S2, Edge& edge, int s, int t) override;
    void dfs(vector<vector<int>>& graph, int s, vector<bool>& visited);
    bool bfs();

private:
    vector<vector<int> > Graph;
    vector<vector<int> > residualG;
    vector<int> path;
};


#endif //GOMORYHU_FORDFULKERSON_H
