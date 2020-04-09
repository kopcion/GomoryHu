//
// Created by kopcion on 08.04.2020.
//

#ifndef GOMORYHU_GOMORYHUTREE_H
#define GOMORYHU_GOMORYHUTREE_H

#include <vector>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include "MinCuts/MinCutFunc.h"
#include "utils.h"


using namespace std;
class GomoryHuTree {
public:
    GomoryHuTree(set<int>& vertices, vector<vector<int> >& graph, MinCutFunc func);
private:
    void createTree(vector<pair<vertex&, set<Edge, EdgeComparator>>>& tmpGraph);
    void splitNode(vector<pair<vertex&, set<Edge, EdgeComparator>>>& tmpGraph, vertex& top, vertex& S1, vertex& S2, Edge& edge);

    vector<vector<int> > tree;
};

#endif //GOMORYHU_GOMORYHUTREE_H
