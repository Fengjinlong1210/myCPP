#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include "reference.h"
using namespace std;

// 1.列表初始化
/*
C++98 允许使用{}对数组和结构体元素进行统一的列表初始值设置
C++11 可以使用{}对自定义类型和内置类型进行初始化


struct A
{
	A(int a, int b)
		:_a(a), _b(b)
	{}

	int _a;
	int _b;
};

int main()
{
	//C++98
	int arr[] = { 1, 2, 3, 4, 5 };
	int arr2[5] = { 0 };
	A a1 = { 1, 2 };
	A a[3] = { {1, 1}, {2, 2}, {3, 3} };	//使用{}对数组进行初始化

	//C++11 可以使用{}对自定义类型和内置类型进行初始化
	int i1 = 10;
	int i2 = { 0 };
	int i3{ 1 };	//可以不加=号
	int arr3[5]{ 0 };
	int arr4[5]{ 1, 2, 3, 4, 5 };

	A a2{ 1, 2 };
	A a3[3]{ {1, 1}, {2, 2}, {3, 3} };

	int* pa = new int[4]{ 1, 2, 3, 4 };	//也可以用于对new的对象进行初始化

	A a4(1, 2);		//通过圆括号调用构造函数
	A a5{ 1, 2 };	//新增的列表初始化支持调用构造函数

}

*/

// 2.initializer_list

/*
通过{}来创建initializer_list对象，由于c++11的大部分容器支持了用initializer_list进行构造
所以可以直接用大括号对容器进行初始化

int main()
{
	auto arr = { 1, 2, 3, 4, 5 };
	cout << typeid(arr).name() << endl;
	//class std::initializer_list<int>

	//initializer_list通常作为构造函数的参数，也可作为operator=的参数
	//这样就可以通过列表初始化{}来给容器初始化
	vector<int> v1 = { 1, 2, 3, 4, 5 };
	list<int> l1 = { 1, 2, 3, 4, 5 };
	map<string, string> m1 = { {"haha", "hehe"}, {"heihei", "hhhhh"} };
	return 0;
}
*/

// 3.decltype
/*
auto要求变量必须进行初始化，否则就无法识别变量的类型
而decltype可以不对变量进行初始化，只进行声明


int main()
{
	double a = 2.3;
	int b = 10;
	decltype(a * b) c;
	//decltype根据括号中的内容判断类型
	int* pa = &b;
	cout << typeid(c).name() << endl;
	cout << typeid(pa).name() << endl;
	return 0;
}*/

// 4.右值引用
/*
右值：字面常量，表达式的返回值，函数返回值(除左值引用返回) (具有只读属性，不能取地址)
左值：可寻址的非只读表达式，可以赋值，可以取地址

左值引用的使用场景：
	1.做参数传参可以减少拷贝
	2.做返回值也可减少拷贝
左值引用的局限性：
	1.当函数中要返回的对象是函数的局部变量时，出了作用域就不存在，因此无法返回引用，需要进行拷贝


int func(int x, int y)
{
	return x + y;
}

int main()
{
	//左值引用
	int a = 10;
	int b = 20;
	int& ra = a;

	//右值引用
	int&& rr1 = 10;
	int&& rr2 = a + b;		//表达式
	int&& rr3 = func(1, 2);	//函数返回值

	//const左值既可以引用左值， 也可引用右值
	const int& cr1 = 100;
	const int& cr2 = a + b;
	const int& cr3 = func(1, 2);

	//右值引用只能引用右值， 不能引用左值
	//但是右值引用可以引用move后的左值
	int&& rr4 = move(a);
							//a和b在这一刻拥有了右值属性
	int&& rr5 = move(b);


	rr4 = 100;		//对引用的修改也改变了a和b本身
	rr5 = 200;
	return 0;
}


int main()
{
	Fjl::string str1 = Fjl::to_string(1234567);
	Fjl::string str2 = Fjl::to_string(-1234567);
	//使用传值返回，会导致至少一次拷贝

	//加入右值引用的移动构造后，在返回右值前，会调用移动构造
	//把右值的资源直接窃取，用之前右值的内容来构造自己，交换右值和this，不算一次拷贝

	//在移动构造和拷贝构造都存在时，编译器会选择最匹配的调用
	Fjl::string str3;
	str3 = Fjl::to_string(4173741);
	//to_string返回时先调用移动构造，构造出对象，然后在给str3赋值时，又调用移动赋值

	return 0;
}*/

//move函数
/*
move函数不移动任何资源，只是将左值引用强制转化为右值引用，然后实现移动语义（）
许多容器也支持了move的插入


int main()
{
	list<string> l1;
	string str = "hello world";

	l1.push_back(move(str));
	//把str当作右值引用，直接交换掉str的内容

}*/

//完美转发
/*
forward<T>(t) 保留传参时的右值属性

当右值引用被传到函数中后，为了在函数中实现移动语义，会给这个参数左值引用的属性
如果需要在该函数中继续向其他函数传入右值属性，就无法实现

所以通过完美转发来实现右值引用的属性保留


void Fun(int& x) { cout << "左值引用" << endl; }
void Fun(const int& x) { cout << "const 左值引用" << endl; }

//std::forward 完美转发在传参的过程中保留对象原生类型属性
void Fun(int&& x) { cout << "右值引用" << endl; }
void Fun(const int&& x) { cout << "const 右值引用" << endl; }

template<typename T>
void PerfectForward(T&& t)	//万能引用，既可以接受左值引用，也可接受右值引用
{
	Fun(forward<T>(t));//实现传参后右值引用属性的保留
	//Fun(t);

}

int main()
{
	PerfectForward(10); // 右值
	int a;
	PerfectForward(a); // 左值
	PerfectForward(std::move(a)); // 右值
	const int b = 8;
	PerfectForward(b); // const 左值
	PerfectForward(std::move(b)); // const 右值
	return 0;
}
*/

//完美转发的应用场景：在多层函数中都需要传递右值引用

int main()
{
	Fjl::List<string> l1;
	string str;
	l1.PushBack(move(str));
	return 0;
}