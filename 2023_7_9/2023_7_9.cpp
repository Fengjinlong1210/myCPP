#define _CRT_SECURE_NO_WARNINGS 1
#include "singleton.h"
#include <ctime>
using namespace std;
int main()
{
	//����ģʽ, �ڽ���main����֮ǰ������˶����ʵ����, ͨ����̬��Ա������ȡ�ö����ָ��
	/*auto instance = singleton::get_instance();
	instance->push(1);
	instance->push(2);
	instance->push(3);
	instance->push(4);
	instance->push(5);
	instance->push(6);
	instance->print();*/
	srand((unsigned int)time(nullptr));
	auto instance = singleton::get_instance();
	auto thread_func = [&](int n = 10)
	{
		while (n--)
		{
			int x = rand() % 100 + 1;
			instance->push(x);
			this_thread::sleep_for(chrono::seconds(1));
		}
	};

	thread t1(thread_func);
	thread t2(thread_func);

	t1.join();
	t2.join();

	instance->print();
	return 0;
}