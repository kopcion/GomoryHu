//
// Created by kopcion on 08.04.2020.
//

#ifndef GOMORYHU_MINCUTFUNC_H
#define GOMORYHU_MINCUTFUNC_H
#include <vector>
#include <set>
#include <queue>
#include "../utils.h"

using namespace std;

class MinCutFunc {
public:
    virtual int minCut(vector<unordered_map<int,int> >& graph, int s, int t) = 0;
    void minCut(vector<unordered_map<int,int> >& graph, int s, int t, int* cut){
        *cut = minCut(graph, s, t);
    }
    set<int> getSourceSide() {
        vector<bool> visited(_graph.size(), false);
        queue<int> q;
        q.push(source);
        visited[source] = true;

        while(!q.empty()){
            int vertex = q.front(); q.pop();

            for(auto v : _graph[vertex]){
                if(visited[v.first] or !v.second) continue;
                visited[v.first] = true;
                q.push(v.first);
            }
        }
        set<int> out;
        for(int i=0; i < visited.size(); ++i){
            if(visited[i]) out.insert(i);
        }
        return move(out);
    }
    void printGraph(vector<unordered_map<int,int> >& graph){
        int i=0;
        for(auto vertex : graph){
            cout<<"vertex: "<<i++<<endl;
            for(auto edge : vertex){
                cout<<"to: "<<edge.first<<" with cap: "<<edge.second<<endl;
            }
        }
    }

protected:
    virtual ~MinCutFunc(){};

    vector<unordered_map<int,int> > _graph;
    int source, target;
};


#endif //GOMORYHU_MINCUTFUNC_H
