//
// Created by kopcion on 08.04.2020.
//

#ifndef GOMORYHU_UTILS_H
#define GOMORYHU_UTILS_H

#include <set>
#include <unordered_map>
#include <iostream>

using namespace std;

typedef struct edge{
    int vertex;
    int weight;
    set<pair<int,int> > subEdges;
} Edge;

struct EdgeComparator{
    bool operator() (const Edge& one, const Edge& two){
        return one.vertex < two.vertex;
    }
};



typedef set<int> vertex;

#endif //GOMORYHU_UTILS_H
