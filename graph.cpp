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
    vector<int> pool(nodes);
    bool flag;
    int erased;
    pool.clear();
    fill(pool.begin(), pool.end(), -1);
    for( int i = 0; i < nodes; i++) if(live[i]){
            for(set<int>::iterator v = g[i].begin(); v != g[i].end(); v++) if(live[*v]) pool[*v] = i;
            for(set<int>::iterator v = g[i].begin(); v != g[i].end(); v) if(live[*v] && i < (*v)){
                    int num = *v;
                     int sum = 0;
                    bool delFlag = true;
                    for(set<int>::iterator t = g[num].begin(); t != g[num].end(); t++) if(live[*t]  && pool[*t] >= i) {
                            sum++;
                            if(sum >= lb - 2) {
                                delFlag = false;
                                break;
                            }
                        }
                    v++;
                    if(delFlag){
#if GRAPH_DEBUG
                        cout << "Erased Edge:" << i << "," << num << endl;
#endif
                        g[i].erase(num);
                        g[num].erase(i);
                    }
                } else v++;
        }
    kill();
}

bool degreeCompare(vector<int> g, int a, int b)
{
    return g[a] < g[b];
}

void quickSort(vector<int> &orders, vector<int> &degrees, int l,int r){
    int i, j, t, mid;
    mid = orders[(l+r) >> 1];
    i = l; j = r;
    do{
        while (degrees[orders[i]] < degrees[mid]) i++;
        while (degrees[orders[j]] > degrees[mid]) j--;
        if (i <= j) {
            t = orders[i];
            orders[i] = orders[j];
            orders[j] = t;
            i++; j--;
        }
    }
    while (i <= j);
    if (i < r) quickSort(orders, degrees, i,r);
    if (l < j) quickSort(orders, degrees, l,j);
}

void Graph::filterBasedOnKcore() {//这里会修改图！需要复制一份过来！待修改！
    orders.resize(nodes);
    coreNumber.resize(nodes);
    vector<int> degrees(nodes);
    vector<bool> livePoints(nodes);
    int* speedTest;
    int cur_core, max_core;
#if GRAPH_DEBUG
    cout << "k-core simplification." << endl;
#endif
    livePoints = live;
    for(int i = 0; i < nodes; i++) orders[i] = i;
    kill();//杀死所有度为0的点。
    degrees = d;

    quickSort(orders, degrees, 0, nodes - 1);
    //sort(orders.begin(), orders.end(), bind(degreeCompare, degrees, _1, _2));//杀死后正序排序

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

                if (degrees[curPoint] == nodes - i - 1 || cur_core >= lb - 1) {
                    for (int j = i + 1; j < nodes; j++) coreNumber[orders[j]] = cur_core;
                    break;
                }

                for (set<int>::iterator v = g[curPoint].begin(); v != g[curPoint].end(); v++)
                    if(livePoints[*v]) degrees[*v]--;
                quickSort(orders, degrees, i + 1, nodes - 1);
            }
            i++;
        }
        int i = 0;

        while(i < nodes){
            if (live[i] && coreNumber[i] < lb - 1) deleteNode(i);
            i++;
        }
    }
    kill();
}

int Graph::kcoreMini() {
    orders.resize(nodes);
    coreNumber.resize(nodes);
    vector<int> degrees(nodes);
    vector<bool> livePoints(nodes);
    int* speedTest;
    int cur_core, max_core;
    vector<int> temp;

    livePoints = live;
    for(int i = 0; i < nodes; i++) orders[i] = i;
    degrees = d;

    quickSort(orders, degrees, 0, nodes - 1);

    //for(int i = 0; i < nodes; i++)
    //    cout << "[" << orders[i] << "] " << degrees[orders[i]] << " ";
    //cout << endl;

    int i = 0;
    if(i < nodes) {
        int curPoint = orders[i];
        cur_core = degrees[curPoint];//cur_core>=1才对
        livePoints[curPoint] = false;
        coreNumber[curPoint] = cur_core;
        max_core = cur_core;
        while (i < nodes) {
            curPoint = orders[i];
            //cout << "choose:[" << curPoint << "]" << degrees[curPoint] << endl;

            if (live[curPoint]) {
                if (degrees[curPoint] > cur_core) cur_core = degrees[curPoint];
                if (cur_core > max_core) max_core = cur_core;
                //cout << "cur_core[" << curPoint << "]=" << cur_core << endl;

                livePoints[curPoint] = false;

                coreNumber[curPoint] = cur_core;

                if (degrees[curPoint] == nodes - i - 1) {
                    for (int j = i + 1; j < nodes; j++)
                    {
                        coreNumber[orders[j]] = cur_core;
                        if(livePoints[orders[j]]) temp.push_back(orders[j]);
                        else cout << "Someone dead! HELP!" << endl;
                    }
                    //maximalClique(temp);
                    cout << "Final:" << nodes - i << endl;
                    return nodes - i;
                }

                for (set<int>::iterator v = g[curPoint].begin(); v != g[curPoint].end(); v++)
                    if (livePoints[*v]) degrees[*v]--;
                quickSort(orders, degrees, i + 1, nodes - 1);
                //for(int t = i+1; t < nodes; t++)
                //    cout << "[" << orders[t] << "] " << degrees[orders[t]] << " ";
                //cout << endl;
            }
            i++;
        }
    }

    return 0;
}

void Graph::maximalClique(vector<int> &t) {
    for(vector<int>::iterator x = t.begin(); x != t.end(); x++){
        int num = *x;
        vector<int>::iterator y = x + 1;
        for(;y != t.end(); y++){
            int num2 = *y;
            if(find(g[num].begin(), g[num].end(), num2) == g[num].end())
            {
                cout << "Cannot find:" << num << "," << num2 << endl;

                for(int i = 0; i < nodes; i++){
                    cout << i << ":";
                    for(set<int>::iterator v = g[i].begin(); v != g[i].end(); v++)
                        cout << *v << ",";
                    cout << endl;
                }
                assert(0);
            }
        }
    }
    cout << t.size() << " Pass!" << endl;
    for(int i = 0; i < nodes; i++) {
        cout << i << ":";
        for (set<int>::iterator v = g[i].begin(); v != g[i].end(); v++)
            cout << *v << ",";
        cout << endl;
    }

}


