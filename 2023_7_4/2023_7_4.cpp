#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <algorithm>
#include <functional>
#include <string>
#include <Windows.h>
#include <vector>
using namespace std;

/*
lambda���ʽ
	lambda�ĸ�������ָ����ʽ���ڵ�{}һֱ���ϲ�����������������
	��׽�б�����ɶ����׽���, ����[=, &a, &b]���ò�׽a��b��ֵ��׽��������
	��׽�б����ظ���׽������[=, a] =�Ѿ���׽�����б���������a������ɱ��뱨��
	
	�������������lambda���ʽ�Ĳ�׽�б����Ϊ��

	lambda���ʽ�����໥��ֵ����Ϊ�ǲ�ͬ����


class fruit
{
public:
	fruit(const char* name, int price)
		:_name(name), _price(price)
	{}

	string _name;
	int _price;
};

struct ComparePriceLess
{
	bool operator()(fruit& f1, fruit& f2)
	{
		return f1._price < f2._price;
	}
};

struct ComparePriceGreater
{
	bool operator()(fruit& f1, fruit& f2)
	{
		return f1._price > f2._price;
	}
};

struct CompareNameLess
{
	bool operator()(fruit& f1, fruit& f2)
	{
		return f1._name < f2._name;
	}
};

struct CompareNameGreater
{
	bool operator()(fruit& f1, fruit& f2)
	{
		return f1._name > f2._name;
	}
};

int main()
{
	//lambda���ʽ

	//�����������͵����������algorithm�е�sort����
	int arr[] = { 3,6,8,11,5,7,17,0,67 };
	sort(arr, arr + sizeof(arr) / sizeof(arr[0]));
	sort(arr, arr + sizeof(arr) / sizeof(arr[0]), greater<int>());//����ȽϺ���

	//��������������Ҫ�Լ���д�ȽϺ���
	//��Ҫ��д����º���������Ҳ��Ϊ����
	vector<fruit> v = { {"ƻ��", 10}, {"�㽶", 20}, {"����", 15} };
	sort(v.begin(), v.end(), CompareNameLess());
	sort(v.begin(), v.end(), CompareNameGreater());
	sort(v.begin(), v.end(), ComparePriceLess());
	sort(v.begin(), v.end(), ComparePriceGreater());

	//����ͨ��lambda����������������
	//lambda���ʽ���﷨
	//[]��׽�б�
	//()�����б� �޲ο���ʡ��С����
	//mutable  lambda���ʽĬ����const������mutable����ȡ�����ԣ�ʹ��ʱ����ʡ�Ժ����б�()
	//->return���ͣ���д���ɱ����������Ƶ�
	//{} �����壬����ʹ�ò����б�Ĳ�����Ҳ��ʹ�ò��񵽵ı���

	int a = 10;
	int b = 20;
	int c = 30;
	int d = 40;
	auto ret1 = [=] {return a + b + c + d; };//[=]��ʾ��ֵ���ݲ��������������еı���
	cout << ret1() << endl; //ret��һ���º�������������operator()�����

	auto ret2 = [&] {return b = a + c; };//[&]�����÷�ʽ��׽�������������б���
	cout << ret2() << endl;

	auto ret3 = [](int a, int b, int c)->int {return a + b + c; };
	cout << ret3(1, 2, 3) << endl;

	auto ret4 = [&a](int x, int y) {return a = x + y * 2; };
	cout << ret4(10, 2) << endl;
	return 0;

}

class fruit
{
public:
	fruit(const char* name, int price)
		:_name(name), _price(price)
	{}

	string _name;
	int _price;
};

int main()
{
	vector<fruit> v = { {"ƻ��", 10}, {"�㽶", 20}, {"����", 15}, {"â��", 30} , {"����", 40}};
	//ͨ��lambda���ʽʵ������
	auto print = [](fruit& f) {cout << f._name << "�۸�: " << f._price << endl; };
	for (auto& e : v)
	{
		print(e);
	}
	cout << endl;

	sort(v.begin(), v.end(), [](fruit& f1, fruit& f2) {return f1._name < f2._name; });
	for (auto& e : v)
	{
		print(e);
	}
	cout << endl;


	sort(v.begin(), v.end(), [](fruit& f1, fruit& f2) {return f1._price< f2._price; });
	for (auto& e : v)
	{
		print(e);
	}
	cout << endl;


	return 0;
}*/

//int main()
//{
//	int a = 10;
//	while (1)
//	{
//		int b = 20;
//		while (1)
//		{
//			auto ret = [=] {return a + b; };
//			//���Բ����ϲ���{}�еı���
//			cout << ret() << endl;
//			Sleep(1000);
//		}
//	}
//}

//�ȽϺ��������lambda���ʽ
/*
struct func
{
	void operator()()
	{
		cout << "func()" << endl;
	}
};

int main()
{
	func f;
	auto lambda = [] {cout << "lambda" << endl; };

	f();
	lambda();

	//�ڷ�����У����������lambda���ʽ����ͬ��������
	return 0;
}*/


/*
C++�߳̿� thread
*/
#include <thread>
#include <chrono>

int thread_func1(int n = 10)
{
	int cnt = 0;
	for (int i = 1; i <= n; ++i)
	{
		cnt += i;
	}
	this_thread::sleep_for(std::chrono::seconds(2));
	cout << "thread_func1_id: " << this_thread::get_id() << "  cnt = " << cnt << endl;
	return cnt;
}

struct Thread_Func2
{
	int operator()(int n = 10)
	{
		int cnt = 0;
		for (int i = 1; i <= n; ++i)
		{
			cnt += i;
		}
		this_thread::sleep_for(std::chrono::seconds(4));

		cout << "thread_func2_id: " << this_thread::get_id()<< "  cnt = " << cnt << endl;
		return cnt;
	}
};

//�����ռ�this_thread������get_id�ӿڣ����øýӿڵ��߳��ܹ�����ȡ�Լ����߳�id

int main()
{
	//lambda���ʽ
	auto thread_func3 = [](int n = 10)
	{
		int cnt = 0;
		for (int i = 1; i <= n; ++i)
		{
			cnt += i;
		}
		this_thread::sleep_for(std::chrono::seconds(6));

		cout << "thread_func3_id: " << this_thread::get_id() << "  cnt = " << cnt << endl;
		return cnt;
	};

	//����ָ�����̺߳���
	thread t1(thread_func1, 20);
	
	//�����������̺߳���(�º���)
	Thread_Func2 thread_func2;
	thread t2(thread_func2, 30);

	//lambda���ʽ���̺߳���
	thread t3(thread_func3, 25);

	t1.join();
	t2.join();
	t3.join();

	return 0;
}