#include <iostream>
using namespace std;
typedef struct Node
{
	int data, flag;
	struct Node * left;
	struct Node *right;
}node;

node *nwNode(int d);
void nodeInsert(node *&head, int d);
node *tBuild(int n);
int tJudge(node *head, int n);
void flagReset(node *head);
void tDelete(node *head);

/*

思路：先建立模板树，然后依次将待测试树和其比较。
比较过的结点的标志设为1，若该结点未比较过且其数据不等，则两树不同。
*/
int main()
{
	int n, line, i;
	cin >> n;
	while (n)
	{
		cin >> line;
		node *head = tBuild(n);
		for (i = 0; i < line; i++)
		{
			if (tJudge(head, n))
				cout << "Yes" << endl;
			else
				cout << "No" << endl;

			flagReset(head);
		}
		tDelete(head);

		cin >> n;
	}

	return 0;
}

node *nwNode(int d)
{
	node *p = new node;
	p->data = d;
	p->flag = 0;
	p->left = p->right = NULL;
	return p;
}
void nodeInsert(node *&head, int d)
{

	if (!head)
		head = nwNode(d);
	else
	{
		if (d > head->data)
			nodeInsert(head->right, d);
		else
			nodeInsert(head->left, d);
	}
}
node *tBuild(int n)
{
	int i, d;
	cin >> d;
	node *head = nwNode(d);
	for (i = 1; i < n; i++)
	{
		cin >> d;
		nodeInsert(head, d);
	}
	return head;
}
int tJudge(node *head, int n)
{
	node *T;
	int i, t, fflag = 1;
	for (i = 0; i < n; i++)
	{
		T = head;
		cin >> t;
		while (T && fflag)
		{
			if (T->flag == 1)
			{
				if (t > T->data)
					T = T->right;
				else
					T = T->left;
			}
			else if (T->flag == 0 && T->data == t)
			{
				T->flag = 1;
				break;
			}
			else
			{
				fflag = 0;
				break;
			}
		}
	}
	if (fflag == 0 || T == NULL)
		return 0;
	else
		return 1;
}
void flagReset(node *head)	//需要恢复结点的标志。
{
	if (head->left)
		flagReset(head->left);
	if (head->right)
		flagReset(head->right);
	head->flag = 0;
}
void tDelete(node *head)
{
	if (head->left)
		tDelete(head->left);
	if (head->right)
		tDelete(head->right);
	delete head;
}
