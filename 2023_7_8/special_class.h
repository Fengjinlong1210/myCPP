#pragma once
#include <iostream>


/*
设计一个类，不能被拷贝

C++98: 将拷贝构造和赋值重载设置为private属性
C++11: 使用 = delete禁止生成


class NoCopy1
{
public:
	NoCopy1(int data)
		:_data(data)
	{}
private:
	NoCopy1(const NoCopy1& obj)
	{}

	NoCopy1& operator=(const NoCopy1& obj)
	{}

private:
	int _data;
};

class NoCopy2
{
public:
	NoCopy2(int data)
		:_data(data)
	{}

	NoCopy2(const NoCopy1& obj) = delete;
	NoCopy2& operator=(const NoCopy1& obj) = delete;
	//禁止生成
private:
	int _data;
};*/

/*
设置一个只能在堆上开辟空间的类
	: 将构造函数设为私有，通过static成员函数在堆上申请空间


class OnlyHeap
{
public:
	static OnlyHeap* create_obj(int data = 0)
	{
		return new OnlyHeap(data);
	}

private:
	OnlyHeap(int data)
		:_data(data)			//默认构造函数
	{}

	OnlyHeap(const OnlyHeap& obj) = delete; //防止外部通过拷贝构造在栈上创建对象
private:
	int _data;
};*/

/*
设计一个只能在栈上创建对象的类


class OnlyStack1
{
	//将构造函数设为私有，禁止生成拷贝构造，用static成员函数创建对象
public:
	static OnlyStack1 create_obj(int data = 0)
	{
		return OnlyStack1(data);
	}
private:
	OnlyStack1(int data)
		:_data(data)
	{}

	OnlyStack1(const OnlyStack1& obj) = delete;
private:
	int _data;
};

class OnlyStack2
{
	//公开构造函数，禁用operator new，就无法创造对象
public:
	OnlyStack2(int data = 0)
		:_data(data)
	{}

	OnlyStack2(const OnlyStack2& obj)
	{
		_data = obj._data;
	}

	void* operator new(size_t size) = delete;

private:
	int _data;
};*/

/*
设计一个不能被继承的类
	C++98: 构造函数私有化，派生类无法调用基类的构造函数
	C++11: final修饰
*/

class NoInherit1
{
public:
	static NoInherit1 create_obj()
	{
		return NoInherit1();
	}
private:
	NoInherit1()	//默认构造
	{}
};

//class child : public NoInherit
//{
//public:
//	child()		基类构造函数不能调用
//	{}
//private:
//};

class NoInherit2 final
{
public:
	NoInherit2()
	{}
};

//class child : public NoInherit2	//语法限制，不能被继承
//{
//
//};