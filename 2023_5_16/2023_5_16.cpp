#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

/*
虚函数表


class base
{
public:
	virtual void func1()
	{
		cout << "base:func1()" << endl;
	}

	virtual void func2()
	{
		cout << "base:func2()" << endl;
	}

	virtual void func3()
	{
		cout << "base:func3()" << endl;
	}

	int _a;
};

class derive : public base
{
public:
	virtual void func1()
	{
		cout << "derive:func1()" << endl;
	}

	virtual void func2()
	{
		cout << "derive:func2()" << endl;
	}

	virtual void func4()
	{
		cout << "derive:fun4()" << endl;
	}
};

//类中包含一个虚函数表指针，这个指针指向一个虚函数表，虚函数表以nullptr结尾
//要打印虚函数表，需要先获取虚函数指针中的地址，找到虚函数表
//定义一个函数指针，指向虚函数表的开始，当函数指针不为空时，打印虚函数，

typedef void(*VF_PTR)();

void PrintVF(VF_PTR* vp)
{
	printf("VFT:%p\n", vp);
	//打印虚函数表
	for (int i = 0; vp[i] != nullptr; ++i)
	{
		printf("vp[%d]:%p->", i, vp[i]);
		VF_PTR func = vp[i];
		func();
	}
}

int main()
{
	//cout << sizeof(A) << endl;
	//在32位下，sizeof(A)的大小是八个字节
	//因为类中有虚函数，所以类中也有一个虚函数表指针，指向一个虚函数表

	base a;
	derive b;

	//取出对象中前4/8个字节的内容，也就是取出虚函数表的地址
	PrintVF((VF_PTR*)(*((int*)&a)));
	PrintVF((VF_PTR*)(*((int*)&b)));

	//派生类中如果未重写基类的虚函数，则会继承基类的虚函数，不会形成重写/覆盖


	return 0;
}*/

/*
多继承中的虚函数表
*/

class base1
{
public:
	virtual void func1()
	{
		cout << "base1:func1()" << endl;
	}

	virtual void func2()
	{
		cout << "base1:func2()" << endl;
	}

	virtual void func3()
	{
		cout << "base1:func3()" << endl;
	}

	int _a;
};

class base2
{
public:
	virtual void func1()
	{
		cout << "base2:func1()" << endl;
	}

	virtual void func2()
	{
		cout << "base2:func2()" << endl;
	}

	virtual void func3()
	{
		cout << "base2:func3()" << endl;
	}

	int _a;
};

class derive : public base1, public base2
{
public:
	virtual void func1()
	{
		cout << "derive:func1()" << endl;
	}

	virtual void func2()
	{
		cout << "derive:func2()" << endl;
	}

	virtual void func4()
	{
		cout << "derive:fun4()" << endl;
	}
};

typedef void(*VF_PTR)();

void PrintVF(VF_PTR* vp)
{
	printf("VFT:%p\n", vp);
	//打印虚函数表
	for (int i = 0; vp[i] != nullptr; ++i)
	{
		printf("vp[%d]:%p->", i, vp[i]);
		VF_PTR func = vp[i];
		func();
	}
}

int main()
{
	base1 b1;
	base2 b2;
	derive d;
	//取出base1的虚函数表和base2的虚函数表
	PrintVF((VF_PTR*)(*((int*)&d)));
	PrintVF((VF_PTR*)(*(int*)((char*)&d + sizeof(base1))));
	//多继承中，未重写的虚函数放在第一个继承的虚函数表中

	return 0;
}