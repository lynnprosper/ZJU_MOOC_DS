#include<iostream>
using namespace std;

void shell(int *A, int n);//希尔排序；

int main()
{
	int i, n;
	cin >> n;
	int *list = new int[n+1];
	for (i = 1; i <= n; i++)
		cin >> list[i];
	shell(list, n);
	for (i = 1; i <= n; i++)
	{
		if (i == n)
			cout << list[i] << endl;
		else
			cout << list[i] << ' ';
	}
	return 0;
}

void shell(int *A, int n)
{
	int i, j, d;
	for (d = n / 2; d > 0; d /= 2)
	{
		for (i = d+1; i <= n; i ++)
		{
			if (A[i] < A[i - d])
			{
				A[0] = A[i];
				for (j = i - d; j>0 && A[0]<A[j]; j -= d)
					A[j + d] = A[j];
				A[j + d] = A[0];
			}
		}
	}

	return;
}
