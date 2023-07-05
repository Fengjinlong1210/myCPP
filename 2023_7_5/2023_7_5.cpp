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
���������̣߳��ò��кʹ������ַ�ʽ����Ч�ʱȽ�


int x = 0;
mutex mtx;
list<int> lt;


auto add_func1 = [](int n)
{
	//for (int i = 0; i < n; ++i)
	//{
	//	//����
	//	mtx.lock();
	//	++x;
	//	lt.push_back(i);
	//	lt.push_back(n);

	//	mtx.unlock();
	//}

	//����
	mtx.lock();
	for (int i = 0; i < n; ++i)
	{
		++x;
		lt.push_back(i);
		lt.push_back(n);
	}
	mtx.unlock();

	//���forѭ����ֻ��һ��++���������е�Ч��ҪԶ���ڲ���
	//��Ϊ�����л����������������ĵ�ʱ��ռ��ʱ�����

	//���forѭ���еĲ������ӣ����ַ�ʽ��Ч������
	//��Ϊ�����л����������������ĵ�ʱ��ռ��ʱ����

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
���������̣߳������ӡ1-100������
�ؼ���	
	1. �ô�ӡ�������߳���������
	2. ������һ���߳�����ִ�У�Ҫ�������߳̽���ִ��
��Ҫʹ�û�������condition_variable
condition_variable::wait ��Ҫһ��unique_lock����lck
	���øýӿڵ�ִ�������ٴ�����ֱ���յ�notified
	����������̵߳�˲�䣬�����lck.unlock�����������̻߳�ȡ��
	�̱߳�notified���̱߳��������ͬʱ����lck.lock��Ȼ��ʹlck���ڸýӿڱ�����ʱ��״̬��Ȼ�󷵻�

	�ýӿڵĵڶ���������һ��������������Ҫ����º������󣬵�����Ϊfalseʱ�Ż�block
	������trueʱ�Ż�unblock
	����������Է�ֹ��ٵĻ���

	unique_lock��Ҫһ��mutex����
	���ڹ���ʱ�Զ�lock������ʱ�Զ�unlock
	������������lock��unlock

	�������ʼ����ʱ���ᴴ�������̣߳��ȱ����ȵ��̻߳�������
	�����ӡ�������߳����뵽�����������ܵ�wait����������Ϊ�����������������
	���Ի�ֱ���������1��Ȼ���x����++�����֪ͨż�����̿��Խ��������ż��������wait�еõ���
	Ȼ��ż���������ִ�У���֪ͨ��������ִ��

	�����ӡż�����߳������뵽����������Ϊ������������������wait����wait���ͷ�����̵߳���
	ż���߳��ͷź������߳̾Ϳ������뵽����Ȼ����������߼����ִ��

	��x�Ѿ��������100ʱ���������ֵ������߳�ִ�У�Ϊ�˲�����100��Ҫ�������߳������Ƴ�ѭ��������




int main()
{
	mutex mtx;
	condition_variable cond;
	int x = 1;
	int n = 100;

	auto thread_func1 = [&, n]()	//lambda���ʽ�������е�����,n��ֵ����ֹn���޸�
	{
		//��ӡ����
		while (1)
		{
			unique_lock<mutex> lock(mtx);//��������
			if (x >= n)
			{
				break;
			}
			//�����ż���������ȴ�
			//waitһ��������д��
			//if (x % 2 == 0)
			//{
			//	cond.wait(lock);
			//}
			//wait����������д��
			cond.wait(lock, [&x] //�������Ҫ��׽x�����ã����������߳��ڸ���xʱ������߳��е�x���ֲ���
				{
					cout << "thread1:" << x << endl;
					return x % 2 != 0; 
				});//���ʽΪ�٣�����wait
			//cout << "thread1:" << x << endl;

			cout << this_thread::get_id() << ": x = " << x << endl;
			++x;


			cond.notify_one();
		}
	};

	auto thread_func2 = [&, n]()
	{
		//��ӡż��
		while (1)
		{
			unique_lock<mutex> lock(mtx);
			if (x > 100)
			{
				break;
			}
			//����������������ȴ�
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
atomic��ʹ��
ԭ����ֻ�ܴ�ģ������н��й��죬����ʹ�ÿ������졢��ֵ���ƶ�����


int main()
{
	const int N = 10000;
	atomic<int> x;	//����x��һ��int�����������ԭ����
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
	//��Ϊx�Ĳ�������ԭ���ԣ���++��ʱ�򲻻���Ϊ�л������̶߳�����++ʧЧ
	return 0;
}*/

/*
lock_guard��unique_lock,��RAII������

lock_guard��mutex���з�װ������Ҫ�����ĵط�������һ��lock_guard����
�ڵ��ù��캯��ʱ�Զ���������������ʱ���������������Զ�����

unique_lock������lock_guard�Ĺ��ܣ�ͬʱ������һЩ�ӿ�
�����������Ƽ������ͷţ�Ҳ֧���ƶ���ֵ

�������������Զ�ռ����Ȩ�ķ�ʽ����mutex�������ͽ�������֧�ֿ���
����ʱ����Ҫ����һ��mutex����
*/

/*
function��װ����������һ����ģ��
template <class Ret, class... Args> 
class function<Ret(Args...)>;
*/