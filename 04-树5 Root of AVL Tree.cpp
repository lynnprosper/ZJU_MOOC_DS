#include <iostream>
#include <algorithm>
using namespace std;
typedef struct Node
{
	int data;
	struct Node *left;
	struct Node *right;
}node;

int GetH(node *T);
node *SingleLL(node *T);
node *SingleRR(node *T);
node *DoubleLR(node *T);
node *DoubleRL(node *T);
node *nInsert(node *T, int d);

//经典的AVL旋转问题。
int main()
{
	node *T = NULL;
	int N, i, t;
	cin >> N;
	for (i = 0; i < N; i++)
	{
		cin >> t;
		T = nInsert(T, t);
	}
	cout << T->data << endl;

	return 0;
}

int GetH(node *T)
{
	if (!T)
		return 0;

	return(max(GetH(T->left), GetH(T->right)) + 1);
}	 //取得树的高度， 空树高度为0。

node *SingleLL(node *T)	//左单旋；
{
	node *B = T->left;
	T->left = B->right;
	B->right = T;

	return B;
}

node *SingleRR(node *T)	//右单旋；
{
	node *B = T->right;
	T->right = B->left;
	B->left = T;

	return B;
}

node *DoubleLR(node *T)	//左右双旋；
{
	T->left = SingleRR(T->left);
	T = SingleLL(T);

	return T;
}

node *DoubleRL(node *T)	//右左双旋；
{
	T->right = SingleLL(T->right);
	T = SingleRR(T);

	return T;
}

node *nInsert(node *T, int d)	//建立AVL树；
{
	if (!T)
	{
		T = new node;
		T->data = d;
		T->left = NULL;
		T->right = NULL;
	}
	else if (d < T->data)
	{
		T->left = nInsert(T->left, d);	//递归左插入；
		if (GetH(T->left) - GetH(T->right) == 2)	//平衡处理；
		{
			if (d < T->left->data)
				T = SingleLL(T);
			else
				T = DoubleLR(T);
		}
	}
	else if (d > T->data)
	{
		T->right = nInsert(T->right, d);	//递归右插；
		if (GetH(T->left) - GetH(T->right) == -2)	//平衡处理；
		{
			if (d > T->right->data)
				T = SingleRR(T);
			else
				T = DoubleRL(T);
		}
	}

	return T;
}
