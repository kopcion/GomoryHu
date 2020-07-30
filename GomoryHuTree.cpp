#include <assert.h>
#include <thread>
#include <random>
#include <wait.h>
#include <zconf.h>
#include "GomoryHuTree.h"


vector<int> cutsValues;
vector<set<int> > cutsDivisions;


GomoryHuTree::GomoryHuTree(vector<unordered_map<int,int> > graph, MinCutFunc** func, int num){
    NUM_OF_THREADS = num;
    cutsDivisions.resize(NUM_OF_THREADS);
    cutsValues.resize(NUM_OF_THREADS);
    superNodes.resize(graph.size(), 1);
    treeNodes.push(pair<int,int>(graph.size()-1, 1));
    vector<unordered_map<int,int> > contractedGraph;
    cutTree.resize(2);

    set<int> S;
    for(int i=1; i < graph.size(); ++i){
        S.insert(i);
    }
    verticesInNodes[1] = move(S);

    while(cutTree.size() < graph.size()){
        auto X = treeNodes.top(); treeNodes.pop();
        assert(X.first>=2);

        vector<int> vertexMapping(graph.size());
        constructContracted(X.second, X.first, contractedGraph, vertexMapping, graph, superNodes);

        thread threads[NUM_OF_THREADS];
        for(int i=0; i < NUM_OF_THREADS; ++i){
            pair<int,int> st = getSourceTarget(X.second);

            threads[i] = thread([i, contractedGraph, &vertexMapping, st, func]()mutable{
                cutsValues[i] = func[i]->minCut(contractedGraph, vertexMapping[st.first], vertexMapping[st.second]);
                cutsDivisions[i] = func[i]->getSourceSide();
                if(i != 0) return;
            });
        }

        for(int i=0; i < NUM_OF_THREADS; ++i) {
            threads[i].join();
        }

        int bestId = 0;
        int target = verticesInNodes[X.second].size()/2;
        int current = target<<2;
        for(int i=0; i < NUM_OF_THREADS; ++i){
            if(current > target - cutsDivisions[i].size()){
                bestId = i;
                current = target - cutsDivisions[i].size();
            }
        }

        splitRoot(X, cutsValues[bestId], cutsDivisions[bestId], superNodes, vertexMapping);
    }
    transformTree();
}

pair<int,int> GomoryHuTree::getSourceTarget(int nodeId){
    default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    int range = verticesInNodes[nodeId].size();
    int sIt = generator()%range;
    int tIt = generator()%range;
    while(sIt == tIt) tIt = generator()%range;

    pair<int,int> out;
    auto it = verticesInNodes[nodeId].begin();
    for(int i=0; i < range; ++i){
        if(sIt == i){
            out.first = *it;
        }
        if(tIt == i){
            out.second = *it;
        }
        ++it;
    }
    return out;
}



void GomoryHuTree::constructContracted(int root,
                                       int size,
                                       vector<unordered_map<int,int> >& contractedGraph,
                                       vector<int>& vertexMapping,
                                       vector<unordered_map<int,int> >& graph,
                                       vector<int>& superNodes){
    vector<int> component(cutTree.size(), 0);
    int components = getComponents(root, component);

    int id = 1;
    for(int i=1; i < graph.size(); ++i){
        if(superNodes[i] != root){
            vertexMapping[i] = component[superNodes[i]];
        } else {
            vertexMapping[i] = components + id++;
        }
    }
    contractedGraph.clear();
    contractedGraph.resize(components + size + 1);

    for(int i=1; i < graph.size(); ++i){
        for(auto u : graph[i]) {
            if (vertexMapping[i] == vertexMapping[u.first] && superNodes[i] != root) continue;

            contractedGraph[vertexMapping[i]][vertexMapping[u.first]] += u.second;
        }
    }
}

void GomoryHuTree::splitRoot(pair<int, int> X, int cut, set<int> &source, vector<int>& superNodes, vector<int>& vertexMapping) {
    int newNodeId = cutTree.size();
    cutTree.emplace_back();
    cutTree[X.second][newNodeId] = cut;
    cutTree[newNodeId][X.second] = cut;

    queue<int> queue;
    for(auto v : verticesInNodes[X.second]){
        if(source.find(vertexMapping[v]) == source.end()){
            queue.push(v);
        }
    }

    while(!queue.empty()){
        assert(verticesInNodes[X.second].erase(queue.front()) > 0);
        verticesInNodes[newNodeId].insert(queue.front());
        superNodes[queue.front()] = newNodeId;
        queue.pop();
    }
    treeNodes.push(pair<int,int>(verticesInNodes[X.second].size(), X.second));
    treeNodes.push(pair<int,int>(verticesInNodes[newNodeId].size(), newNodeId));

    for(auto v : cutTree[X.second]){
        if(v.second == 0) {
            queue.push(v.first);
            continue;
        }
        if(v.first == newNodeId) continue;
        int u = *verticesInNodes[v.first].begin();
        if(source.find(vertexMapping[u]) == source.end()){
            cutTree[newNodeId][v.first] = v.second;
            cutTree[v.first][newNodeId] = v.second;
            cutTree[v.first].erase(X.second);
            queue.push(v.first);
        }
    }
    while(!queue.empty()){
        cutTree[X.second].erase(queue.front());
        queue.pop();
    }
}
