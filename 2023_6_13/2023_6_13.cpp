#define _CRT_SECURE_NO_WARNINGS 1
#include "AVLTree.h"
#include <ctime>

void TestAVL()
{
	AVLTree<int, int> t;
	srand((unsigned int)time(nullptr));
	const int N = 100000;

	for (int i = 0; i < N; ++i)
	{
		int key = rand();
		t.insert(make_pair(key, key));
	}
	cout << "是否是AVL树：" << t.isBalance() << endl;
}

void TestAVL2()
{

}

int main()
{

	//int arr[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	//for (auto& e : arr)
	//{
	//	if (e == 9)
	//	{
	//		int x;
	//		(void)x;
	//	}
	//	t.insert(make_pair(e, e));
	//	cout << "insert " << e << "成功" << endl;
	//}
	//t.InOrder();

	//cout << "是否是AVL树：" << t.isAVLTree() << endl;
	
	AVLTree<int, int> t;
	
	cout << t.TestIsAVL() << endl;



	return 0;
}