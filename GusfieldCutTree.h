//
// Created by kopcion on 05.06.2020.
//

#ifndef GOMORYHU_GUSFIELDCUTTREE_H
#define GOMORYHU_GUSFIELDCUTTREE_H

#include <vector>
#include <unordered_map>
#include "MinCuts/MinCutFunc.h"

using namespace std;

class GusfieldCutTree {
public:
    GusfieldCutTree(vector<unordered_map<int,int> >&, MinCutFunc*, int);

    int getMinCut(int, int);

    void printGraph(){
        int i=0;
        for(auto vertex : cutTree){
            cout<<"vertex: "<<i++<<endl;
            for(auto edge : vertex){
                cout<<"to: "<<edge.first<<" with cap: "<<edge.second<<endl;
            }
        }
        cout<<"\n\n";
    }

private:
    vector<unordered_map<int,int> > cutTree;
    int NUM_OF_THREADS;

    int dfs(int, int, int, vector<bool>&);
};


#endif //GOMORYHU_GUSFIELDCUTTREE_H
