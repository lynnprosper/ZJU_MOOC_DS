#include<iostream>
using namespace std;

/*
思路：最少的交换次数，即每次交换，有一个元素放到正确位置。
用A[0]（不能是0）和下标是A[0]的元素交换，直到A[0]为0.此时
要判断所以元素是否是在正确位置。
如果不是，就让A[0]和这个元素交换。
这个位置如何选取？从下标1的位置开始扫描即可。
*/
void Swap(int *a, int *b);	//交换；
int FirstNot(int *A, int begin, int end);	//寻找第一个不等的元素；
int main()
{
	//freopen("in.txt", "r", stdin);
	int N, i, cnt = 0;
	cin >> N;
	int *A = new int[N];
	for (i = 0; i < N; i++)
		cin >> A[i];

	int cur = FirstNot(A, 1, N - 1);	//寻找第一个不等的元素；
	while (cur != 0)
	{
		if (A[0] == 0)	//未交换完；
		{
			Swap(A, A + cur);
			cnt++;
		}

		while (A[0] != 0)
		{
			Swap(A, A + A[0]);
			cnt++;
		}
		cur = FirstNot(A, cur, N - 1);
	}
	cout << cnt << endl;

	return 0;
}

void Swap(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

int FirstNot(int *A, int begin, int end)
{
	for (int i = begin; i <= end; i++)
	{
		if (A[i] != i)
			return i;
	}
	return 0;
}
