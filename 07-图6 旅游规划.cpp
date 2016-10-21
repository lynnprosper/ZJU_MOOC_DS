#include<iostream>
#include<algorithm>	//用到min（）；
using namespace std;
#define MaxN 501
struct Node	//结点定义；
{
	int di;
	int fee;
};
struct Graph
{
	Node Ma[MaxN][MaxN];
	int Nv;
	int Ne;
};

/*
思路：dijikstra算法求无向图的单源最短路径；
数据结构用邻接矩阵；
*/
void Init_G(Graph *G, int &c1, int &c2);	//初始化图；
void Dijkstra(Graph *G, int &c1, int &c2, int *dist, int *cost, int *col);
int FindMin(Graph *G, int *dist, int *col);	//找到剩余点中的最小路径；

int main()
{
	Graph *G = new Graph;
	int c1, c2;
	Init_G(G, c1, c2);	//初始化图；
	int *dist = new int[G->Nv];	//存储路径长度；
	int *cost = new int[G->Nv];	//存储路径费用；
	int *col = new int[G->Nv];	//记录最短路径的点；
	Dijkstra(G, c1, c2, dist, cost, col);

	delete[] dist;
	delete[] cost;
	delete[] col;
	delete G;
	return 0;
}

void Init_G(Graph *G, int &c1, int &c2)
{
	int n, m, i, j;
	cin >> n >> m >> c1 >> c2;
	G->Nv = n;
	G->Ne = m;
	int t1, t2, d1, co1;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)	//矩阵初始化为最大值；
		{
			G->Ma[i][j].di = G->Ma[j][i].di = MaxN;
			G->Ma[i][j].fee = G->Ma[j][i].fee = MaxN;
		}
	}
	for (i = 0; i < m; i++)	//注意题目中的是无向图；
	{
		cin >> t1 >> t2 >> d1 >> co1;
		G->Ma[t1][t2].di = G->Ma[t2][t1].di = d1;
		G->Ma[t1][t2].fee = G->Ma[t2][t1].fee = co1;
	}

	return;
}

void Dijkstra(Graph *G, int &c1, int &c2, int *dist, int *cost, int *col)
{
	int i;
	for (i = 0; i < G->Nv; i++)
	{
		dist[i] = G->Ma[c1][i].di;
		cost[i] = G->Ma[c1][i].fee;
		col[i] = 0;
	}
	dist[c1] = 0;
	col[c1] = 1;	//先收录起点；
	int minv;
	while (1)
	{
		minv = FindMin(G, dist, col);
		if (minv == -1)
			break;
		col[minv] = 1;
		for (i = 0; i < G->Nv; i++)
		{
			if (col[i] == 0)
			{
				if (dist[minv] + G->Ma[minv][i].di < dist[i])
				{
					dist[i] = dist[minv] + G->Ma[minv][i].di;
					cost[i] = cost[minv] + G->Ma[minv][i].fee;
				}
				else if (dist[minv] + G->Ma[minv][i].di == dist[i])	//长度相等，判断费用大小；
					cost[i] = min(cost[minv] + G->Ma[minv][i].fee, cost[i]);
			}
		}
	}

	cout << dist[c2] << ' ' << cost[c2] << endl;

	return;
}

int FindMin(Graph *G, int *dist, int *col)
{
	int mindi = MaxN;
	int i, minv;
	for (i = 0; i < G->Nv; i++)
	{
		if (col[i] == 0 && dist[i] < mindi)
		{
			mindi = dist[i];
			minv = i;
		}
	}
	if (mindi < MaxN)
		return minv;
	else
		return -1;	//不存在返回-1；
}
