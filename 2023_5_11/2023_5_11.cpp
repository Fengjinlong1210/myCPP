#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

/*
多态的构成条件：1.被调用的函数必须是虚函数，且派生类要对虚函数进行重写
				虚函数的重写：派生类中有一个与基类完全相同的虚函数（返回值/函数名/参数相同）
			 2.必须由基类的指针或引用调用


class Person
{
public:
	virtual void BuyTicket(int a = 0)
	{
		cout << "全价" << endl;
		cout << "Person " << a << endl;
	}
protected:
};

class Student : public Person
{
public:
	virtual void BuyTicket(int a = 1)  //派生类的虚函数是对基类虚函数的重写，会继承基类函数的接口
									   //只是对函数的实现进行重写
	{
		cout << "半价" << endl;
		cout << "Student " << a << endl;

	}
protected:
};

void func(Person& rp)
{
	rp.BuyTicket();
}

int main()
{
	Person p;
	Student s;

	func(p);
	//子类对象的指针/引用可以赋值给父类对象
	Person* ps = &s;
	Person& rs = s;
	func(rs);
	return 0;
}*/

/*
虚函数重写的例外


//1.协变：派生类重写虚函数时可以返回不同的类型
//基类虚函数返回基类的指针或引用，派生类虚函数返回派生类的指针或引用
//可以返回其他基类和派生类
class A
{
};

class B : public A
{
};

class Person
{
public:
	virtual A* BuyTicket()
	{
		cout << "全价" << endl;
		return new A;
	}
protected:
};

class Student : public Person
{
public:
	virtual B* BuyTicket()
	{
		cout << "半价" << endl;
		return new B;
	}
protected:
};

int main()
{
	return 0;
}*/


//2.析构函数的重写
//基类的析构函数加了virtual关键字，无论派生类是否加virtual都构成重写
/*
class A
{
public:
	//~A()
	virtual ~A()
	{
		cout << "~A()" << endl;
	}
};

class B :public A
{
public:
	~B()
	{
		cout << "~B()" << endl;
	}
};

int main()
{
	//A a;
	//B b;
	//调用顺序为 ：1.析构b的派生部分，2.析构b的基类部分，3，析构a

	//A* pa = new A;
	//B* pb = new B;

	//delete pa;
	//delete pb;
	//这种情况调用也没问题

	A* p = new B;
	delete p;   //通过父类指针指向子类，只会调用父类的析构函数，可能会导致内存泄漏
	//给父类加上virtual后，对父类虚函数构成重写，就会自动调用子类的析构函数

}*/


/*
final关键字：可以让类中的函数不能被重写


class A
{
public:
	virtual void func() final  //该函数不能被子类重写
	{}
};

class B : public A
{

};

class C final //final在类名后面，该类就不能被继承
{
public:
};

int main()
{
	return 0;
}*/

/*
override关键字：检查虚函数有没有构成重写


class A
{
public:
	virtual void func()
	{
		cout << "A" << endl;
	}
};

class B :public A
{
public:
	void func() override  //增加了override
	{
		//如果没有virtual或者参数不同就会报错
		cout << "B" << endl;
	}
};

void call(A* pa)
{
	pa->func();
}

int main()
{
	A* pa = new A;
	B* pb = new B;
	call(pa);
	call(pb);
	return 0;
}*/

/*
抽象类 ： 包含纯虚函数的类称为抽象类，不能被实例化出对象
纯虚函数规定了派生类必须对虚函数进行重写，也体现了对基类接口的继承
*/

class A  //
{
public:
	virtual void func() = 0;  //在虚函数后加上 = 0，使虚函数构成纯虚函数
	
	int _a;
};

class B : public A	//继承了纯虚函数的类只有对虚函数进行重写才能实例化出对象
{
public:
	virtual void func()
	{
		cout << "void func()" << endl;
	}
};

int main()
{
	B b;
	return 0;
}