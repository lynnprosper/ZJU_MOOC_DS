#include<iostream>
using namespace std;
#define MaxN 1002
#define inf 65535	//不可达的最大值。
int G[MaxN][MaxN];	//冒充下邻接矩阵；
int dist[MaxN];	//未收录的点到已生成的生成树中的点的最短路长度；

/*
思路：Prim算法。结构是邻接矩阵。
但要比真正的Prim算法简略，因为题目只要输出总权值，所以我们就不用
同时建立最小生成树，只需要累加边权值。
*/
void Init_G(int N, int M);	//初始化并读入数据，构造邻接矩阵；
int Prim(int N);
int FindMin(int N);	//找到未收录点到生成树的最小边权值；

int main()
{
	int N, M, wt;
	cin >> N >> M;
	Init_G(N, M);
	wt = Prim(N);
	cout << wt << endl;

	return 0;
}

void Init_G(int N, int M)	//初始化并读入数据，构造邻接矩阵；
{
	int i, j;
	for (i = 1; i <= N; i++)	//初始化矩阵；
	{
		for (j = 1; j <= N; j++)
		{
			if (i == j)
				G[i][j] = 0;
			else
				G[i][j] = G[j][i] = inf;
		}
	}

	int s, d, wt;
	for (i = 0; i < M; i++)
	{
		cin >> s >> d >> wt;
		G[s][d] = G[d][s] = wt;
	}

	return;
}

int Prim(int N)
{
	int i, v, sumw, vcnt;
	sumw = 0;
	vcnt = 1;
	for (i = 1; i <= N; i++)	//点1作为起点；
		dist[i] = G[1][i];	//初始化为到点1的长度；

	while (1)
	{
		v = FindMin(N);
		if (v == -1)
			break;
		sumw += dist[v];
		dist[v] = 0;	//收录进生成树，不为0表示不是生成树的点；
		vcnt++;
		for (i = 1; i <= N; i++)
		{
			if (dist[i] && G[v][i] < inf)	//更新因收录v而使得其他未收录点到生成树的最短长度；
			{
				if (G[v][i] < dist[i])
					dist[i] = G[v][i];
			}
		}
	}

	if (vcnt < N)
		return -1;
	else
		return sumw;
}

int FindMin(int N)
{
	int min, minv, i;
	min = inf;
	for (i = 1; i <= N; i++)
	{
		if (dist[i] && dist[i] < min)
		{
			min = dist[i];
			minv = i;
		}
	}
	if (min == inf)	//顶点不存在；
		return -1;
	else
		return minv;
}
