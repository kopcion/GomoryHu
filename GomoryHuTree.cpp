


#include "GomoryHuTree.h"

GomoryHuTree::GomoryHuTree(vector<unordered_map<int,int> >& graph, MinCutFunc* func){
    vector<int> superNodes(graph.size(), 1);
    priority_queue<pair<int,int> > treeNodes;
    treeNodes.push(pair<int,int>(graph.size(), 1));
    vector<unordered_map<int,int> > contractedGraph;

    while(cutTree.size() < graph.size()){
        auto X = treeNodes.top(); treeNodes.pop();

        constructContracted(X.second, X.first, contractedGraph, graph, superNodes);
    }
}

void GomoryHuTree::constructContracted(int root, int size, vector<unordered_map<int,int> >& contractedGraph, vector<unordered_map<int,int> >& graph, vector<int>& superNodes){
    vector<int> component(cutTree.size(), 0);
    int components = dfsUtil(root, component);

    vector<int> vertexMapping(graph.size());
    int id = 0;
    for(int i=0; i < graph.size(); ++i){
        if(superNodes[i] != root){
            vertexMapping[i] = superNodes[i];
        } else {
            vertexMapping[i] = components + id++;
        }
    }
    contractedGraph.clear();
    contractedGraph.resize(components + size);

    for(int i=0; i < graph.size(); ++i){
        for(auto u : graph[i]) {
            if (superNodes[i] == superNodes[u.first] && superNodes[i] != root) continue;

            contractedGraph[vertexMapping[i]][vertexMapping[u.first]] += u.second;
        }
    }
}