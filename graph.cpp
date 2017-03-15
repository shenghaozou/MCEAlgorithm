//Created by David Pynes
#include<set>
#include<iostream>
#include<string>
#include<vector>
using namespace std;


typedef set<int> node;


class Graph 
{
	private:
		int nodes;
		int edges;
	public:
		vector<node> g;

		void init(int vNum) {
			nodes = vNum;
			g.resize(vNum + 1);
			for(int i = 0; i < vNum; i++) g[i].clear();
		};

		void createNode(int n, set<int> r)
		{
			g[n] = r;
		}

		void createConnection(int n1_, int n2_)
		{
			g[n1_].insert(n2_);
			g[n2_].insert(n1_);
		}


		void print() 
		{
			cout << "Displaying Graph: " << endl;
		 	for (int i = 0; i < nodes; i++)
		 	{
		 		cout << "Vertex: "<< i << " Connects to: [ ";
				for (set<int>::iterator jt = g[i].begin(); jt != g[i].end(); jt++)
					cout << (*jt) <<" ";
				cout << "]" << endl;
			}
			cout << endl;
		}
};