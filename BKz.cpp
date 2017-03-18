//
// Created by admin on 16/03/2017.
//



#include "BKz.h"

void setPrint(set<int> x, string name)
{
    cout << "Set " << name << ":";
    for (set<int>::iterator v = x.begin(); v != x.end(); v++)
        cout << *v << " ";
    cout << endl;
}

void BKz::BronKerboschz(set<int> R, set<int> P, set<int> X, int recursiveCallCount)
{
    vector<node> &g = graph.g;
    vector<bool> &live = graph.live;
#if DEBUG
    cout << "level:" << recursiveCallCount << endl;
    setPrint(R,"R");
    setPrint(P,"P");
    setPrint(X,"X");
#endif
    if (P.size() == 0 && X.size() == 0) {
        printR(R);
        return;
    }

    set<int> PuX;
    set<int> P_Nu;
    int maxDegreePoint;
    int maxDegree;
    PuX.clear();
    P_Nu.clear();
    set_union(P.begin(), P.end(), X.begin(), X.end(), inserter(PuX, PuX.end()));
    /*
    maxDegreePoint = 0;
    maxDegree = 0;
    if(PuX.size() != 0) {
        for(set<int>::iterator puxt = PuX.begin(); puxt != PuX.end(); puxt++){
            if(graph.d[*puxt] > maxDegree){
                maxDegree = graph.d[*puxt];
                maxDegreePoint = *puxt;
            }
        }
    */

    if(PuX.size() != 0) {
        set<int>::iterator puxt = PuX.begin();
        set_difference(P.begin(), P.end(), g[*puxt].begin(), g[*puxt].end(), inserter(P_Nu, P_Nu.end()));
#if DEBUG
        cout << "Current u:" << *puxt << endl;
        setPrint(P_Nu,"P-N(u)");
#endif
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

            BronKerboschz(RuV, PnNv, XnNv, recursiveCallCount + 1);//++recursiveCallCount);
            int temp = *v;
            X.insert(temp);
            P_Nu.erase(temp);
            P.erase(temp);

            if (P_Nu.empty())
                return;
            else
                v = P_Nu.begin();
        }
        else {
            while(v != P_Nu.end() && !live[*v]) v++;
            if (v == P_Nu.end()) return;
        }
    }
}