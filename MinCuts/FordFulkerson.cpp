//
// Created by kopcion on 08.04.2020.
//

#include "FordFulkerson.h"

int FordFulkerson::minCut(vector<unordered_map<int,int>> &graph, int s, int t) {
    _graph = graph;
    source = s;
    target = t;
    int u, v, out = 0;

    path.resize(graph.size());

    while (bfs()) {
        int capacity = INT32_MAX;

        v = target;
        while(v!=source){
            u = path[v];
            capacity = min(capacity, _graph[u][v]);
            v=path[v];
        }

        v = target;
        while(v != source){
            u = path[v];
            _graph[u][v] -= capacity;
            _graph[v][u] += capacity;
            v=path[v];
        }

        out += capacity;
    }

    return out;
}

void FordFulkerson::dfs(int vertex, vector<bool>& visited){
    visited[vertex] = true;
    for (auto v : _graph[vertex])
        if (!visited[v.first] && v.second)
            dfs(v.first, visited);
}

bool FordFulkerson::bfs(){
    vector<bool> visited(_graph.size(), false);
    queue<int> queue;

    queue.push(source);
    visited[source] = true;
    path[source] = -1;

    while(!queue.empty()){
        int u = queue.front(); queue.pop();

        for(auto v : _graph[u]){
            if(!visited[v.first] && v.second){
                queue.push(v.first);
                path[v.first] = u;
                visited[v.first] = true;
            }
        }
    }

    return visited[target];
}