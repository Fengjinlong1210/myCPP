#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

//析构函数没有参数，不能被重载，但可以声明成虚函数
//析构函数如果不声明成虚函数，用父类的指针指向子类，析构父类指针时不会调用子类的析构函数
//如果步给父类的析构加上virtual，可能会导致内存泄漏
/*
class A
{
public:
	virtual ~A()
	{
		cout << "~A()" << endl;
	}
};

class B : public A
{
public:
	~B()
	{
		cout << "~B()" << endl;
	}

};

int main()
{
	A* pa = new B;
	delete pa;

	//不加virtual时，只会调用父类的析构函数
	//加了virtual，子类的析构函数对父类的析构函数构成重写，会调用子类的析构函数和父类的析构函数
	return 0;
}*/

//把类的析构函数声明成private，可以通过静态成员函数来创造对象
/*
class A
{
	A()
	{
		cout << "A()" << endl;
	}
public:
	static A* get_obj()
	{
		A* pa = new A;
		return pa;
	}
};

int main()
{
	A::get_obj();
}*/

