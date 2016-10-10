#include <iostream>
#include <algorithm>	//使用平方和开方函数；
#include <vector>
using namespace std;
#define MinD 42.5

struct Point	//存储点坐标；
{
	int x, y;
	int visited = 0;
};

double Distance(const Point a, const Point b);	//计算两点距离；
void Build_array(vector<Point> &pv, int n);	//保存每个点的数组；
void Create_first(vector<Point> &pv, vector<int> &f, int n, int D);	//处理第一次；
void Search_dfs(vector<Point> &pv, int i, int D, int N);	//dfs递归；

/*
把每个点存入一维数组，递归两点距离是否满足即可；
*/
int main()
{
	vector<Point> pv;
	vector<int> Firstp;
	int N, D;
	cin >> N >> D;
	Build_array(pv, N);

	if (D >= MinD)
	{
		cout << "Yes" << endl;
		return 0;
	}
	Create_first(pv, Firstp, N, D);
	if (Firstp.empty())
	{
		cout << "No" << endl;
		return 0;
	}

	for (int i = 0; i < (int)Firstp.size(); i++)
		Search_dfs(pv, Firstp[i], D, N);
	cout << "No" << endl;

	return 0;
}

double Distance(const Point a, const Point b)
{
	return(sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2)));
}

void Build_array(vector<Point> &pv, int n)
{
	Point t;
	for (int i = 0; i < n; i++)
	{
		cin >> t.x >> t.y;
		pv.push_back(t);
	}

	return;
}

void Create_first(vector<Point> &pv, vector<int> &f, int n, int D)
{
	Point O;
	O.x = O.y = 0;
	for (int i = 0; i < n; i++)
	{
		if (Distance(pv[i], O) <= (D + 7.5))
			f.push_back(i);
	}

	return;
}

void Search_dfs(vector<Point> &pv, int i, int D, int N)
{
	pv[i].visited = 1;
	if ((50 - abs(pv[i].x) <= D) || (50 - abs(pv[i].y) <= D))
	{
		cout << "Yes" << endl;
		exit(0);
	}
	for (int j = 0; j < N; j++)
	{
		if (!pv[j].visited && Distance(pv[i], pv[j]) <= D)
			Search_dfs(pv, j, D, N);
	}

	return;
}
