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
			//cout << "string(char* str)" << endl;
			_str = new char[_capacity + 1];
			strcpy(_str, str);
			//构造
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
			cout << "string(const string& s) -- 深拷贝" << endl;
			string tmp(s._str);
			swap(tmp);

		}

		// 赋值重载
		string& operator=(const string& s)
		{
			cout << "string& operator=(string s) -- 深拷贝" << endl;
			string tmp(s);
			swap(tmp);
			return *this;
		}

		// 移动构造
		string(string&& s)
			:_str(nullptr)
			, _size(0)
			, _capacity(0)
		{
			cout << "string(string&& s) -- 移动语义" << endl;
			swap(s);
		}

		// 移动赋值
		string& operator=(string&& s)
		{
			cout << "string& operator=(string&& s) -- 移动语义" << endl;
			swap(s);
			return *this;
		}

		~string()
		{
			cout << "析构" << endl;
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

	string to_string(int value)
	{
		bool flag = true;
		if (value < 0)
		{
			flag = false;
			value = 0 - value;
		}
		Fjl::string str;
		while (value > 0)
		{
			int x = value % 10;
			value /= 10;
			str += ('0' + x);
		}
		if (flag == false)
		{
			str += '-';
		}

		std::reverse(str.begin(), str.end());
		return str;
		//返回的是右值
		//这里不能返回引用，如果没有移动构造，需要对str进行拷贝
		//如果string很长，深拷贝的消耗就很大
	}
	template<class T>
	struct ListNode
	{
		ListNode* _next = nullptr;
		ListNode* _prev = nullptr;
		T _data;
	};
	template<class T>
	class List
	{
		typedef ListNode<T> Node;
	public:
		List()
		{
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;
		}
		void PushBack(T&& x)
		{
			//进入函数后，x就失去了右值引用属性，为了在下一层函数中保持该属性
			//要使用forward继续向下传递

			//Insert(_head, x);
			Insert(_head, std::forward<T>(x));
			//调用insert时，保持右值属性
		}
		void PushFront(T&& x)
		{
			//Insert(_head->_next, x);
			Insert(_head->_next, std::forward<T>(x));
		}
		void Insert(Node* pos, T&& x)
		{
			Node* prev = pos->_prev;
			Node* newnode = new Node;
			newnode->_data = std::forward<T>(x); // 关键位置
			//保持右值属性
			// prev newnode pos
			prev->_next = newnode;
			newnode->_prev = prev;
			newnode->_next = pos;
			pos->_prev = newnode;
		}
		void Insert(Node* pos, const T& x)
		{
			Node* prev = pos->_prev;
			Node* newnode = new Node;
			newnode->_data = x; // 关键位置
			// prev newnode pos
			prev->_next = newnode;

			newnode->_prev = prev;
			newnode->_next = pos;
			pos->_prev = newnode;
		}
	private:
		Node* _head;
	};
}

