


#include <assert.h>
#include "GomoryHuTree.h"

GomoryHuTree::GomoryHuTree(vector<unordered_map<int,int> >& graph, MinCutFunc* func){
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
        for(auto v : verticesInNodes[X.second]){
            cout<<v<<" ";
        }cout<<endl;

        vector<int> vertexMapping(graph.size());
//        cout<<"constructContracted\n";
        constructContracted(X.second, X.first, contractedGraph, vertexMapping, graph, superNodes);
//        cout<<"done constructContracted\n";
//        int i=0;
//        for(auto vertex : contractedGraph){
//            cout<<"\tvertex: "<<i++<<endl;
//            for(auto edge : vertex){
//                cout<<"\tto: "<<edge.first<<" with cap: "<<edge.second<<endl;
//            }
//        }cout<<endl;

        int s, t, count = 0;
        for(int i=1; i < superNodes.size() && count < 2; ++i){
            if(superNodes[i] == X.second){
                if(count == 0) s = i;
                else t = i;
                count++;
            }
        }


        int cut = func->minCut(contractedGraph, vertexMapping[s], vertexMapping[t]);
        printf("Chosen root %d with size %d\n", X.second, X.first);
//        printf("Chosen root %d with size %d\n\tVertices: ", X.second, X.first);
        printf("mincut: %d, (s,t) = (%d, %d)\n", cut, s, t);
//        printf("mincut: %d, (s,t) = (%d, %d)\n", cut, vertexMapping[s], vertexMapping[t]);

        set<int> source = func->getSourceSide();
        splitRoot(X, cut, source, superNodes, vertexMapping);
//        printGraph();
    }
    transformTree();
}

void GomoryHuTree::constructContracted(int root,
                                       int size,
                                       vector<unordered_map<int,int> >& contractedGraph,
                                       vector<int>& vertexMapping,
                                       vector<unordered_map<int,int> >& graph,
                                       vector<int>& superNodes){
    vector<int> component(cutTree.size(), 0);
    int components = getComponents(root, component);

//    cout<<"\tcomponents "<<components<<endl;
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

    for(auto v : source){
        cout<<v<<" ";
    } cout<<endl;

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
//    printf("Pushing nodes (%d, %d) and (%d, %d), top of queue is node (%d, %d), size of queue %d\n", verticesInNodes[X.second].size(), X.second,
//           verticesInNodes[newNodeId].size(), newNodeId, treeNodes.top().first, treeNodes.top().second, treeNodes.size());

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
//    printGraph();
}
