//
// Created by admin on 16/03/2017.
//

#ifndef GRAD_BKZ3_H
#define GRAD_BKZ3_H
#include "MCE.h"

class BKz3:public MCE{
public:
    void preprocessing(){
        P.clear();
        X.clear();
        R.clear();



        for(int t = 0; t < vNum; t++) graph.d[t] = graph.g[t].size();
        auto start = high_resolution_clock::now();
        graph.basicInfo();
        graph.filterBasedOnDegree();
        //graph.basicInfo();
        graph.filterBasedOnEdge();
        graph.filterBasedOnDegree();
        //for(int t = 0; t < vNum; t++) graph.d[t] = graph.g[t].size();
        //graph.filterBasedOnKcore2();
        graph.basicInfo();
        //graph.basicInfo();
        //for(int t = 0; t < vNum; t++) graph.d[t] = graph.g[t].size();
        //for(int i = 0; i < vNum; i++) if(graph.live[i]) P.insert(i);
        cout << duration_cast<milliseconds>(high_resolution_clock::now() - start).count() << "ms\n";
        //exit(0);


    }
    void solve(){
        initP = P.size();
        BronKerboschz(P, X, recursiveCount);
    }
private:
    set<int> P;
    set<int> X;
    vector<int> R;
    int initP;
    void BronKerboschz(set<int> P, set<int> X, int recursiveCallCount);
    void pivotSelection(set<int> &, set<int> &, vector<int> &, int);
    void pivotSelection2(set<int> &, set<int> &, vector<int> &, int);
};


#endif //GRAD_BKZ2_H
