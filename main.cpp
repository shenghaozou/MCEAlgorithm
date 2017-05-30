//Created by David Pynes
#include "BK.h"
#include "BKz.h"
#include "BKz2.h"
#include "BKz3.h"
#include "BKz4.h"
#include "BKz5.h"
#include "BKz6.h"
#include "BKz7.h"
#include "BKz8.h"
#include "experiment.h"

void setPrint(set<int> x, string name);

void satTest();

int main() 
{
    //satTest();

    MCE *alg = new BKz8();
    //alg -> run(20);
    alg = new BKz3();
    alg -> run(10);


/*
    MCE *alg = new BKz8();
    alg -> run(10);
    alg = new BKz8();
    alg -> run(11);
    alg = new BKz8();
    alg -> run(12);
    alg = new BKz8();
    alg -> run(13);
    alg = new BKz8();
    alg -> run(14);
*/

/*
    MCE *alg = new BKz3();
    alg -> run(9);
    alg = new BKz3();
    alg -> run(10);
    alg = new BKz3();
    alg -> run(11);
    alg = new BKz3();
    alg -> run(12);
    alg = new BKz3();
    alg -> run(13);
*/
/*
cout << "------------------" << endl;

     MCE *alg2 = new BKz();
    alg2 -> run(9);
    alg2 = new BKz();
    alg2 -> run(10);
    alg2 = new BKz();
    alg2 -> run(11);
    alg2 = new BKz();
    alg2 -> run(12);
    alg2 = new BKz();
    alg2 -> run(13);
*/


    //MCE *alg3 = new BKz();
    //alg3 -> run(9);

    //MCE *alg2 = new BK2();
    //alg2 -> run(9);

    //MCE *alg4 = new BKz4();
    //alg4 -> run(9);


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
