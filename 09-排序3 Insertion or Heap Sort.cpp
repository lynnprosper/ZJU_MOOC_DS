#include<iostream>
using namespace std;

int Is_Insert(int *a, int *b, int n);	//判断是否插入；
void Print(int *b, int n);	//输出序列；
void HeapSort(int *b, int n);	//堆排；
void AdjustDown(int *b, int n);	//把根结点向下调整，使之有序；

/*
思路：先判断是否插入。
堆的话找到待排序位置，执行一次调整就ok；
注意，一个测试点（最小N，heap）未通过；
*/
int main()
{
	int n, i;
	cin >> n;
	int *A = new int[n + 1];
	int *B = new int[n + 1];
	for (i = 1; i <= n; i++)
		cin >> A[i];
	for (i = 1; i <= n; i++)
		cin >> B[i];

	int flag = Is_Insert(A, B, n);	//判断是否插入；
	if (!flag)
		HeapSort(B, n);	//堆排；

	delete[] A, B;
	return 0;
}

int Is_Insert(int *a, int *b, int n)
{
	int j, i, x;
	for (i = 1; i < n; i++)
	{
		if (b[i] > b[i + 1])
		{
			x = i + 1;
			if (i == 1 && a[1] != b[1])	//堆排；
				return 0;
			break;
		}
	}
	if (i == n)	//序列有序，是堆排；
		return 0;
	b[0] = b[x];
	for (j = i; b[j] > b[0]; j--)	//插入调整；
		b[j + 1] = b[j];
	b[j + 1] = b[0];
	cout << "Insertion Sort" << endl;
	Print(b, n);
	return 1;
}

void Print(int *b, int n)
{
	int i;
	for (i = 1; i <= n; i++)
	{
		if (i == n)
			cout << b[i] << endl;
		else
			cout << b[i] << ' ';
	}
	return;
}

void HeapSort(int *b, int n)
{
	int i;
	for (i = n; b[i] > b[1]; i--);
	if (i > 1)
	{
		swap(b[1], b[i]);	//找到位置，交换；
		i--;
		AdjustDown(b, i);	//调整，使堆为最大堆；
	}
	cout << "Heap Sort" << endl;
	Print(b, n);

	return;
}

void AdjustDown(int *b, int n)	//把根结点向下调整，使之有序；
{
	int x = b[1];
	int pa, ch;
	for (pa = 1; pa * 2 <= n; pa = ch)
	{
		ch = pa * 2;
		if (ch != n && b[ch] < b[ch + 1])
			ch++;
		if (x >= b[ch])
			break;
		else
			b[pa] = b[ch];
	}
	b[pa] = x;

	return;
}
