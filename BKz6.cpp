//
// Created by admin on 16/03/2017.
//



#include "BKz6.h"

void vectorDebug(vector<int> &d);
void setDebug(set<int> &d);

void quickSort(vector<int> &orders, vector<int> &degrees, int l,int r);

void setPrint(set<int> x, string name);




void BKz6::BronKerboschz(vector<int> P, vector<int> X, int recursiveCallCount) {
    vector<vector<bool>> &matrix = graph.matrix;
    vector<int> &levels = graph.levels;


    int selected, level;
    int comparison = 0;

    if (P.size() == 0 && X.size() == 0) {
        //cout << "success!" << endl;
        printR(R);
        return;
    }


    if (P.size() + R.size() < lb) return;

    if (P.size() != 0) {
        if (graph.matrixFirstTime) graph.matrixFirstTime = false;
        else {
            if (X.size() != 0) {
                graph.maxD = X[0];
                comparison = graph.d[X[0]];
            }
            if (graph.d[P[0]] > comparison) graph.maxD = P[0];
        }
        selected = graph.maxD;
    }
    vector<bool> PLive(P.size(), true);
    int i = 0;
    for (vector<int>::iterator v = P.begin(); v != P.end();v++) {
        //cout << "matrix[" << *v << "][" << selected << "]" << endl;
        if (!matrix[*v][selected]) {
            vector<int> P_new;
            vector<int> X_new;
            //cout << "current V:" << *v << endl;
            R.push_back(*v);
            /*
            cout << "current level:" << recursiveCallCount<< endl;
            cout << "current R:";
            vectorDebug(R);

            cout << "vector P:";
            vectorDebug(P);
            cout << "vector X:";
            vectorDebug(X);
            */
            int i2 = 0;
            for (vector<int>::iterator v2 = P.begin(); v2 != P.end(); v2++)
            {
                if (matrix[*v][*v2] && PLive[i2] && graph.live[*v2])
                {
                    //cout << "Ppush:" << *v2 << endl;
                    P_new.push_back(*v2);
                }
                i2++;
            }
            for (vector<int>::iterator v2 = X.begin(); v2 != X.end(); v2++) if (matrix[*v][*v2]) X_new.push_back(*v2);
            /*
            cout << "new level:" << recursiveCallCount + 1 << endl;
            cout << "vector new P:";
            vectorDebug(P_new);
            cout << "vector new X:";
            vectorDebug(X_new);
            */
            BronKerboschz(P_new, X_new, recursiveCallCount + 1);
            R.pop_back();
            int tmp = *v;
            X.push_back(tmp);
            graph.live[tmp] = false;
            //P_erase
            PLive[i] = false;
        }
        i++;
    }
}
void BKz6::solve() {
    vector<bool> tempLive(graph.live);
    vector<int> P_;
    vector<node> &g = graph.g;
    queue<int> q;
    int i = 0;
    int sum = 0;
    int lives = 0;
    int sumi;
    //graph.matrixConvert();
    while(i < tempLive.size()) {
        sumi = 0;
        P.clear();
        P_.clear();
        while (i < tempLive.size() && !tempLive[i]) i++;
        if (i < tempLive.size()) {
            q.push(i);
            P.clear();
            while (!q.empty()) {
                int tmp = q.front();
                q.pop();
                if(tempLive[tmp]) {

                    P_.push_back(tmp);
                    tempLive[tmp] = false;
                    for (set<int>::iterator v = g[tmp].begin(); v != g[tmp].end(); v++) if (tempLive[*v]) q.push(*v);
                }
            }
            X.clear();
            graph.matrixConvert(P_);
            for(int i = 0; i < P_.size(); i++) if(graph.live[i]) P.push_back(i);
            if (P.size() >= lb) BronKerboschz(P, X, recursiveCount);
            sum = sum + 1;
            graph.matrixFlag = false;
        }
    }
}



