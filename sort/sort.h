#pragma once
#include <iostream>
#include <climits>
#include <algorithm>
#include <vector>
using namespace std;

class Sort
{
public:
	//ð������ÿ�ΰ�һ�����������ƶ������Ȼ���ƶ��ڶ�������֣��Դ�����
	static void BubbleSort(vector<int>& arr)
	{
		cout << "����ǰ: ";
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
		cout << "�����: ";
		Sort::print(arr);
	}

	//��������: ��1�±꿪ʼ��ÿ�ΰ�Ԫ�ز��뵽ǰ�������������
	static void InsertSort(vector<int>& arr)
	{
		cout << "����ǰ: ";
		Sort::print(arr);
		int n = arr.size();
		for (int i = 0; i < n - 1; ++i)
		{
			//�����ǰҪ�����ֵС���������е�ǰλ�õ�ֵ
			//����Ҫ�ò����ֵ������ǰ�ƶ���ֱ�����뵽���ʵ�λ��
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
			//��ѭ��ʱ��key�ҵ��˶�Ӧ��λ�� key >= arr[j]
			arr[j + 1] = key;
		}

		cout << "�����: ";
		Sort::print(arr);
	}

	static void ShellSort(vector<int>& arr)
	{
		cout << "����ǰ: ";
		Sort::print(arr);
		//ϣ������: �Բ���������Ż���ͨ���������ڲ�������ǰ�ӽ����򣬿����������Ч��
		//ѡ��һ��gap���Լ��gap��Ԫ�ؽ�������Ȼ�󲻶���Сgap���������������
		int n = arr.size();
		int gap = n / 2;
		while (gap > 0)
		{
			//ÿ��forѭ�����ǶԲ�ͬ��gap��������
			// 9 8 7 6 5 4 3 2 1 0
			// ֻ���n - gap�������򣬺���Ļᱻ��������
			for (int i = 0; i < n - gap; ++i)
			{
				//�����ǰҪ�����ֵС���������е�ǰλ�õ�ֵ
				//����Ҫ�ò����ֵ������ǰ�ƶ���ֱ�����뵽���ʵ�λ��
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
				//��ѭ��ʱ��key�ҵ��˶�Ӧ��λ�� key >= arr[j]
				arr[j + gap] = key;
			}
			gap /= 2;

		}

		cout << "�����: ";
		Sort::print(arr);
	}

	//static void SelectSort(vector<int>& arr)
	//{
	//	cout << "����ǰ: ";
	//	Sort::print(arr);

	//	ÿ��ѡ��һ����С��ֵ����������ǰ�ˣ����ѭ��ֱ������ɹ�
	//	����˫��ѡ������ͬʱѡһ����С�ĺ�����
	//	int n = arr.size();
	//	for (int i = 0; i < n - 1; ++i)
	//	{
	//		�ҳ���С��ֵ
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

	//	cout << "�����: ";
	//	Sort::print(arr);
	//}

	static void SelectSort(vector<int>& arr)
	{
		cout << "����ǰ: ";
		Sort::print(arr);

		int n = arr.size();
		int head = 0;
		int tail = n - 1;
		while (head < tail)
		{
			int i = 0;
			int maxIndex = head;	//�±�
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
			//������ֵ�п��ܱ��ƶ�������ǰ�棬��Ҫ����
			if (maxIndex == head)
			{
				maxIndex = minIndex;
			}
			swap(arr[maxIndex], arr[tail]);

			++head;
			--tail;
		}

		cout << "�����: ";
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