#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

//��������û�в��������ܱ����أ��������������麯��
//��������������������麯�����ø����ָ��ָ�����࣬��������ָ��ʱ��������������������
//��������������������virtual�����ܻᵼ���ڴ�й©
/*
class A
{
public:
	virtual ~A()
	{
		cout << "~A()" << endl;
	}
};

class B : public A
{
public:
	~B()
	{
		cout << "~B()" << endl;
	}

};

int main()
{
	A* pa = new B;
	delete pa;

	//����virtualʱ��ֻ����ø������������
	//����virtual����������������Ը������������������д���������������������͸������������
	return 0;
}*/

//�������������������private������ͨ����̬��Ա�������������
/*
class A
{
	A()
	{
		cout << "A()" << endl;
	}
public:
	static A* get_obj()
	{
		A* pa = new A;
		return pa;
	}
};

int main()
{
	A::get_obj();
}*/

