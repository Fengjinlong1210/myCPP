#pragma once
#include <iostream>
#include <vector>
#include <thread>
#include <string>
using namespace std;
//C++11֧�ֵĳ�ʼ����̬��Ա���̰߳�ȫ����
class Singleton
{
public:
	static Singleton* get_instance()
	{
		//�ٶԾ�̬��Ա��ʼ��ʱ�����̰߳�ȫ��
		static Singleton _instance;
		return &_instance;
	}

	void push(int data)
	{
		_data.push_back(data);
	}

	void print()
	{
		for (auto& e : _data)
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;
	}
private:
	Singleton()
	{}

	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
private:
	std::vector<int> _data;
};


class base
{
public:
	base(int val = 0)
		:_val(val)
	{}

	virtual void get_type()
	{
		cout << "I am base class" << endl;
	}
private:
	int _val;
};

class derived1 : public base
{
public:
	derived1(string str = "default")
		:_str(str)
	{}

	void get_type()
	{
		cout << "I am first -- derived" << endl;
	}

	virtual void get_val()
	{
		cout << "my value string = " << _str << endl;
	}
private:
	string _str;
};

class derived2 : public derived1
{
public:
	derived2(double val = 0)
		:_val(val)
	{}

	void get_type()
	{
		cout << "I am second -- derived" << endl;
	} 

	void get_value()
	{
		cout << "my value double = " << _val << endl;
	}
private:
	double _val;
};