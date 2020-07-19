

#include <iostream>
#include <assert.h>
#include "MinCuts/Dinics.h"
#include "MinCuts/PushRelabel.h"
#include "MinCuts/FordFulkerson.h"
#include "GusfieldCutTree.h"
#include "GomoryHuTree.h"
#include <chrono>
#include <fstream>
#include "WattsStrogatz.h"


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

const int NUM_OF_THREADS = 8;

int main(){
    Dinics cut;
    PushRelabel cut2;
    FordFulkerson cut3;
//    wattStrogatzModel(200,20);
//    return 0;
    int n, m;
//    ifstream file("/home/kopcion/CLionProjects/GomoryHu/graph05k20k.txt", std::ios_base::in);
//    ifstream file("/home/kopcion/CLionProjects/GomoryHu/WattsStrogatzN200K20.txt", std::ios_base::in);
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

    for(int i=1; i < graph.size()-1;++i){
        for(int j=i+1; j< graph.size();++j){
            vector<unordered_map<int,int> > g2 = graph;
            vector<unordered_map<int,int> > g3 = graph;
            vector<unordered_map<int,int> > g4 = graph;
            cout<<"s,t: ("<<i<<" "<<j<<") "<<cut.minCut(g2,i,j)<<" "<<cut2.minCut(g3,i,j)<<" "<<cut3.minCut(g4,i, j)<<endl;
        }
    }
    return 0;
/*

    FordFulkerson* cuts[NUM_OF_THREADS];
    for(int i=0; i < NUM_OF_THREADS; ++i){
        cuts[i] = new FordFulkerson();
    }

    cout<<"Started Dinics\n";
    auto start = high_resolution_clock::now();
    GomoryHuTree treee(graph, (MinCutFunc**)cuts, 8);
    auto stop = high_resolution_clock::now();
    cout<<"Dinics "<<duration_cast<microseconds>(stop - start).count()<<endl;
    cout<<"Started Dinics\n";
    start = high_resolution_clock::now();
    GomoryHuTree treeee(graph, (MinCutFunc**)cuts, 4);
    stop = high_resolution_clock::now();
    cout<<"Dinics "<<duration_cast<microseconds>(stop - start).count()<<endl;
    cout<<"Started Dinics\n";
    start = high_resolution_clock::now();
    GomoryHuTree treeeee(graph, (MinCutFunc**)cuts, 8);
    stop = high_resolution_clock::now();
    cout<<"Dinics "<<duration_cast<microseconds>(stop - start).count()<<endl;
    cout<<"Started Dinics\n";
    start = high_resolution_clock::now();
    GusfieldCutTree tree2(graph, &cut3);
    stop = high_resolution_clock::now();
    cout<<"Dinics "<<duration_cast<microseconds>(stop - start).count()<<endl;
//    GusfieldCutTree tree(graph, &cut);
//    GusfieldCutTree tree1(graph, &cut2);
 return 0;
    for(int i=1; i < graph.size()-1;++i){
        for(int j=i+1; j< graph.size();++j){
            vector<unordered_map<int,int> > g2 = graph;
            cout<<"s,t: ("<<i<<" "<<j<<") "<<treee.getMinCut(i,j)<<" "<<tree2.getMinCut(i,j)<<" "<<cut3.minCut(g2,i, j)<<endl;
        }
    }

    for(int i=0; i < NUM_OF_THREADS; ++i){
        delete cuts[i];
    }
    return 0;

//    cout<<"Started Dinics\n";
//    auto start = high_resolution_clock::now();
//    GusfieldCutTree tree(graph, &cut);
//    auto stop = high_resolution_clock::now();
//    cout<<"Dinics "<<duration_cast<microseconds>(stop - start).count()<<endl;

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
*/
}
