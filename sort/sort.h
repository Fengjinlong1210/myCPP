#pragma once
#include <iostream>
#include <climits>
#include <algorithm>
#include <vector>
using namespace std;

class Sort
{
public:
	//冒泡排序：每次把一个最大的数字移动到最后，然后移动第二大的数字，以此类推
	static void BubbleSort(vector<int>& arr)
	{
		cout << "排序前: ";
		Sort::print(arr);
		int n = arr.size();
		for (int i = 0; i < n - 1; ++i)
		{
			for (int j = 0; j < n - i - 1; j++)
			{
				if (arr[j] > arr[j + 1])
				{
					swap(arr[j], arr[j + 1]);
				}
			}
		}
		cout << "排序后: ";
		Sort::print(arr);
	}

	//插入排序: 从1下标开始，每次把元素插入到前面的有序数组中
	static void InsertSort(vector<int>& arr)
	{
		cout << "排序前: ";
		Sort::print(arr);
		int n = arr.size();
		for (int i = 0; i < n - 1; ++i)
		{
			//如果当前要插入的值小于有序序列当前位置的值
			//就让要让插入的值不断向前移动，直到插入到合适的位置
			int key = arr[i + 1];
			int j = i;
			while (j >= 0)
			{
				if (arr[j] > key)
				{
					arr[j + 1] = arr[j];
					--j;
				}
				else
				{
					break;
				}
			}
			//出循环时，key找到了对应的位置 key >= arr[j]
			arr[j + 1] = key;
		}

		cout << "排序后: ";
		Sort::print(arr);
	}

	static void ShellSort(vector<int>& arr)
	{
		cout << "排序前: ";
		Sort::print(arr);
		//希尔排序: 对插入排序的优化，通过让序列在插入排序前接近有序，可以提高排序效率
		//选择一个gap，对间隔gap的元素进行排序，然后不断缩小gap，让数组近似有序
		int n = arr.size();
		int gap = n / 2;
		while (gap > 0)
		{
			//每轮for循环都是对不同的gap进行排序
			// 9 8 7 6 5 4 3 2 1 0
			// 只需对n - gap进行排序，后面的会被分入组内
			for (int i = 0; i < n - gap; ++i)
			{
				//如果当前要插入的值小于有序序列当前位置的值
				//就让要让插入的值不断向前移动，直到插入到合适的位置
				int key = arr[i + gap];
				int j = i;
				while (j >= 0)
				{
					if (arr[j] > key)
					{
						arr[j + gap] = arr[j];
						j -= gap;
					}
					else
					{
						break;
					}
				}
				//出循环时，key找到了对应的位置 key >= arr[j]
				arr[j + gap] = key;
			}
			gap /= 2;

		}

		cout << "排序后: ";
		Sort::print(arr);
	}

	//static void SelectSort(vector<int>& arr)
	//{
	//	cout << "排序前: ";
	//	Sort::print(arr);

	//	每次选择一个最小的值放入数组最前端，如此循环直到排序成功
	//	或是双向选择排序，同时选一个最小的和最大的
	//	int n = arr.size();
	//	for (int i = 0; i < n - 1; ++i)
	//	{
	//		找出最小的值
	//		int minIndex = i;
	//		for (int j = i + 1; j < n; ++j)
	//		{
	//			if (arr[j] < arr[minIndex])
	//			{
	//				minIndex = j;
	//			}
	//		}
	//		int tmp = arr[minIndex];
	//		arr[minIndex] = arr[i];
	//		arr[i] = tmp;
	//	}

	//	cout << "排序后: ";
	//	Sort::print(arr);
	//}

	static void SelectSort(vector<int>& arr)
	{
		cout << "排序前: ";
		Sort::print(arr);

		int n = arr.size();
		int head = 0;
		int tail = n - 1;
		while (head < tail)
		{
			int i = 0;
			int maxIndex = head;	//下标
			int minIndex = head;
			for (i = head + 1; i <= tail; ++i)
			{
				if (arr[i] > arr[maxIndex]) 
				{
					maxIndex = i;
				}
				if (arr[i] < arr[minIndex])
				{
					minIndex = i;
				}
			}

			swap(arr[minIndex], arr[head]);
			//如果最大值有可能被移动到了最前面，需要交换
			if (maxIndex == head)
			{
				maxIndex = minIndex;
			}
			swap(arr[maxIndex], arr[tail]);

			++head;
			--tail;
		}

		cout << "排序后: ";
		Sort::print(arr);
	}

	static void print(const vector<int>& arr)
	{
		for (auto& num : arr)
		{
			cout << num << ", ";
		}
		cout << endl;
	}
};