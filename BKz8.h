//
// Created by admin on 16/03/2017.
//

#ifndef GRAD_BKZ8_H
#define GRAD_BKZ8_H
#include "MCE.h"
#define DENSITY_THRESHOLD 0.006
class BKz8:public MCE{
public:
    void preprocessing(){
        P.clear();
        X.clear();
        R.clear();



        for(int t = 0; t < vNum; t++) graph.d[t] = graph.g[t].size();
        auto start = high_resolution_clock::now();

        graph.basicInfo();
        //graph.filterMixed_();

        graph.filterBasedOnDegree();
        //graph.basicInfo();
        graph.filterBasedOnEdge();
        //graph.basicInfo();
        graph.filterBasedOnDegree();
        //graph.basicInfo();
        graph.filterBasedOnEdge();
        //graph.basicInfo();
        graph.filterBasedOnDegree();

        //for(int t = 0; t < vNum; t++) graph.d[t] = graph.g[t].size();
        //graph.filterBasedOnKcore2();
        graph.basicInfo();
        //graph.basicInfo();
        for(int t = 0; t < vNum; t++) graph.d[t] = graph.g[t].size();
        //for(int i = 0; i < vNum; i++) if(graph.live[i]) P.insert(i);
        cout << duration_cast<milliseconds>(high_resolution_clock::now() - start).count() << "ms\n";
        //exit(0);


    }
    void solve(){
        dfsGenerate();
        //BronKerboschz(graph, P, X, recursiveCount);
    }
private:
    set<int> P;
    set<int> X;
    vector<int> R;
    int initP;
    vector<int> subgraph_c2r;
    vector<int> subgraph_r2c;

    void BronKerboschz(Graph &subgraph, set<int> P, set<int> X, int recursiveCallCount);
    void pivotSelection2(Graph &subgraph, set<int> &, set<int> &, vector<int> &, int);
    bool dfsRun(set<int> &ans, vector<bool> &live, int point);
    bool bfsRun(set<int> &ans, vector<bool> &live, int point);
    void dfsGenerate();
};


#endif //GRAD_BKZ8_H
