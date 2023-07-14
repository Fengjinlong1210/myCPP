#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Date
{
	friend ostream& operator << (ostream& out, const Date& d);
	friend istream& operator >> (istream& in, Date& d);
public:
	Date(int year = 1, int month = 1, int day = 1)
		:_year(year)
		, _month(month)
		, _day(day)
	{}

	//重载bool，支持判断
	operator bool()
	{
		// 这里是随意写的，假设输入_year为0，则结束
		if (_year == 0)
			return false;
		else
			return true;
	}
private:
	int _year;
	int _month;
	int _day;
};
istream& operator >> (istream& in, Date& d)
{
	in >> d._year >> d._month >> d._day;
	return in;
}
ostream& operator << (ostream& out, const Date& d)
{
	out << d._year << " " << d._month << " " << d._day;
	return out;
}

//log作为每次向文件写入或读取的基本单位
struct log_data
{
	//二进制读写不能使用string,因为string包含指向空间的指针
	//string _address;
	char _address[32];
	size_t _port;
	Date _date;
};

//定义一个文件流对象，该对象可以实现对文件的文本读写和二进制读写
class file_stream
{
public:
	file_stream(string filename)
		:_filename(filename)
	{}

	void text_write(const log_data& data)
	{
		//打开输出流文件
		ofstream ofs(_filename, ofstream::out | ofstream::trunc);
		//
		ofs << data._address << " " << data._port << " " << data._date << endl;
		ofs.close();
	}

	void text_read(log_data& data)
	{
		ifstream ifs(_filename, ifstream::in);
		ifs >> data._address >> data._port >> data._date;
		ifs.close();
	}

	void binary_write(const log_data& data)
	{
		ofstream ofs(_filename, ofstream::out | ofstream::binary);
		ofs.write((char*)&data, sizeof(data));
		ofs.close();
	}

	void binary_read(const log_data& data)
	{
		ifstream ifs(_filename, ifstream::in | ofstream::binary);
		ifs.read((char*)(&data), sizeof(data));
		ifs.close();
	}
private:
	string _filename;
};