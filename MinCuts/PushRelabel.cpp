//
// Created by kopcion on 26.05.2020.
//

#include "PushRelabel.h"

int PushRelabel::minCut(vector<unordered_map<int,int>> &graph, int s, int t) {
    flow.clear();
    height.clear();
    isInQueue.clear();
    _graph = graph;
    source = s;
    target = t;
    preflow();
    count = 0;

    while(!overflowingVertices.empty()){
        if(count%(graph.size()*graph.size()) == 0) globalRelabel();
        if(overflowingVertices.front() == source or overflowingVertices.front() == target){
            overflowingVertices.pop();
            continue;
        }
        discharge();
    }
    return flow[target];
}

void PushRelabel::preflow() {
    Flow.resize(_graph.size());
    isInQueue.resize(_graph.size(), false);
    flow.resize(_graph.size(), 0);
    flow[source] = INT32_MAX;
    height.resize(_graph.size(), 0);
    height[source] = _graph.size();
    push(source);
}

void PushRelabel::globalRelabel(){
    vector<int> dist(_graph.size(), -1);
    dist[target] = 0;
    for(int i=1; i < _graph.size(); ++i){
        cout<<"kappa\n";
        if(dist[i] == -1) dfs(i, dist);
    }
    for(int i=1; i < _graph.size(); ++i){
        cout<<height[i]<<" "<<dist[i]<<endl;
        height[i] = dist[i];
    }
}

void PushRelabel::dfs(int vertex, vector<int>& dist){
    if(dist[vertex] != -1) return;
    for(auto u : _graph[vertex]){
        if(dist[u.first] == -1 && u.second > 0){
            dfs(u.first, dist);
            dist[vertex] = (dist[vertex] == -1) ? dist[u.first] + 1 : min(dist[vertex], dist[u.first] + 1);
        }
    }
}

bool PushRelabel::push(int vertex){
    bool changed = false;
    for(auto v : _graph[vertex]){
        count++;
        if(height[vertex] <= height[v.first] || v.second <= 0) continue;

        changed = true;
        int flowToPush = min(flow[vertex], v.second);
//        printf("Pushing from %d to %d amount %d through %d\n", vertex, v.first, flowToPush, v.second);
        flow[vertex] -= flowToPush;
        flow[v.first] += flowToPush;
        _graph[vertex][v.first] -= flowToPush;
        _graph[v.first][vertex] += flowToPush;

        if(!isInQueue[v.first]){
            isInQueue[v.first] = true;
            overflowingVertices.push(v.first);
        }
        if(flow[vertex] == 0) break;
    }
    return changed;
}

void PushRelabel::relabel(int vertex) {
    count++;
    int minHeight = INT32_MAX;
    for(auto v : _graph[vertex]){
        if(v.second <= 0) continue;

        if(minHeight > height[v.first]){
            minHeight = height[v.first];
            height[vertex] = minHeight + 1;
        }
    }
}

void PushRelabel::discharge() {
    int vertex = overflowingVertices.front();
    overflowingVertices.pop();
    isInQueue[vertex] = false;

    while(flow[vertex] > 0){
        push(vertex);

        if(flow[vertex]) relabel(vertex);
    }
}