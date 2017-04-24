//
// Created by admin on 15/04/2017.
//

#include "sat.h"

void Sat::addClause(vector<int> &t, bool rlx) {
    int index = data.size();
    clause tmp;
    tmp.sat = false;
    tmp.relax = rlx;
    tmp.data.clear();
    data.push_back(tmp);

    for(vector<int>::iterator v = t.begin(); v != t.end(); v++){
        int num = *v;
        if(num > 0) posWatches[toVar(num)].push_back(index);
        else negWatches[toVar(num)].push_back(index);
        data[index].push_back(num);
    }
}

void Sat::init(bool firstTime) {//after add Clause
    aliveClauses = data.size();
    for(vector<clause>::iterator t = data.begin(); t != data.end(); t++) (*t).alive = (*t).data.size();
    for(int i = 0; i < alive.size(); i++) alive[i] = true;
    reason.resize(nodes);
    failed = -1;

}

bool Sat::up(int t) {
    nodeSat tmp;
    tmp.var = toVar(t);
    tmp.reason = 0;
    reason[toVar(t)] = tmp;
    assert(t != 0);
    queue<int> q;
    q.push(t);
    while(!q.empty()) {
        int n = q.front();
        cout << "Current:" << n << endl;
        debug();
        q.pop();
        tmp.var = toVar(n);
        if (alive[toVar(n)]) {
            vector<vector<int>> *_posWatches = n > 0 ? &posWatches : &negWatches;
            vector<vector<int>> *_negWatches = n > 0 ? &negWatches : &posWatches;
            alive[toVar(n)] = false;
            cout << "UP:" << n << endl;
            for (vector<int>::iterator v = (*_posWatches)[toVar(n)].begin(); v != (*_posWatches)[toVar(n)].end(); v++) {
                int cindex = *v;
                cout << "Pos watch:" << cindex << endl;
                if (!data[cindex].sat) data[cindex].sat = true;
                aliveClauses--;
                if (aliveClauses == 0) {
                    cout << "ALIVE:0" << endl;
                    return true;
                }
                if (data[cindex].relax) {
                    int lit = 0;
                    bool res = true;
                    tmp.reason = cindex;
                    for (vector<int>::iterator t = data[cindex].data.begin(); t != data[cindex].data.end(); t++) {
                        if (toVar(*t) != toVar(n)) {
                            reason[toVar(*t)] = tmp;
                            cout << "Relax Option:" << endl;
                            assert(*t != 0);
                            cout << -*t << " entered the queue." << endl;
                            q.push(-*t);
                        }
                    }
                }
            }
            for (vector<int>::iterator v = (*_negWatches)[toVar(n)].begin(); v != (*_negWatches)[toVar(n)].end(); v++) {
                int cindex = *v;
                if (!data[cindex].sat) {
                    cout << "Neg watch:" << cindex << endl;
                    if (data[cindex].alive >= 3) {
                        data[cindex].alive--;
                    } else if (data[cindex].alive == 2) {
                        int lit = 0;
                        for (vector<int>::iterator t = data[cindex].data.begin(); t != data[cindex].data.end(); t++)
                            if (alive[toVar(*t)] && toVar(*t) != toVar(n)) lit = *t;
                        assert(lit != 0);
                        tmp.reason = cindex;
                        reason[toVar(lit)] = tmp;
                        data[cindex].alive--;
                        assert(lit != 0);
                        cout << lit << " entered the queue." << endl;
                        q.push(lit);
                    } else {
                        failed = toVar(n);
                        failed_index = cindex;
                        return false;
                    }
                }

            }
        }
    }
        return true;
}

void Sat::relax(int upLit) {
    int start = nodes;
    int startNodes = nodes;
    int newvar = 0;
    vector<bool> seen(data.size(), false);
    vector<int> newClause;
    queue<int> q;
    q.push(failed_index);
    cout << "Conflict Clause:";
    while(!q.empty()) {
        int f = q.front();
        cout << "Popped clause:" << f << endl;
        q.pop();
        if(!seen[f]) {
            int clauseSize = data[f].data.size();
            seen[f] = true;
            for (int i = 0; i < clauseSize; i++) {
                int lit = data[f].data[i];
                int var = toVar(lit);
                cout << endl << "relax variable " << var << " from clauses " << f << " whose size is "
                     << data[f].data.size() << endl;
                assert(var < nodes);
                int cindex = reason[var].reason;
                if (!seen[cindex]) {
                    q.push(cindex);
                    cout << cindex << " is pushed" << endl;
                } else cout << cindex << " is skipped" << endl;
            }
            newvar = newVar();
            cout << "clause " << f << " is adding new variable " << newvar << endl;
            data[f].data.push_back(newvar + 1);
            newClause.push_back(newvar + 1);
        }
    }
    cout << endl;
    assert(newvar != 0);
    newvar = newVar();
    newClause.push_back(newvar + 1);
    addClause(newClause, true);
    newClause.clear();
    newClause.push_back(newvar + 1);
    newClause.push_back(upLit);
    addClause(newClause, false);
}

int Sat::newVar() {
    int newvar = nodes;
    cout << "generated new node:" << newvar << endl;
    nodes++;
    posWatches.resize(nodes);
    negWatches.resize(nodes);
    posWatches[newvar].clear();
    negWatches[newvar].clear();
    alive.resize(nodes);
    alive[newvar] = true;
    reason.resize(nodes);
    return newvar;
}

void Sat::debug() {
    cout << "-----------------------------------------------------" << endl;
    cout << "Var:" << nodes << " Clause:" << data.size() << endl;
    cout << "Alive:";
    for(int i = 0; i < alive.size(); i++) if (alive[i]) cout << i << " ";
    cout << endl;
    cout << "Clauses:" << endl;
    for(int i = 0; i < data.size(); i++){
        cout << "(" << i << ")";
        cout << (data[i].sat ? "S" : " ") << (data[i].relax ? "R":" ") << "[" << data[i].alive << "]";
        for (vector<int>::iterator v = data[i].data.begin(); v != data[i].data.end(); v++) if (alive[toVar(*v)]) cout << *v << " ";
        cout << endl;
    }
    cout << "Conflict:" << endl;
    for(int i = 0; i < nodes; i++){
        cout << i << " var:" << reason[i].var << " reason clause index:" << reason[i].reason << endl;
    }
}

void satTest(){
    vector<int> data;
    ifstream satFile;
    int lits, clauses, up;
    int failed;
    satFile.open("sat.txt");
    satFile >> lits >> clauses >> up;
    Sat s(lits);
    for(int i = 0; i < clauses; i++){
        data.clear();
        int tmp;
        satFile >> tmp;
        while(tmp != 0){
            data.push_back(tmp);
            satFile >> tmp;
        }
        s.addClause(data);
    }
    s.init(true);
    s.debug();
    if(!s.up(up)){
        cout << "RELAX!" << endl;
        s.relax(up);
        cout << "RELAX FINISHED." << endl;
        s.init(false);
        s.debug();
    }

    satFile.close();



}