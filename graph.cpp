#include "graph.h"

void Graph::init(int vNum) {
    nodes = vNum;
    g.resize(vNum);
    live.resize(vNum);
    d.resize(vNum);
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
#if GRAPH_DEBUG
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

bool degreeCompare(vector<int> g, int a, int b)
{
    return g[a] < g[b];
}

void Graph::filterBasedOnKcore() {//这里会修改图！需要复制一份过来！待修改！
    orders.resize(nodes);
    coreNumber.resize(nodes);
    vector<int> degrees(nodes);
    vector<bool> livePoints(nodes);
    int cur_core, max_core;

    livePoints = live;

    for(int i = 0; i < nodes; i++) orders[i] = i;
    kill();//杀死所有度为0的点。
    degrees = d;
    sort(orders.begin(), orders.end(), bind(degreeCompare, degrees, _1, _2));//杀死后正序排序
    int i = 0;
    int remaining;
    while(!live[orders[i]] && i < nodes)i++;
    remaining = nodes - i;//我们假定，之前的点如果死了，那么度一定为0。
    if(i < nodes){
        int curPoint = orders[i];
        cur_core = degrees[curPoint];//cur_core>=1才对
        livePoints[curPoint] = false;
        coreNumber[curPoint] = cur_core;
#if GRAPH_DEBUG
        cout << "k-core[" << curPoint << "]=" << cur_core << endl;
#endif
        max_core = cur_core;
        i++;
        while(i < nodes) {
            curPoint = orders[i];
            if (live[curPoint]) {
                if (degrees[curPoint] > cur_core) cur_core = degrees[curPoint];
                if (cur_core > max_core) max_core = cur_core;

                livePoints[curPoint] = false;

                coreNumber[curPoint] = cur_core;
#if GRAPH_DEBUG
                cout << "k-core[" << curPoint << "]=" << cur_core << endl;
#endif
                if (degrees[curPoint] == nodes - i - 1 || cur_core >= lb - 1) {
                    for (int j = i + 1; j < nodes; j++)
                    {
                        coreNumber[orders[j]] = cur_core;
#if GRAPH_DEBUG
                        cout << "k-core[" << orders[j] << "]=" << cur_core << endl;
#endif
                    }
                    break;
                }

                for (set<int>::iterator v = g[curPoint].begin(); v != g[curPoint].end(); v++)
                    if(livePoints[*v]) degrees[*v]--;
                /*sharedNeighbour.clear();
                set_intersection(g[curPoint].begin(), g[curPoint].end(), orders.begin() + i, orders.end(),
                                 inserter(sharedNeighbour, sharedNeighbour.end()));
                for (set<int>::iterator v = sharedNeighbour.begin(); v != sharedNeighbour.end(); v++) {
                    if (live[*v]) degrees[*v]--;
                }
                 */
                sort(orders.begin() + i + 1, orders.end(), bind(degreeCompare, degrees, _1, _2));
                /*
                int temp, m;
                for(int t = i + 1; t < nodes; t++){
                    m = t;
                    while (m >= i + 2 && degrees[orders[m]] < degrees[orders[m - 1]]) m--;
                */


            }
            i++;
        }
        int i = 0;
#if GRAPH_DEBUG
        cout << "LB:" << lb << endl;
#endif
        while(i < nodes){
            if (live[i] && coreNumber[i] < lb - 1) {
#if GRAPH_DEBUG
                cout << "LIVE(" << i << "):" << live[i] << endl;
                cout << "CORE_NUM:" << coreNumber[i] << endl;
#endif
                deleteNode(i);
            }
            i++;
        }
    }
    kill();
}