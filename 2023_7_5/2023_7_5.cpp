#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <thread>
#include <mutex>
#include <ctime>
#include <list>
#include <condition_variable>
#include <atomic>
using namespace std;

/*
创建两个线程，用并行和串行两种方式进行效率比较


int x = 0;
mutex mtx;
list<int> lt;


auto add_func1 = [](int n)
{
	//for (int i = 0; i < n; ++i)
	//{
	//	//并行
	//	mtx.lock();
	//	++x;
	//	lt.push_back(i);
	//	lt.push_back(n);

	//	mtx.unlock();
	//}

	//串行
	mtx.lock();
	for (int i = 0; i < n; ++i)
	{
		++x;
		lt.push_back(i);
		lt.push_back(n);
	}
	mtx.unlock();

	//如果for循环中只有一个++操作，串行的效率要远高于并行
	//因为并行切换进程上下文所消耗的时间占总时间过多

	//如果for循环中的操作增加，两种方式的效率相差不多
	//因为并行切换进程上下文所消耗的时间占总时间少

};


int main()
{
	int N = 1000000;
	clock_t begin = clock();

	thread t1(add_func1, N);
	thread t2(add_func1, N);

	t1.join();
	t2.join();
	clock_t end = clock();

	cout << "x = " << x << endl;
	cout << "time: " << end - begin << endl;

	return 0;
}*/

/*
创建两个线程，交替打印1-100的数字
关键：	
	1. 让打印奇数的线程先跑起来
	2. 不能让一个线程连续执行，要让两个线程交替执行
需要使用环境变量condition_variable
condition_variable::wait 需要一个unique_lock对象lck
	调用该接口的执行流会再次阻塞直到收到notified
	在阻塞这个线程的瞬间，会调用lck.unlock，允许其他线程获取锁
	线程被notified后，线程被解除阻塞同时调用lck.lock，然后使lck处于该接口被调用时的状态，然后返回

	该接口的第二个参数是一个断言条件，需要传入仿函数对象，当条件为false时才会block
	当条件true时才会unblock
	这个参数可以防止虚假的唤醒

	unique_lock需要一个mutex对象
	会在构造时自动lock，析构时自动unlock
	可以自主调用lock或unlock

	这个程序开始运行时，会创建两个线程，先被调度的线程会申请锁
	如果打印奇数的线程申请到了锁，不会受到wait的阻塞，因为满足了奇数这个条件
	所以会直接输出数字1，然后对x进行++，最后通知偶数进程可以解除阻塞，偶数进程在wait中得到锁
	然后偶数进程向后执行，再通知奇数进程执行

	如果打印偶数的线程先申请到了锁，会因为不满足条件而阻塞再wait处，wait会释放这个线程的锁
	偶数线程释放后，奇数线程就可以申请到锁，然后按照上面的逻辑向后执行

	当x已经被输出到100时，接下来轮到奇数线程执行，为了不超过100，要给两个线程设置推出循环的条件




int main()
{
	mutex mtx;
	condition_variable cond;
	int x = 1;
	int n = 100;

	auto thread_func1 = [&, n]()	//lambda表达式捕获所有的引用,n的值，防止n被修改
	{
		//打印奇数
		while (1)
		{
			unique_lock<mutex> lock(mtx);//先申请锁
			if (x >= n)
			{
				break;
			}
			//如果是偶数就阻塞等待
			//wait一个参数的写法
			//if (x % 2 == 0)
			//{
			//	cond.wait(lock);
			//}
			//wait两个参数的写法
			cond.wait(lock, [&x] //这里必须要捕捉x的引用，否则其他线程在更改x时，这个线程中的x保持不变
				{
					cout << "thread1:" << x << endl;
					return x % 2 != 0; 
				});//表达式为假，进行wait
			//cout << "thread1:" << x << endl;

			cout << this_thread::get_id() << ": x = " << x << endl;
			++x;


			cond.notify_one();
		}
	};

	auto thread_func2 = [&, n]()
	{
		//打印偶数
		while (1)
		{
			unique_lock<mutex> lock(mtx);
			if (x > 100)
			{
				break;
			}
			//如果是奇数就阻塞等待
			//if (x % 2 == 1)
			//{
			//	cond.wait(lock);
			//}
			cond.wait(lock, [&x] 
				{
					cout << "thread2:" << x << endl;
					return x % 2 == 0; 
				});
			//cout << "thread2:" << x << endl;

			cout << this_thread::get_id() << ": x = " << x << endl;
			++x;
			cond.notify_one();
		}
	};
	thread t1(thread_func1);
	thread t2(thread_func2);

	t1.join();
	t2.join();
	return 0;
}*/

/*
atomic的使用
原子类只能从模板参数中进行构造，不能使用拷贝构造、赋值、移动构造


int main()
{
	const int N = 10000;
	atomic<int> x;	//声明x是一个int，其操作具有原子性
	auto thread_func1 = [&]()
	{
		int i = 0;
		for (i = 0; i < N; ++i)
		{
			++x;
		}
	};

	auto thread_func2 = [&]()
	{
		int i = 0;
		for (i = 0; i < N; ++i)
		{
			++x;
		}
	};

	thread t1(thread_func1);
	thread t2(thread_func2);

	t1.join();
	t2.join();

	cout << "x = " << x << endl;
	//因为x的操作具有原子性，在++的时候不会因为切换其他线程而导致++失效
	return 0;
}*/

/*
lock_guard和unique_lock,即RAII风格的锁

lock_guard对mutex进行封装，在需要加锁的地方，声明一个lock_guard对象
在调用构造函数时自动上锁，出作用域时调用下析构函数自动解锁

unique_lock包含了lock_guard的功能，同时增加了一些接口
可以主动控制加锁或释放，也支持移动赋值

这两种锁都是以独占所有权的方式管理mutex的上锁和解锁，不支持拷贝
构造时，需要传入一个mutex对象
*/

/*
function包装器：本质是一个类模板
template <class Ret, class... Args> 
class function<Ret(Args...)>;
*/