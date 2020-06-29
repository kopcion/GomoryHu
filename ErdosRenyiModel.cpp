//
// Created by kopcion on 06.06.2020.
//

#include <vector>
#include <unordered_map>
#include <ctime>

using namespace std;

vector<unordered_map<int,int>> edgeParametrized(int vertices, int edges, int maxWeight){
    std::srand(time(nullptr));
    vertices++; // enumerating from 1, not 0
    vector<unordered_map<int,int>> graph(vertices);

    //edge coding
    for(int i=0; i < edges; ++i){
        int edge = rand()%(vertices*vertices);
        int weight = rand()%maxWeight;
        graph[edge%vertices][edge/vertices] = weight;
        graph[edge/vertices][edge%vertices] = weight;
    }
}