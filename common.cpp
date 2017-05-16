//
// Created by admin on 25/04/2017.
//

#include "common.h"

void vectorDebug(vector<int> &d){
    cout << d.size();
    int i = 0;
    for(vector<int>::iterator v = d.begin(); v != d.end(); v++){
        cout << "(" << i << ")" << ":" << *v << " ";
        i++;
    }
    cout << endl;
}

void setDebug(set<int> &d){
    cout << d.size() << "|";
    for(set<int>::iterator v = d.begin(); v != d.end(); v++){
        cout << *v << " ";
    }
    cout << endl;
}