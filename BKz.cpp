//
// Created by admin on 16/03/2017.
//

#include "BKz.h"
void BKz::BronKerboschz(set<int> R, set<int> P, set<int> X, int& recursiveCallCount)
{
    vector<node> &g = graph.g;
    vector<bool> &live = graph.live;

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

    for(set<int>::iterator v = P_Nu.begin(); v != P_Nu.end(); v){
        set<int> v_;	//create a singleton set {v}
        if(live[*v]) {
            v_.insert(*v);
#if DEBUG
            cout << "current V:"<< *v << endl;
#endif

            set<int> RuV;
            set<int> XuV;
            set<int> PnNv;
            set<int> XnNv;
            set<int> P_v;

            RuV.clear();
            XuV.clear();
            PnNv.clear();
            XnNv.clear();
            P_v.clear();

            set_union(R.begin(), R.end(), v_.begin(), v_.end(), inserter(RuV, RuV.end()));
            set_intersection(P.begin(), P.end(), g[*v].begin(), g[*v].end(), inserter(PnNv, PnNv.end()));
            set_intersection(X.begin(), X.end(), g[*v].begin(), g[*v].end(), inserter(XnNv, XnNv.end()));

            BronKerboschz(RuV, PnNv, XnNv, ++recursiveCallCount);


            P.erase(*v);
            X.insert(*v);
            if (P.empty())
                return;
            else
                v = P.begin();
        }
        else {
            while(v != P.end() && !live[*v]) v++;
            if (v == P.end()) return;
        }
    }
}