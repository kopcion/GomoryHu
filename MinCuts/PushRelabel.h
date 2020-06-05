//
// Created by kopcion on 26.05.2020.
//

#ifndef GOMORYHU_PUSHRELABEL_H
#define GOMORYHU_PUSHRELABEL_H

#include "MinCutFunc.h"
#include <queue>
class PushRelabel : public MinCutFunc{
public:
    int minCut(vector<unordered_map<int,int>> &graph, int s, int t) override;

private:
    void preflow();
    bool push(int);
    void relabel(int);
    void discharge();

    vector<unordered_map<int,int> > Flow;
    queue<int> overflowingVertices;
    vector<bool> isInQueue;
    vector<int> flow;
    vector<int> height;
};


#endif //GOMORYHU_PUSHRELABEL_H
