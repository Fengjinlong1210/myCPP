#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <fstream>
#include <sstream>
#include "fstream.h"
using namespace std;

/*
������֧����operator bool���������������ж�
*/

//int main()
//{
//	fstream fs("test.txt", fstream::in | fstream::out | fstream::app);
//	fs << "hahahaha" << endl;
//
//	fs.close();
//	return 0;
//}

//int main()
//{
//	log_data log1{ "192.168.1.1", 8081, { 2023, 7, 14 } };//�б��ʼ��
//	//file_stream fs("test.txt");
//	//fs.text_write(log1);
//	//log_data log2;
//	//fs.text_read(log2);
//	//cout << log2._address << ":" << log2._port << ":" << log2._date << endl;
//	file_stream fs("test.txt");
//	fs.binary_write(log1);
//	log_data log2;
//	fs.binary_read(log2);
//	cout << log2._address << ":" << log2._port << ":" << log2._date << endl;
//	return 0;
//}

//int main()
//{
//	fstream fs("text.txt", fstream::binary | fstream::trunc | fstream::out | fstream::in);
//	//string str("hello world");
//	const char str[] = { "hello world" };
//	fs.write(str, sizeof(str));
//	//fs.flush();
//	fs.close();
//
//	char res[64];
//	fstream rd("text.txt", fstream::binary | fstream::in);
//	rd.read(res, sizeof res);
//	rd.close();
//	cout << res << endl;
//}

/*
stringstream
���ַ��������롢���
����ƴ���ַ���������ֵת�����ַ��������л��ṹ��

int main()
{
	string str;
	stringstream out_ss(str, stringstream::app | stringstream::in | stringstream::out);	//Ĭ�Ϲ���Ͱ����������������ַ�ʽ
	out_ss << 12312490 << "hahdafsd" << endl;//��str�����
	cout << out_ss.str() << endl;

	cout << "--------------------------" << endl;
	out_ss << 1231241 << endl; 
	cout << out_ss.str() << endl;

	string res;
	while(out_ss >> res);	//���������뵽�ַ���
	//cout << res << endl;
	return 0;
}*/

struct data_type
{
	int _val1;
	double _val2;
	string _name;
};

int main()
{
	data_type w = { 1, 3.14, "fengjinlong" };
	stringstream outstrm;
	//�ÿո���Ϊ�ָ�
	outstrm << w._val1 << " " << w._val2 << " " << w._name << endl;

	//��string�洢�����������
	string str = outstrm.str();

	data_type r;
	stringstream instrm(str);	//��str�ж�ȡ����
	instrm >> r._val1 >> r._val2 >> r._name;
	cout << "val1 = " << r._val1 << endl;
	cout << "val2 = " << r._val2 << endl;
	cout << "name = " << r._name << endl;
}