//
// Created by kopcion on 29.07.2020.
//

#ifndef GOMORYHU_BARABASIALBERT_H
#define GOMORYHU_BARABASIALBERT_H

#include <unordered_map>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <iostream>

using namespace std;

vector<unordered_map<int,int> > barabasiAlbertModel(int n){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    vector<unordered_map<int,int> > out(n+1);
    std::normal_distribution<double> distribution (1000.0,100.0);
    std::ofstream ofs ("../BarabasiAlbert" + to_string(n) + ".txt", std::ofstream::out);
    int degree_sum = 12;
    vector<int> degrees(n+1);

    {
        out[1][2] = max((int) distribution(generator), 1);
        out[2][1] = max((int) distribution(generator), 1);
        out[2][3] = max((int) distribution(generator), 1);
        out[3][2] = max((int) distribution(generator), 1);
        out[3][4] = max((int) distribution(generator), 1);
        out[4][3] = max((int) distribution(generator), 1);
        out[4][5] = max((int) distribution(generator), 1);
        out[5][4] = max((int) distribution(generator), 1);
        out[1][4] = max((int) distribution(generator), 1);
        out[4][1] = max((int) distribution(generator), 1);
        out[2][5] = max((int) distribution(generator), 1);
        out[5][2] = max((int) distribution(generator), 1);
        degrees[1] = 2;
        degrees[2] = 3;
        degrees[3] = 2;
        degrees[4] = 3;
        degrees[5] = 2;

    }
    std::uniform_int_distribution<int> prob(0,100);
    int discarded = 0;
    for(int i=6; i <= n; ++i){
        int tmp = 0;
        bool connected = false;
        for(int j=1; j < i; ++j){
            int weight = max((int)distribution(generator), 1);
            int probability = (int)((double)degrees[j] / (double)degree_sum * 100);
            if(probability >= prob(generator)){
                tmp += 2;
                out[i][j] = weight;
                out[j][i] = weight;
                degrees[i]++;
                degrees[j]++;
                connected = true;
            } else {
                discarded++;
            }
        }
        if(!connected){
            int weight = max((int)distribution(generator), 1);
            tmp++;
            out[i][i-1] = weight;
            out[i-1][i] = weight;
            degrees[i]++;
            degrees[i-1]++;
        }
        degree_sum += tmp;
    }

    ofs << n << " " << degree_sum<<endl;
    for(int i=1; i < out.size(); ++i){
        for(auto v : out[i]){
            ofs << i << " " << v.first<<" "<<v.second<<endl;
        }
    }

    ofs.close();
    return out;
}
#endif //GOMORYHU_BARABASIALBERT_H
