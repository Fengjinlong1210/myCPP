#pragma once
#include <iostream>
#include <algorithm>
#include <climits>
#include <cassert>
#include <cstring>
using namespace std;

namespace Fjl
{
	class String
	{
	public:
		String(const String& str)
		{
			if (str._str == nullptr)
			{
				assert(false);
			}
			_str = new char[str._capacity];
			memcpy(_str, str._str, sizeof(char) * (str._size + 1));
			_capacity = str._capacity;
			_size = str._size;
		}

		String(const char* str = "")
		{
			size_t n = strlen(str);
			_capacity = (n + 1 > _capacity) ? n + 1 : _capacity;
			_str = new char[_capacity];
			memset(_str, 0, _capacity);
			_size = n;
			memcpy(_str, str, sizeof(char) * (n + 1));
		}

		String(const String& str, size_t pos, size_t n = String::npos)
		{
			assert(pos < str.size());
			String ret;
			if (str._size - pos > n)
			{
				memcpy((void*)ret.c_str(), str.c_str() + pos, sizeof(char) * n);
				ret._size = n;
			}
			else
			{
				//n超过了有效长度，全部返回
				memcpy((void*)ret.c_str(), str.c_str() + pos, sizeof(char) * (str.size() - pos));
				ret._size = str.size() - pos;
			}
			swap(ret);
		}

		String& operator=(const String& str)
		{
			String tmp(str);
			swap(tmp);
			return *this;
		}

		String& operator=(const char* str)
		{
			String tmp(str);
			swap(tmp);
			return *this;
		}

		String substr(size_t pos = 0, size_t n = String::npos) const
		{
			assert(pos < _size);
			if (pos == _size)
			{
				return String("");
			}
			String ret(*this, pos, n);
			return ret;
		}

		void resize(size_t n, char ch = '\0')
		{
			if (n > _size)
			{
				if (n > _capacity)
				{
					reserve(n);
				}
				memset(_str + _size, ch, n - _size);
			}
			_size = n;
			_str[n] = '\0';
		}

		void reserve(size_t n = 0)
		{
			if (n <= _capacity)
			{
				return;
			}
			auto newstr = new char[n];
			memset(newstr, 0, n);
			if (_str)
			{
				memcpy(newstr, _str, _size + 1);
				delete[] _str;
			}
			_str = newstr;
			_capacity = n;
		}

		void push_back(char ch)
		{
			expand(1);
			_str[_size] = ch;
			_size++;
		}

		void pop_back()
		{
			assert(_size > 0);
			_str[_size - 1] = '\0';
			_size--;
		}

		String& operator+=(const String& str)
		{
			operator+=(str._str);
			return *this;
		}

		String& operator+=(const char* s)
		{
			size_t length = strlen(s);
			expand(length);
			//_size后面的内容均是可用的
			memcpy(_str + _size, s, length);
			_size += length;
			return *this;
		}

		String& operator+=(const char ch)
		{
			push_back(ch);
			return *this;
		}

		~String()
		{
			if (_str)
			{
				delete[] _str;
			}
		}

		size_t size() const
		{
			return _size;
		}

		size_t capacity() const
		{
			return _capacity;
		}

		void clear()
		{
			memset(_str, 0, _capacity);
		}

		bool empty() const
		{
			return _size == 0;
		}

		char& operator[](size_t pos)
		{
			assert(pos < _size);
			return _str[pos];
		}

		char& front()
		{
			if (_size == 0)
			{
				assert(false);
			}
			return _str[0];
		}

		char& back()
		{
			if (_size == 0)
			{
				assert(false);
			}
			return _str[_size - 1];
		}

		const char* c_str() const
		{
			return _str;
		}

		String& insert(size_t pos, const String& s)
		{
			assert(pos >= 0 && pos < _size);

		}

		String& insert(size_t pos, const char* s)
		{

		}

		String& insert(size_t pos, const char ch)
		{

		}

		void print()
		{
			for (size_t i = 0; i < _size; ++i)
			{
				cout << _str[i];
			}
			cout << endl;
		}
	public:
		static const size_t npos = INT_MAX;
	private:
		void expand(size_t length)
		{
			if (length + _size + 1 > _capacity)
			{
				//需要扩容
				size_t newsize = length > _capacity ? length + _capacity : _capacity * 2;
				auto newstr = new char[newsize];
				memset(newstr, 0, newsize);
				memcpy(newstr, _str, _capacity);
				delete[] _str;
				_str = newstr;
				_capacity = newsize;
			}
		}

		void swap(String& str)
		{
			std::swap(str._str, _str);
			std::swap(str._size, _size);
			std::swap(str._capacity, _capacity);
		}

	private:
		char* _str = nullptr;
		size_t _size = 0;
		size_t _capacity = 16;
	};
	const size_t String::npos;
}