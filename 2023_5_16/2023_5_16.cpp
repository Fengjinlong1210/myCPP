#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

/*
�麯����


class base
{
public:
	virtual void func1()
	{
		cout << "base:func1()" << endl;
	}

	virtual void func2()
	{
		cout << "base:func2()" << endl;
	}

	virtual void func3()
	{
		cout << "base:func3()" << endl;
	}

	int _a;
};

class derive : public base
{
public:
	virtual void func1()
	{
		cout << "derive:func1()" << endl;
	}

	virtual void func2()
	{
		cout << "derive:func2()" << endl;
	}

	virtual void func4()
	{
		cout << "derive:fun4()" << endl;
	}
};

//���а���һ���麯����ָ�룬���ָ��ָ��һ���麯�����麯������nullptr��β
//Ҫ��ӡ�麯������Ҫ�Ȼ�ȡ�麯��ָ���еĵ�ַ���ҵ��麯����
//����һ������ָ�룬ָ���麯����Ŀ�ʼ��������ָ�벻Ϊ��ʱ����ӡ�麯����

typedef void(*VF_PTR)();

void PrintVF(VF_PTR* vp)
{
	printf("VFT:%p\n", vp);
	//��ӡ�麯����
	for (int i = 0; vp[i] != nullptr; ++i)
	{
		printf("vp[%d]:%p->", i, vp[i]);
		VF_PTR func = vp[i];
		func();
	}
}

int main()
{
	//cout << sizeof(A) << endl;
	//��32λ�£�sizeof(A)�Ĵ�С�ǰ˸��ֽ�
	//��Ϊ�������麯������������Ҳ��һ���麯����ָ�룬ָ��һ���麯����

	base a;
	derive b;

	//ȡ��������ǰ4/8���ֽڵ����ݣ�Ҳ����ȡ���麯����ĵ�ַ
	PrintVF((VF_PTR*)(*((int*)&a)));
	PrintVF((VF_PTR*)(*((int*)&b)));

	//�����������δ��д������麯�������̳л�����麯���������γ���д/����


	return 0;
}*/

/*
��̳��е��麯����
*/

class base1
{
public:
	virtual void func1()
	{
		cout << "base1:func1()" << endl;
	}

	virtual void func2()
	{
		cout << "base1:func2()" << endl;
	}

	virtual void func3()
	{
		cout << "base1:func3()" << endl;
	}

	int _a;
};

class base2
{
public:
	virtual void func1()
	{
		cout << "base2:func1()" << endl;
	}

	virtual void func2()
	{
		cout << "base2:func2()" << endl;
	}

	virtual void func3()
	{
		cout << "base2:func3()" << endl;
	}

	int _a;
};

class derive : public base1, public base2
{
public:
	virtual void func1()
	{
		cout << "derive:func1()" << endl;
	}

	virtual void func2()
	{
		cout << "derive:func2()" << endl;
	}

	virtual void func4()
	{
		cout << "derive:fun4()" << endl;
	}
};

typedef void(*VF_PTR)();

void PrintVF(VF_PTR* vp)
{
	printf("VFT:%p\n", vp);
	//��ӡ�麯����
	for (int i = 0; vp[i] != nullptr; ++i)
	{
		printf("vp[%d]:%p->", i, vp[i]);
		VF_PTR func = vp[i];
		func();
	}
}

int main()
{
	base1 b1;
	base2 b2;
	derive d;
	//ȡ��base1���麯�����base2���麯����
	PrintVF((VF_PTR*)(*((int*)&d)));
	PrintVF((VF_PTR*)(*(int*)((char*)&d + sizeof(base1))));
	//��̳��У�δ��д���麯�����ڵ�һ���̳е��麯������

	return 0;
}