#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include "reference.h"
using namespace std;

// 1.�б��ʼ��
/*
C++98 ����ʹ��{}������ͽṹ��Ԫ�ؽ���ͳһ���б��ʼֵ����
C++11 ����ʹ��{}���Զ������ͺ��������ͽ��г�ʼ��


struct A
{
	A(int a, int b)
		:_a(a), _b(b)
	{}

	int _a;
	int _b;
};

int main()
{
	//C++98
	int arr[] = { 1, 2, 3, 4, 5 };
	int arr2[5] = { 0 };
	A a1 = { 1, 2 };
	A a[3] = { {1, 1}, {2, 2}, {3, 3} };	//ʹ��{}��������г�ʼ��

	//C++11 ����ʹ��{}���Զ������ͺ��������ͽ��г�ʼ��
	int i1 = 10;
	int i2 = { 0 };
	int i3{ 1 };	//���Բ���=��
	int arr3[5]{ 0 };
	int arr4[5]{ 1, 2, 3, 4, 5 };

	A a2{ 1, 2 };
	A a3[3]{ {1, 1}, {2, 2}, {3, 3} };

	int* pa = new int[4]{ 1, 2, 3, 4 };	//Ҳ�������ڶ�new�Ķ�����г�ʼ��

	A a4(1, 2);		//ͨ��Բ���ŵ��ù��캯��
	A a5{ 1, 2 };	//�������б��ʼ��֧�ֵ��ù��캯��

}

*/

// 2.initializer_list

/*
ͨ��{}������initializer_list��������c++11�Ĵ󲿷�����֧������initializer_list���й���
���Կ���ֱ���ô����Ŷ��������г�ʼ��

int main()
{
	auto arr = { 1, 2, 3, 4, 5 };
	cout << typeid(arr).name() << endl;
	//class std::initializer_list<int>

	//initializer_listͨ����Ϊ���캯���Ĳ�����Ҳ����Ϊoperator=�Ĳ���
	//�����Ϳ���ͨ���б��ʼ��{}����������ʼ��
	vector<int> v1 = { 1, 2, 3, 4, 5 };
	list<int> l1 = { 1, 2, 3, 4, 5 };
	map<string, string> m1 = { {"haha", "hehe"}, {"heihei", "hhhhh"} };
	return 0;
}
*/

// 3.decltype
/*
autoҪ�����������г�ʼ����������޷�ʶ�����������
��decltype���Բ��Ա������г�ʼ����ֻ��������


int main()
{
	double a = 2.3;
	int b = 10;
	decltype(a * b) c;
	//decltype���������е������ж�����
	int* pa = &b;
	cout << typeid(c).name() << endl;
	cout << typeid(pa).name() << endl;
	return 0;
}*/

// 4.��ֵ����
/*
��ֵ�����泣�������ʽ�ķ���ֵ����������ֵ(����ֵ���÷���) (����ֻ�����ԣ�����ȡ��ַ)
��ֵ����Ѱַ�ķ�ֻ�����ʽ�����Ը�ֵ������ȡ��ַ

��ֵ���õ�ʹ�ó�����
	1.���������ο��Լ��ٿ���
	2.������ֵҲ�ɼ��ٿ���
��ֵ���õľ����ԣ�
	1.��������Ҫ���صĶ����Ǻ����ľֲ�����ʱ������������Ͳ����ڣ�����޷��������ã���Ҫ���п���


int func(int x, int y)
{
	return x + y;
}

int main()
{
	//��ֵ����
	int a = 10;
	int b = 20;
	int& ra = a;

	//��ֵ����
	int&& rr1 = 10;
	int&& rr2 = a + b;		//���ʽ
	int&& rr3 = func(1, 2);	//��������ֵ

	//const��ֵ�ȿ���������ֵ�� Ҳ��������ֵ
	const int& cr1 = 100;
	const int& cr2 = a + b;
	const int& cr3 = func(1, 2);

	//��ֵ����ֻ��������ֵ�� ����������ֵ
	//������ֵ���ÿ�������move�����ֵ
	int&& rr4 = move(a);
							//a��b����һ��ӵ������ֵ����
	int&& rr5 = move(b);


	rr4 = 100;		//�����õ��޸�Ҳ�ı���a��b����
	rr5 = 200;
	return 0;
}


int main()
{
	Fjl::string str1 = Fjl::to_string(1234567);
	Fjl::string str2 = Fjl::to_string(-1234567);
	//ʹ�ô�ֵ���أ��ᵼ������һ�ο���

	//������ֵ���õ��ƶ�������ڷ�����ֵǰ��������ƶ�����
	//����ֵ����Դֱ����ȡ����֮ǰ��ֵ�������������Լ���������ֵ��this������һ�ο���

	//���ƶ�����Ϳ������춼����ʱ����������ѡ����ƥ��ĵ���
	Fjl::string str3;
	str3 = Fjl::to_string(4173741);
	//to_string����ʱ�ȵ����ƶ����죬���������Ȼ���ڸ�str3��ֵʱ���ֵ����ƶ���ֵ

	return 0;
}*/

//move����
/*
move�������ƶ��κ���Դ��ֻ�ǽ���ֵ����ǿ��ת��Ϊ��ֵ���ã�Ȼ��ʵ���ƶ����壨��
�������Ҳ֧����move�Ĳ���


int main()
{
	list<string> l1;
	string str = "hello world";

	l1.push_back(move(str));
	//��str������ֵ���ã�ֱ�ӽ�����str������

}*/

//����ת��
/*
forward<T>(t) ��������ʱ����ֵ����

����ֵ���ñ����������к�Ϊ���ں�����ʵ���ƶ����壬������������ֵ���õ�����
�����Ҫ�ڸú����м�������������������ֵ���ԣ����޷�ʵ��

����ͨ������ת����ʵ����ֵ���õ����Ա���


void Fun(int& x) { cout << "��ֵ����" << endl; }
void Fun(const int& x) { cout << "const ��ֵ����" << endl; }

//std::forward ����ת���ڴ��εĹ����б�������ԭ����������
void Fun(int&& x) { cout << "��ֵ����" << endl; }
void Fun(const int&& x) { cout << "const ��ֵ����" << endl; }

template<typename T>
void PerfectForward(T&& t)	//�������ã��ȿ��Խ�����ֵ���ã�Ҳ�ɽ�����ֵ����
{
	Fun(forward<T>(t));//ʵ�ִ��κ���ֵ�������Եı���
	//Fun(t);

}

int main()
{
	PerfectForward(10); // ��ֵ
	int a;
	PerfectForward(a); // ��ֵ
	PerfectForward(std::move(a)); // ��ֵ
	const int b = 8;
	PerfectForward(b); // const ��ֵ
	PerfectForward(std::move(b)); // const ��ֵ
	return 0;
}
*/

//����ת����Ӧ�ó������ڶ�㺯���ж���Ҫ������ֵ����

int main()
{
	Fjl::List<string> l1;
	string str;
	l1.PushBack(move(str));
	return 0;
}