#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <functional>
#include <thread>
#include <string>
using namespace std;

/*
��װ��/��
��װ��������һ����ģ��
����������װ����������ָ�롢�º������󣨻��κΰ���operator()����Ķ��󣩡�lambda���ʽ
����ͨ������õ�call signatureֱ�ӵ��ñ���װ�ĺ���
template <class T>  function;     // undefinedtemplate

template<class Ret, class... Args>
class function<Ret(Args...)>;



template<class T>
struct func4
{
	T opreator(T a, T b)
	{
		return a - b;
	}
};

struct func2
{
	int operator()(int a, int b)
	{
		return a - b;
	}
};

//lambda���ʽ
auto func3 = [](int a, int b) {return a * b; };

//��ͨ����
int func1(int a, int b)
{
	return a + b;
}

int main()
{
	function<int(int, int)> add = func1;//����ָ��
	function<int(int, int)> sub = func2();//��������
	function<int(int, int)> mul = func3;//lambda���ʽ

	return 0;
}*/

/*
bind��һ������ģ�壬���Խ��俴����һ������ͨ��������
����һ���ɵ��ö�������һ���µĿɵ��ö�������Ӧԭ�����Ĳ����б�
bind����ʵ�ֽ����������󶨲���

����bind��һ����ʽ��auto newCallable = bind(callable,arg_list);

�����ǵ���newCallableʱ���Ὣarg_list����callable������callable
arg_list����_n���������֣���Щ������ռλ������ʾnewCallable�Ĳ���
n��ʾnewCallable�еĲ�����callable�е�λ��


template<class T>
struct func
{
	T operator()(T a, T b)
	{
		return a + b;
	}
};

class A
{
public:
	void Afunction(const char* str)
	{
		cout << "Afunction:: " << str << endl;
	}
};

void print(int a, int b)
{
	cout << "print(int a, int b) " << endl;
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
}

int main()
{
	function<void(int, int)> f1 = bind(print, placeholders::_1, placeholders::_2);
	function<void(int, int)> f2 = bind(print, placeholders::_2, placeholders::_1);
	//�ȴ���ɵ��ú������ٴ�����

	//�󶨳�Ա������Ҫ��&��ͬʱ����ǰ����ʵ����::�����ú������ڶ�����������������Ȼ���ǲ���
	func<int> addint;
	auto func1 = bind(&func<int>::operator(), addint, placeholders::_1, placeholders::_2);
	A a1;
	function<void(const char*)> printstr = bind(&A::Afunction, a1, placeholders::_1);

	f1(10, 20);
	f2(10, 20);//��������������λ��

	cout << func1(100, 200) << endl;
	printstr("hfasdfkaslhdfajspdojf");
	return 0;
}*/

/*
�����쳣

func
{
	throw ...���쳣
}

try
{
	//���
}
catch(exception e1)
{
	//�����쳣����д���
}
catch(exception e2)
{
	//�����쳣����д���
}
catch(exception e3)
{
	//�����쳣����д���
}
catch(...)
{

}

�쳣���������ƥ�䣬���catch�ж�����ͣ���ѡ�������catch����
�׳��쳣�󣬻������쳣����Ŀ�������ΪҪ����catch����������Ķ����ڱ�catch�������

catch���Բ���������͵��쳣����Ҫ��֤�ܷ����쳣�Ĵ�����ʲô

catch�п������쳣�Ļ�����н��ܣ�throw������Ķ����������Լ̳ж��ֲ�ͬ���͵��������쳣
ͳһ�û������

ƥ��catch��ԭ��
�ȼ��throw����Ƿ���try�ڲ���try���õĺ����У�������ڲ����ٲ��Ҷ�Ӧ��catch���
��ǰ����ջ��û��ƥ���catch���͵��ϲ㺯��ջ�м�����
�����main����ջ����Ȼû��ƥ���catch������ֱ���˳�
�����֤����������catch�Ĺ��̽�ջչ�������ͨ��������һ��catch(...)����û��ƥ�䵽���쳣����ֹ����ֱ���˳�
�ҵ�ƥ���catch�󣬻�����catch���������ִ��


void func()
{
	cout << "test try catch" << endl;
	throw "error 1";
}

int main()
{
	try
	{
		func();
	}
	catch(const char* errStr)
	{
		cout << errStr << endl;
	}

	return 0;
}*/

/*
�쳣�������׳�
��㺯��ջ֡�У�������catch�������׳��쳣���ø��ϲ�ĺ�������catch


double division(int a, int b)
{
	if (b == 0)
	{
		throw "��0����";
	}
	return a / b;
}

void func()
{
	cout << "����������" << endl;
	int* arr = new int[10];
	int a = 100;
	int b = 0;
	try
	{
		division(a, b);
	}
	catch(...)
	{
		delete[] arr;
		cout << "delete[]" << endl;
		//catch������漰��Դ�ͷţ������Ƚ����ͷţ�Ȼ�������ϲ㺯��ջ֡����throw

		throw;//�����׳�
	}
}

int main()
{
	try
	{
		func();
	}
	catch(const char* str)
	{
		cout << str << endl;
	}
	return 0;
}*/

/*
�쳣��ȫ
��ò�Ҫ�ڹ�������������쳣������ᵼ�³�ʼ������������Դй¶

�ں������ thorw(A), ��ʾָ���׳�A���͵��쳣

// �����ʾ�������ֻ���׳�bad_alloc���쳣
void* operator new (std::size_t size) throw (std::bad_alloc);
// �����ʾ������������׳��쳣
void* operator delete (std::size_t size, void* ptr) throw()

c++11��noexcept��Ĭ�ϲ����׳��쳣
*/

/*
�쳣���ŵ㣺
	1. ͨ���쳣����׼�ķ�Ӧ�쳣�ĸ�����Ϣ������������ջ���õ���Ϣ�������׶�λbug
	2. ����ֱ����main�в��񣬲�����ִ������㷵�ص����
	3. ��������Ҳ��Ҫʹ���쳣
	4. ���ֺ���ʹ���쳣���ô��������޷�ͨ������ֵ���������ĺ���
�쳣��ȱ�㣺
	1. �쳣����ִ������������Ϊ���ң���˵�������
	2. ���ܿ����������Ժ��Բ���
	3. C++û����Դ���ջ��ƣ���Ҫ�Լ�����Դ���й����������쳣���ܵ�����Դй¶������������
		���Ҫʹ��RAII��������Դ��������
	4. C++�쳣��ϵ�����ã���Ҫ�Լ������쳣��ϵ
	5. �쳣���淶ʹ�ûᵼ�ºܶ�������Ҫ���й淶
		a. �׳����쳣Ҫ�̳�һ������
		b. �����Ƿ����쳣����ʲô���͵��쳣����Ҫ����ȷ�Ĺ涨
*/

/*
�Լ����һ���쳣��ϵ
*/
#include <ctime>
class base_exception
{
public:
	base_exception(int errnum, string des)
		:_errno(errnum), _err_description(des)
	{}

	virtual string what() const
	{
		return _err_description;
	}
protected:
	int _errno;
	string _err_description;
};

class network_exception :public base_exception
{
public:
	network_exception(int errnum, string des, string neterr)
		:base_exception(errnum, des), _net_err(neterr)
	{}

	virtual string what() const
	{
		string str;
		str += "errno : ";
		str += to_string(_errno);
		str += ",";
		str += _err_description;
		str += ":";
		str += _net_err;

		return str;
	}
protected:
	string _net_err;
};

class thread_exception :public base_exception
{
public:
	thread_exception(int errnum, string des, string therr)
		:base_exception(errnum, des), _th_err(therr)
	{}

	virtual string what() const
	{
		string str;
		str += "errno : ";
		str += to_string(_errno);
		str += ",";
		str += _err_description;
		str += ":";
		str += _th_err;
		return str;
	}
private:
	string _th_err;
};

void netFunc()
{
	while (1)
	{
		int num = rand() % 10 + 1;
		if (num == 1)
		{
			throw thread_exception(1, "network_error", "Network Interrupt");

		}
		else if (num == 2)
		{
			throw thread_exception(2, "network_error", "Network Not Nonnected");
		}

	}
}

void threadFunc()
{
	while (1)
	{
		int num = rand() % 10 + 1;
		if (num == 3)
		{
			throw thread_exception(3, "thread_error", "Deadlock");
		}
		else if (num == 4)
		{
			throw thread_exception(4, "thread_error", "Execute Interrupt");
		}
	}
}

int main()
{
	srand((unsigned int)time(nullptr));
	while (1)
	{
		try
		{
			threadFunc();
			netFunc();
			this_thread::sleep_for(chrono::seconds(1));
		}
		catch (base_exception& e)
		{
			cout << e.what() << endl;
		}
		catch (...)
		{
			cout << "unknow error!" << endl;
		}
	}
	return 0;
}