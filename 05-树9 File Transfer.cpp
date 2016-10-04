#include <iostream>
using namespace std;

int *Create(int n);	//创建静态链表；
int FindRoot(int *co, int d);	//查找根结点；
void Union(int *co, int root1, int root2);	//合并
void CheckCon(int *co);	//检查是否连通；
void Insert(int *co);	//将两个连通；
void CheckNet(int *co, int n);	//检查整个连通网；

//思路：考察并查集操作；
int main()
{
	int n;
	char ch;
	cin >> n;
	int *co = Create(n);
	do
	{
		cin >> ch;
		switch(ch)
		{
		case 'C':CheckCon(co); break;
		case 'I':Insert(co); break;
		case 'S':CheckNet(co, n); break;
		}
	} while (ch != 'S');

	return 0;
}

int *Create(int n)
{
	int i;
	int *co = new int[n+1];	//下标表示编号， 值表示父结点；
	for (i = 0; i <= n; i++)	//每个结点根结点值为-1，表示各结点独立；
		co[i] = -1;	

	return co;
}

int FindRoot(int *co, int d)	//找到根结点；
{
	if (co[d] < 0)
		return d;
	else
		return co[d] = FindRoot(co, co[d]);	//表示将所有子结点均指向一个总根，用到了路径压缩思想；以缩减查找规模；
}

void CheckCon(int *co)	//检查连通性；
{
	int t1, t2;
	cin >> t1 >> t2;
	int root1 = FindRoot(co, t1);
	int root2 = FindRoot(co, t2);

	if (root1 == root2)
		cout << "yes" << endl;
	else
		cout << "no" << endl;

	return;
}

void Union(int *co, int root1, int root2)	//合并；
{
	if (co[root1] < co[root2])	// 用到了按秩归并， 把小树并到大树上；
	{
		co[root1] += co[root2];
		co[root2] = root1;
	}
	else
	{
		co[root2] += co[root1];
		co[root1] = root2;
	}

	return;
}

void Insert(int *co)
{
	int t1, t2;
	cin >> t1 >> t2;
	int root1 = FindRoot(co, t1);
	int root2 = FindRoot(co, t2);
	if (root1 != root2)
		Union(co, root1, root2);

	return;
}

void CheckNet(int *co, int n)
{
	int i, cnt = 0;
	for (i = 1; i <= n; i++)
	{
		if (co[i] < 0)
			cnt++;
	}

	if (cnt == 1)
		cout << "The network is connected." << endl;
	else
		printf("There are %d components.\n", cnt);

	return;
}
