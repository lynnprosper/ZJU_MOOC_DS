#include <iostream>
#include <queue>
using namespace std;
typedef struct node
{
	int left;
	int right;
}Node;

Node *tBuild(int &h);   //call by reference;
void LevelOrder(Node *tr, int h);

//idea: build the tree use static link firstly;
// then traverse the tree by imitating level-order travese;
int main()
{
	int hd;
	Node *tr = tBuild(hd);
	LevelOrder(tr, hd);

	return 0;
}

Node *tBuild(int &h)
{
	int n, i;
	char tleft, tright;
	cin >> n;
	Node *tr = new Node[n];
	int *check = new int[n];
	for (i = 0; i < n; i++)
		check[i] = 0;

	for (i = 0; i < n; i++)
	{
		cin >> tleft >> tright;
		if (tleft == '-')
			tr[i].left = -1;
		else
		{
			tr[i].left = tleft - '0';
			check[tr[i].left] = 1;
		}

		if (tright == '-')
			tr[i].right = -1;
		else
		{
			tr[i].right = tright - '0';
			check[tr[i].right] = 1;
		}
	}

	for (i = 0; i < n; i++)
	{
		if (!check[i])
			break;
	}
	h = i;
	return tr;
}

void LevelOrder(Node *tr, int h)
{
	int t, flag = 1;
	queue<int> q;
	q.push(h);
	while (!q.empty())
	{
		t = q.front();
		q.pop();
		if (tr[t].left == -1 && tr[t].right == -1)
		{
			if (flag)
			{
				cout << t;
				flag = 0;
			}
			else
				cout << ' ' << t;
		}
		else
		{
			if (tr[t].left != -1)
				q.push(tr[t].left);
			if (tr[t].right != -1)
				q.push(tr[t].right);
		}
	}
	cout << endl;
}
