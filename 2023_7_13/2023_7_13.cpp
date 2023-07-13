#define _CRT_SECURE_NO_WARNINGS 1
#include "test.h"
#include <ctime>

using namespace std;

/*
C++的类型转换
static_cast
const_cast
dynamic_cast
reinterpret_cast
*/

//	1. dynamic_cast
/*
dynamic_cast只能用于含有虚函数的类
在转换之前，会检查能否完成转换，如果不能就返回0

总结：父类指针指向父类对象时，无法转换成指向派生类，因为父类指针无法明确派生类中的成员
	父类指针指向子类时，可以转换成派生类指针

	子类指针无论指向子类对象还是父类对象，都可以转换成子类指针


//base* get_ptr()
//{
//	int num = rand() % 3;
//	switch (num)
//	{
//	case 0:
//		return new base(rand() % 100);
//		break;
//	case 1:
//		return new derived1();
//		break;
//	case 2:
//		return new derived2();
//		break;
//	default:
//		return nullptr;
//		break;
//	}
//}
//
//int main()
//{
//	srand(static_cast<unsigned int>(time(nullptr)));
//	base* ptr_base;
//	derived1* ptr_derived1;
//	int i = 0;
//	for (; i < 10; ++i)
//	{
//		ptr_base = get_ptr();
//		ptr_base->get_type();
//		if (ptr_derived1 = dynamic_cast<derived1*>(ptr_base))
//		{
//			//这里基类指针无法强制转换成派生类，所以dynamic_cast返回0，没有执行下面的语句
//			//ptr_derived1->get_val();
//			cout << "convertion successful" << endl;
//		}
//	}
//	return 0;
//}

//int main()
//{
//	base b1;
//	derived1 d1;
//	derived2 d2;
//	base* pb = nullptr;
//	derived1* pd1= nullptr;
//	derived2* pd2= nullptr;
//
//	//父类指针可以指向派生类，会发生截断
//	pb = &b1;
//	pb = &d1;
//	pb = &d2;
//
//	//派生类指针不能指向父类
//	//d1 = &b1;
//
//	//pb = &b1;
//	pb = &d1;
//	pb = &d2;
//	//父类指针指向父类时，不能转换成子类指针
//	//父类指针指向派生类时，可以转换成派生类指针
//	if (pd1 = dynamic_cast<derived1*>(pb))
//	{
//		cout << "convertion" << endl;
//	}
//	return 0;
//}

class A
{
public:
	virtual void f() 
	{
		cout << "base f()" << endl;
	}

};
class B : public A
{
public:
	void f()
	{
		cout << "derived f()" << endl;
	}
};
void fun(A* pa)
{
	// dynamic_cast会先检查是否能转换成功，能成功则转换，不能则返回
	B* pb1 = static_cast<B*>(pa);
	B* pb2 = dynamic_cast<B*>(pa);
	cout << "pb1:" << pb1 << endl;
	cout << "pb2:" << pb2 << endl;
}
int main()
{
	A a;
	B b;
	fun(&a);
	fun(&b);
	//子类指针不能指向父类
	//B* pb = &a;
	//父类指针可以指向子类，发生截断
	A* pa = &b;
	A* pa2 = &a;
	B* pb = &b;
	//派生类指针可以直接转换为基类指针，转型后会调用派生类的虚函数，构成多态
	((A*)pb)->f();
	cout << endl;
	//基类指针(指向基类对象)转换为派生类指针, 仍然会调用派生类虚函数

	((B*)pa)->f();
	((B*)pa2)->f();	//指向基类的指针，不会构成多态

	return 0;
}*/

/*
	2. reinterpret_cast
	该操作允许将任意指针转化为其他任意整数类型，转化时执行逐个比特复制

int main()
{
	int a = 100;
	int* ptr = reinterpret_cast<int*>(a);
	cout << ptr << endl;	//将该指针的值置为a的整数值
	int b = 200;
	int* ptr2 = &b;
	int c = reinterpret_cast<int>(ptr2);
	//用int存储指针的值
	printf("ptr2 = %p\n", ptr2);
	printf("c = %x\n", c);
	return 0;
}*/

/*
	3. const_cast
	用于去除const属性, const_cast中必须是指针、引用

int main()
{
	volatile const int a = 100;		//增加volatile关键字，告诉编译器每次都要从内存中读取
	int* ptr = const_cast<int*>(&a);
	cout << "a = " << a << endl;
	*ptr = 200;
	cout << "a = " << a << endl;
	cout << "*ptr = " << *ptr << endl;
	//这里会打印出两个不同的值，原因是编译器识别到a是一个const常量，将a放到寄存器中
	//读取a时，直接会从寄存器中读取
	return 0;

}*/

/*
	4. static_cast
	用于非多态类型的转换，不能用于两个不相关的类型
*/