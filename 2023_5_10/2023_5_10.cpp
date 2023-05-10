#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

//�̳�/��̳�


/*
��̳У�һ����̳������������ϸ���


class base1
{
public:
	base1()
	{
		cout << "base1()" << endl;
	}

	~base1()
	{
		cout << "~base1()" << endl;
	}
protected:
	int _a;
};

class base2
{
public:
	base2()
	{
		cout << "base2()" << endl;
	}

	~base2()
	{
		cout << "~base2()" << endl;
	}
protected:
	int _b;
};

class derived : public base1, public base2  //ͬʱ�̳�base1��base2
{
public:
	derived()
	{
		cout << "derived()" << endl;
	}

	~derived()
	{
		cout << "~derived()" << endl;
	}
private:
	int _c;
};

int main()
{
	derived d1;
	return 0;
}

*/

/*
���μ̳У�һ�����౻����������̳У�����һ����ͬʱ�̳���������������


class A
{
public:
	A()
	{
		cout << "A()" << endl;
	}
	~A()
	{
		cout << "~A()" << endl;
	}
	int _a;
};

class B : public A
{
public:
	B()
	{
		cout << "B()" << endl;
	}
	~B()
	{
		cout << "~B()" << endl;
	}
	int _b;
};

class C : public A
{
public:
	C()
	{
		cout << "C()" << endl;
	}
	~C()
	{
		cout << "~C()" << endl;
	}
	int _c;
};

class D : public B, public C
{
public:
	D()
	{
		cout << "D()" << endl;
	}
	~D()
	{
		cout << "~D()" << endl;
	}
protected:
	int _D;
};

//���μ̳л���ֶ����Ժ���������
//��ײ���������̳����λ����е����ݣ�����������࣬���Ҳ���ȷ�������ĸ������еĻ���

int main()
{
	D d;
	d.B::_a = 100;	//��Ҫͨ��ָ��������ܷ��ʻ����е����ݣ����ǲ��ܽ����������
	d.C::_a = 101;
	d._b = 200;
	d._c = 300;
	return 0;
}*/

/*
������̳�


class A
{
public:
	A()
	{
		cout << "A()" << endl;
	}
	~A()
	{
		cout << "~A()" << endl;
	}
	int _a;
};

class B : virtual public A
{
public:
	B()
	{
		cout << "B()" << endl;
	}
	~B()
	{
		cout << "~B()" << endl;
	}
	int _b;
};

class C : virtual public A
{
public:
	C()
	{
		cout << "C()" << endl;
	}
	~C()
	{
		cout << "~C()" << endl;
	}
	int _c;
};

class D : public B, public C
{
public:
	D()
	{
		cout << "D()" << endl;
	}
	~D()
	{
		cout << "~D()" << endl;
	}
protected:
	int _d;
};

//�����μ̳��������������ָ�룬ÿ��ָ��ָ��һ�ű����м�¼�ŴӸ��ൽ�����ƫ����
//����ָ�뱻��Ϊ�����ָ�룬ָ��ı��Ϊ�����

//int main()
//{
//	D d;
//	d.B::_a = 10;
//	d.C::_a = 15;
//	d._b = 12;
//	d._c = 16;
//	return 0;
//}

//�̳���һ��is-a�Ĺ�ϵ��ÿ�����������ǻ�����
//�����һ��has-a�Ĺ�ϵ��ÿ��b�а���a
*/


/*
��̬����ͬ����ȥ���ĳ����Ϊ����ͬ�����״̬��ͬ
*/

class Person
{
public:
	virtual void BuyTicket()
	{
		cout << "ȫ��" << endl;
	}
};

class Student : public Person
{
public:
	virtual void BuyTicket()
	{
		cout << "���" << endl;
	}
};

int main()
{
	Person p;
	Student s;
	p.BuyTicket();
	s.BuyTicket();
	return 0;
}