#include <iostream>
using namespace std;
#define Min -10001;
struct Heap
{
	int *data;
	int size;
};

Heap *Create(int N);	//建小顶堆；
void Insert(Heap *H, int t);	//插入元素；
void Print(Heap *H, int d);	//打印路径；

int main()
{
	int N, M, i, t;
	cin >> N >> M;
	Heap *H = Create(N);
	for (i = 0; i < N; i++)
	{
		cin >> t;
		Insert(H, t);
	}
	for (i = 0; i < M; i++)
	{
		cin >> t;
		Print(H, t);
	}

	return 0;
}

Heap *Create(int N)
{
	Heap *H = new Heap;
	H->data = new int[N + 1];	//堆都是从下标1的位置开始存储；
	H->size = 0;
	H->data[0] = Min;

	return H;
}

void Insert(Heap *H, int t)
{
	int i = ++H->size;	//先插入最后一个位置， 然后依次往上过滤；
	for (i = H->size; t < H->data[i / 2]; i /= 2)
		H->data[i] = H->data[i / 2];
	H->data[i] = t;
}

void Print(Heap *H, int d)
{
	int i;
	cout << H->data[d];
	for (i = d / 2; i > 0; i /= 2)
		cout << ' ' << H->data[i];
	cout << endl;

	return;
}
