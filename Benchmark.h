//
// Created by kopcion on 27.07.2020.
//

#ifndef GOMORYHU_BENCHMARK_H
#define GOMORYHU_BENCHMARK_H
#include <iostream>
#include <fstream>
#include "MinCuts/FordFulkerson.h"
#include "MinCuts/PushRelabel.h"
#include "MinCuts/Dinics.h"
#include "GusfieldCutTree.h"
#include "GomoryHuTree.h"
#include <chrono>

using namespace std;
using namespace std::chrono;

void readGraph(string filePath, vector<unordered_map<int,int> >& graph){
    int n,m;
    ifstream file(filePath, std::ios_base::in);
    file>>n>>m;
    graph.resize(n+1);
    for(int i=0; i < m; ++i){
        int a, b, c;
        file>>a>>b>>c;
        graph[a][b] = c;
        graph[b][a] = c;
    }
}

void benchmark(string filePath, string outputFile){
    vector<unordered_map<int,int> > graph;
    readGraph(filePath, graph);
    ofstream outputGH_D(outputFile + "GH_D", std::ios_base::out);
    ofstream outputGH_PR(outputFile + "GH_PR", std::ios_base::out);
    ofstream outputGH_FF(outputFile + "GH_FF", std::ios_base::out);
    ofstream outputGS_D(outputFile + "GS_D", std::ios_base::out);
    ofstream outputGS_PR(outputFile + "GS_PR", std::ios_base::out);
    ofstream outputGS_FF(outputFile + "GS_FF", std::ios_base::out);
    auto start = high_resolution_clock::now();
    auto stop = high_resolution_clock::now();

    for(int NUM_OF_THREADS = 1; NUM_OF_THREADS <= 4; NUM_OF_THREADS*=2){
        cout<<"doing NUM_OF_THREADS: "<<NUM_OF_THREADS<<endl;
        FordFulkerson* fordFulkerson[NUM_OF_THREADS];
        for(int i=0; i < NUM_OF_THREADS; ++i){
            fordFulkerson[i] = new FordFulkerson();
        }
        Dinics* dinics[NUM_OF_THREADS];
        for(int i=0; i < NUM_OF_THREADS; ++i){
            dinics[i] = new Dinics();
        }
        PushRelabel* pushRelabel[NUM_OF_THREADS];
        for(int i=0; i < NUM_OF_THREADS; ++i){
            pushRelabel[i] = new PushRelabel();
        }

        start = high_resolution_clock::now();
        GusfieldCutTree gusfieldCutTree_fordFulkerson(graph, (MinCutFunc**)fordFulkerson, NUM_OF_THREADS);
        stop = high_resolution_clock::now();
        outputGS_FF<<"GusfieldCutTree::fordFulkerson "<<duration_cast<microseconds>(stop - start).count()<<endl;
        cout<<'\t'<<1<<endl;
        start = high_resolution_clock::now();
        GomoryHuTree gomoryHuTree_fordFulkerson(graph, (MinCutFunc**)fordFulkerson, NUM_OF_THREADS);
        stop = high_resolution_clock::now();
        outputGH_FF<<"GomoryHuTree::fordFulkerson "<<duration_cast<microseconds>(stop - start).count()<<endl;
        cout<<'\t'<<2<<endl;
        start = high_resolution_clock::now();
        GusfieldCutTree gusfieldCutTree_dinics(graph, (MinCutFunc**)dinics, NUM_OF_THREADS);
        stop = high_resolution_clock::now();
        outputGS_D<<"GusfieldCutTree::dinics "<<duration_cast<microseconds>(stop - start).count()<<endl;
        cout<<'\t'<<3<<endl;
        start = high_resolution_clock::now();
        GomoryHuTree gomoryHuTree_dinics(graph, (MinCutFunc**)dinics, NUM_OF_THREADS);
        stop = high_resolution_clock::now();
        outputGH_D<<"GomoryHuTree::dinics "<<duration_cast<microseconds>(stop - start).count()<<endl;
        cout<<'\t'<<4<<endl;
        start = high_resolution_clock::now();
        GusfieldCutTree gusfieldCutTree_pushRelabel(graph, (MinCutFunc**)pushRelabel, NUM_OF_THREADS);
        stop = high_resolution_clock::now();
        cout<<'\t'<<5<<endl;
        outputGS_PR<<"GusfieldCutTree::pushRelabel "<<duration_cast<microseconds>(stop - start).count()<<endl;
//        start = high_resolution_clock::now();
//        GomoryHuTree gomoryHuTree_pushRelabel(graph, (MinCutFunc**)pushRelabel, NUM_OF_THREADS);
//        stop = high_resolution_clock::now();
//        cout<<'\t'<<6<<endl;
//        outputGH_PR<<"GomoryHuTree::pushRelabel "<<duration_cast<microseconds>(stop - start).count()<<endl;
    }
}
#endif //GOMORYHU_BENCHMARK_H
