#include "common.h"
using namespace std::placeholders;
#ifndef GRAD_GRAPH_H
#define GRAD_GRAPH_H

class Graph
{
	private:
        int lb = 0;
	public:
		int nodes;
        bool matrixFlag = false;
        bool matrixFirstTime;
		vector<node> g;
        vector<bool> live;
		vector<int> coreNumber;
		vector<int> orders;
		vector<int> d;
        int maxD;

        vector<vector<bool>> matrix;
        int matrixSize;
        int matrixFirstLivePointer;
        vector<int> matrixc2r;
        vector<int> matrixr2c;
        vector<int> levels;

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
        void filterBasedOnKcore2();
        bool KcoreDegreesComp(int, int);

        vector<int> degrees;
		void islandTest();
		int kcoreMini();
        void deleteNode(int);
        void kill();
		void maximalClique(vector<int> &t);
        void matrixConvert();
		void matrixConvert(vector<int> &P);
        void basicInfo();

        //void quickSort(vector<int> &, int, int);
};
#endif