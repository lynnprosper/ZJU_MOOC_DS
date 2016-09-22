#include <iostream>
using namespace std;

typedef struct tnode
{
	char ch;
	int left;
	int right;
}tNode;
tNode * tBuild(int &m);
int isOmorphic(tNode *t1, int h1, tNode *t2, int h2);

//key: use recursion method;
//data structure use static link to imitate the bi-tree;
int main()
{
	int h1, h2;

	tNode *tr1 = tBuild(h1);
	tNode *tr2 = tBuild(h2);

	if (isOmorphic(tr1, h1, tr2, h2))
		cout << "Yes" << endl;
	else
		cout << "No" << endl;

	delete[] tr1;
	delete[] tr2;

	return 0;
}

tNode * tBuild(int &m)
{
	int i, n;
	cin >> n;
	tNode *tr = new tNode[n];

	if (n)
	{
		int * check = new int[n];
		for (i = 0; i < n; i++)
			check[i] = 0;

		char t1, t2;
		for (i = 0; i < n; i++)
		{
			cin >> tr[i].ch >> t1 >> t2;
			if (t1 == '-')
				tr[i].left = -1;		// '-1' means it's a leaf node;
			else
			{
				tr[i].left = t1 - '0';
				check[tr[i].left] = 1;
			}
			if (t2 == '-')
				tr[i].right = -1;
			else
			{
				tr[i].right = t2 - '0';
				check[tr[i].right] = 1;
			}
		}

		for (i = 0; i < n; i++)
		{
			if (!check[i])
				break;
		}
		m = i;			//find the head node;
		return tr;
	}
	else
	{
		m = -1;
		return NULL;
	}
}

int isOmorphic(tNode *t1, int h1, tNode *t2, int h2)	// recursion;
{
	if (h1 == -1 && h2 == -1)
		return 1;
	if ((h1 == -1 && h2 != -1) || (h1 != -1 && h2 == -1))
		return 0;
	if (t1[h1].ch != t2[h2].ch)
		return 0;

	return((isOmorphic(t1, t1[h1].left, t2, t2[h2].left) && isOmorphic(t1, t1[h1].right, t2, t2[h2].right)) ||
		(isOmorphic(t1, t1[h1].right, t2, t2[h2].left) && isOmorphic(t1, t1[h1].left, t2, t2[h2].right)));

}
