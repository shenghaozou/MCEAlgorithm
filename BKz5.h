//
// Created by admin on 24/04/2017.
//

#ifndef GRAD_BKZ5_H
#define GRAD_BKZ5_H

#include "MCE.h"

class BKz5:public MCE{
public:
    void preprocessing(){
        P.clear();
        X.clear();
        R.clear();
        for(int t = 0; t < vNum; t++) graph.d[t] = graph.g[t].size();
        graph.filterBasedOnDegree();
        graph.filterBasedOnKcore();
        graph.filterBasedOnEdge();
        for(int t = 0; t < vNum; t++) graph.d[t] = graph.g[t].size();
        //for(int i = 0; i < vNum; i++) if(graph.live[i]) P.insert(i);

    }
    void solve();
private:
    set<int> P;
    set<int> X;
    vector<int> R;
    int initP;
    void BronKerboschz(set<int> P, set<int> X, int recursiveCallCount);
    void pivotSelection2(set<int> &, set<int> &, vector<int> &, int);
};


#endif //GRAD_BKZ4_H
