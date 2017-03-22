//
// Created by admin on 16/03/2017.
//

#ifndef GRAD_BKZ2_H
#define GRAD_BKZ2_H
#include "MCE.h"

class BKz2:public MCE{
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
        for (int i = 0; i < vNum;i++) if(graph.live[i]) P.insert(i);


    }
    void solve(){
        BronKerboschz(R, P, X, recursiveCount);
    }
private:
    set<int> P;
    set<int> X;
    set<int> R;
    void BronKerboschz(set<int> R, set<int> P, set<int> X, int recursiveCallCount);
    void pivotSelection(set<int> &, set<int> &, vector<int> &, int);
};


#endif //GRAD_BKZ2_H
