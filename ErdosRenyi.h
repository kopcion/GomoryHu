//
// Created by kopcion on 30.07.2020.
//

#ifndef GOMORYHU_ERDOSRENYI_H
#define GOMORYHU_ERDOSRENYI_H
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <fstream>


using namespace std;

void ER(string input, string output){
    vector<unordered_map<int,int> > graph;

    int n,m;
    ifstream file("/home/kopcion/CLionProjects/GomoryHu/" + input, std::ios_base::in);
    file>>n>>m;
    graph.resize(n+1);
    for(int i=0; i < m; ++i){
        int a, b, c;
        file>>a>>b>>c;
        graph[a][b] = c;
        graph[b][a] = c;
    }

    priority_queue<pair<int,int> > pq;
    vector<int> component(n+1, -1);
    int comp = 1;
    int size = 0;
    for(int i=1; i < component.size(); ++i){
        if(component[i] != -1) continue;

        component[i] = comp;
        queue<int> q;
        q.push(i);
        while(!q.empty()){
            int u = q.front(); q.pop();
            size++;

            for(auto v : graph[u]){
                if(component[v.first] != -1) continue;

                component[v.first] = comp;
                q.push(v.first);
            }
        }
        pq.push(pair<int,int>(size, comp));
        size = 0;
        comp++;
    }

    std::ofstream ofs ("../ErdosRenyi" + to_string(n/100) + ".txt", std::ofstream::out);
    int edges = 0;
    for(int i=1; i < graph.size(); ++i){
        if(component[i] != pq.top().second) continue;

        for(auto v : graph[i]){
            if(component[v.second] != pq.top().second) continue;

            edges++;
        }
    }
    ofs << pq.top().first << " " << edges<<endl;
    for(int i=1; i < graph.size(); ++i){
        if(component[i] != pq.top().second) continue;

        for(auto v : graph[i]){
            if(component[v.second] != pq.top().second) continue;

            ofs << i << " " << v.first<<" "<<v.second<<endl;
        }
    }
    cout<<pq.top().first << " " << edges<<endl;
    ofs.close();
}
#endif //GOMORYHU_ERDOSRENYI_H
