//
// Created by kopcion on 11.07.2020.
//

#include <unordered_map>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>

using namespace std;

vector<unordered_map<int,int> > wattStrogatzModel(int n, int k, int beta = 10){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    vector<unordered_map<int,int> > out(n+1);
    std::normal_distribution<double> distribution (1000.0,100.0);

    for(int i=0; i < n; ++i){
        for(int j= -k/2; j < k/2; j++){
            if((i+j + n)%n == i) continue;
            int weight = max((int)distribution(generator), 1);
            out[i+1][(i+j + n)%n + 1] = weight;
//            out[(i+j + n)%n + 1][i+1] = weight;
        }
    }

    for(int i=0; i < n; ++i){
        for(int j = i+1; j <= i+k/2; ++j){
            if( beta > generator()%100){
                cout<<"rewire"<<endl;
                int l = generator()%(n-k);
                int m = 0;
                while(l){
                    if(out[i+1].find((j+m)%n + 1) == out[i+1].end() && (j+m)%n != i){
                        l--;
                    }
                    m++;
                }
                out[i+1][(j+m)%n + 1] = out[i+1][j%n+1];
                out[(j+m)%n + 1][i+1] = out[i+1][j%n+1];
                out[i+1].erase(j%n+1);
                out[j%n+1].erase(i+1);
            }
        }
    }

    std::ofstream ofs ("../WattsStrogatzN" + to_string(n) + "K" + to_string(k) + ".txt", std::ofstream::out);

    ofs << n << " " << n*k<<endl;
    for(int i=1; i < out.size(); ++i){
        for(auto v : out[i]){
            ofs << i << " " << v.first<<" "<<v.second<<endl;
        }
    }

    ofs.close();
    return out;
}