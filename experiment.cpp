//
// Created by admin on 03/04/2017.
//

#include "experiment.h"
#include <time.h>
#include <random>
#include <unistd.h>

void experiment::generateGraph(double precise, int size) {
    graph.init(size);
    vector<vector<bool>> g2(
            size,
            vector<bool>(size, false));

    int a = 0;
    int b = size - 1;
    int i = 0;
    int edges = (int) (size * (size - 1) / 2 * precise);
    cout << edges << endl;
    while (i < edges) {
        int r1 = (rand() % (b - a + 1)) + a;
        int r2 = (rand() % (b - a + 1)) + a;
        cout << i << endl;
        if (r1 != r2 && g2[r1][r2] != true) {
            g2[r1][r2] = true;
            g2[r2][r1] = true;
            graph.g[r1].insert(r2);
            graph.g[r2].insert(r1);
            i++;
        }
    }

    cout << "Successfully generate the graph!" << endl;

}

void experiment::generateGraph2(double precise, int size) {
    graph.init(size);
    int edges = (int) (size * (size - 1) / 2 * precise);
    cout << edges << endl;
    for(int i = 0; i < size; i++)
        for(int j = i + 1; j < size; j++){
            int r1 = rand() & 1;
            if (r1) {
                graph.g[i].insert(j);
                graph.g[j].insert(i);
            }
    }
    for(int t = 0; t < size; t++) graph.d[t] = graph.g[t].size();
    cout << "Successfully generate the graph!" << endl;
}

double experiment::doExperimentNormal(double density, int size) {
    srand((unsigned)time(NULL) + random);
    generateGraph2(density, size);
    validTest(density,size);
    set<int> R;
    double sum = 0;
    set<int> P;
    R.clear();
    for(int i = 0; i < size; i++) if (graph.live[i]) P.insert(i);
    for(int i = 0; i < testTime; i++) sum += BK(R, P, 0);
    return sum/testTime;
}

int experiment::BK(set<int> R, set<int> P, int recursiveCallCount) {
    vector<node> &g = graph.g;
    vector<bool> &live = graph.live;

    if (P.size() == 0) {
        return recursiveCallCount;
    }

    int r1 = rand() % P.size();
    set<int> v_;	//create a singleton set {v}
    set<int>::iterator v = P.begin();
    int a = 0;
    while(a < r1){
        v++;
        a++;
    }

    if(live[*v]) {
        v_.insert(*v);

        set<int> RuV;
        set<int> PnNv;

        RuV.clear();
        PnNv.clear();

        set_union(R.begin(), R.end(), v_.begin(), v_.end(), inserter(RuV, RuV.end()));
        set_intersection(P.begin(), P.end(), g[*v].begin(), g[*v].end(), inserter(PnNv, PnNv.end()));
        return BK(RuV, PnNv, recursiveCallCount + 1);
    }
    else{
        cout << "Point should be live!" << endl;
        assert(0);
    }

}

double experiment::doExperimentAd(double density, int size) {
    srand((unsigned)time(NULL) + random);;
    generateGraph2(density, size);
    return graph.kcoreMini();

}

void experiment::massTest() {
    int t = 0;
    double sum = 0;
    for(int i = 0; i < totalTestTime; i++) {
        random++;
        double temp = doExperimentAd(0.5, 1000);
        cout << i << ':' << temp << endl;
        sum += temp;
    }
    cout << "Total:" << sum / totalTestTime << endl;
}

bool experiment::validTest(double density, int size) {
    /*test of density*/
    int edges = (int)(size * size / 2 * density);
    int sum = 0;
    for(int i = 0; i < size; i++) sum += graph.g[i].size();
    cout << "real edges:" << sum / 2 << endl;
}

