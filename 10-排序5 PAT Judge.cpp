#include<iostream>
using namespace std;
#include<algorithm>
struct Node
{
	int id;
	int pbm[6];	//问题个数；
	int tscre;	//总分；
	int fcnt;	//满分个数；
	int fflag;	//是否通过编译标志位；
};

/*
核心写好快排的比较函数；
最后一个测试点未通过；
*/
static bool cmp(const Node &a, const Node &b);
void Print(Node *stu, int n, int k);
int main()
{
	//freopen("in.txt", "r", stdin);
	int N, K, M, i, j;
	cin >> N >> K >> M;
	Node *stu = new Node[N + 1];
	for (i = 0; i <= N; i++)	//数组初始化；
	{
		stu[i].tscre = stu[i].fcnt = stu[i].fflag = 0;
		for (j = 0; j <= K; j++)
			stu[i].pbm[j] = -1;
	}

	int *scr = new int[K + 1];	//每个问题总分；
	for (i = 1; i <= K; i++)
		scanf("%d", &scr[i]);

	int t1, t2, t3, d;
	for (i = 0; i < M; i++)
	{
		scanf("%d %d %d", &t1, &t2, &t3);
		if (t3 > -1)
			stu[t1].fflag = 1;	//置标志位；
		stu[t1].id = t1;
		t3 = t3 > -1 ? t3 : 0;	//若得分-1，更改为0；
		if (stu[t1].pbm[t2] != -1)
			d = t3 - stu[t1].pbm[t2];	//判断一个题多次提交，计入的分数；
		else
			d = t3;	//第一次提交；

		if (d > 0)
		{
			stu[t1].tscre += d;
			stu[t1].pbm[t2] = t3;
			if (t3 == scr[t2])	//此处会过滤掉多次得满分的情况；
				stu[t1].fcnt++;
		}
	}

	stu[0].tscre = -1;	//数组第一个初始化，用来比较；
	sort(stu + 1, stu + N + 1, cmp);
	Print(stu, N, K);

	delete[] stu, scr;
	return 0;
}

bool cmp(const Node &a, const Node &b)
{
	if (a.tscre != b.tscre)
		return a.tscre > b.tscre;
	else
	{
		if (a.fcnt != b.fcnt)
			return a.fcnt > b.fcnt;
		else
			return a.id < b.id;
	}
}

void Print(Node *stu, int n, int k)
{
	int i, j, flag;
	for (i = 1; i <= n; i++)
	{
		if (stu[i].fflag)
		{
			if (stu[i].tscre != stu[i - 1].tscre)
			{
				flag = i;
				printf("%d ", flag);
			}
			else
				printf("%d ", flag);

			printf("%05d %d", stu[i].id, stu[i].tscre);
			for (j = 1; j <= k; j++)
			{
				if (stu[i].pbm[j] != -1)
					printf(" %d", stu[i].pbm[j]);
				else
					printf(" -");
			}
			printf("\n");
		}

	}

	return;
}
