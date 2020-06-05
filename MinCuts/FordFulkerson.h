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
public:
    int minCut(vector<unordered_map<int,int> >&, int, int);

private:
    void dfs(int, vector<bool>&);
    bool bfs();

    vector<int> path;
};


#endif //GOMORYHU_FORDFULKERSON_H
