#define _CRT_SECURE_NO_WARNINGS 1
#include "BinarySearchTree.h"

void Test1()
{
	BSTree<int> t1;
	int arr[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13 };
	for (auto& e : arr)
	{
		t1.InsertR(e);
	}
	t1.InOrder();

	for (auto& e : arr)
	{
		t1.EraseR(e);
		t1.InOrder();
	}

}

int main()
{
	Test1();
	return 0;
}