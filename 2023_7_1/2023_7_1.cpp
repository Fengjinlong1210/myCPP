#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <list>
#include "test.h"
#include "DateClass.h"
using namespace std;

/*
C++11��������������Ĭ�ϳ�Ա�������ֱ���Ĭ���ƶ������Ĭ���ƶ���ֵ
��һ����û���Լ�ʵ���ƶ�����ʱ��ͬʱҲû��ʵ�������������������졢������ֵ���أ��������ͻ��Զ�����Ĭ���ƶ�����
�Զ����ɵ�Ĭ�Ϲ���������е��������ͻ�������ֽڿ����������Զ������ͻ����������͵��ƶ�����
�������Զ�������û��ʵ���ƶ����죬�ͻ���ÿ�������

Ĭ���ƶ���ֵͬ��/

//�ſ��������������졢������ֵ�е�����һ��ʱ���������Ͳ�������Ĭ�ϵ��ƶ�����
	//��Ϊ����������Ϊ�����в��漰��Դ���ͷ�

	//Person(Person&& p) = default;
	//��Ĭ�ϳ�Ա��������� = default���ñ�����ǿ�����ɸ����͵�Ĭ�Ϻ���

	  ��Ĭ�ϳ�Ա��������� = delete, ���ֹ����������Ĭ�ϵĳ�Ա����


int main()
{
	Person s1 = "asdfabdfbsd";
	Person s2 = s1;
	Person s3 = std::move(s1);
	Person s4;
	s4 = std::move(s2);
	return 0;
}*/

/*
�ɱ����ģ��
*/



//template<class T>
//void showArgs(T val)
//{
//	cout << val << endl;
//	//�������һ������
//}
//
//template<class T, class ...Args>	//��ģ�����ǰ��... ˵��Args��һ��ģ�������
//void showArgs(const T& val, Args... args)
//{
//	cout << val << " ";		//ÿ��ȡ����һ�����������, Ȼ�����µݹ�
//	showArgs(args...);
//}

/*
��ͬʱ���õ���C++11������һ�����ԡ�����ʼ����
��ͨ����ʼ���б�����ʼ��һ���䳤����, {(printarg(args), 0)...}����չ����((printarg(arg1),0),
(printarg(arg2),0), (printarg(arg3),0), etc... )�����ջᴴ��һ��Ԫ��ֵ��Ϊ0������int arr[sizeof...
(Args)]�������Ƕ��ű��ʽ���ڴ�������Ĺ����л���ִ�ж��ű��ʽǰ��Ĳ���printarg(args)
��ӡ��������Ҳ����˵�ڹ���int����Ĺ����оͽ�������չ���ˣ���������Ŀ�Ĵ�����Ϊ����
���鹹��Ĺ���չ��������

template<class T>
void printArg(T val)
{
	cout << val << " ";
}

template<class ...Args>
void showArgs(Args... args)
{
	int arr[] = { (printArg(args), 0)... };
	cout << endl;
}

int main()
{
	showArgs(1, 2, 'a', 3.14, "hello");
	return 0;
}*/

/*
emplaceϵ�в���, ��push_back����������ǿ��Դ���ɱ����, �ñ�����ֱ�ӹ���
push_back���Դ����б��ʼ�����й���

int main()
{
	list<Fjl::string> lt;
	
	Fjl::string str1 = "1111111";
	Fjl::string str2("2222222");

	cout << endl;
	cout << endl;
	lt.push_back(str1);
	lt.emplace_back(str1);
	cout << endl;
	lt.push_back(move(str1));	//ֱ�ӵ����ƶ�����
	lt.emplace_back(move(str2));

	cout << endl;
	lt.push_back("1235");		//push_back�ȵ��ù��촴��������, Ȼ������ƶ�����
	lt.emplace_back("34234");	//emplaceֱ�ӵ��ù��캯��
	return 0;
}*/



int main()
{
	list<Date> lt;
	Date d1(2023, 7, 1);
	Date d2(2023, 5, 7);

	cout << endl;
	lt.push_back(d1);
	lt.emplace_back(d1);
	cout << endl;
	lt.push_back(move(d1));
	lt.emplace_back(move(d2));
	cout << endl;

	cout << endl;
	lt.push_back({ 2023, 5, 13 }); //��ֵ	//�б��ʼ���������Ĺ��캯��
	lt.push_back(Date(2021, 5, 1));//��ֵ	//��ʾ���ù��캯��
	cout << endl;
	lt.emplace_back(2013, 7, 1);	//֧�ֲ�����, ֱ�ӵ��ù���
	lt.emplace_back(Date(2019, 3, 1));//����+�ƶ�����
	cout << endl;
	return 0;
}