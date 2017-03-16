#include "graph.h"

void Graph::init(int vNum) {
    nodes = vNum;
    g.resize(vNum + 1);
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
    if(live[i]){
        for(set<int>::iterator v = g[i].begin(); v != g[i].end(); v++) if(live[*v]) g[*v].erase(i);
        g[i].clear();
    }
}

void Graph::filterBasedOnDegree() {
    for (int i = 0; i < nodes; i++) if (live[i] && g[i].size() < lb) deleteNode(i);
}

void Graph::filterBasedOnEdge(){
    set<int> unionOf;
    bool flag;
    for( int i = 0; i < nodes; i++) if(live[i])
            for(set<int>::iterator v = g[i].begin(); v != g[i].end(); v) if(live[*v]){
                    flag = true;
                    if (g[i].size() >= lb && g[*v].size() >= lb){
                        unionOf.clear();
                        set_union(g[i].begin(), g[i].end(), g[*v].begin(), g[*v].end(), inserter(unionOf, unionOf.end()));
                        if(unionOf.size() >= flag) flag = false;
                    }
                    if(flag){
                        g[i].erase(*v);
                        g[*v].erase(i);
                        if(g[i].size() == 0) live[i] = false;
                        if(g[*v].size() == 0) live[*v] = false;
                    }
                }
}

bool degreeCompare(vector<node> g, int a, int b)
{
    return g[a].size() < g[b].size();
}

void Graph::filterBasedOnKcore() {
    vector<int> orders(nodes);
    vector<int> coreNumber(nodes);
    int cur_core;
    for(int i = 0; i < nodes; i++) orders[i] = i;
    sort(orders.begin(), orders.end(), bind(degreeCompare, g, _1, _2));
    int i = 0;
    while((!live[i] || g[orders[i]].size()== 0) && i < nodes)i++;
    if(i < nodes){
        cur_core = g[orders[i]].size();
        i++;
        while(i < nodes){
            if(g[orders[i]].size() > cur_core) cur_core = g[orders[i]].size();
            coreNumber[orders[i]] = cur_core;
            i++;
        }
    }
}