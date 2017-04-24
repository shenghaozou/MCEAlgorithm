//
// Created by admin on 03/04/2017.
//

#ifndef GRAD_EXPERIMENT_H
#define GRAD_EXPERIMENT_H
#include "graph.h"

class experiment {
    Graph graph;
public:
    int random = 0;
    int testTime = 100;
    int totalTestTime = 200;
    void generateGraph(double precise, int size);
    void generateGraph2(double precise, int size);
    double doExperimentNormal(double density, int size);
    int BK(set<int>, set<int>, int recursiveCallCount);
    double doExperimentAd(double density, int size);
    void massTest();
    bool validTest(double, int);
};


#endif //GRAD_EXPERIMENT_H
