#pragma once
#include <iostream>
using namespace std;

class Date
{
	friend ostream& operator<<(ostream& out, const Date& dt);

	friend istream& operator>>(istream& in, Date& dt);

public:
	//���캯��
	Date(int year = 0, int month = 0, int day = 0)
		:_year(1), _month(1), _day(1)
		//ÿ������ֻ���ڳ�ʼ���б��ʼ��һ��

	{
		cout << "Date() ���캯��" << this << endl;
		_year = year;
		_month = month;
		_day = day;
	}

	//��������
	~Date()
	{
		//cout << "!Date() ��������" << this << endl;
	}

	//�������캯��
	Date(const Date& dt)
	{
		cout << "Date(&) �������캯��" << this << endl;
		_year = dt._year;
		_month = dt._month;
		_day = dt._day;
	}

	Date(Date&& dt)
	{
		cout << "Date(&&) �ƶ����캯��" << endl;
		swap(dt);
	}

	//��ֵ���غ���
	Date& operator=(const Date& dt)
	{
		cout << "Date(&) ��ֵ���غ���" << this << endl;
		//�ж����Ҳ������Ƿ���ͬһ��
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
		cout << "Date(&&) �ƶ���ֵ����" << this << endl;
		//�ж����Ҳ������Ƿ���ͬһ��
		Date tmp(dt);
		swap(tmp);

		return *this;
	}

	//����+=����
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

	//����+����
	Date operator+(int day)//���ܴ����÷��أ���Ϊtmp������
	{
		Date tmp(*this);
		tmp += day;

		return tmp;
	}

	//����-=����
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

	//����-����
	Date operator-(int day)
	{
		Date tmp(*this);
		tmp -= day;
		return tmp;
	}

	//ǰ������++
	Date& operator++()
	{
		*this += 1;
		return *this;
	}

	//��������++
	Date operator++(int)
	{
		Date tmp = *this;
		*this += 1;
		return tmp;
	}

	//���������>
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

	//���ڵ��������>=
	bool operator>=(const Date& dt2)
	{
		return *this > dt2 || *this == dt2;
	}

	//С������� <
	bool operator<(const Date& dt2)
	{
		return !(*this >= dt2);
	}

	//С�ڵ�������� <=
	bool operator<=(const Date& dt2)
	{
		return *this < dt2 || *this == dt2;
	}

	//��������� ==
	bool operator==(const Date& dt2)
	{
		return this->_year == dt2._year &&
			this->_month == dt2._month &&
			this->_day == dt2._day;
	}

	//����������� !=
	bool operator!=(const Date& dt2)
	{
		return this->_year != dt2._year ||
			this->_month != dt2._month ||
			this->_day != dt2._day;
	}

	//��������-����
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

	//void operator<<(ostream& out)//�������������Date����
	//{
	//	out << _year << "��" << _month << "��" << _day << "��" << endl;
	//}

	//Ϊ�����������Ϊcout����Ҫ���ⲿ�ض���

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
	out << dt._year << "��" << dt._month << "��" << dt._day << "��" << endl;
	return out;
}

istream& operator>>(istream& in, Date& dt)
{
	in >> dt._year >> dt._month >> dt._day;
	return in;
}