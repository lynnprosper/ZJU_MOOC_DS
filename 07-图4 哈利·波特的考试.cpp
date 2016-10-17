#include<iostream>
#include<vector>
using namespace std;
#define Inf 65535
#define Mlen 101
int G[Mlen][Mlen];

/*
思路：这是最短路径问题。
稠密图，数据结构采用邻接矩阵。
用Floyd算法求出任两点间的最短路径；
然后找出一点到其余点的路径最大值；
再找出这些最大值的最小值；
*/
void Init_G(int G[][Mlen], int N, int M);	//初始化图；
void Floyd(int G[][Mlen], int N);	//floyd算法；
int Find_Max(int G[][Mlen], int row, int N);	//找出一点到其余点的路径最大值；

int main()
{
	int N, M;
	cin >> N >> M;
	Init_G(G, N, M);
	Floyd(G, N);

	int num, t, min_len = Mlen;
	for (int i = 1; i <= N; i++)	//找出路径最大值的最小值；
	{
		t = Find_Max(G, i, N);
		if (t == Inf)
		{
			cout << 0 << endl;
			return 0;
		}
		if (t < min_len)
		{
			num = i;
			min_len = t;
		}
	}
	cout << num << ' ' << min_len << endl;

	return 0;
}

void Init_G(int G[][Mlen], int N, int M)
{
	for (int i = 1; i <= N; i++)	
	{
		for (int j = 1; j <= N; j++)
		{
			if (i == j)
				G[i][j] = 0;	//0表示无边；
			else
				G[i][j] = Inf;	//最大值表示两点不可达；
		}
	}

	int a, b, v;
	for (int i = 0; i < M; i++)	//读入数据，赋值；
	{
		cin >> a >> b >> v;
		G[a][b] = G[b][a] = v;
	}

	return;
}

void Floyd(int G[][Mlen], int N)	//floyd算法；
{
	for (int k = 1; k <= N; k++)
	{
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				if (G[i][k] + G[k][j] < G[i][j])
					G[i][j] = G[i][k] + G[k][j];
			}
		}
	}

	return;
}

int Find_Max(int G[][Mlen], int row, int N)	//找出一点到其余点的路径最大值；
{
	int max = 0;
	for (int i = 1; i <= N; i++)
	{
		max = max < G[row][i] ? G[row][i] : max;
	}

	return max;
}
