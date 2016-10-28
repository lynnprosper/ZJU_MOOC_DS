#include<iostream>
#include<queue>
#include<algorithm>	//使用max(), min();
using namespace std;
#define MaxN 101
#define inf 65535
/*
思路： 核心是关键路径， 算法--拓扑排序， 结构--邻接矩阵；
1.正向拓扑一次，得出最早完成时间；
2.逆向拓扑一次，得出最晚完成时间；
3.两者之差等于两点的权值，即为关键边；
*/

struct Graph	//定义邻接矩阵；
{
	int nv, ne;
	int G[MaxN][MaxN];
};
int early[MaxN] = { 0 };
int latest[MaxN];
int indeg[MaxN] = { 0 };	//入度值；
int outdeg[MaxN] = { 0 };	//出度值；

void Init_G(Graph *Mg);	//初始化矩阵；
int Topsort(Graph *Mg);	//正向拓扑；
void Back_Tops(Graph *Mg, int m_wt);	//逆向拓扑

int main()
{
	Graph *Mg = new Graph;
	Init_G(Mg);
	int m_wt = Topsort(Mg);	//关键路径长度；

	int i, j;
	if (m_wt == -1)	//有环跳出；
		cout << 0 << endl;
	else
	{
		cout << m_wt << endl;
		Back_Tops(Mg, m_wt);
		for (i = 1; i <= Mg->nv; i++)	//逆序输出；
		{
			for (j = Mg->nv; j > 0; j--)
			{
				if (Mg->G[i][j] && Mg->G[i][j] < inf)
				{
					if (early[i] == latest[j] - Mg->G[i][j])	//两者之差等于两点的权值，即为关键边；
						cout << i << "->" << j << endl;
				}
			}
		}
	}

	delete[] Mg;
	return 0;
}

void Init_G(Graph *Mg)	//初始化矩阵；
{
	cin >> Mg->nv >> Mg->ne;
	int i, j;
	for (i = 1; i <= Mg->nv; i++)
	{
		for (j = 1; j <= Mg->nv; j++)	//开始赋值为无穷；
		{
			if (i == j)
				Mg->G[i][j] = 0;
			else
				Mg->G[i][j] = Mg->G[j][i] = inf;
		}
		latest[i] = inf;
	}

	int s, d, wt;
	for (i = 0; i < Mg->ne; i++)	//读入数据；
	{
		cin >> s >> d >> wt;
		Mg->G[s][d] = wt;
		indeg[d]++;
		outdeg[s]++;
	}

	return;
}

int Topsort(Graph *Mg)	//正向拓扑；
{
	int i;
	queue<int> Q;

	for (i = 1; i <= Mg->nv; i++)
	{
		if (indeg[i] == 0)	//将入度0的点压入队列；
			Q.push(i);
	}

	int v, cnt = 0;
	while (!Q.empty())
	{
		v = Q.front();
		Q.pop();
		cnt++;

		for (i = 1; i <= Mg->nv; i++)
		{
			if (Mg->G[v][i] && Mg->G[v][i] < inf)	//边存在；
			{
				early[i] = max(early[i], early[v] + Mg->G[v][i]);
				if (--indeg[i] == 0)
					Q.push(i);
			}
		}
	}

	if (cnt < Mg->nv)	//表示有环；
		return -1;
	else
	{
		int t = 0;
		for (i = 1; i <= Mg->nv; i++)
			t = max(t, early[i]);
		return t;
	}
}

void Back_Tops(Graph *Mg, int m_wt)	//逆向拓扑
{
	int i;
	queue<int> Q;

	for (i = 1; i <= Mg->nv; i++)
	{
		if (outdeg[i] == 0)
		{
			Q.push(i);
			latest[i] = m_wt;
		}
	}

	int v;
	while (!Q.empty())
	{
		v = Q.front();
		Q.pop();
		for (i = 1; i <= Mg->nv; i++)
		{
			if (Mg->G[i][v] && Mg->G[i][v] < inf)
			{
				latest[i] = min(latest[i], latest[v] - Mg->G[i][v]);
				if (--outdeg[i] == 0)
					Q.push(i);
			}
		}
	}

	return;
}
