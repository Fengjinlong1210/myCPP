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

	//����bool��֧���ж�
	operator bool()
	{
		// ����������д�ģ���������_yearΪ0�������
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

//log��Ϊÿ�����ļ�д����ȡ�Ļ�����λ
struct log_data
{
	//�����ƶ�д����ʹ��string,��Ϊstring����ָ��ռ��ָ��
	//string _address;
	char _address[32];
	size_t _port;
	Date _date;
};

//����һ���ļ������󣬸ö������ʵ�ֶ��ļ����ı���д�Ͷ����ƶ�д
class file_stream
{
public:
	file_stream(string filename)
		:_filename(filename)
	{}

	void text_write(const log_data& data)
	{
		//��������ļ�
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