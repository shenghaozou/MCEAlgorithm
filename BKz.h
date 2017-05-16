//
// Created by admin on 16/03/2017.
//

#ifndef GRAD_BKZ_H
#define GRAD_BKZ_H
#include "MCE.h"

class BKz:public MCE{
public:
    void preprocessing(){
        P.clear();
        X.clear();
        R.clear();
        graph.filterBasedOnDegree();
        //graph.filterBasedOnKcore();
        //graph.filterBasedOnEdge();
        //graph.filterBasedOnDegree();
        for(int t = 0; t < vNum; t++) graph.d[t] = graph.g[t].size();
        for (int i = 0; i < vNum;i++) if(graph.live[i]) P.insert(i);


    }
    void solve(){
        BronKerboschz(R, P, X, recursiveCount);
    }
private:
    void getBranch(set<int> &branch, set<int> &currentP, int currentLB);
    set<int> P;
    set<int> X;
    set<int> R;
    void BronKerboschz(set<int> R, set<int> P, set<int> X, int recursiveCallCount);
};


#endif //GRAD_BKZ_H
