#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <functional>
#include <thread>
#include <string>
using namespace std;

/*
包装器/绑定
包装器本质是一个类模板
可以用来包装函数、函数指针、仿函数对象（或任何包含operator()的类的对象）、lambda表达式
可以通过定义好的call signature直接调用被包装的函数
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

//lambda表达式
auto func3 = [](int a, int b) {return a * b; };

//普通函数
int func1(int a, int b)
{
	return a + b;
}

int main()
{
	function<int(int, int)> add = func1;//函数指针
	function<int(int, int)> sub = func2();//函数对象
	function<int(int, int)> mul = func3;//lambda表达式

	return 0;
}*/

/*
bind是一个函数模板，可以将其看成是一个函数通用适配器
接受一个可调用对象，生成一个新的可调用对象来适应原函数的参数列表
bind可以实现交换参数、绑定参数

调用bind的一般形式：auto newCallable = bind(callable,arg_list);

当我们调用newCallable时，会将arg_list传给callable，调用callable
arg_list包含_n这样的名字，这些参数是占位符，表示newCallable的参数
n表示newCallable中的参数在callable中的位置


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
	//先传入可调用函数，再传参数

	//绑定成员函数需要加&，同时在最前加上实例化::被调用函数，第二个参数传函数对象，然后是参数
	func<int> addint;
	auto func1 = bind(&func<int>::operator(), addint, placeholders::_1, placeholders::_2);
	A a1;
	function<void(const char*)> printstr = bind(&A::Afunction, a1, placeholders::_1);

	f1(10, 20);
	f2(10, 20);//交换了两个参数位置

	cout << func1(100, 200) << endl;
	printstr("hfasdfkaslhdfajspdojf");
	return 0;
}*/

/*
捕获异常

func
{
	throw ...抛异常
}

try
{
	//语句
}
catch(exception e1)
{
	//捕获到异常后进行处理
}
catch(exception e2)
{
	//捕获到异常后进行处理
}
catch(exception e3)
{
	//捕获到异常后进行处理
}
catch(...)
{

}

异常会进行类型匹配，如果catch有多个类型，就选择最近的catch进入
抛出异常后，会生成异常对象的拷贝，因为要传入catch，这个拷贝的对象在被catch后会销毁

catch可以捕获各种类型的异常，但要保证能分清异常的错误是什么

catch中可以用异常的基类进行接受，throw派生类的对象，这样可以继承多种不同类型的派生类异常
统一用基类接受

匹配catch的原则：
先检查throw语句是否在try内部或try调用的函数中，如果是内部，再查找对应的catch语句
当前函数栈中没有匹配的catch，就到上层函数栈中继续找
如果到main函数栈中仍然没有匹配的catch，程序直接退出
这个验证调用链查找catch的过程叫栈展开，因此通常在最后加一个catch(...)接受没有匹配到的异常，防止程序直接退出
找到匹配的catch后，会沿着catch后的语句继续执行


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
异常的重新抛出
多层函数栈帧中，可以在catch后重新抛出异常，让更上层的函数重新catch


double division(int a, int b)
{
	if (b == 0)
	{
		throw "除0错误";
	}
	return a / b;
}

void func()
{
	cout << "其他处理函数" << endl;
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
		//catch后，如果涉及资源释放，可以先进行释放，然后再向上层函数栈帧继续throw

		throw;//继续抛出
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
异常安全
最好不要在构造和析构中抛异常，否则会导致初始化不完整或资源泄露

在函数后加 thorw(A), 表示指挥抛出A类型的异常

// 这里表示这个函数只会抛出bad_alloc的异常
void* operator new (std::size_t size) throw (std::bad_alloc);
// 这里表示这个函数不会抛出异常
void* operator delete (std::size_t size, void* ptr) throw()

c++11的noexcept，默认不会抛出异常
*/

/*
异常的优点：
	1. 通过异常对象精准的反应异常的各种信息，甚至包含堆栈调用的信息，更容易定位bug
	2. 可以直接在main中捕获，不会出现错误码层层返回的情况
	3. 第三方库也需要使用异常
	4. 部分函数使用异常更好处理，比如无法通过返回值返会错误码的函数
异常的缺点：
	1. 异常导致执行流乱跳，较为混乱，因此调试困难
	2. 性能开销，但可以忽略不计
	3. C++没有资源回收机制，需要自己对资源进行管理，所以抛异常可能导致资源泄露或者死锁问题
		因此要使用RAII来处理资源回收问题
	4. C++异常体系不好用，需要自己定义异常体系
	5. 异常不规范使用会导致很多错误，因此要进行规范
		a. 抛出的异常要继承一个基类
		b. 函数是否抛异常、抛什么类型的异常，都要做明确的规定
*/

/*
自己设计一个异常体系
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