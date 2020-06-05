//
// Created by kopcion on 02.06.2020.
//

#include "Dinics.h"


int Dinics::minCut(vector<unordered_map<int,int> > &graph, int s, int t){
    _graph = graph;
    source = s;
    target = t;
    vector<int> dist(graph.size(), -1); dist[source] = 0;
    vector<bool> visited(graph.size(), false);
    int output = 0;
    int count = 3;
    while(bfs(dist) && count--){
        while(true) {
            visited.clear();
            visited.resize(_graph.size(), false);
            int flow = dfs(dist, visited, source, INT16_MAX);
            if(flow == -1) break; //level graph is saturated, no more s-t path, construct new level graph

            output += flow;
        }
        dist.clear();
        dist.resize(_graph.size(), -1); dist[source] = 0;
    }

    return output;
}

int Dinics::dfs(vector<int>& dist, vector<bool> &visited, int current, int currentFlow){
    visited[current] = true;
    if(current == target) {
        return currentFlow;
    }

    for(auto& v : _graph[current]){
        if(dist[current] + 1 != dist[v.first]  or visited[v.first] or v.second == 0) continue;

        int flow = dfs(dist, visited, v.first, min(currentFlow, v.second));
        if(flow > 0){
            _graph[current][v.first] -= flow;
            _graph[v.first][current] += flow;

            return flow;
        }
    }

    return -1;
}

bool Dinics::bfs(vector<int> &dist){
    queue<int> queue;
    queue.push(source);

    while(!queue.empty()){
        int u = queue.front(); queue.pop();

        for(auto& v : _graph[u]){
            if(v.second == 0 || dist[v.first] != -1) continue;

            dist[v.first] = dist[u] + 1;

            queue.push(v.first);
        }
    }
    return dist[target] != -1;
}
