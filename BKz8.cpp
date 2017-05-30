//
// Created by admin on 16/03/2017.
//



#include "BKz8.h"
void setDebug(set<int> &d);
void vectorDebug(vector<int> &d);
void quickSort(vector<int> &orders, vector<int> &degrees, int l,int r);

void setPrint(set<int> x, string name);

void BKz8::pivotSelection2(Graph &subgraph, set<int> &P,set <int> &X, vector<int> &P_Nu, int currentLB)
{

    vector<int> r2c(subgraph.nodes, -1);
    vector<int> c2r(P.size());
    vector<int> color(P.size());
    vector<node> &g = subgraph.g;

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

void BKz8::BronKerboschz(Graph &subgraph, set<int> P, set<int> X, int recursiveCallCount)
{
    vector<node> &g = subgraph.g;
    vector<bool> &live = subgraph.live;

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
        if(P.size() > subgraph.coloringThreshold * initP && lb - recursiveCallCount >= 3/*recursiveCallCount <= 0*/)
        {
            pivotSelection2(subgraph, P, X, P_Nu, lb - recursiveCallCount);
            //cout << "P_size:" << P.size() << " level:" << recursiveCallCount << "P_Nu_size:" << P_Nu.size() << endl;
        }
        else {
            //cout << "P:";
            //setDebug(P);
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
            BronKerboschz(subgraph, PnNv, XnNv, recursiveCallCount + 1);
            R.pop_back();
            int temp = *v;
            X.insert(temp);
            P.erase(temp);
        }

    }
}

void BKz8::dfsGenerate() {
    Graph subgraph;
    subgraph_r2c.resize(graph.nodes);
    vector<bool> tmpLive(graph.live);
    set<int> ans;
    set<int> tmp;
    int i = 0;
    int e = 0;
    int t;

    int resCount = 0;
    double double_v, double_e, density;
    while(!tmpLive[i]) i++;
    while(i < tmpLive.size()){
        ans.clear();
        X.clear();
        R.clear();
        bfsRun(ans, tmpLive, i);
        cout << "Ans:" << ans.size() << endl;
        //setDebug(ans);
        subgraph_c2r.resize(ans.size());
        t = 0;
        for(set<int>::iterator v = ans.begin(); v != ans.end(); v++){
            subgraph_c2r[t] = *v;
            subgraph_r2c[*v] = t;
            t++;
        }
        //cout << "R2C:";
        //vectorDebug(subgraph_r2c);
        int ansSize = ans.size();


        if(ans.size() >= graph.lb) {
            cout << "Search Size:" << ans.size() << endl;
            subgraph.init(ans.size());

            for (int i = 0; i < ans.size(); i++) {
                tmp.clear();
                set_intersection(graph.g[subgraph_c2r[i]].begin(), graph.g[subgraph_c2r[i]].end(), ans.begin(), ans.end(), inserter(tmp, tmp.end()));
                //cout << "graph(" << subgraph_c2r[i] << ")";
                //setDebug(graph.g[subgraph_c2r[i]]);
                //cout << "Tmp:";
                //setDebug(tmp);
                for(set<int>::iterator v = tmp.begin(); v != tmp.end(); v++) subgraph.g[i].insert(subgraph_r2c[*v]);
                //cout << "subgraph(" << i << ")";
                //setDebug(subgraph.g[i]);
                e += subgraph.g[i].size();

            }
            double_v = ans.size();
            double_e = e / 2;
            density = double_e / (double_v * (double_v - 1) / 2);
            if(density > DENSITY_THRESHOLD) subgraph.coloringThreshold = 1;
            else subgraph.coloringThreshold = 0.2;
            //cout << "Density" << density << " ONLY_PIVOTING:" << (density > DENSITY_THRESHOLD) << endl;
            initP = ans.size();
            ans.clear();
            for(int i = 0; i < ansSize; i++) ans.insert(i);
            for(int t = 0; t < ansSize; t++) subgraph.d[t] = subgraph.g[t].size();
            //subgraph.basicInfo();
            BronKerboschz(subgraph, ans, X, resCount);
        }
        while(i < tmpLive.size() && !tmpLive[i]) i++;
    }
}

bool BKz8::dfsRun(set<int> &ans, vector<bool> &live, int point) {
    vector<node> &g = graph.g;
    assert(live[point]);
    cout << "ANS_SIZE:" << ans.size() << endl;
    ans.insert(point);

    live[point] = false;
    for(set<int>::iterator v = g[point].begin(); v != g[point].end(); v++) if(live[*v]) dfsRun(ans, live, *v);
}

bool BKz8::bfsRun(set<int> &ans, vector<bool> &live, int point) {
    vector<node> &g = graph.g;
    assert(live[point]);
    queue<int> q;
    q.push(point);
    while(!q.empty()){
        int num = q.front();
        q.pop();
        if(live[num]){
            live[num] = false;
            for(set<int>::iterator v = g[num].begin(); v != g[num].end(); v++) if(live[*v]) q.push(*v);
            ans.insert(num);
        }
    }
    return false;
}






