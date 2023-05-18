#define _CRT_SECURE_NO_WARNINGS 1
#include "BinarySearchTree.h"

int main()
{
	int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13 };
	BSTree<int> t1;

	for (auto e : a)
	{
		t1.Insert(e);
	}
	t1.InOrder();
	for (auto& e : a)
	{
		t1.Erase(e);
		t1.InOrder();
	}

	return 0;
}