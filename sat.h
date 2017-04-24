//
// Created by admin on 15/04/2017.
//

#ifndef GRAD_SAT_H
#define GRAD_SAT_H
#include "common.h"
#include <queue>

struct nodeSat{
    int reason;
    int var;
};



struct clause{
    vector<int> data;
    inline int size(){return data.size();}
    inline void push_back(int n){data.push_back(n);}
    int alive;
    bool sat;
    bool relax;
};

class Sat {
public:
    Sat(int vNum){
        nodes = vNum;
        posWatches.resize(vNum);
        negWatches.resize(vNum);
        alive.resize(vNum);
    }
    void addClause(vector<int> &t, bool rlx = false);
    void init(bool firstTime);
    bool up(int n);
    void relax(int upLit);
    inline int size(){return data.size();}
    void debug();

private:
    int nodes;
    int failed, failed_index;
    int aliveClauses;
    int newVar();
    vector<vector<int>> posWatches, negWatches;
    vector<clause> data;
    vector<bool> alive;
    vector<nodeSat> reason;
    inline int toVar(int p) {return abs(p) - 1;}
};


#endif //GRAD_SAT_H
