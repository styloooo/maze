#ifndef MAZE_H
#define MAZE_H

#include "png.h"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "dsets.h"
#include <sys/time.h>
#include <time.h>
using namespace std;

class SquareMaze
{
	private:
	void make(int x, int y, DisjointSets & d, int & count);
	void trim(int store, vector<int>& temp);
	class doubool
	{
		public:
		bool right;
		bool down;
		doubool();
	};
	doubool** ar;
	int w,h;
	public:
	SquareMaze();
	~SquareMaze();
	void makeMaze (int width, int height);
	bool canTravel(int x,int y,int dir) const;
	void setWall(int x,int y,int dir,bool exists);
	vector<int> solveMaze();
	PNG* drawMaze() const;
	PNG* drawMazeWithSolution();
};






#endif
