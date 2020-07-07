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

    int getMinCut(int source, int target) {
        vector<bool> visited(cutTree.size(), false);

        return dfs(source, target, INT32_MAX, visited);
//        return dfs(superNodes[source], superNodes[target], INT32_MAX, visited);
    }

    void transformTree(){
        vector<unordered_map<int, int> > newTree(cutTree.size());
        for(int i=1; i < cutTree.size(); ++i){
            for(auto v : cutTree[i]){
                newTree[*verticesInNodes[i].begin()][*verticesInNodes[v.first].begin()] = v.second;
            }
        }
        cutTree = move(newTree);
    }

    int dfs(int vertex, int target, int currentFlow, vector<bool> &visited) {
        visited[vertex] = true;
        if(vertex == target) {
            return currentFlow;
        }

        for(auto& v : cutTree[vertex]){
            if(visited[v.first]) continue;

            int flow = dfs(v.first, target, min(currentFlow, v.second), visited);
            if(flow > 0){
                return flow;
            }
        }

        return -1;
    }

    void printGraph(){
        printf("\nPrinting graph\n");
        int i=0;
        for(auto vertex : cutTree){
            if(i==0){
                i++;
                continue;
            }
            cout<<"vertex: "<<i++<<endl;
            for(auto edge : vertex){
                cout<<"\tto: "<<edge.first<<" with cap: "<<edge.second<<endl;
            }
            cout<<endl;
        }
        cout<<"";
    }

    int getComponents(int v, vector<int>& component){
//        printGraph();
        vector<bool> visited(cutTree.size(), false);
        visited[v] = true;
        int compNo = 1;

        for(auto u : cutTree[v]){
            if(u.second > 0) dfs(u.first, compNo++, component, visited);
        }

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

    void constructContracted(int, int, vector<unordered_map<int,int> >&, vector<int>&, vector<unordered_map<int,int> >&, vector<int>&);
private:
    vector<int> superNodes;
    vector<unordered_map<int,int> > cutTree;
    unordered_map<int, set<int> > verticesInNodes;
    priority_queue<pair<int,int> > treeNodes;

    //    int dfs(int, int, int, vector<bool>&);
    void splitRoot(pair<int, int>, int, set<int>&, vector<int>&, vector<int>&);
};

#endif //GOMORYHU_GOMORYHUTREE_H
