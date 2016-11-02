#include<iostream>
#include<algorithm>
using namespace std;

void Print(int a[], int n);
int Is_Insert(int a[], int b[], int n);
void Merge(int *b, int n);
int Get_L(int *b, int n);	//求出归并段长度;

/*
思路：先判断是否插入，若不是执行归并。
归并的话先求出归并段长度。
本代码最后两个测试点未通过，冏~
*/
int main()
{
	int n, i;
	cin >> n;
	int *A = new int[n];
	int *B = new int[n];
	for (i = 0; i < n; i++)
		cin >> A[i];
	for (i = 0; i < n; i++)
		cin >> B[i];
	int d = Is_Insert(A, B, n);
	if (d)
		Merge(B, n);

	delete[] A, B;
	
	return 0;
}

void Print(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		if (i != n - 1)
			cout << a[i] << ' ';
		else
			cout << a[i] << endl;
	}
}

int Is_Insert(int a[], int b[], int n)
{
	int i, t, m;
	int flag = 1;
	for (i = 1; i < n - 1; i++)
	{
		if (flag && b[i] > b[i + 1])
		{
			flag = 0;
			t = i;
		}
		if (!flag && b[i + 1] != a[i + 1])
			return 1;
	}

	cout << "Insertion Sort" << endl;
	m = b[t + 1];
	for (i = t; i >= 0 && b[i] > m; i--)
		b[i + 1] = b[i];
	b[i + 1] = m;
	Print(b, n);

	return 0;
}

int Get_L(int *b, int n)
{
	int i, j;
	for (i = 2; i <= n/2; i *= 2)
	{
		for (j = i; j < n; j += i)
		{
			if (b[j - 1] > b[j])
				return i;
		}
	}

	return n;
}

void Merge(int *b, int n)
{
	int i, d = 0;

	d = Get_L(b, n);
	d *= 2;
	for (i = 0; i <= n - d; i += d)	//利用快排求；
		sort(b + i, b + i + d - 1);
	if (i + d / 2 < n)
		sort(b + i, b + n - 1);
	cout << "Merge Sort" << endl;
	Print(b, n);

	return;
}
