#include<iostream>
#include<queue>	
#include<vector>
#define MAX 1001
using namespace std;

/*
思路：拓扑排序（哭晕了）。冲突说明关键字和该处的有关，可表示一条有向边；
冲突次数即该点的入度， 散列数组下标看作结点号；
不冲突时，按照字典序（从小到大）输出，用优先队列；
邻接表用二维vector模拟；
*/
int key[MAX], indg[MAX];
struct Inc_cmp
{
	bool operator()(int a, int b)	//优先队列的比较函数
	{
		return key[a] > key[b];
	}
};

int main()
{
	int n, i, j, ka;//ka是散列地址；
	priority_queue<int, vector<int>, Inc_cmp> Q;//优先队列
	cin >> n;
	vector<vector<int> > G(n);//邻接表；
	for (i = 0; i < n; i++)
	{
		cin >> key[i];
		ka = key[i] % n;

		if (key[i] > 0)
		{
			indg[i] = (i + n - ka) % n;	//计算入度；

			if (indg[i] == 0)
				Q.push(i);
			else
			{
				for (j = 0; j < indg[i]; j++)
					G[(ka + j) % n].push_back(i);//结点i加入到(ka + j) % n代表的头结点对应的邻接点；
			}
		}
	}

	int t, cnt = 0;
	vector<int> T(n);//保存拓扑的散列地址下标；
	while (!Q.empty())
	{
		t = Q.top();
		Q.pop();
		T[cnt++] = t;
		for (j = 0; j < (int)G[t].size(); j++)
		{
			if (--indg[G[t][j]] == 0)
				Q.push(G[t][j]);
		}
	}

	for (i = 0; i < cnt; i++)//输出；
	{
		if (i == 0)
			cout << key[T[i]];
		else
			cout << ' ' << key[T[i]];
	}
	cout << endl;

	return 0;
}
