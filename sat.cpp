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

    assert(data.size() < 2147483647);
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
    nodeQueue tmpQ;
    tmp.var = toVar(t);
    tmp.reason = 0;
    assert(t != 0);
    queue<nodeQueue> q;
    tmpQ.lit = t;
    tmpQ.reasonClause = -1;
    q.push(tmpQ);
    while(!q.empty()) {
        nodeQueue n_ = q.front();
        int n = n_.lit;
#if SAT_DEBUG
        cout << "Current:" << n << " Reason Clause:" << n_.reasonClause << endl;
        //debug();
#endif
        q.pop();
        tmp.var = toVar(n);
        if (alive[toVar(n)]) {
            reason[toVar(n)] = n_.reasonClause;
            vector<vector<int>> *_posWatches = n > 0 ? &posWatches : &negWatches;
            vector<vector<int>> *_negWatches = n > 0 ? &negWatches : &posWatches;
            alive[toVar(n)] = false;
#if SAT_DEBUG
            cout << "UP:" << n << endl;
#endif
            for (vector<int>::iterator v = (*_posWatches)[toVar(n)].begin(); v != (*_posWatches)[toVar(n)].end(); v++) {
                int cindex = *v;
#if SAT_DEBUG
                cout << "Pos watch:" << cindex << endl;
#endif
                if (!data[cindex].sat) data[cindex].sat = true;
                aliveClauses--;
                if (aliveClauses == 0) {
#if SAT_DEBUG
                    cout << "ALIVE:0" << endl;
#endif
                    return true;
                }
                if (data[cindex].relax) {
                    int lit = 0;
                    bool res = true;
                    //tmp.reason = cindex;
                    for (vector<int>::iterator t = data[cindex].data.begin(); t != data[cindex].data.end(); t++) {
                        if (toVar(*t) != toVar(n)) {
                            //reason[toVar(*t)] = tmp;
#if SAT_DEBUG
                            cout << "Relax Option:" << endl;
                            assert(*t != 0);
                            cout << -*t << " entered the queue with reason clause" << cindex << endl;
#endif
                            tmpQ.lit = -*t;
                            tmpQ.reasonClause = cindex;
                            q.push(tmpQ);
                        }
                    }
                }
            }
            for (vector<int>::iterator v = (*_negWatches)[toVar(n)].begin(); v != (*_negWatches)[toVar(n)].end(); v++) {
                int cindex = *v;
                if (!data[cindex].sat) {
#if SAT_DEBUG
                    cout << "Neg watch:" << cindex << endl;
#endif
                    if (data[cindex].alive >= 3) {
                        data[cindex].alive--;
                    } else if (data[cindex].alive == 2) {
                        int lit = 0;
                        for (vector<int>::iterator t = data[cindex].data.begin(); t != data[cindex].data.end(); t++)
                            if (alive[toVar(*t)] && toVar(*t) != toVar(n)) lit = *t;
                        assert(lit != 0);
                        //tmp.reason = cindex;
                        //reason[toVar(lit)] = tmp;
                        data[cindex].alive--;
#if SAT_DEBUG
                        assert(lit != 0);
                        cout << lit << " entered the queue with reason clause" << cindex << endl;
#endif
                        tmpQ.lit = lit;
                        tmpQ.reasonClause = cindex;
                        q.push(tmpQ);
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
#if SAT_DEBUG
    cout << "Conflict Clause:";
#endif
    while(!q.empty()) {
        int f = q.front();
#if SAT_DEBUG
        cout << "Popped clause:" << f << endl;
#endif
        q.pop();
        if(!seen[f]) {
            int clauseSize = data[f].data.size();
            seen[f] = true;
            for (int i = 0; i < clauseSize; i++) {
                int lit = data[f].data[i];
                int var = toVar(lit);
#if SAT_DEBUG
                cout << endl << "relax variable " << var << " from clauses " << f << " whose size is "
                     << data[f].data.size() << endl;
                assert(var < nodes);
#endif
                int cindex = reason[var];
                if (cindex >= 0 && !seen[cindex]) {
                    q.push(cindex);
#if SAT_DEBUG
                    cout << cindex << " is pushed" << endl;
                    } else
                        cout << cindex << " is skipped" << endl;
#else
                    }
#endif
            }
            newvar = newVar();
#if SAT_DEBUG
            cout << "clause " << f << " is adding new variable " << newvar << endl;
#endif
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
#if SAT_DEBUG
    cout << "generated new node:" << newvar << endl;
#endif
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
        cout << i << " var:" << i << " reason clause index:" << reason[i] << endl;
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
#if SAT_DEBUG
    s.debug();
#endif
    if(!s.up(up)){
#if SAT_DEBUG
        cout << "RELAX!" << endl;
        s.debug();
#endif
        s.relax(up);
#if SAT_DEBUG
        cout << "RELAX FINISHED." << endl;
#endif
        s.init(false);
#if SAT_DEBUG
        s.debug();
#endif
    }
    satFile.close();
}