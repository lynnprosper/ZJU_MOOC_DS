#include<iostream>
#include<algorithm>
#include<cstring>	//字符串处理函数；
#define MAX 1000000
using namespace std;

struct Node	//散列链表结点；
{
	char data[12];
	Node *next;
	int cnt;
};
struct HashT	//散列表；
{
	int size;
	Node *ht;	//散列表表头数组；
};

/*
思路：为了提高速度，用散列结构（分离链接法）。
取号码后5位作为关键字。
注意：不能用cpp的string容器，其会超时，只有用c的char了。
*/
int Hash(int k, int p);	//hash函数；
HashT *Create(int N);	//新表；
int MinPrime(int N);	//散列表的大小，比总数大的最小质数；
Node *FindPos(HashT *T, char *key, int &pos);	//查找结点；
void Insert(HashT *T, char *key);	//插入结点；
void Output(HashT *T);
int main()
{
	//freopen("in.txt", "r", stdin);
	int N, i;
	char key[12];
	cin >> N;
	HashT *T = Create(N * 2);
	for (i = 0; i < N; i++)	//读入数据；
	{
		cin >> key;
		Insert(T, key);
		cin >> key;
		Insert(T, key);
	}
	Output(T);

	return 0;
}

int Hash(int k, int p)
{
	return k%p;
}
int MinPrime(int N)
{
	int t = (N % 2) ? N + 2 : N + 1;
	while (t < MAX)
	{
		int i = (int)sqrt(t);
		for (i; i > 2; i--)
		{
			if (t%i == 0)
				break;
		}
		if (i == 2) break;
		else t += 2;
	}
	return t;
}

HashT *Create(int N)
{
	HashT *T = new HashT;
	T->size = MinPrime(N);
	T->ht = new Node[T->size];
	for (int i = 0; i < T->size; i++)
	{
		T->ht[i].cnt = 0;
		T->ht[i].data[0] = '\0';
		T->ht[i].next = NULL;
	}

	return T;
}
Node *FindPos(HashT *T, char *key, int &pos)
{
	pos = Hash(atoi(key+6), T->size);
	Node *p = T->ht[pos].next;
	while (p && strcmp(p->data, key))
		p = p->next;

	return p;
}
void Insert(HashT *T, char *key)
{
	int pos;
	Node *p = FindPos(T, key, pos);
	if (!p)
	{
		Node *newn = new Node;
		newn->next = T->ht[pos].next;
		T->ht[pos].next = newn;
		newn->cnt = 1;
		strcpy(newn->data, key);
	}
	else
		p->cnt++;

	return;
}
void Output(HashT *T)	//遍历散列表，找最大值；
{
	int i, maxn, partner;
	Node *p;
	char re[12];
	maxn = partner = 0;
	for (i = 0; i < T->size; i++)
	{
		p = T->ht[i].next;
		while (p)
		{
			if (maxn < p->cnt)
			{
				maxn = p->cnt;
				partner = 1;
				strcpy(re, p->data);
			}
			else if (maxn == p->cnt)
			{
				partner++;
				if (strcmp(re, p->data)>0)	strcpy(re, p->data);
			}
			p = p->next;
		}
	}
	if (partner == 1)
		printf("%s %d\n", re, maxn);
	else
		printf("%s %d %d\n", re, maxn, partner);

	return;
}
