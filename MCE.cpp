//
// Created by admin on 15/03/2017.
//

#include "MCE.h"

void MCE::init()
{
    ifstream f(FILE_NAME);

    int n, m, t1, t2;
    f >> n >> m;
    graph.init(n);
    while(!f.eof()) {
        f >> t1 >> t2;
        if(t1 != t2) graph.createConnection(t1, t2);
    }
#if DEBUG
    graph.print();
#endif
    vNum = n;
    sumMCE = 0;
    f.close();
}

void MCE::printR(set<int> R)
{
#if MCE_OUTPUT
    if(R.size() >= lb) {
        cout << "Maximal Clique found: " << endl;
        cout << "[ ";
        for (set<int>::iterator rt = R.begin(); rt != R.end(); rt++)
            std::cout << *rt << " ";
        cout << "] " << endl;
        sumMCE++;
#if ANS_ANALYSIS
        ans.insert(R);
#endif
#if REPEAT_ANALYSIS
        if(ans2.find(R) != ans2.end()) ans2.insert(R);
        else
        assert("ERROR! REPEATED VALUE!");
#endif
    }
#endif
}

void MCE::preprocessing() {
    cout << "Error! Preprocessing haven't been implemented!" << endl;
}

void MCE::solve() {
    cout << "Error! Solve haven't been implemented!" << endl;
}

void MCE::run(int i) {
    auto start = high_resolution_clock::now();
    init();
    graph.setLowerBound(i);
    lb = i;//just for debug! lb = i;
    preprocessing();
    solve();
    cout << "Sum of all maximal clique:" << sumMCE << endl << endl;
    cout << "finished.";
    cout << duration_cast<milliseconds>(high_resolution_clock::now() - start).count() << "ms\n";
}


