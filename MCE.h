//
// Created by admin on 15/03/2017.
//

#ifndef GRAD_MCE_H
#define GRAD_MCE_H
#include "graph.h"

class MCE {
private:
    Graph graph;
    int vNum;
    int sumMCE;
public:
    void init();
    void printR(set<int> R);
    virtual void preprocessing();
    virtual void solve();
};


#endif //GRAD_MCE_H
