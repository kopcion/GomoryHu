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

/*
 * For any edge u,v with capacity c in Input Graph, there is edge v,u with capacity >= 0
 * */

class GomoryHuTree {
public:
    GomoryHuTree(vector<unordered_map<int,int> >&, MinCutFunc*);

    int getMinCut(int, int);

    void printGraph(){
        int i=0;
        for(auto vertex : cutTree){
            cout<<"vertex: "<<i++<<endl;
            for(auto edge : vertex){
                cout<<"to: "<<edge.first<<" with cap: "<<edge.second<<endl;
            }
        }
        cout<<"\n\n";
    }

    int dfsUtil(int v, vector<int>& component){
        vector<bool> visited(cutTree.size(), false);
        visited[v] = true;
        int compNo = 1;

        for(auto u : cutTree[v])
            if(u.second > 0) dfs(u.first, compNo++, component, visited);

        return compNo - 1;
    }

    void dfs(int v, int compNo, vector<int>& component, vector<bool>& visited){
        if(visited[v]) return;
        visited[v] = true;

        component[v] = compNo;
        for(auto u : cutTree[v]){
            dfs(u.first, compNo, component, visited);
        }
    }

    void constructContracted(int, int, vector<unordered_map<int,int> >&, vector<unordered_map<int,int> >&, vector<int>&);
private:
    vector<unordered_map<int,int> > cutTree;

//    int dfs(int, int, int, vector<bool>&);
};

#endif //GOMORYHU_GOMORYHUTREE_H
