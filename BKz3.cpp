//
// Created by admin on 16/03/2017.
//



#include "BKz3.h"
void quickSort(vector<int> &orders, vector<int> &degrees, int l,int r);

void setPrint(set<int> x, string name);

void BKz3::pivotSelection(set<int> &P,set <int> &X, vector<int> &P_Nu, int currentLB)
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

void BKz3::pivotSelection2(set<int> &P,set <int> &X, vector<int> &P_Nu, int currentLB)
{

    vector<int> r2c(graph.nodes, -1);
    vector<int> c2r(P.size());
    vector<int> color(P.size());
    vector<node> &g = graph.g;
    int index = 0;
    vector<int>occupied(currentLB - 1);
    vector<int>renumber(currentLB - 1);
    //cout << "Start PivotSelection2" << endl;
    fill(color.begin(), color.end(), -1);

    for(set<int>::iterator i = P.begin(); i != P.end(); i++){
        int num = *i;
        r2c[num] = index;
        c2r[index] = num;
        index++;
    }

    for(int i = 0; i < P.size(); i++) {
        int rnum = c2r[i];
        int selected = 0;
        fill(occupied.begin(), occupied.end(), -1);
        for (set<int>::iterator v = g[rnum].begin(); v != g[rnum].end(); v++) {
            int cnum = r2c[*v];
            if (cnum != -1 && color[cnum] != -1) occupied[color[cnum]] = occupied[color[cnum]] == -1 ? cnum : -2;
        }
        while (selected < currentLB - 1 && occupied[selected] != -1) selected++;
        if (selected >= currentLB - 1)
        {
            bool successfulRenumber = false;
            for(int newColor = 0; newColor < currentLB - 1; newColor++){ 
                if (occupied[newColor] >= 0) {
                    fill(renumber.begin(), renumber.end(), true);
                    renumber[newColor] = false;
                    int cnum = occupied[newColor];
                    int rnum = c2r[cnum];
                    for (set<int>::iterator v = g[rnum].begin(); v != g[rnum].end(); v++) {
                        int cnumNei = r2c[*v];
                        if (cnumNei != -1 && color[cnumNei] != -1) renumber[color[cnumNei]] = false;
                    }
                    selected = 0;
                    while (selected < currentLB - 1 && !renumber[selected]) selected++;
                    if (selected < currentLB - 1) {
                        color[cnum] = selected;
                        color[i] = newColor;
                        successfulRenumber = true;
                        //cout << "successful ReColor!" << endl;
                        break;
                    }
                }
            }
            if (!successfulRenumber) P_Nu.push_back(c2r[i]);
        } else color[i] = selected;
    }
    //cout << "Finish PivotSelection2" << endl;
}

void BKz3::BronKerboschz(set<int> P, set<int> X, int recursiveCallCount)
{
    vector<node> &g = graph.g;
    vector<bool> &live = graph.live;

#if DEBUG
    cout << "level:" << recursiveCallCount << endl;
    //setPrint(R,"R");
    setPrint(P,"P");
    setPrint(X,"X");
#endif
    if (P.size() == 0 && X.size() == 0) {
        printR(R);
        return;
    }

    set<int> PuX;
    vector<int> P_Nu;
    PuX.clear();
    P_Nu.clear();


    if (P.size() + R.size() < lb) return;
    if(P.size() != 0) {
        if(P.size() > 0.2 * initP && lb - recursiveCallCount >= 3/*recursiveCallCount <= 0*/)
        {
            pivotSelection2(P, X, P_Nu, lb - recursiveCallCount);
            //cout << "P_size:" << P.size() << " level:" << recursiveCallCount << "P_Nu_size:" << P_Nu.size() << endl;
        }
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

    for(vector<int>::iterator v = P_Nu.begin(); v != P_Nu.end(); v++) {

    

        set<int> v_;	//create a singleton set {v}
        if(live[*v]) {
            v_.insert(*v);
#if DEBUG
            cout << "current V:"<< *v << endl;
#endif

            set<int> XuV;
            set<int> PnNv;
            set<int> XnNv;
            set<int> P_v;

            XuV.clear();
            PnNv.clear();
            XnNv.clear();
            P_v.clear();

            R.push_back(*v);
            set_intersection(P.begin(), P.end(), g[*v].begin(), g[*v].end(), inserter(PnNv, PnNv.end()));
            set_intersection(X.begin(), X.end(), g[*v].begin(), g[*v].end(), inserter(XnNv, XnNv.end()));
#if DEBUG
            setPrint(PnNv, "new P");
            setPrint(XnNv, "new X");
#endif
            BronKerboschz(PnNv, XnNv, recursiveCallCount + 1);
            R.pop_back();
            int temp = *v;
            X.insert(temp);
            P.erase(temp);
        }

    }
}



