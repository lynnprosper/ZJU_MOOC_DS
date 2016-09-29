#include <iostream>
using namespace std;

int incCmp(const void *a, const void *b);	//快排比较函数；
void tBuild(int *T, int root, int *ino, int &pos, int n);	//模拟建造完全二叉树；
void Print(int *T, int n);	//打印输出；

/*
思路：刚开始打算仿照AVL想法建树，后面发现无法根据左右旋转来平衡。
后面看了下大牛的思路。
题意其实是构造一个完全二叉排序树，所以我们要分析完全二叉树的性质， 即结点下标i，
左子结点2i， 右子结点2i+1， 这是完全二叉树特有的性质。所以结构上我们可以用数组来表示。
然后如何保证有序呢？不要忘了，二叉排序树中序遍历是有序的。
于是问题就成了，通过完全二叉树的中序遍历输出层序遍历。
*/
int main()
{
	int N, i;
	int pos = 0;
	cin >> N;
	int *T = new int[N+1];
	int *ino = new int[N];
	for (i = 0; i < N; i++)
		cin >> ino[i];
	qsort(ino, N, sizeof(ino[0]), incCmp);	//数组排序形成中序遍历；
	tBuild(T, 1, ino, pos, N);	//模拟建造完全二叉树；
	Print(T, N + 1);

	return 0;
}

int incCmp(const void *a, const void *b)	//快排比较函数；
{
	return (*(int*)a - *(int*)b);
}

void tBuild(int *T, int root, int *ino, int &pos, int n)	//模拟建造完全二叉树；
{
	if (root > n)	//递归终止条件；
		return;
	int left, right;
	left = root << 1;	//左子结点下标；
	right = (root << 1) + 1;	//右子结点下标；
	tBuild(T, left, ino, pos, n);	//左递归；
	T[root] = ino[pos++];
	tBuild(T, right, ino, pos, n);	//右递归；
}

void Print(int *T, int n)	//打印输出；
{
	int i, flag = 1;
	for (i = 1; i < n; i++)
	{
		if (flag)
		{
			cout << T[i];
			flag = 0;
		}
		else
			cout << ' ' << T[i];
	}
	cout << endl;

	return;
}
