#include "MCE.h"

class BK1:public MCE{
public:
    void preprocessing(){
        P.clear();
        X.clear();
        R.clear();
        for (int i = 0; i < vNum;i++) P.insert(i);
    }
    void solve(){
        BronKerbosch1(R, P, X, recursiveCount);
    }
private:
    set<int> P;
    set<int> X;
    set<int> R;
    void BronKerbosch1(set<int> R, set<int> P, set<int> X, int& recursiveCallCount);
};

class BK2:public MCE{
public:
    void preprocessing(){
        P.clear();
        X.clear();
        R.clear();
        for (int i = 0; i < vNum;i++) P.insert(i);
    }
    void solve(){
        BronKerbosch2(R, P, X, recursiveCount);
    }
private:
    set<int> P;
    set<int> X;
    set<int> R;
    void BronKerbosch2(set<int> R, set<int> P, set<int> X, int& recursiveCallCount);
};