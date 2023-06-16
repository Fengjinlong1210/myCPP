#define _CRT_SECURE_NO_WARNINGS 1
#include "RBTree.h"
#include <ctime>
//#include "test.h"

void Test1()
{
	RBTree<int, int> t;
	int arr[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	for (auto& e : arr)
	{
		t.insert(make_pair(e, e));
	}
	t.InOrder();
	cout << "ÊÇ·ñÊÇºìºÚÊ÷" << t.IsBalance() << endl;
}

void Test2()
{
	RBTree<int, int> t;
	srand((unsigned int)time(nullptr));
	const int N = 100;
	for (int i = 0; i < N; ++i)
	{
		int x = rand();
		t.insert(make_pair(x, x));
	}
	t.InOrder();
	cout << "ÊÇ·ñÊÇºìºÚÊ÷" << t.IsBalance() << endl;
}

int main()
{
	Test2();

	return 0;
}

