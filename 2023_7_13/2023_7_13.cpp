#define _CRT_SECURE_NO_WARNINGS 1
#include "test.h"
#include <ctime>

using namespace std;

/*
C++������ת��
static_cast
const_cast
dynamic_cast
reinterpret_cast
*/

//	1. dynamic_cast
/*
dynamic_castֻ�����ں����麯������
��ת��֮ǰ�������ܷ����ת����������ܾͷ���0

�ܽ᣺����ָ��ָ�������ʱ���޷�ת����ָ�������࣬��Ϊ����ָ���޷���ȷ�������еĳ�Ա
	����ָ��ָ������ʱ������ת����������ָ��

	����ָ������ָ����������Ǹ�����󣬶�����ת��������ָ��


//base* get_ptr()
//{
//	int num = rand() % 3;
//	switch (num)
//	{
//	case 0:
//		return new base(rand() % 100);
//		break;
//	case 1:
//		return new derived1();
//		break;
//	case 2:
//		return new derived2();
//		break;
//	default:
//		return nullptr;
//		break;
//	}
//}
//
//int main()
//{
//	srand(static_cast<unsigned int>(time(nullptr)));
//	base* ptr_base;
//	derived1* ptr_derived1;
//	int i = 0;
//	for (; i < 10; ++i)
//	{
//		ptr_base = get_ptr();
//		ptr_base->get_type();
//		if (ptr_derived1 = dynamic_cast<derived1*>(ptr_base))
//		{
//			//�������ָ���޷�ǿ��ת���������࣬����dynamic_cast����0��û��ִ����������
//			//ptr_derived1->get_val();
//			cout << "convertion successful" << endl;
//		}
//	}
//	return 0;
//}

//int main()
//{
//	base b1;
//	derived1 d1;
//	derived2 d2;
//	base* pb = nullptr;
//	derived1* pd1= nullptr;
//	derived2* pd2= nullptr;
//
//	//����ָ�����ָ�������࣬�ᷢ���ض�
//	pb = &b1;
//	pb = &d1;
//	pb = &d2;
//
//	//������ָ�벻��ָ����
//	//d1 = &b1;
//
//	//pb = &b1;
//	pb = &d1;
//	pb = &d2;
//	//����ָ��ָ����ʱ������ת��������ָ��
//	//����ָ��ָ��������ʱ������ת����������ָ��
//	if (pd1 = dynamic_cast<derived1*>(pb))
//	{
//		cout << "convertion" << endl;
//	}
//	return 0;
//}

class A
{
public:
	virtual void f() 
	{
		cout << "base f()" << endl;
	}

};
class B : public A
{
public:
	void f()
	{
		cout << "derived f()" << endl;
	}
};
void fun(A* pa)
{
	// dynamic_cast���ȼ���Ƿ���ת���ɹ����ܳɹ���ת���������򷵻�
	B* pb1 = static_cast<B*>(pa);
	B* pb2 = dynamic_cast<B*>(pa);
	cout << "pb1:" << pb1 << endl;
	cout << "pb2:" << pb2 << endl;
}
int main()
{
	A a;
	B b;
	fun(&a);
	fun(&b);
	//����ָ�벻��ָ����
	//B* pb = &a;
	//����ָ�����ָ�����࣬�����ض�
	A* pa = &b;
	A* pa2 = &a;
	B* pb = &b;
	//������ָ�����ֱ��ת��Ϊ����ָ�룬ת�ͺ�������������麯�������ɶ�̬
	((A*)pb)->f();
	cout << endl;
	//����ָ��(ָ��������)ת��Ϊ������ָ��, ��Ȼ������������麯��

	((B*)pa)->f();
	((B*)pa2)->f();	//ָ������ָ�룬���ṹ�ɶ�̬

	return 0;
}*/

/*
	2. reinterpret_cast
	�ò�����������ָ��ת��Ϊ���������������ͣ�ת��ʱִ��������ظ���

int main()
{
	int a = 100;
	int* ptr = reinterpret_cast<int*>(a);
	cout << ptr << endl;	//����ָ���ֵ��Ϊa������ֵ
	int b = 200;
	int* ptr2 = &b;
	int c = reinterpret_cast<int>(ptr2);
	//��int�洢ָ���ֵ
	printf("ptr2 = %p\n", ptr2);
	printf("c = %x\n", c);
	return 0;
}*/

/*
	3. const_cast
	����ȥ��const����, const_cast�б�����ָ�롢����

int main()
{
	volatile const int a = 100;		//����volatile�ؼ��֣����߱�����ÿ�ζ�Ҫ���ڴ��ж�ȡ
	int* ptr = const_cast<int*>(&a);
	cout << "a = " << a << endl;
	*ptr = 200;
	cout << "a = " << a << endl;
	cout << "*ptr = " << *ptr << endl;
	//������ӡ��������ͬ��ֵ��ԭ���Ǳ�����ʶ��a��һ��const��������a�ŵ��Ĵ�����
	//��ȡaʱ��ֱ�ӻ�ӼĴ����ж�ȡ
	return 0;

}*/

/*
	4. static_cast
	���ڷǶ�̬���͵�ת��������������������ص�����
*/