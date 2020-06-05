/*
#include "GomoryHuTree.h"

GomoryHuTree::GomoryHuTree(vertex& vertices, vector<vector<int> >& graph, MinCutFunc* func){
    queue<set<int> > queue;
    vector<pair<vertex&, set<Edge, EdgeComparator>>> tmpGraph(vertices.size());

    tmpGraph[*vertices.upper_bound(-1)].first = vertices;
    queue.push(vertices);

    //gomory hu tree will have n vertices, id of set of vertices is id of smallest vertex
    while(!queue.empty()){
        vertex& top = queue.front(); queue.pop();
        if(top.size() == 1) continue;

        auto it = top.begin();
        int s = *(it++);
        int t  = *it;
        vertex S1;
        vertex S2;

        Edge edge;
//        func->minCut(graph, top, S1, edge, s, t);
        splitNode(tmpGraph, top, S1, S2, edge);
    }

    createTree(tmpGraph);
}

void GomoryHuTree::splitNode(vector<pair<vertex&, set<Edge, EdgeComparator>>>& graph, vertex& top, vertex& S1, vertex& S2, Edge& edge) {
    //fill S2
    for (auto x : top) {
        if (S1.find(x) != top.end()) continue;

        S2.insert(x);
    }

    set<Edge, EdgeComparator> S1Neighbours;
    set<Edge, EdgeComparator> S2Neighbours;
    edge.vertex = *S2.begin();
    S1Neighbours.insert(edge);
    edge.vertex = *S1.begin();
    S2Neighbours.insert(edge);

    //for each neigbour of top vertex, decide if its S1 or S2
    for (auto neighbour : graph[*top.begin()].second) {
        if (S1.count((*neighbour.subEdges.begin()).first) || S1.count((*neighbour.subEdges.begin()).second)) {
            S1Neighbours.insert(neighbour);
        } else {
            S2Neighbours.insert(neighbour);
        }
    }
    graph[*S1.begin()].second = move(S1Neighbours);
    graph[*S2.begin()].second = move(S2Neighbours);
    
    //update vertex of S1, S2
    Edge tmpEdge = {.vertex = *top.begin()};
    if(*top.begin() == *S1.begin()){
        for (auto neighbour : graph[*S2.begin()].second){
            Edge tmp = *graph[neighbour.vertex].second.find(tmpEdge);
            graph[neighbour.vertex].second.erase(tmpEdge);
            graph[neighbour.vertex].second.insert(tmp);
        }
    } else {
        for (auto neighbour : graph[*S1.begin()].second){
            Edge tmp = *graph[neighbour.vertex].second.find(tmpEdge);
            graph[neighbour.vertex].second.erase(tmpEdge);
            graph[neighbour.vertex].second.insert(tmp);
        }
    }
        
}

void GomoryHuTree::createTree(vector<pair<vertex&, set<Edge, EdgeComparator>>>& tmpGraph){}
*/
