//Created by David Pynes
#include<set>
#include<algorithm>
#include<vector>
#include<iterator>
#include<fstream>
#include "graph.cpp"
#include <chrono>


#define DEBUG 0
#define FILE_NAME "brain3.edges"
using namespace std;
using namespace std::chrono;
Graph graph;
int sumMCE = 0;

void printR(set<int> R)
{
	cout << "Maximal Clique found: " << endl;
	cout << "[ ";
	for (set<int>::iterator rt = R.begin(); rt != R.end(); rt++)
		std::cout << *rt << " ";
	cout << "] "<<  endl;
    sumMCE++;
}

//bronkerbosch w/o pivot//
void BronKerbosch1(set<int> R, set<int> P, set<int> X, int& recursiveCallCount)
{
	vector<node> &g = graph.g;
	if (P.size() == 0 && X.size() == 0)
		printR(R);
	for (set<int>::iterator v = P.begin(); v != P.end();v)
	{
		set<int> v_;	//create a singleton set {v}
		v_.insert(*v);
#if DEBUG
		cout << "current V:"<< *v << endl;
#endif

		/* BronKerbosch1(R U {v}, P n N(v), X n N(v)) */
		set<int> RuV;
		set<int> XuV;
		set<int> PnNv;
		set<int> XnNv;
		set<int> P_v;

        RuV.clear(); XuV.clear(); PnNv.clear(); XnNv.clear(); P_v.clear();
        set_union(R.begin(), R.end(), v_.begin(), v_.end(), inserter(RuV, RuV.end()));
		set_intersection(P.begin(), P.end(), g[*v].begin(), g[*v].end(), inserter(PnNv, PnNv.end()));
		set_intersection(X.begin(), X.end(), g[*v].begin(), g[*v].end(), inserter(XnNv, XnNv.end()));

		BronKerbosch1(RuV, PnNv, XnNv, ++recursiveCallCount);

		P.erase(*v);
		X.insert(*v);
		
		if (P.empty())
			return;
		else
			v = P.begin();
	}
}

//Bronkerbosch w/ pivot//
void BronKerbosch2(set<int> R, set<int> P, set<int> X, int& recursiveCallCount)
{
	vector<node> &g = graph.g;

	if (P.size() == 0 && X.size() == 0) {
		printR(R);
		return;
	}

	set<int> PuX;
	set<int> P_Nu;
	PuX.clear();
	P_Nu.clear();
	set_union(P.begin(), P.end(), X.begin(), X.end(), inserter(PuX, PuX.end()));

	if(PuX.size() != 0) {
		set<int>::iterator puxt = PuX.begin();
		set_difference(P.begin(), P.end(), g[*puxt].begin(), g[*puxt].end(), inserter(P_Nu, P_Nu.end()));
		}

	for(set<int>::iterator v = P_Nu.begin(); v != P_Nu.end(); v)
	{
		set<int> v_;	//create a singleton set {v}
		v_.insert(*v);
#if DEBUG
		cout << "current V:"<< *v << endl;
#endif

		set<int> RuV;
		set<int> XuV;
		set<int> PnNv;
		set<int> XnNv;
		set<int> P_v;

        RuV.clear(); XuV.clear(); PnNv.clear(); XnNv.clear(); P_v.clear();

        set_union(R.begin(), R.end(), v_.begin(), v_.end(), inserter(RuV, RuV.end()));
		set_intersection(P.begin(), P.end(), g[*v].begin(), g[*v].end(), inserter(PnNv, PnNv.end()));
		set_intersection(X.begin(), X.end(), g[*v].begin(), g[*v].end(), inserter(XnNv, XnNv.end()));

		BronKerbosch2(RuV, PnNv, XnNv, ++recursiveCallCount);

		//RuV.clear(); XuV.clear(); PnNv.clear(); XnNv.clear(); P_v.clear();

		P.erase(*v);
		X.insert(*v);

		if (P.empty())
			return;
		else
			v = P.begin();
	}
}


int init()
{
	ifstream f(FILE_NAME);

	int n, m, t1, t2;
	f >> n >> m;
	graph.init(n);
	while(!f.eof()) {
		f >> t1 >> t2;
		graph.createConnection(t1, t2);
	}
#if DEBUG
	graph.print();
#endif
	return n;
}

int main() 
{
    auto start = high_resolution_clock::now();
	int vNum = init();

	set<int> R;
	R.clear();
	set<int> X;
	X.clear();
	set<int> P; //g is the set of vertices in graph.
	P.clear();
	for (int i = 0; i < vNum;i++) P.insert(i);
	int ans = 1; //variable specific to HW counting recursive calls.

	BronKerbosch1(R, P, X, ans);
	cout << "The total number of recursive calls upon BronKerbosch1 "<< ans << endl << endl;
    cout << "Sum of all maximal clique:" << sumMCE << endl << endl;
	cout << "finished.";
    cout << duration_cast<milliseconds>(high_resolution_clock::now() - start).count() << "ms\n";
	return 0;
} 
