#include "graph.h"

void Graph::init(int vNum) {
    nodes = vNum;
    g.resize(vNum);
    live.resize(vNum);
    fill(live.begin(), live.end(), true);
    for(int i = 0; i < vNum; i++) g[i].clear();
};

void Graph::print() {
    cout << "Displaying Graph: " << endl;
    for (int i = 0; i < nodes; i++)
    {
        cout << "Vertex: "<< i << " Connects to: [ ";
        for (set<int>::iterator jt = g[i].begin(); jt != g[i].end(); jt++)
            cout << (*jt) <<" ";
        cout << "]" << endl;
    }
    cout << endl;
};

void Graph::kill(){
    for(int i = 0; i < nodes; i++) if(live[i] && g[i].size() == 0) live[i] = false;
}

void Graph::deleteNode(int i){
#if DEBUG
    cout << "Point Deleted:" << i << endl;
#endif
    if(live[i]){
        for(set<int>::iterator v = g[i].begin(); v != g[i].end(); v++) if(live[*v]) g[*v].erase(i);
        g[i].clear();
    }

}

void Graph::filterBasedOnDegree() {
    for (int i = 0; i < nodes; i++)
        if (live[i] && (int)(g[i].size()) < lb - 1) deleteNode(i);
    kill();
}

void Graph::filterBasedOnEdge(){
    set<int> unionOf;
    bool flag;
    for( int i = 0; i < nodes; i++) if(live[i])
            for(set<int>::iterator v = g[i].begin(); v != g[i].end(); v) if(live[*v] && i < (*v)){
                    flag = true;
                    if ((int)(g[i].size()) >= lb - 1 && (int)(g[*v].size()) >= lb - 1){
                        unionOf.clear();
                        set_union(g[i].begin(), g[i].end(), g[*v].begin(), g[*v].end(), inserter(unionOf, unionOf.end()));
                        if((int)(unionOf.size()) >= lb - 2) flag = false;
                    }
                    if(flag){
#if DEBUG
                        cout << "Erased:" << *v << "," << i << endl;
#endif
                        g[i].erase(*v);
                        g[*v].erase(i);
                        v = g[i].begin();
                        while(v != g[i].end() && !live[*v]) v++;
                        if (v == g[i].end()) break;
                    } else v++;
                } else v++;
    kill();
}

bool degreeCompare(vector<node> g, int a, int b)
{
    return g[a].size() < g[b].size();
}

void Graph::filterBasedOnKcore() {//这里会修改图！需要复制一份过来！待修改！
    vector<int> orders(nodes);
    vector<int> coreNumber(nodes);
    set<int> sharedNeighbour;
    vector<node> _g = g;
    int cur_core, max_core;

    for(int i = 0; i < nodes; i++) orders[i] = i;
    kill();//杀死所有度为0的点。
    sort(orders.begin(), orders.end(), bind(degreeCompare, _g, _1, _2));//杀死后正序排序
    int i = 0;
    int remaining;
    while(!live[orders[i]] && i < nodes)i++;
    remaining = nodes - i;//我们假定，之前的点如果死了，那么度一定为0。
    if(i < nodes){
        int curPoint = orders[i];
        cur_core = _g[curPoint].size();//cur_core>=1才对
#if DEBUG
        cout << "k-core[" << curPoint << "]=" << cur_core << endl;
#endif
        max_core = cur_core;
        i++;
        while(i < nodes) {
            curPoint = orders[i];
            if (live[curPoint]) {
                if (_g[curPoint].size() > cur_core) cur_core = _g[curPoint].size();
                if (cur_core > max_core) max_core = cur_core;
                coreNumber[curPoint] = cur_core;
#if DEBUG
                cout << "k-core[" << curPoint << "]=" << cur_core << endl;
#endif
                if (g[curPoint].size() == nodes - i - 1) {
                    for (int j = i + 1; j < nodes; j++)
                    {
                        coreNumber[orders[j]] = cur_core;
#if DEBUG
                        cout << "k-core[" << orders[j] << "]=" << cur_core << endl;
#endif
                    }
                    break;
                }
                sharedNeighbour.clear();
                set_intersection(_g[curPoint].begin(), _g[curPoint].end(), orders.begin() + i, orders.end(),
                                 inserter(sharedNeighbour, sharedNeighbour.end()));
                for (set<int>::iterator v = _g[curPoint].begin(); v != _g[curPoint].end(); v++) {
                    if (live[*v]) _g[*v].erase(curPoint);
                }
                sort(orders.begin() + i + 1, orders.end(), bind(degreeCompare, _g, _1, _2));
            }
            i++;
        }
        int i = 0;
        while(i < nodes){
            if (live[i] && coreNumber[i] < lb) deleteNode(i);
            i++;
        }
    }
    kill();
}