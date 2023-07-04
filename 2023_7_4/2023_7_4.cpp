#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <algorithm>
#include <functional>
#include <string>
#include <Windows.h>
#include <vector>
using namespace std;

/*
lambda表达式
	lambda的父作用域指向表达式所在的{}一直向上查找所包含的作用域
	捕捉列表可以由多个捕捉项构成, 例如[=, &a, &b]引用捕捉a、b，值捕捉其他变量
	捕捉列表不能重复捕捉，例如[=, a] =已经捕捉了所有变量，包含a，会造成编译报错
	
	在作用域以外的lambda表达式的捕捉列表必须为空

	lambda表达式不能相互赋值，因为是不同的类


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
	//lambda表达式

	//对与内置类型的排序可以用algorithm中的sort函数
	int arr[] = { 3,6,8,11,5,7,17,0,67 };
	sort(arr, arr + sizeof(arr) / sizeof(arr[0]));
	sort(arr, arr + sizeof(arr) / sizeof(arr[0]), greater<int>());//传入比较函数

	//对于内置类型需要自己编写比较函数
	//需要编写多个仿函数，命名也较为困难
	vector<fruit> v = { {"苹果", 10}, {"香蕉", 20}, {"西瓜", 15} };
	sort(v.begin(), v.end(), CompareNameLess());
	sort(v.begin(), v.end(), CompareNameGreater());
	sort(v.begin(), v.end(), ComparePriceLess());
	sort(v.begin(), v.end(), ComparePriceGreater());

	//可以通过lambda函数来解决这个问题
	//lambda表达式的语法
	//[]捕捉列表
	//()参数列表， 无参可以省略小括号
	//mutable  lambda表达式默认是const函数，mutable可以取消常性，使用时不能省略函数列表()
	//->return类型，不写会由编译器进行推导
	//{} 函数体，可以使用参数列表的参数，也可使用捕获到的变量

	int a = 10;
	int b = 20;
	int c = 30;
	int d = 40;
	auto ret1 = [=] {return a + b + c + d; };//[=]表示以值传递捕获父作用域中所有的变量
	cout << ret1() << endl; //ret是一个仿函数对象，重载了operator()运算符

	auto ret2 = [&] {return b = a + c; };//[&]以引用方式捕捉父作用域中所有变量
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
	vector<fruit> v = { {"苹果", 10}, {"香蕉", 20}, {"西瓜", 15}, {"芒果", 30} , {"葡萄", 40}};
	//通过lambda表达式实现排序
	auto print = [](fruit& f) {cout << f._name << "价格: " << f._price << endl; };
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
//			//可以捕获上层多个{}中的变量
//			cout << ret() << endl;
//			Sleep(1000);
//		}
//	}
//}

//比较函数对象和lambda表达式
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

	//在反汇编中，函数对象和lambda表达式用相同的语句调用
	return 0;
}*/


/*
C++线程库 thread
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

//命名空间this_thread包含了get_id接口，调用该接口的线程能够给获取自己的线程id

int main()
{
	//lambda表达式
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

	//函数指针做线程函数
	thread t1(thread_func1, 20);
	
	//函数对象做线程函数(仿函数)
	Thread_Func2 thread_func2;
	thread t2(thread_func2, 30);

	//lambda表达式做线程函数
	thread t3(thread_func3, 25);

	t1.join();
	t2.join();
	t3.join();

	return 0;
}