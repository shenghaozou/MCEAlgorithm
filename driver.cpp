//Created by David Pynes
#include "graph.h"

Graph graph;
int sumMCE = 0;

void BronKerbosch1(set<int> R, set<int> P, set<int> X, int& recursiveCallCount);
void BronKerbosch2(set<int> R, set<int> P, set<int> X, int& recursiveCallCount);

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
