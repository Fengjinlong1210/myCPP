#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <list>
#include "test.h"
#include "DateClass.h"
using namespace std;

/*
C++11的类新增了两个默认成员函数，分别是默认移动构造和默认移动赋值
当一个类没有自己实现移动构造时，同时也没有实现析构函数、拷贝构造、拷贝赋值重载，编译器就会自动生成默认移动构造
自动生成的默认构造对与类中的内置类型会进行逐字节拷贝，对于自定义类型会调用这个类型的移动构造
如果这个自定义类型没有实现移动构造，就会调用拷贝构造

默认移动赋值同理/

//放开析构、拷贝构造、拷贝赋值中的任意一个时，编译器就不会生成默认的移动构造
	//因为编译器会认为该类中不涉及资源的释放

	//Person(Person&& p) = default;
	//在默认成员函数后面加 = default会让编译器强制生成该类型的默认函数

	  在默认成员函数后面加 = delete, 会禁止编译器生成默认的成员函数


int main()
{
	Person s1 = "asdfabdfbsd";
	Person s2 = s1;
	Person s3 = std::move(s1);
	Person s4;
	s4 = std::move(s2);
	return 0;
}*/

/*
可变参数模板
*/



//template<class T>
//void showArgs(T val)
//{
//	cout << val << endl;
//	//接收最后一个参数
//}
//
//template<class T, class ...Args>	//在模板参数前加... 说明Args是一个模板参数包
//void showArgs(const T& val, Args... args)
//{
//	cout << val << " ";		//每次取出第一个参数并输出, 然后向下递归
//	showArgs(args...);
//}

/*
。同时还用到了C++11的另外一个特性——初始化列
表，通过初始化列表来初始化一个变长数组, {(printarg(args), 0)...}将会展开成((printarg(arg1),0),
(printarg(arg2),0), (printarg(arg3),0), etc... )，最终会创建一个元素值都为0的数组int arr[sizeof...
(Args)]。由于是逗号表达式，在创建数组的过程中会先执行逗号表达式前面的部分printarg(args)
打印出参数，也就是说在构造int数组的过程中就将参数包展开了，这个数组的目的纯粹是为了在
数组构造的过程展开参数包

template<class T>
void printArg(T val)
{
	cout << val << " ";
}

template<class ...Args>
void showArgs(Args... args)
{
	int arr[] = { (printArg(args), 0)... };
	cout << endl;
}

int main()
{
	showArgs(1, 2, 'a', 3.14, "hello");
	return 0;
}*/

/*
emplace系列插入, 与push_back最大的区别就是可以传入可变参数, 让编译器直接构造
push_back可以传入列表初始化进行构造

int main()
{
	list<Fjl::string> lt;
	
	Fjl::string str1 = "1111111";
	Fjl::string str2("2222222");

	cout << endl;
	cout << endl;
	lt.push_back(str1);
	lt.emplace_back(str1);
	cout << endl;
	lt.push_back(move(str1));	//直接调用移动构造
	lt.emplace_back(move(str2));

	cout << endl;
	lt.push_back("1235");		//push_back先调用构造创建出对象, 然后调用移动构造
	lt.emplace_back("34234");	//emplace直接调用构造函数
	return 0;
}*/



int main()
{
	list<Date> lt;
	Date d1(2023, 7, 1);
	Date d2(2023, 5, 7);

	cout << endl;
	lt.push_back(d1);
	lt.emplace_back(d1);
	cout << endl;
	lt.push_back(move(d1));
	lt.emplace_back(move(d2));
	cout << endl;

	cout << endl;
	lt.push_back({ 2023, 5, 13 }); //右值	//列表初始化会调用类的构造函数
	lt.push_back(Date(2021, 5, 1));//右值	//显示调用构造函数
	cout << endl;
	lt.emplace_back(2013, 7, 1);	//支持参数包, 直接调用构造
	lt.emplace_back(Date(2019, 3, 1));//构造+移动构造
	cout << endl;
	return 0;
}