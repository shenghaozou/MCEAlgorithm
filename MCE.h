//
// Created by admin on 15/03/2017.
//

#ifndef GRAD_MCE_H
#define GRAD_MCE_H
#include "graph.h"

class MCE {
protected:
    Graph graph;
    int vNum;
    int sumMCE;
    int recursiveCount = 0;
public:
    void init();
    void printR(set<int> R);
    void run();
    virtual void preprocessing();
    virtual void solve();
};

extern Graph graph;
extern int sumMCE;

#endif //GRAD_MCE_H
