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
			cout << "string(char* str) -- char* ����" << endl;
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
		// ��������
		string(const string& s)
			:_str(nullptr)
		{
			cout << "string(const string& s) -- �������� ���" << endl;
			string tmp(s._str);//�ô����string����һ����ʱ����, Ȼ�󽻻���ʱ�����thisָ��
			//thisָ���ָ������ʱ����, ԭ����this���ݱ�����
			swap(tmp);

			//������ʱ,tmp��Ϊ��ʱ�����������������
		}
		// ��ֵ����
		string& operator=(const string& s)
		{

			cout << "string& operator=(string s) -- ��ֵ���� ���" << endl;
			string tmp(s);
			swap(tmp);
			return *this;
		}
		// �ƶ�����
		Fjl::string(string&& s)
			:_str(nullptr)
			, _size(0)
			, _capacity(0)
		{
			cout << "string(string&& s) -- �ƶ����� �ƶ�����" << endl;
			swap(s);
		}
		// �ƶ���ֵ
		string& operator=(string&& s)
		{
			cout << "string& operator=(string&& s) -- �ƶ���ֵ �ƶ�����" << endl;
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
		size_t _capacity; // �������������ʶ��\0
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

	//�ſ��������������졢������ֵ�е�����һ��ʱ���������Ͳ�������Ĭ�ϵ��ƶ�����
	//��Ϊ����������Ϊ�����в��漰��Դ���ͷ�

	//Person(Person&& p) = default;
	//��Ĭ�ϳ�Ա��������� = default���ñ�����ǿ�����ɸ����͵�Ĭ�Ϻ���

	~Person()
	{}
private:
	Fjl::string _name;
	int _age;
};
