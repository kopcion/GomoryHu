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

    while(!overflowingVertices.empty()){
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

bool PushRelabel::push(int vertex){
    bool changed = false;
    for(auto v : _graph[vertex]){
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
    int minHeight = INT32_MAX;
    for(auto v : _graph[vertex]){
        if(v.second <= 0) continue;

        if(minHeight > height[v.first]){
            minHeight = height[v.first];
            height[vertex] = minHeight + 1;
        }
    }
}

//TODO
void PushRelabel::discharge() {
//    cout<<"discharge\n";
    int vertex = overflowingVertices.front();
    overflowingVertices.pop();
    isInQueue[vertex] = false;

    while(flow[vertex] > 0){
//        cout<<"\tdischarge::while\n";
//        cout<<"\t\tflow[vertex] == "<<flow[vertex]<<endl;
        push(vertex);

        if(flow[vertex]) relabel(vertex);
    }
}