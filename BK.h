#include "MCE.h"
extern Graph graph;
extern int sumMCE;
class BK:public MCE{
public:
    void preprocessing();
    void solve();
}