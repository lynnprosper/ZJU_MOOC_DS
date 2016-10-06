#include <iostream>
#include <string>
using namespace std;
struct Heap
{
	int *data;
	int size = 0;
};
struct cnode
{
	int tag = 0;
	cnode *left = nullptr;
	cnode *right = nullptr;
};

Heap *Init_Heap(int n);	//初始化小根堆（利用静态链表的逻辑结构）；
void Insert_Heap(Heap *H, int x);	//把元素依次插入小根堆；
int Delmin_Heap(Heap *H);	//删除小根堆中的最小元素；
int Cal_Wpl(Heap *H);	//计算huffman编码的wpl；
int wpl_prefix(int *sample, int n, int &re);	//计算待测编码的wpl及判断是否为前缀编码；

/*思路：要判断是否，需要解决两个问题： 1）编码wpl等于huffman编码的wpl；
2)待测编码是前缀编码。
问题1： 首先要求出标准wpl。观察huffman树，我们发现其wpl是非叶子结点权值和。
于是，我们无需构造出huffman树来求权值(麻烦点），通过模拟树的构造过程，
理由小根堆的特点求出wpl；

而待测编码的wpl就是利用每个编码的字符串长度，乘以每个字符的权值得到；
问题2：
思路是构造一个二叉树出来，模拟huffman树。
1.让每个编码遍历树，结束时在当前结点设置标记为1；
2.如果遍历时，未结束时碰到了标记为1的结点，则不是前缀编码；
3.结束时，未碰到标记点（包括最后一个），是前缀编码。
*/
int main()
{
	int n, i, val;
	char ch;
	cin >> n;
	int *sample = new int[n];	//每个字符权值存储在这里；
	Heap *H = Init_Heap(n);	//初始化小根堆（利用静态链表的逻辑结构）；
	for (i = 0; i < n; i++)
	{
		cin >> ch >> val;
		sample[i] = val;
		Insert_Heap(H, val);	//把元素依次插入小根堆；
	}
	int best_wpl = Cal_Wpl(H);	//计算huffman编码的wpl；

	int m, wpl, re;	//re是用来判断是否前缀编码，是为1，否为0；
	cin >> m;
	for (i = 0; i < m; i++)
	{
		wpl = wpl_prefix(sample, n, re);	//计算待测编码的wpl及判断是否为前缀编码；
		if (wpl == best_wpl && re == 1)
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
	}
	delete sample;

	return 0;
}

Heap *Init_Heap(int n)
{
	Heap *H = new Heap;
	H->data = new int[n + 1];	//堆的下标从1开始（为了操作方便）；
	H->data[0] = -1;	//小根堆赋值最小值；

	return H;
}

void Insert_Heap(Heap *H, int x)	//把元素依次插入小根堆；
{
	int i = ++(H->size);
	for (; H->data[i / 2] > x; i /= 2)	//从下往上过滤；
		H->data[i] = H->data[i / 2];
	H->data[i] = x;

	return;
}

int Delmin_Heap(Heap *H)	//删除小根堆中的最小元素；
{
	int t = H->data[H->size--];
	int min = H->data[1];
	int pa, chi;
	for (pa = 1; pa * 2 <= H->size; pa = chi)	//从上往下过滤最小元素；
	{
		chi = pa * 2;
		if (chi != H->size && H->data[chi + 1] < H->data[chi])	//找到子结点的最小下标；
			chi++;
		if (t < H->data[chi])
			break;
		else
			H->data[pa] = H->data[chi];
	}
	H->data[pa] = t;	//赋值最小元素

	return min;
}

int Cal_Wpl(Heap *H)	//计算huffman编码的wpl；
{
	int sum = 0;
	if (H->size > 1)
	{
		int i, t1, t2, t;
		int m = H->size;
		for (i = 1; i < m; i++)
		{
			t1 = Delmin_Heap(H);	//模拟构造huffman树的过程，先取出两个最小值，相加，把和插入堆中；
			t2 = Delmin_Heap(H);
			t = t1 + t2;
			Insert_Heap(H, t);
			sum += t;
		}
	}
	else
		sum = H->data[0];

	return sum;
}

int wpl_prefix(int *sample, int n, int &re)	//计算待测编码的wpl及判断是否为前缀编码；
{
	int i, j, len, wpl = 0;
	char ch;
	string st;
	cnode *phead = new cnode;
	cnode *p = phead;
	re = 1;
	for (i = 0; i < n; i++)
	{
		cin >> ch >> st;	//此处计算wpl；
		len = st.length();
		wpl += len*sample[i];

		if (re != 0)	//此处判断是否前缀编码；
		{
			for (j = 0; j < len; j++)
			{
				if (st[j] == '0')	//0的话判断左边；
				{
					if (p->left == nullptr)	//左边空，新建结点；
					{
						cnode *q = new cnode;
						p->left = q;
					}
					else
					{
						if (p->tag == 1)
						{
							re = 0;
							break;
						}
					}
					p = p->left;
				}
				else if (st[j] == '1')	//判断右边；
				{
					if (p->right == nullptr)
					{
						cnode *q = new cnode;
						p->right = q;
					}
					else
					{
						if (p->tag == 1)
						{
							re = 0;
							break;
						}
					}
					p = p->right;
				}
			}

			if (p->left == nullptr && p->right == nullptr)
				re = 1;
			else
				re = 0;
			if (p->tag == 0)	//注意此处需要判断，最后结点标记不为1才能赋值（待测编码有可能有相同的）；
				p->tag = 1;
			else
				re = 0;

			p = phead;
		}
	}

	return wpl;
}
