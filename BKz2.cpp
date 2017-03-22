//
// Created by admin on 16/03/2017.
//



#include "BKz2.h"
void quickSort(vector<int> &orders, vector<int> &degrees, int l,int r);

void setPrint(set<int> x, string name);

void BKz2::pivotSelection(set<int> &P,set <int> &X, vector<int> &P_Nu, int currentLB)
{

    vector<int> r2c(graph.nodes, -1);
    vector<int> c2r(P.size());
    vector<int> remaining;
    vector<node> &g = graph.g;
    int index = 0;
    vector<vector<bool>> color(
            P.size(),
            vector<bool>(currentLB - 1, true));

    for(set<int>::iterator i = P.begin(); i != P.end(); i++){
        int num = *i;
        r2c[num] = index;
        c2r[index] = num;
        index++;
    }

    for(int i = 0; i < P.size(); i++){
        int rnum = c2r[i];
        int selected = 0;
        while(selected < currentLB - 1 && !color[i][selected]) selected++;
        if(selected >= currentLB - 1) P_Nu.push_back(c2r[i]);
        else
            for(set<int>::iterator v = g[rnum].begin(); v != g[rnum].end(); v++){
                int cnum = r2c[*v];
                if(cnum != -1) color[cnum][selected] = false;
            }
    }

}

void BKz2::BronKerboschz(set<int> R, set<int> P, set<int> X, int recursiveCallCount)
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
    //set<int> P_Nu;
    vector<int> P_Nu;
    PuX.clear();
    P_Nu.clear();


    if (P.size() + R.size() < lb) return;
    if(P.size() != 0) {
        if(recursiveCallCount <= 0) pivotSelection(P, X, P_Nu, lb - recursiveCallCount);
        else {
            set_union(P.begin(), P.end(), X.begin(), X.end(), inserter(PuX, PuX.end()));
            set<int>::iterator puxt = PuX.begin();
            set_difference(P.begin(), P.end(), g[*puxt].begin(), g[*puxt].end(), inserter(P_Nu, P_Nu.end()));
#if DEBUG
            cout << "Current u:" << *puxt << endl;
            setPrint(P_Nu,"P-N(u)");
#endif
        }
    }

/*
    if(PuX.size() != 0) {
        set<int>::iterator puxt = PuX.begin();
        set_difference(P.begin(), P.end(), g[*puxt].begin(), g[*puxt].end(), inserter(P_Nu, P_Nu.end()));
#if DEBUG
        cout << "Current u:" << *puxt << endl;
        setPrint(P_Nu,"P-N(u)");
#endif
        }
       */

    for(vector<int>::iterator v = P_Nu.begin(); v != P_Nu.end(); v++){
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
#if DEBUG
            setPrint(RuV, "new R");
            setPrint(PnNv, "new P");
            setPrint(XnNv, "new X");
#endif
            BronKerboschz(RuV, PnNv, XnNv, recursiveCallCount + 1);//++recursiveCallCount);
            int temp = *v;
            X.insert(temp);
            P.erase(temp);
        }
    }
}



