#include "common.h"
using namespace std::placeholders;
class Graph 
{
	private:
		int nodes;
		int edges;
        int lb = 0;
	public:
		vector<node> g;
        vector<bool> live;
		vector<int> coreNumber;
		vector<int> orders;
		vector<int> d;
		void init(int vNum);
        void setLowerBound(int limit){lb = limit;};
		void createNode(int n, set<int> r) {
			g[n] = r;
		}
		void createConnection(int n1_, int n2_)
		{
			g[n1_].insert(n2_);
			g[n2_].insert(n1_);
		}
		void print();
        void filterBasedOnDegree();
        void filterBasedOnEdge();
        void filterBasedOnKcore();
        void deleteNode(int);
        void kill();
};