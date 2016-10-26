#include<iostream>
#include<queue>
using namespace std;
#define MaxN 100
/*
思路：关键路径的变形，即找出最长路径长度。
算法：拓扑排序；
数据结构：邻接表；
*/

struct Edge	//邻接表的边定义；
{
	int v1, v2;
	int wt;
};
struct Ajnode	//邻接点；
{
	int ajn;	//结点值；
	int wt;	//权值；
	Ajnode *next = nullptr;
};
struct Ahead	//边表头结点；
{
	Ajnode *first = nullptr;
};
struct Graph
{
	int nv, ne;
	Ahead ah[MaxN];
};

Graph *Init_G(int N);	//初始化构造邻接表；
void Insert_G(Graph *G, Edge e);	//插入邻接表边；
Graph *Build_G();	//建图；
void Topsort(Graph *G);	//拓扑排序；

int main()
{
	Graph *G = Build_G();	//建图；
	Topsort(G);	//拓扑排序；

	return 0;
}

Graph *Init_G(int N)
{
	Graph *G = new Graph;	//初始化顶点数；
	G->nv = N;

	return G;
}

void Insert_G(Graph *G, Edge e)	//插入邻接表边；
{
	Ajnode *aj = new Ajnode;
	aj->wt = e.wt;
	aj->ajn = e.v2;
	aj->next = G->ah[e.v1].first;
	G->ah[e.v1].first = aj;

	return;
}

Graph *Build_G()	//建图；
{
	int N, i;
	cin >> N;
	Graph *G = Init_G(N);
	Edge te;
	cin >> G->ne;

	for (i = 0; i < G->ne; i++)
	{
		cin >> te.v1 >> te.v2 >> te.wt;
		Insert_G(G, te);
	}

	return G;
}

void Topsort(Graph *G)	//拓扑排序；
{
	int N = G->nv;
	int i;
	Ajnode *w;
	int Indegree[MaxN] = { 0 };	//存储顶点的入度，初始化0；
	for (i = 0; i < N; i++)
	{
		for (w = G->ah[i].first; w; w = w->next)
			Indegree[w->ajn]++;	//统计入度；
	}

	queue<int> Q;
	for (i = 0; i < N; i++)	//将入度0的点压入队列；
	{
		if (Indegree[i] == 0)
			Q.push(i);
	}

	int tn, cnt, cptime[MaxN] = { 0 };	//cptime[]统计顶点代表事件完成的时间最大值；
	cnt = 0;	//统计弹出的顶点数，小于总数，表示图不连通；
	while (!Q.empty())
	{
		tn = Q.front();
		Q.pop();
		cnt++;

		for (w = G->ah[tn].first; w; w = w->next)	//处理每个顶点的邻接点；
		{
			if (cptime[tn] + w->wt > cptime[w->ajn])	//更新时间最大值；
				cptime[w->ajn] = cptime[tn] + w->wt;
			if(--Indegree[w->ajn] == 0)	//入度为0，压入；
				Q.push(w->ajn);
		}
	}

	if (cnt != N)
		cout << "Impossible" << endl;
	else
	{
		int t = -1;
		for (i = 0; i < N; i++)
		{
			if (cptime[i] > t)
				t = cptime[i];
		}
		cout << t << endl;
	}

	return;
}
