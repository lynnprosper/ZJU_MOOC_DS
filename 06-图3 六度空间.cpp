#include <iostream>
#include <queue>	//用做队列容器；
#define MaxN 10001
using namespace std;

struct Enode	//定义边；
{
	int v1, v2;
};
struct Avnode	//定义邻接表的邻接点；
{
	int data;
	Avnode * next;
};
struct Ahead	//定义邻接表的头结点；也可以不定义结构，这里是为了方便封装；
{
	Avnode *phead = nullptr;
};
struct Graph	//定义图的结构；
{
	int nv;
	int ne;
	Ahead ah[MaxN];
};
int visited[MaxN] = { 0 };	//存储结点是否访问；

Graph *Init_Graph(int vnum);	//初始化图；
void Insert_E(Graph *G, Enode *E);	//把边的关系插入图中；
Graph *Build_G();	//建立图；
void OutputE(Graph *G);	//输出边；
int BFS(Graph *G, int v);	//广度遍历；

int main()
{
	Graph * G = Build_G();	//建立图；
	OutputE(G);	//输出边；

	
	return 0;
}

Graph *Init_Graph(int vnum)	//初始化的图只有顶点，没有边；
{
	Graph *G = new Graph;
	G->nv = vnum;
	G->ne = 0;

	return G;
}

void Insert_E(Graph *G, Enode *E)
{
	Avnode *nAv = new Avnode;
	nAv->data = E->v2;
	nAv->next = G->ah[E->v1].phead;	//注意指针；
	G->ah[E->v1].phead = nAv;

	Avnode *nAv2 = new Avnode;	//无向图两边都要插入；
	nAv2->data = E->v1;
	nAv2->next = G->ah[E->v2].phead;
	G->ah[E->v2].phead = nAv2;

	return;
}

Graph *Build_G()	//建立图；
{
	int tnv;
	Enode *E = new Enode;
	cin >> tnv;
	Graph *G = Init_Graph(tnv);
	cin >> G->ne;
	for (int i = 0; i < G->ne; i++)
	{
		cin >> E->v1 >> E->v2;
		Insert_E(G, E);
	}

	return G;
}

void OutputE(Graph *G)
{
	int cnt;
	for (int i = 1; i <= G->nv; i++)
	{
		cnt = BFS(G, i);

		for (int j = 1; j <= G->nv; j++)	//这里需要初始化；
			visited[j] = 0;

		printf("%d: %.2f%%\n", i, (float)cnt * 100 / G->nv);
	}

	return;
}

int BFS(Graph *G, int v)	//广度遍历；
{
	visited[v] = 1;
	int cnt = 1;
	queue<int> Q;
	int last = v;
	Q.push(v);
	
	int tail, level = 0;	//tail是每一层最后一个压入的点；
	Avnode *w;
	while (!Q.empty())
	{
		v = Q.front();
		Q.pop();
		for (w = G->ah[v].phead; w; w = w->next)
		{
			if (!visited[w->data])
			{
				visited[w->data] = 1;
				cnt++;
				tail = w->data;
				Q.push(w->data);
			}
		}
		if (v == last)	//当弹出的结点和最后压入的点相同时，代表该层遍历完毕，切入下一层；
		{
			level++;
			last = tail;
		}
		if (level == 6)
			break;
	}

	return cnt;
}
