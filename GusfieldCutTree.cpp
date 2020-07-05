//
// Created by kopcion on 05.06.2020.
//

#include "GusfieldCutTree.h"

GusfieldCutTree::GusfieldCutTree(vector<unordered_map<int,int> >& graph, MinCutFunc* func){
    cutTree.resize(graph.size());

    //initialize
    for(int i=2; i < graph.size(); ++i){
        cutTree[i][1] = -1;
        cutTree[1][i] = -1;
    }

    //calculate
    for(int source=2; source < graph.size(); ++source){
//        printGraph();
        int target = cutTree[source].begin()->first;
//        cout<<"considering pair "<<source<<" "<<target<<endl;

        int capacity = func->minCut(graph, source, target);
//        cout<<"\nminCut with value "<<capacity<<"\n\n";
        cutTree[source][target] = capacity;
        cutTree[target][source] = capacity;

        queue<int> queue;
        set<int> sourceSide = func->getSourceSide();
        for(auto vertex : cutTree[target]){
            if(vertex.first == source) continue;
            if(sourceSide.find(vertex.first) != sourceSide.end()){
                int tmp = cutTree[target][vertex.first];
                queue.push(vertex.first);
                cutTree[vertex.first].erase(target);
                cutTree[source][vertex.first] = tmp;
                cutTree[vertex.first][source] = tmp;
            }
        }
        while(!queue.empty()){
            cutTree[target].erase(queue.front());
            queue.pop();
        }
    }
//    printGraph();
}

int GusfieldCutTree::getMinCut(int source, int target) {
    vector<bool> visited(cutTree.size(), false);

    return dfs(source, target, INT32_MAX, visited);
}

int GusfieldCutTree::dfs(int vertex, int target, int currentFlow, vector<bool> &visited) {
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