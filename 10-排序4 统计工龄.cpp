#include<iostream>
using namespace std;

/*
建一个工龄数组，统计人数，类似桶排序的思想。
*/
int main()
{
	int A[51] = { 0 };
	int N, i, t, max = 0;
	cin >> N;
	for (i = 0; i < N; i++)
	{
		cin >> t;
		A[t]++;
		if (t > max)
			max = t;
	}
	for (i = 0; i <= max; i++)
	{
		if (A[i])
			cout << i << ':' << A[i] << endl;
	}

	return 0;
}
