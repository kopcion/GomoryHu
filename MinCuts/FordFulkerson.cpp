//
// Created by kopcion on 08.04.2020.
//

#include "FordFulkerson.h"

int FordFulkerson::minCut(vector<vector<int>> &graph, set<int> &S1, set<int> &S2, Edge& edge, int s, int t) {
    int u, v, out = 0;

    residualG = Graph;

    path.resize(Graph.size());

    while (bfs()) {
        int capacity = INT32_MAX;

        v = Graph.size() - 1;
        u = path[v];
        while (v) {
            capacity = min(capacity, residualG[u][v]);
            v = path[v];
            u = path[v];
        }

        v = Graph.size() - 1;
        u = path[v];
        while (v) {
            residualG[u][v] -= capacity;
            residualG[v][u] += capacity;
            v = path[v];
            u = path[v];
        }

        out += capacity;
    }

    vector<bool> visited(graph.size(), false);
    dfs(residualG, s, visited);

    for(int i=0; i < graph.size(); i++){
        if(visited[i]) S2.insert(i);
    }
}

void FordFulkerson::dfs(vector<vector<int>>& rGraph, int v, vector<bool>& visited){
    visited[v] = true;
    for (int i = 0; i < rGraph[v].size(); i++)
        if (rGraph[v][i] && !visited[i])
            dfs(rGraph, i, visited);
}

bool FordFulkerson::bfs(){
    vector<bool> visited(residualG.size(), false);
    queue<int> queue;

    queue.push(0);
    visited[0] = true;
    path[0] = -1;

    while(!queue.empty()){
        int u = queue.front(); queue.pop();

        for(int v=0; v < residualG[u].size(); v++){
            if(!visited[v] && residualG[u][v] > 0){
                queue.push(v);
                path[v] = u;
                visited[v] = true;
            }
        }
    }

    return visited[Graph.size()-1];
}