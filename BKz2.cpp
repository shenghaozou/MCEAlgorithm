//
// Created by admin on 16/03/2017.
//



#include "BKz2.h"
void quickSort(vector<int> &orders, vector<int> &degrees, int l,int r);

void setPrint(set<int> x, string name);

void BKz2::pivotSelection(set<int> &P_Nu,set <int> &X)
{
    enum Status{Dead = 0, Protected, Center, Selected, Shared};
    vector<Status> pivot;
    vector<int> pivotNum;
    static vector<int> pointMap(graph.nodes);
    set<int> selected;
    vector<int> temp;
    vector<node> &g = graph.g;
    set<int> tempP_Nu;
    int index = 0;
    set<int>::iterator i;
    selected.clear();
    fill(pointMap.begin(), pointMap.end(), -1);
    pivotNum.clear();

    int smallest = 0;
    for(i = P_Nu.begin(); i != P_Nu.end(); i++){
        int num = *i;
        if(pointMap[num] == -1) {
            pointMap[num] = index++;
            pivot.push_back(Center);
            pivotNum.push_back(num);
        }//check whether it is right!
    }
    for(i = X.begin(); i != X.end(); i++){
        int num = *i;
        if(pointMap[num] == -1) {
            pointMap[num] = index++;
            pivot.push_back(Center);
            pivotNum.push_back(num);
        }//check whether it is right!
    }
    while(smallest < index){
        temp.clear();
        int realNum = pivotNum[smallest];
        pivot[smallest] = Selected;
        for(i = g[realNum].begin(); i != g[realNum].end(); i++)
        {
            int num = *i;
            int mapedNum = pointMap[num];
            if (mapedNum != -1){
                temp.push_back(num);
                pivot[mapedNum] = Dead;
            }
        } // Kill points
        for (vector<int>::iterator i = temp.begin(); i != temp.end(); i++)
            for (set<int>::iterator t = g[*i].begin(); t != g[*i].end(); t++){
                int num = *t;
                int mapedNum = pointMap[num];
                if (mapedNum != -1 && pivot[mapedNum] == Center) pivot[mapedNum] = Protected;
            } // Protect points
        smallest++;
        while(smallest < index && pivot[smallest] != Center) smallest++;
    }
    for(int i = 0; i < index; i++){
        if(pivot[i] == Selected || pivot[i] == Protected){
            tempP_Nu.insert(pivotNum[i]);
            //set_difference(P_Nu.begin(), P_Nu.end(), g[pivotNum[i]].begin(), g[pivotNum[i]].end(),inserter(tempP_Nu, tempP_Nu.end()));
        }
    }
    P_Nu = tempP_Nu;


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
    set<int> P_Nu;
    int maxDegreePoint;
    int maxDegree;
    PuX.clear();
    P_Nu.clear();
    set_union(P.begin(), P.end(), X.begin(), X.end(), inserter(PuX, PuX.end()));

    maxDegreePoint = 0;
    maxDegree = 0;
    /*
    if(PuX.size() != 0) {
        for(set<int>::iterator puxt = PuX.begin(); puxt != PuX.end(); puxt++){
            if(graph.d[*puxt] > maxDegree){
                maxDegree = graph.d[*puxt];
                maxDegreePoint = *puxt;
            }
        }
        set_difference(P.begin(), P.end(), g[maxDegreePoint].begin(), g[maxDegreePoint].end(), inserter(P_Nu, P_Nu.end()));
    }
     */

    if (P.size() + R.size() < lb) return;


    if(PuX.size() != 0) {
        set<int>::iterator puxt = PuX.begin();
        set_difference(P.begin(), P.end(), g[*puxt].begin(), g[*puxt].end(), inserter(P_Nu, P_Nu.end()));
#if DEBUG
        cout << "Current u:" << *puxt << endl;
        setPrint(P_Nu,"P-N(u)");
#endif
    }

    /*
    P_Nu = P;
    pivotSelection(P_Nu, X);
#if DEBUG
    setPrint(P_Nu, "P_Nu");
#endif
     */

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
#if DEBUG
            setPrint(RuV, "new R");
            setPrint(PnNv, "new P");
            setPrint(XnNv, "new X");
#endif
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



