#include <iostream>
#include <queue>
using namespace std;
#define MaxV 11
int G[MaxV][MaxV] = { 0 };	//全局变量；
int visited[MaxV] = { 0 };	//存储结点是否访问过；

void BuildG(int e);	//建立图；
void ListDfs(int v);	//DFS遍历输出；
void Dfs(int n, int v);	//DFS遍历结点值；
void InitVisited(int v);	//初始化为0；
void ListBfs(int v);	//BFS遍历输出；
void Bfs(int n, int v);	//BFS遍历结点值；

/*
思路：考虑到要按照从小到大的顺序遍历输出，结构用邻接矩阵（邻接表不方便，要用小根堆才能实现）。
1.建立图（用二维数组表示）， 依次读入各边；
2.DFS遍历输出；
3.BFS遍历输出；
*/
int main()
{
	int v, e;
	cin >> v >> e;
	BuildG(e);
	ListDfs(v);
	InitVisited(v);
	ListBfs(v);

	return 0;
}

void BuildG(int e)
{
	int i, v1, v2;
	for (i = 0; i < e; i++)
	{
		cin >> v1 >> v2;
		G[v1][v2] = G[v2][v1] = 1;
	}

	return;
}

void ListDfs(int v)
{
	int i;
	for (i = 0; i < v; i++)
	{
		if (!visited[i])
		{
			cout << "{ ";
			Dfs(i, v);
			cout << '}' << endl;
		}
	}

	return;
}

void Dfs(int n, int v)
{
	int i;
	visited[n] = 1;
	cout << n << ' ';
	for (i = 0; i < v; i++)	//递归实现；
	{
		if (!visited[i] && G[n][i])
			Dfs(i, v);
	}

	return;
}

void InitVisited(int v)
{
	for (int i = 0; i < v; i++)
		visited[i] = 0;

	return;
}

void ListBfs(int v)
{
	for (int i = 0; i < v; i++)
	{
		if (!visited[i])
		{
			cout << "{ ";
			Bfs(i, v);
			cout << '}' << endl;
		}
	}

	return;
}

void Bfs(int n, int v)
{
	int tv;
	queue<int> Q;
	cout << n << ' ';
	visited[n] = 1;
	Q.push(n);
	while (!Q.empty())	//队列实现；
	{
		tv = Q.front();
		Q.pop();
		for (int i = 0; i < v; i++)
		{
			if (!visited[i] && G[tv][i])
			{
				cout << i << ' ';
				visited[i] = 1;
				Q.push(i);
			}
		}
	}

	return;
}
