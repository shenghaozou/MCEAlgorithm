//Created by David Pynes
#include "BK.h"
#include "BKz.h"
#include "BKz2.h"
#include "BKz3.h"
#include "experiment.h"

void setPrint(set<int> x, string name);

void satTest();

int main() 
{
    satTest();


/*
#if ANS_ANALYSIS
    set<set<int>> setBKz, setBK2, setz_2, set2_z;
    MCE *alg = new BKz3();
    alg -> run(8);
    setBK2 = alg -> ans;
#endif


    MCE *alg2 = new BKz3();
    alg2 -> run(10);

#if ANS_ANALYSIS
    setBKz = alg2 -> ans;

    set_difference(setBKz.begin(), setBKz.end(), setBK2.begin(), setBK2.end(), inserter(setz_2,setz_2.end()));
    set_difference(setBK2.begin(), setBK2.end(), setBKz.begin(), setBKz.end(), inserter(set2_z,set2_z.end()));
    cout << "Set Difference:" << endl;
    cout << "setBK2:" << setBK2.size() << endl;
    cout << "setBKz:" << setBKz.size() << endl;
    for(set<set<int>>::iterator v = setz_2.begin(); v!=setz_2.end(); v++){
        setPrint(*v, "Z-2");
    }
    for(set<set<int>>::iterator v = set2_z.begin(); v!=set2_z.end(); v++){
        setPrint(*v, "2-Z");
    }
#endif
*/

	return 0;
} 
