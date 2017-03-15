//
// Created by admin on 15/03/2017.
//

#include "BK.h"

//bronkerbosch w/o pivot//
void BK1::BronKerbosch1(set<int> R, set<int> P, set<int> X, int& recursiveCallCount)
{
    vector<node> &g = graph.g;
    if (P.size() == 0 && X.size() == 0)
        printR(R);
    for (set<int>::iterator v = P.begin(); v != P.end();v)
    {
        set<int> v_;	//create a singleton set {v}
        v_.insert(*v);
#if DEBUG
        cout << "current V:"<< *v << endl;
#endif

        /* BronKerbosch1(R U {v}, P n N(v), X n N(v)) */
        set<int> RuV;
        set<int> XuV;
        set<int> PnNv;
        set<int> XnNv;
        set<int> P_v;

        RuV.clear(); XuV.clear(); PnNv.clear(); XnNv.clear(); P_v.clear();
        set_union(R.begin(), R.end(), v_.begin(), v_.end(), inserter(RuV, RuV.end()));
        set_intersection(P.begin(), P.end(), g[*v].begin(), g[*v].end(), inserter(PnNv, PnNv.end()));
        set_intersection(X.begin(), X.end(), g[*v].begin(), g[*v].end(), inserter(XnNv, XnNv.end()));

        BronKerbosch1(RuV, PnNv, XnNv, ++recursiveCallCount);

        P.erase(*v);
        X.insert(*v);

        if (P.empty())
            return;
        else
            v = P.begin();
    }
}

//Bronkerbosch w/ pivot//
void BK2::BronKerbosch2(set<int> R, set<int> P, set<int> X, int& recursiveCallCount)
{
    vector<node> &g = graph.g;

    if (P.size() == 0 && X.size() == 0) {
        printR(R);
        return;
    }

    set<int> PuX;
    set<int> P_Nu;
    PuX.clear();
    P_Nu.clear();
    set_union(P.begin(), P.end(), X.begin(), X.end(), inserter(PuX, PuX.end()));

    if(PuX.size() != 0) {
        set<int>::iterator puxt = PuX.begin();
        set_difference(P.begin(), P.end(), g[*puxt].begin(), g[*puxt].end(), inserter(P_Nu, P_Nu.end()));
    }

    for(set<int>::iterator v = P_Nu.begin(); v != P_Nu.end(); v)
    {
        set<int> v_;	//create a singleton set {v}
        v_.insert(*v);
#if DEBUG
        cout << "current V:"<< *v << endl;
#endif

        set<int> RuV;
        set<int> XuV;
        set<int> PnNv;
        set<int> XnNv;
        set<int> P_v;

        RuV.clear(); XuV.clear(); PnNv.clear(); XnNv.clear(); P_v.clear();

        set_union(R.begin(), R.end(), v_.begin(), v_.end(), inserter(RuV, RuV.end()));
        set_intersection(P.begin(), P.end(), g[*v].begin(), g[*v].end(), inserter(PnNv, PnNv.end()));
        set_intersection(X.begin(), X.end(), g[*v].begin(), g[*v].end(), inserter(XnNv, XnNv.end()));

        BronKerbosch2(RuV, PnNv, XnNv, ++recursiveCallCount);

        //RuV.clear(); XuV.clear(); PnNv.clear(); XnNv.clear(); P_v.clear();

        P.erase(*v);
        X.insert(*v);

        if (P.empty())
            return;
        else
            v = P.begin();
    }
}