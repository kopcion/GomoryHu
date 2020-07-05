

#include <iostream>
#include <assert.h>
#include "MinCuts/Dinics.h"
#include "MinCuts/PushRelabel.h"
#include "MinCuts/FordFulkerson.h"
#include "GusfieldCutTree.h"
#include "GomoryHuTree.h"
#include <chrono>
#include <fstream>


using namespace std;

void printGraph(vector<unordered_map<int,int> >& graph){
    int i=0;
    for(auto vertex : graph){
        cout<<"vertex: "<<i++<<endl;
        for(auto edge : vertex){
            cout<<"to: "<<edge.first<<" with cap: "<<edge.second<<endl;
        }
    }
}

using namespace std::chrono;
int main(){
    Dinics cut;
    PushRelabel cut2;
    FordFulkerson cut3;
    int n, m;
//    ifstream file("/home/kopcion/CLionProjects/GomoryHu/graph05k20k.txt", std::ios_base::in);
    ifstream file("/home/kopcion/CLionProjects/GomoryHu/test1", std::ios_base::in);
    file>>n>>m;
//    cout<<n<<endl<<m<<endl;
    vector<unordered_map<int,int> > graph(n+1);
    for(int i=0; i < m; ++i){
        int a, b, c;
        file>>a>>b>>c;
        graph[a][b] = c;
        graph[b][a] = c;
    }

    GomoryHuTree treee(graph, &cut2);
    GusfieldCutTree tree(graph, &cut);
    GusfieldCutTree tree1(graph, &cut2);
    GusfieldCutTree tree2(graph, &cut3);

    for(int i=1; i < graph.size()-1;++i){
        for(int j=i+1; j< graph.size();++j){
            cout<<"s,t: ("<<i<<" "<<j<<") "<<treee.getMinCut(i,j)<<" "<<tree2.getMinCut(i,j)<<endl;
        }
    }
    return 0;

    cout<<"Started Dinics\n";
    auto start = high_resolution_clock::now();
//    GusfieldCutTree tree(graph, &cut);
    auto stop = high_resolution_clock::now();
    cout<<"Dinics "<<duration_cast<microseconds>(stop - start).count()<<endl;

    cout<<"Started PushRelabel\n";
    start = high_resolution_clock::now();
//    GusfieldCutTree tree1(graph, &cut2);
    stop = high_resolution_clock::now();
    cout<<"PushRelabel "<<duration_cast<microseconds>(stop - start).count()<<endl;

    cout<<"Started FordFulkerson\n";
    start = high_resolution_clock::now();
//    GusfieldCutTree tree2(graph, &cut3);
    stop = high_resolution_clock::now();
    cout<<"FordFulkerson "<<duration_cast<microseconds>(stop - start).count()<<endl;
}