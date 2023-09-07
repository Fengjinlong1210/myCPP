#define _CRT_SECURE_NO_WARNINGS 1
#include "sort.h"

int main()
{
	vector<int> arr = { 4, 2, 6, 20, 9, 5,10,8, 7, 1, 3, 19, 12, 15,16,13,11,17,18 };

	//Sort::InsertSort(arr);
	//Sort::ShellSort(arr);
	Sort::SelectSort(arr);
	return 0;
}