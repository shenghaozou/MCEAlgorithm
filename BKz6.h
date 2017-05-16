//
// Created by admin on 24/04/2017.
//

#ifndef GRAD_BKZ6_H
#define GRAD_BKZ6_H

#include "MCE.h"

class BKz6:public MCE{
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
    vector<int> P;
    vector<int> X;
    vector<int> R;
    int initP;
    void BronKerboschz(vector<int> P, vector<int> X, int recursiveCallCount);
};


#endif //GRAD_BKZ4_H
