#include<iostream>
#include<algorithm>
#define MAX 1000000
using namespace std;

//散列法-除留余数， 冲突用平方（正的）探测；
int MinPrime(int n);
void Output(int *t, int n, int size);
int main()
{
	int M, N;
	cin >> M >> N;
	int tsize = MinPrime(M);
	int *table = new int[tsize];
	for (int i = 0; i < tsize; i++)	table[i] = 0;
	Output(table, N, tsize);

	delete[] table;
	return 0;
}
int MinPrime(int n)	//取得散列表大小；
{
	int i, p;
	if (n < 3) return 2;
	p = n % 2 ? n : n + 1;
	while (p < MAX)
	{
		for (i = (int)sqrt(p); i > 2; i--)
		{
			if (p %i == 0) break;
		}
		if (i == 2) break;
		else p += 2;
	}

	return p;
}
void Output(int *t, int n, int size)
{
	int i, j, data, pos;
	int half = size / 2;
	for (i = 0; i < n; i++)
	{
		if (i == 0)	//先输出第一个；
		{
			cin >> data;
			pos = data % size;
			t[pos] = 1;
			cout << pos;
		}
		else
		{
			cin >> data;
			pos = data % size;
			j = 1;
			while (t[pos] && j <= half)	//平方探测的j值<= 表长的一半；
			{
				pos = (data + j*j) % size;
				j++;
			}
			if (!t[pos])
			{
				cout << ' ' << pos;
				t[pos] = 1;
			}
			else cout << " -";
		}
	}
	cout << endl;

	return;
}
