#pragma once
#include <iostream>
using namespace std;

class Date
{
	friend ostream& operator<<(ostream& out, const Date& dt);

	friend istream& operator>>(istream& in, Date& dt);

public:
	//构造函数
	Date(int year = 0, int month = 0, int day = 0)
		:_year(1), _month(1), _day(1)
		//每个变量只能在初始化列表初始化一次

	{
		cout << "Date() 构造函数" << this << endl;
		_year = year;
		_month = month;
		_day = day;
	}

	//析构函数
	~Date()
	{
		//cout << "!Date() 析构函数" << this << endl;
	}

	//拷贝构造函数
	Date(const Date& dt)
	{
		cout << "Date(&) 拷贝构造函数" << this << endl;
		_year = dt._year;
		_month = dt._month;
		_day = dt._day;
	}

	Date(Date&& dt)
	{
		cout << "Date(&&) 移动构造函数" << endl;
		swap(dt);
	}

	//赋值重载函数
	Date& operator=(const Date& dt)
	{
		cout << "Date(&) 赋值重载函数" << this << endl;
		//判断左右操作数是否是同一个
		if (this != &dt)
		{
			_year = dt._year;
			_month = dt._month;
			_day = dt._day;
		}

		return *this;
	}

	Date& operator=(Date&& dt)
	{
		cout << "Date(&&) 移动赋值函数" << this << endl;
		//判断左右操作数是否是同一个
		Date tmp(dt);
		swap(tmp);

		return *this;
	}

	//日期+=天数
	Date& operator+=(int day)
	{
		_day += day;
		while (_day > GetMonthDay(_year, _month))
		{
			_day -= GetMonthDay(_year, _month);
			_month++;
			if (_month > 12)
			{
				_year++;
				_month = 1;
			}
		}

		return *this;
	}

	//日期+天数
	Date operator+(int day)//不能传引用返回，因为tmp会销毁
	{
		Date tmp(*this);
		tmp += day;

		return tmp;
	}

	//日期-=天数
	Date& operator-=(int day)
	{
		_day -= day;
		while (_day < 1)
		{
			if (_month > 1)
			{
				_month--;
				_day += GetMonthDay(_year, _month);
			}
			else
			{
				_year--;
				_month = 12;
				_day += GetMonthDay(_year, _month);
			}
		}

		return *this;
	}

	//日期-天数
	Date operator-(int day)
	{
		Date tmp(*this);
		tmp -= day;
		return tmp;
	}

	//前置日期++
	Date& operator++()
	{
		*this += 1;
		return *this;
	}

	//后置日期++
	Date operator++(int)
	{
		Date tmp = *this;
		*this += 1;
		return tmp;
	}

	//大于运算符>
	bool operator>(const Date& dt2)
	{
		if (this->_year > dt2._year)
		{
			return true;
		}
		else if (this->_year == dt2._year && this->_month > dt2._month)
		{
			return true;
		}
		else if (this->_year == dt2._year && this->_month == dt2._month && this->_day > dt2._day)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	//大于等于运算符>=
	bool operator>=(const Date& dt2)
	{
		return *this > dt2 || *this == dt2;
	}

	//小于运算符 <
	bool operator<(const Date& dt2)
	{
		return !(*this >= dt2);
	}

	//小于等于运算符 <=
	bool operator<=(const Date& dt2)
	{
		return *this < dt2 || *this == dt2;
	}

	//等于运算符 ==
	bool operator==(const Date& dt2)
	{
		return this->_year == dt2._year &&
			this->_month == dt2._month &&
			this->_day == dt2._day;
	}

	//不等于运算符 !=
	bool operator!=(const Date& dt2)
	{
		return this->_year != dt2._year ||
			this->_month != dt2._month ||
			this->_day != dt2._day;
	}

	//返回日期-日期
	int operator-(const Date& dt2)
	{
		Date max = *this;
		Date min = dt2;
		int flag = 1;
		if (*this > max)
		{
			max = dt2;
			min = *this;
			flag = -1;
		}
		int count = 0;
		while (min != max)
		{
			++min;
			++count;
		}
		return count * flag;
	}

	int GetMonthDay(int year, int month)
	{
		int Month[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

		if (((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0))) && month == 2)
		{
			return Month[2] + 1;
		}
		return Month[month];
	}

	//void operator<<(ostream& out)//左操作数必须是Date类型
	//{
	//	out << _year << "年" << _month << "月" << _day << "日" << endl;
	//}

	//为了让左操作数为cout，需要在外部重定义

	void swap(Date& dt)
	{
		::swap(dt._day, _day);
		::swap(dt._month, _month);
		::swap(dt._year, _year);
	}

	void Print()
	{
		cout << _year << "/" << _month << "/" << _day << endl;
	}

private:
	int _year;
	int _month;
	int _day;
};

ostream& operator<<(ostream& out, const Date& dt)
{
	out << dt._year << "年" << dt._month << "月" << dt._day << "日" << endl;
	return out;
}

istream& operator>>(istream& in, Date& dt)
{
	in >> dt._year >> dt._month >> dt._day;
	return in;
}