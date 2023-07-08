#pragma once
#include <iostream>


/*
���һ���࣬���ܱ�����

C++98: ����������͸�ֵ��������Ϊprivate����
C++11: ʹ�� = delete��ֹ����


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
	//��ֹ����
private:
	int _data;
};*/

/*
����һ��ֻ���ڶ��Ͽ��ٿռ����
	: �����캯����Ϊ˽�У�ͨ��static��Ա�����ڶ�������ռ�


class OnlyHeap
{
public:
	static OnlyHeap* create_obj(int data = 0)
	{
		return new OnlyHeap(data);
	}

private:
	OnlyHeap(int data)
		:_data(data)			//Ĭ�Ϲ��캯��
	{}

	OnlyHeap(const OnlyHeap& obj) = delete; //��ֹ�ⲿͨ������������ջ�ϴ�������
private:
	int _data;
};*/

/*
���һ��ֻ����ջ�ϴ����������


class OnlyStack1
{
	//�����캯����Ϊ˽�У���ֹ���ɿ������죬��static��Ա������������
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
	//�������캯��������operator new�����޷��������
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
���һ�����ܱ��̳е���
	C++98: ���캯��˽�л����������޷����û���Ĺ��캯��
	C++11: final����
*/

class NoInherit1
{
public:
	static NoInherit1 create_obj()
	{
		return NoInherit1();
	}
private:
	NoInherit1()	//Ĭ�Ϲ���
	{}
};

//class child : public NoInherit
//{
//public:
//	child()		���๹�캯�����ܵ���
//	{}
//private:
//};

class NoInherit2 final
{
public:
	NoInherit2()
	{}
};

//class child : public NoInherit2	//�﷨���ƣ����ܱ��̳�
//{
//
//};