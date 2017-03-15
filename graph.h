#include "common.h"

class Graph 
{
	private:
		int nodes;
		int edges;
	public:
		vector<node> g;
		void init(int vNum);
		void createNode(int n, set<int> r) {
			g[n] = r;
		}
		void createConnection(int n1_, int n2_)
		{
			g[n1_].insert(n2_);
			g[n2_].insert(n1_);
		}
		void print();
};