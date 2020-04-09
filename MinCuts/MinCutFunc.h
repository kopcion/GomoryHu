//
// Created by kopcion on 08.04.2020.
//

#ifndef GOMORYHU_MINCUTFUNC_H
#define GOMORYHU_MINCUTFUNC_H
#include <vector>
#include <set>
#include "../utils.h"

using namespace std;

class MinCutFunc {
public:
    virtual int minCut(vector<vector<int> >& graph, set<int>& S1, set<int>& S2, Edge& edge, int s, int t) = 0;
    virtual ~MinCutFunc()=0;
};


#endif //GOMORYHU_MINCUTFUNC_H
