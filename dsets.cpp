#include "dsets.h"
int DisjointSets::find(int elem)
{
	if(v[elem]>=0)
		return v[elem]=find(v[elem]);
	return elem;
}
void DisjointSets::setunion(int a,int b)
{
	if(a==b)
		return;
	int xa=find(a);
	int xb=find(b);
	int fa=v[xa];
	int fb=v[xb];
	int size=fa+fb;
	if(fa<=fb)//size of set containing a is greater than size of set containing b
	{
		v[xa]=size;
		v[xb]=xa;
	}
	else
	{
		v[xb]=size;
		v[xa]=xb;
	}
}
void DisjointSets::addelements(int num)
{
	for(int i=0;i<num;i++)
	{
		v.push_back(-1);
	}
}
