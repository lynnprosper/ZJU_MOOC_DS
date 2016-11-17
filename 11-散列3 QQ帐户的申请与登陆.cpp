#include<iostream>
#include<string>
#include<map>
using namespace std;

//这里取了个巧， 用了STL中的map。应该是用分离链表法进行散列的
//散列函数用除留余数法，从号码第四位起作为关键字；
int main()
{
	map<string, string> mymap;
	char a;
	string num, pw;
	int i, n;
	cin >> n;
	for (i = 0; i < n; i++)
	{
		cin >> a >> num >> pw;
		if (a == 'L')
		{
			if (mymap.find(num) == mymap.end())
				cout << "ERROR: Not Exist" << endl;
			else if (mymap[num] != pw)
				cout << "ERROR: Wrong PW" << endl;
			else
				cout << "Login: OK" << endl;
		}
		else if (a == 'N')
		{
			if (mymap.find(num) != mymap.end())
				cout << "ERROR: Exist" << endl;
			else
			{
				mymap.insert(make_pair(num, pw));
				cout << "New: OK" << endl;
			}
		}

	}

	return 0;
}
