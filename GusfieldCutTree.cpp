//
// Created by kopcion on 05.06.2020.
//

#include <thread>
#include <omp.h>
#include "GusfieldCutTree.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "openmp-use-default-none"
GusfieldCutTree::GusfieldCutTree(vector<unordered_map<int,int> > graph, MinCutFunc** func, int num = 1){
    NUM_OF_THREADS = num;
    cutTree.resize(graph.size());

    //initialize
    for(int i=2; i < graph.size(); ++i){
        cutTree[i][1] = -1;
        cutTree[1][i] = -1;
    }

    //calculate
    #pragma omp parallel for num_threads(NUM_OF_THREADS)
    for(int source=2; source < graph.size(); ++source){
        bool done = false;
        while (!done){
            int target = cutTree[source].begin()->first;


            int capacity = func[omp_get_thread_num()]->minCut(graph, source, target);

            queue<int> queue;;
            set<int> sourceSide = func[omp_get_thread_num()]->getSourceSide();

            #pragma omp critical
            {
                if(cutTree[source].find(target) != cutTree[source].end()){
                    cutTree[source][target] = capacity;
                    cutTree[target][source] = capacity;

                    for (auto vertex : cutTree[target]) {
                        if (vertex.first == source) continue;
                        if (sourceSide.find(vertex.first) != sourceSide.end()) {
                            int tmp = cutTree[target][vertex.first];
                            queue.push(vertex.first);
                            cutTree[vertex.first].erase(target);
                            cutTree[source][vertex.first] = tmp;
                            cutTree[vertex.first][source] = tmp;
                        }
                    }
                    while (!queue.empty()) {
                        cutTree[target].erase(queue.front());
                        queue.pop();
                    }
                    done = true;
                }
            }
        }
    }
//    printGraph();
}
#pragma clang diagnostic pop

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