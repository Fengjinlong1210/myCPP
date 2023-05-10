#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

//继承/多继承


/*
多继承：一个类继承了两个及以上个类


class base1
{
public:
	base1()
	{
		cout << "base1()" << endl;
	}

	~base1()
	{
		cout << "~base1()" << endl;
	}
protected:
	int _a;
};

class base2
{
public:
	base2()
	{
		cout << "base2()" << endl;
	}

	~base2()
	{
		cout << "~base2()" << endl;
	}
protected:
	int _b;
};

class derived : public base1, public base2  //同时继承base1和base2
{
public:
	derived()
	{
		cout << "derived()" << endl;
	}

	~derived()
	{
		cout << "~derived()" << endl;
	}
private:
	int _c;
};

int main()
{
	derived d1;
	return 0;
}

*/

/*
菱形继承：一个基类被两个派生类继承，又有一个类同时继承了这两个派生类


class A
{
public:
	A()
	{
		cout << "A()" << endl;
	}
	~A()
	{
		cout << "~A()" << endl;
	}
	int _a;
};

class B : public A
{
public:
	B()
	{
		cout << "B()" << endl;
	}
	~B()
	{
		cout << "~B()" << endl;
	}
	int _b;
};

class C : public A
{
public:
	C()
	{
		cout << "C()" << endl;
	}
	~C()
	{
		cout << "~C()" << endl;
	}
	int _c;
};

class D : public B, public C
{
public:
	D()
	{
		cout << "D()" << endl;
	}
	~D()
	{
		cout << "~D()" << endl;
	}
protected:
	int _D;
};

//菱形继承会出现二义性和数据冗余
//最底层的派生类会继承两次基类中的数据，造成数据冗余，而且不明确到底是哪个父类中的基类

int main()
{
	D d;
	d.B::_a = 100;	//需要通过指明父类才能访问基类中的数据，但是不能解决数据冗余
	d.C::_a = 101;
	d._b = 200;
	d._c = 300;
	return 0;
}*/

/*
菱形虚继承


class A
{
public:
	A()
	{
		cout << "A()" << endl;
	}
	~A()
	{
		cout << "~A()" << endl;
	}
	int _a;
};

class B : virtual public A
{
public:
	B()
	{
		cout << "B()" << endl;
	}
	~B()
	{
		cout << "~B()" << endl;
	}
	int _b;
};

class C : virtual public A
{
public:
	C()
	{
		cout << "C()" << endl;
	}
	~C()
	{
		cout << "~C()" << endl;
	}
	int _c;
};

class D : public B, public C
{
public:
	D()
	{
		cout << "D()" << endl;
	}
	~D()
	{
		cout << "~D()" << endl;
	}
protected:
	int _d;
};

//虚菱形继承在子类中添加了指针，每个指针指向一张表，表中记录着从父类到祖类的偏移量
//这种指针被称为虚基表指针，指向的表称为虚基表

//int main()
//{
//	D d;
//	d.B::_a = 10;
//	d.C::_a = 15;
//	d._b = 12;
//	d._c = 16;
//	return 0;
//}

//继承是一种is-a的关系，每个派生对象都是基对象
//组合是一种has-a的关系，每个b中包含a
*/


/*
多态：不同对象去完成某个行为，不同对象的状态不同
*/

class Person
{
public:
	virtual void BuyTicket()
	{
		cout << "全价" << endl;
	}
};

class Student : public Person
{
public:
	virtual void BuyTicket()
	{
		cout << "半价" << endl;
	}
};

int main()
{
	Person p;
	Student s;
	p.BuyTicket();
	s.BuyTicket();
	return 0;
}