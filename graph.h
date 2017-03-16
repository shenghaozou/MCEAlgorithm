#include "common.h"
using namespace std::placeholders;
class Graph 
{
	private:
		int nodes;
		int edges;
        int lb;//question here!
	public:
		vector<node> g;
        vector<bool> live;
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
        inline void filterBasedOnDegree();
        void filterBasedOnEdge();
        void filterBasedOnKcore();
        void deleteNode(int);
        inline void kill();
};