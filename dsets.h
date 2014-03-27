#ifndef DSETS_H
#define DSETS_H

#include <iostream>
#include <vector>
using namespace std;
class DisjointSets
{
	private:
	vector<int> v;
	public:
	int find(int elem);
	void setunion(int a,int b);
	void addelements(int num);
};
#endif
