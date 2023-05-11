#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

/*
��̬�Ĺ���������1.�����õĺ����������麯������������Ҫ���麯��������д
				�麯������д������������һ���������ȫ��ͬ���麯��������ֵ/������/������ͬ��
			 2.�����ɻ����ָ������õ���


class Person
{
public:
	virtual void BuyTicket(int a = 0)
	{
		cout << "ȫ��" << endl;
		cout << "Person " << a << endl;
	}
protected:
};

class Student : public Person
{
public:
	virtual void BuyTicket(int a = 1)  //��������麯���ǶԻ����麯������д����̳л��ຯ���Ľӿ�
									   //ֻ�ǶԺ�����ʵ�ֽ�����д
	{
		cout << "���" << endl;
		cout << "Student " << a << endl;

	}
protected:
};

void func(Person& rp)
{
	rp.BuyTicket();
}

int main()
{
	Person p;
	Student s;

	func(p);
	//��������ָ��/���ÿ��Ը�ֵ���������
	Person* ps = &s;
	Person& rs = s;
	func(rs);
	return 0;
}*/

/*
�麯����д������


//1.Э�䣺��������д�麯��ʱ���Է��ز�ͬ������
//�����麯�����ػ����ָ������ã��������麯�������������ָ�������
//���Է������������������
class A
{
};

class B : public A
{
};

class Person
{
public:
	virtual A* BuyTicket()
	{
		cout << "ȫ��" << endl;
		return new A;
	}
protected:
};

class Student : public Person
{
public:
	virtual B* BuyTicket()
	{
		cout << "���" << endl;
		return new B;
	}
protected:
};

int main()
{
	return 0;
}*/


//2.������������д
//�����������������virtual�ؼ��֣������������Ƿ��virtual��������д
/*
class A
{
public:
	//~A()
	virtual ~A()
	{
		cout << "~A()" << endl;
	}
};

class B :public A
{
public:
	~B()
	{
		cout << "~B()" << endl;
	}
};

int main()
{
	//A a;
	//B b;
	//����˳��Ϊ ��1.����b���������֣�2.����b�Ļ��ಿ�֣�3������a

	//A* pa = new A;
	//B* pb = new B;

	//delete pa;
	//delete pb;
	//�����������Ҳû����

	A* p = new B;
	delete p;   //ͨ������ָ��ָ�����ֻ࣬����ø�����������������ܻᵼ���ڴ�й©
	//���������virtual�󣬶Ը����麯��������д���ͻ��Զ������������������

}*/


/*
final�ؼ��֣����������еĺ������ܱ���д


class A
{
public:
	virtual void func() final  //�ú������ܱ�������д
	{}
};

class B : public A
{

};

class C final //final���������棬����Ͳ��ܱ��̳�
{
public:
};

int main()
{
	return 0;
}*/

/*
override�ؼ��֣�����麯����û�й�����д


class A
{
public:
	virtual void func()
	{
		cout << "A" << endl;
	}
};

class B :public A
{
public:
	void func() override  //������override
	{
		//���û��virtual���߲�����ͬ�ͻᱨ��
		cout << "B" << endl;
	}
};

void call(A* pa)
{
	pa->func();
}

int main()
{
	A* pa = new A;
	B* pb = new B;
	call(pa);
	call(pb);
	return 0;
}*/

/*
������ �� �������麯�������Ϊ�����࣬���ܱ�ʵ����������
���麯���涨�������������麯��������д��Ҳ�����˶Ի���ӿڵļ̳�
*/

class A  //
{
public:
	virtual void func() = 0;  //���麯������� = 0��ʹ�麯�����ɴ��麯��
	
	int _a;
};

class B : public A	//�̳��˴��麯������ֻ�ж��麯��������д����ʵ����������
{
public:
	virtual void func()
	{
		cout << "void func()" << endl;
	}
};

int main()
{
	B b;
	return 0;
}