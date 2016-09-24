#include <iostream>
#include <vector>
#include <stack>
#include <string>
using namespace std;

int find_pos(vector<int> &v, int data);
void post_traverse(vector<int> &pre, vector<int> &ino, int left, int right, int head);

//idea: the order of push is the Pre_order bi_tree, one of pop is the In_order bi_tree;
// so by recursion, we can get the post-order using the pre-order and in-order sequences;
int main()
{
	int n, i, node;
	string str;
	stack<int> sta;
	vector<int> pre, ino;
	cin >> n;
	for (i = 0; i < 2*n; i++)
	{
		cin >> str;
		if (str == "Push")		// get the pre-order sequence;
		{
			cin >> node;
			pre.push_back(node);
			sta.push(node);
		}
		else
		{
			ino.push_back(sta.top());	// get the in-order sequence;
			sta.pop();
		}
	}

	post_traverse(pre, ino, 0, n - 1, 0);

	return 0;
}

int find_pos(vector<int> &v, int data)
{
	unsigned int i;
	for (i = 0; i < v.size(); i++)
	{
		if (v[i] == data)
			break;
	}
	return i;
}

void post_traverse(vector<int> &pre, vector<int> &ino, int left, int right, int head)
{
	int pa_pos = find_pos(ino, pre[head]);
	int left_size = pa_pos - left + 1;
	if (head < (int)pre.size())
	{
		if (pa_pos > left)		//recurse left part;
			post_traverse(pre, ino, left, pa_pos - 1, head + 1);
		if (pa_pos < right)
			post_traverse(pre, ino, pa_pos + 1, right, head + left_size);	//recurse right part;
		if (head == 0)
			cout << pre[head] << endl;	// output the parent node;
		else
			cout << pre[head] << ' ';
	}
}
