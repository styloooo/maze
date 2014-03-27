#include "maze.h"
#include <stack>
#include <map>
#include <algorithm>
SquareMaze::doubool::doubool()
{
	right=true;
	down=true;
}
SquareMaze::SquareMaze()
{
	ar=NULL;
	w=0;
	h=0;
}
SquareMaze::~SquareMaze()
{
	for(int i=0;i<w;i++)
		delete []ar[i];
	delete []ar;
}
void SquareMaze::makeMaze (int width, int height)
{
	if(ar!=NULL)
	{
		delete ar;
		ar=NULL;
	}
	ar=new doubool* [width];
	for(int i=0;i<width;i++)
	{
		ar[i]=new doubool[height];
	}
	int x,y;
	w=width;
	h=height;
	DisjointSets d;
	d.addelements(height*width);
	int count=0;
	x=0;
	y=0;
	//make(x,y,d,count);
	srand(time(NULL));
	while(count!=w*h-1)
	{
		bool b = rand()%2;
		if(b && x<w-1)//right
		{	
			if(d.find((x+1)*h+y)!=d.find((x)*h+y))
			{
				d.setunion(d.find(x*h+y),d.find((x+1)*h+y));
				ar[x][y].right=false;
				count++;
			}
		}
		else if(!b && y<h-1)//down
		{
			if(d.find(x*h+y+1)!=d.find(x*h+y))
			{
				d.setunion(d.find(x*h+y),d.find(x*h+y+1));
				ar[x][y].down=false;
				count++;
			}
		}
		x=rand()%w;
		y=rand()%h;
	}
}
/*
void SquareMaze::make(int x, int y, DisjointSets & d, int & count)
{
	if(count!=w*h-1)
	{
		bool b = rand()%2;
		if(b && x<w-1)//right
		{	
			if(d.find((x+1)*h+y)!=d.find((x)*h+y))
			{
				d.setunion(x*h+y,(x+1)*h+y);
				ar[x][y].right=false;
				count++;
			}
		}
		else if(!b && y<h-1)//down
		{
			if(d.find(x*h+y+1)!=d.find(x*h+y))
			{
				d.setunion(x*h+y,x*h+y+1);
				ar[x][y].down=false;
				count++;
			}
		}
		x=rand()%w;
		y=rand()%h;
		make(x,y,d,count);
	}
}
*/
bool SquareMaze::canTravel(int x,int y,int dir) const
{
	if(x>=w||x<0||y<0||y>=h)
		return false;
	if(dir==0)
		return !ar[x][y].right;
	else if(dir==1)
		return !ar[x][y].down;
	else if(dir==2)
	{
		if(x!=0)
			return !ar[x-1][y].right;
		else
			return false;
	}
	else if(dir==3)
	{
		if(y!=0)
			return !ar[x][y-1].down;
		else
			return false;
	}
	else
		return false;
}
void SquareMaze::setWall(int x,int y,int dir,bool exists)
{
	if(dir==0)
	{
		ar[x][y].right=exists;
	}
	else
	{
		ar[x][y].down=exists;
	}
}
vector<int> SquareMaze::solveMaze()
{
	vector<int> a;
	stack<int> s;
	bool used[w][h];
	pair<int,int> tracker[w*h];
	for(int i=0;i<w;i++)
	{
		for(int j=0;j<h;j++)
		{
			used[i][j]=false;
		}
	}
	int x=0,y=0,count=0;
	s.push(0);
	used[0][0]=true;
	tracker[0]=make_pair(-1,1);
	while(!s.empty())
	{
		int val = s.top();
		x=val/h;
		y=val%h;
		s.pop();
		if(canTravel(x,y,0)&&!used[x+1][y])
		{
			s.push((x+1)*h+y);
			used[x+1][y]=true;
			tracker[(x+1)*h+y]=make_pair(x*h+y,tracker[x*h+y].second+1);
		}
		if(canTravel(x,y,1)&&!used[x][y+1])
		{
			s.push(x*h+y+1);
			used[x][y+1]=true;
			tracker[x*h+y+1]=make_pair(x*h+y,tracker[x*h+y].second+1);
		}
		if(canTravel(x,y,2)&&!used[x-1][y])
		{
			s.push((x-1)*h+y);
			used[x-1][y]=true;
			tracker[(x-1)*h+y]=make_pair(x*h+y,tracker[x*h+y].second+1);
		}
		if(canTravel(x,y,3)&&!used[x][y-1])
		{
			s.push(x*h+y-1);
			used[x][y-1]=true;
			tracker[x*h+y-1]=make_pair(x*h+y,tracker[x*h+y].second+1);
		}
	}
	int l=0,store=0;
	for(int i=1;i<=w;i++)
	{
		if(l<tracker[i*h-1].second)
		{
			l=tracker[i*h-1].second;
			store=i*h-1;
			//cout<<i<<endl;
		}
	}
	//cout<<"here endeth"<<endl;
	while(store!=-1)
	{
		a.push_back(store);
		store=tracker[store].first;
	}
	vector<int> done;
	reverse(a.begin(),a.end());
	for(int i=0;i<a.size()-1;i++)
	{
		if((a[i]-a[i+1])==h)
			done.push_back(2);
		else if((a[i]-a[i+1])==-h)
			done.push_back(0);
		else if((a[i]-a[i+1])==1)
			done.push_back(3);
		else if((a[i]-a[i+1])==-1)
			done.push_back(1);
	}
	return done;
}
PNG* SquareMaze::drawMaze() const
{
	PNG * img = new PNG();
	img->resize(w*10+1,h*10+1);
	int i,j,k;
	for(i=0;i<h*10+1;i++)
	{
		(*img)(0,i)->red=0;
		(*img)(0,i)->green=0;
		(*img)(0,i)->blue=0;
	}
	for(i=10;i<w*10+1;i++)
	{
		(*img)(i,0)->red=0;
		(*img)(i,0)->green=0;
		(*img)(i,0)->blue=0;
	}
	for(i=0;i<w;i++)
	{
		for(j=0;j<h;j++)
		{
			if(ar[i][j].right)
			{
				for(k=0;k<=10;k++)
				{
					 (*img)((i+1)*10,j*10+k)->red=0;
					 (*img)((i+1)*10,j*10+k)->green=0;
					 (*img)((i+1)*10,j*10+k)->blue=0;
				}
			}
			if(ar[i][j].down)
			{
				for(k=0;k<=10;k++)
				{
					 (*img)(i*10+k,(j+1)*10)->red=0;
					 (*img)(i*10+k,(j+1)*10)->green=0;
					 (*img)(i*10+k,(j+1)*10)->blue=0;
				}
			}
		}
	}
	return img;
}
PNG* SquareMaze::drawMazeWithSolution()
{
	PNG* img;
	img=drawMaze();
	vector<int> sol = solveMaze();
	int i,j,k;
	unsigned int x=5;
	unsigned int y=5;
	for(i=0;i<sol.size();i++)
	{
		if(sol[i]==0)
		{
			for(k=0;k<=10;k++)
			{
				(*img)(x+k,y)->red=255;
				(*img)(x+k,y)->green=0;
				(*img)(x+k,y)->blue=0;
			}
			x=x+10;
		}
		else if(sol[i]==2)
		{
			for(k=0;k<=10;k++)
			{
				(*img)(x-k,y)->red=255;
				(*img)(x-k,y)->green=0;
				(*img)(x-k,y)->blue=0;
			}
			x=x-10;
		}
		else if(sol[i]==1)
		{
			for(k=0;k<=10;k++)
			{
				(*img)(x,y+k)->red=255;
				(*img)(x,y+k)->green=0;
				(*img)(x,y+k)->blue=0;
			}
			y=y+10;
		}
		else if(sol[i]==3)
		{
			for(k=0;k<=10;k++)
			{
				(*img)(x,y-k)->red=255;
				(*img)(x,y-k)->green=0;
				(*img)(x,y-k)->blue=0;
			}
			y=y-10;
		}
	}
	for(i=-4;i<=4;i++)
	{
		(*img)(x+i,y+5)->red=255;
		(*img)(x+i,y+5)->green=255;
		(*img)(x+i,y+5)->blue=255;
	}
	return img;
}
/*vector<int> SquareMaze::solveMaze()
{
	time_t now,then;
	time(&now);
	vector<int> temp,v;
	vector<vector<int> >oldtemp;
	stack<int> s;
	bool used[w][h];
	bool first=true;
	for(int i=0;i<w;i++)
	{
		for(int j=0;j<h;j++)
		{
			used[i][j]=false;
		}
	}
	int x=0,y=0,count=0;
	s.push(0);
	while(!s.empty())
	{
		int a = s.top();
		x=a/h;
		y=a%h;
		s.pop();
		bool flag=false;
		if(canTravel(x,y,0)&&!used[x+1][y])
		{
			s.push((x+1)*h+y);
			used[x+1][y]=true;
			flag=true;
		}
		if(canTravel(x,y,1)&&!used[x][y+1])
		{
			s.push(x*h+y+1);
			used[x][y+1]=true;
			flag=true;
		}
		if(canTravel(x,y,2)&&!used[x-1][y])
		{
			s.push((x-1)*h+y);
			used[x-1][y]=true;
			flag=true;
		}
		if(canTravel(x,y,3)&&!used[x][y-1])
		{
			s.push(x*h+y-1);
			used[x][y-1]=true;
			flag=true;
		}
		bool over = false;
		if(flag||y==h-1)
		{
			temp.push_back(a);//Error will happen when it can travel but not valid path
			if(temp.size()>1)
			{
				temp.pop_back();
				int val = temp.back();
				int diff = a-val;
				if(((diff==h)&&!ar[val/h][val%h].right)||((diff==-h)&&!ar[a/h][a%h].right)||((diff==-1)&&!ar[a/h][a%h].down)||((diff==1)&&!ar[val/h][val%h].down))
				{
					temp.push_back(a);
				}
				else
				{
					temp.pop_back();
					temp.push_back(a);
				}
			}
			if(!first&&temp.size()==1)
			{
				for(int loop=0;loop<oldtemp.size();loop++)
				{
					for(int i=0;i<oldtemp[loop].size();i++)
					{
						int val = oldtemp[loop][i];
						int diff = a-val;
						if(((diff==h)&&!ar[val/h][val%h].right)||((diff==-h)&&!ar[a/h][a%h].right)||((diff==-1)&&!ar[a/h][a%h].down)||((diff==1)&&!ar[val/h][val%h].down))
						{
							temp.clear();
							for(int j=0;j<=i;j++)
							{
								temp.push_back(oldtemp[loop][j]);
							}
							temp.push_back(a);
							over=true;
							break;
						}
					}
					if(over)
						break;
				}
			}
		}
		if(y==h-1)
		{
			int store=0;
			for(int i=0;i<temp.size()-1;i++)
			{
				int older=temp[i];
				int newer=temp[i+1];
				if(!((newer-older==h && canTravel(older/h,older%h,0))||(newer-older==-h && canTravel(older/h,older%h,2))||(newer-older==1 && canTravel(older/h,older%h,1))||(newer-older==-1 && canTravel(older/h,older%h,3))))
				{
					trim(i,temp);
					i=0;
				}
			}
			first=false;
			oldtemp.push_back(temp);
			count++;
			if(count==w)
				break;
			temp.clear();
		}
	}
	//cout<<"oldtemp -> "<<oldtemp.size()<<endl;
	for(int i=0;i<oldtemp.size();i++)
	{
		if(v.size()<oldtemp[i].size())
			v=oldtemp[i];
	}
	vector<int> done;
	for(int i=0;i<v.size()-1;i++)
	{
		if((v[i]-v[i+1])==h)
			done.push_back(2);
		else if((v[i]-v[i+1])==-h)
			done.push_back(0);
		else if((v[i]-v[i+1])==1)
			done.push_back(3);
		else if((v[i]-v[i+1])==-1)
			done.push_back(1);
	}
	time(&then);
	cout<<difftime(then,now)<<endl;
	return done;
}
void SquareMaze::trim(int store, vector<int> & temp)
{
	int finval=0;
	for(int i=0;i<=store;i++)
	{
		int older=temp[i];
		int newer=temp[store+1];
		if((newer-older==h && canTravel(older/h,older%h,0))||(newer-older==-h && canTravel(older/h,older%h,2))||(newer-older==1 && canTravel(older/h,older%h,1))||(newer-older==-1 && canTravel(older/h,older%h,3)))
		{
			finval=i;
			break;
		}
	}
	temp.erase(temp.begin()+finval+1,temp.begin()+store+1);
}*/
