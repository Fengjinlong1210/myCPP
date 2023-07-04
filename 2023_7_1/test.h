#pragma once
#include <iostream>
#include <cassert>
using namespace std;

namespace Fjl
{
	class string
	{
	public:
		typedef char* iterator;
		iterator begin()
		{
			return _str;
		}
		iterator end()
		{
			return _str + _size;
		}
		string(const char* str = "")
			:_size(strlen(str))
			, _capacity(_size)
		{
			cout << "string(char* str) -- char* 构造" << endl;
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}
		// s1.swap(s2)
		void swap(string& s)
		{
			::swap(_str, s._str);
			::swap(_size, s._size);
			::swap(_capacity, s._capacity);
		}
		// 拷贝构造
		string(const string& s)
			:_str(nullptr)
		{
			cout << "string(const string& s) -- 拷贝构造 深拷贝" << endl;
			string tmp(s._str);//用传入的string创建一个临时对象, 然后交换临时对象和this指针
			//this指针就指向了临时对象, 原本的this内容被析构
			swap(tmp);

			//出函数时,tmp作为临时变量会调用析构函数
		}
		// 赋值重载
		string& operator=(const string& s)
		{

			cout << "string& operator=(string s) -- 赋值重载 深拷贝" << endl;
			string tmp(s);
			swap(tmp);
			return *this;
		}
		// 移动构造
		Fjl::string(string&& s)
			:_str(nullptr)
			, _size(0)
			, _capacity(0)
		{
			cout << "string(string&& s) -- 移动拷贝 移动语义" << endl;
			swap(s);
		}
		// 移动赋值
		string& operator=(string&& s)
		{
			cout << "string& operator=(string&& s) -- 移动赋值 移动语义" << endl;
			swap(s);
			return *this;
		}
		~string()
		{
			delete[] _str;
			_str = nullptr;
		}
		char& operator[](size_t pos)
		{
			assert(pos < _size);
			return _str[pos];
		}
		void reserve(size_t n)
		{
			if (n > _capacity)
			{
				char* tmp = new char[n + 1];
				strcpy(tmp, _str);
				delete[] _str;
				_str = tmp;
				_capacity = n;
			}
		}
		void push_back(char ch)
		{
			if (_size >= _capacity)
			{
				size_t newcapacity = _capacity == 0 ? 4 : _capacity * 2;
				reserve(newcapacity);
			}
			_str[_size] = ch;
			++_size;
			_str[_size] = '\0';
		}
		//string operator+=(char ch)
		string& operator+=(char ch)
		{
			push_back(ch);
			return *this;
		}
		const char* c_str() const
		{
			return _str;
		}
	private:
		char* _str;
		size_t _size;
		size_t _capacity; // 不包含最后做标识的\0
	};
}

class Person
{
public:
	Person(const char* name = "", int age = 0)
		:_name(name)
		, _age(age)
	{}

	Person(const Person& p)
		:_name(p._name)
		, _age(p._age)
	{}

	void swap(Person& p)
	{
		::swap(p._age, _age);
		::swap(p._name, _name);

	}

	Person(Person&& p)
	{
		swap(p);
	}

	Person& operator=(Person&& p)
	{
		swap(p);
		return *this; 
	}

	Person& operator=(const Person& p)
	{
		if (this != &p)
		{
			_name = p._name;
			_age = p._age;
		}
		return *this;
	}

	//放开析构、拷贝构造、拷贝赋值中的任意一个时，编译器就不会生成默认的移动构造
	//因为编译器会认为该类中不涉及资源的释放

	//Person(Person&& p) = default;
	//在默认成员函数后面加 = default会让编译器强制生成该类型的默认函数

	~Person()
	{}
private:
	Fjl::string _name;
	int _age;
};
