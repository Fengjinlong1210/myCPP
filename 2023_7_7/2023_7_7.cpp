#define _CRT_SECURE_NO_WARNINGS 1
#include "SmartPtr.h"

using namespace std;

void Test_sp1()
{
	SmartPtr<int> sp1(new int(10));
	SmartPtr<int> sp2(new int(20));

	cout << "sp1 = " << *sp1 << endl;
	cout << "sp2 = " << *sp2 << endl;

	sp1 = sp2;

	cout << "sp1 = " << *sp1 << endl;
	cout << "sp2 = " << *sp2 << endl;
}

auto thread_func = [](SmartPtr<int>& sp, int n, mutex& mtx)
{
	int i = 0;
	for (; i < n; ++i)
	{
		SmartPtr<int> tmp(sp);
		//cout << "count = " << sp.get_count() << endl;
	}
	//cout << "&sp = " << &sp << endl;

};

//auto thread_func = [](SmartPtr<int>& sp, int n)
//{
//	int i = 0;
//	for (; i < n; ++i)
//	{
//		SmartPtr<int> tmp(sp);
//	}
//};

void Test_thread()
{
	int N = 1000;
	mutex mtx;
	SmartPtr<int> sp(new int(100));
	cout << "&sp = " << &sp << endl;
	thread t1(thread_func, ref(sp), N, ref(mtx));
	thread t2(thread_func, ref(sp), N, ref(mtx));
	//thread t1(thread_func, ref(sp), N);
	//thread t2(thread_func, ref(sp), N);

	t1.join();
	t2.join();
	cout << "count : " << sp.get_count() << endl;
	//this_thread::sleep_for(chrono::seconds(100));
}

int main()
{
	Test_thread();
	//证明线程安全问题
	return 0;
}