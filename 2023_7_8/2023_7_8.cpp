#define _CRT_SECURE_NO_WARNINGS 1
#include "smart_ptr.h"
using namespace std;
using namespace Fjl;
//void test_thread1()
//{
//	SmartPtr<int> sp1(new int(100));
//	auto thread_func = [](SmartPtr<int>& sp, int n, mutex& mtx)
//	{
//		int i = 0;
//		for (; i < n; ++i)
//		{
//			SmartPtr<int> tmp(sp);	//����ָ���++�������̰߳�ȫ��
//
//
//		}
//	};
//
//	int N = 100;
//	mutex mtx;
//	thread t1(thread_func, ref(sp1), N, ref(mtx));
//	thread t2(thread_func, ref(sp1), N, ref(mtx));
//
//	t1.join();
//	t2.join();
//	cout << "count = " << sp1.get_count() << endl;
//}
//
//void test_thread2()
//{
//	SmartPtr<Date> sp1(new Date);
//	auto thread_func = [](SmartPtr<Date>& sp, int n, mutex& mtx)
//	{
//		int i = 0;
//		for (; i < n; ++i)
//		{
//			mtx.lock();
//			SmartPtr<Date> tmp(sp);	//����ָ���++�������̰߳�ȫ��
//			sp->_year++;
//			sp->_month++;
//			sp->_day++;		//����ָ�����������Դ�����̲߳���ȫ�ģ���˷�������ָ�����Դ��Ҫ����
//
//			mtx.unlock();
//		}
//	};
//
//	int N = 100000;
//	mutex mtx;
//	thread t1(thread_func, ref(sp1), N, ref(mtx));
//	thread t2(thread_func, ref(sp1), N, ref(mtx));
//
//	t1.join();
//	t2.join();
//	cout << "count = " << sp1.get_count() << endl;
//
//	cout << "year = " << sp1->_year << endl;
//	cout << "month = " << sp1->_month << endl;
//	cout << "day = " << sp1->_day << endl;
//}
//
//void cycle_ref1()
//{
//	SmartPtr<ListNode> node1(new ListNode);
//	SmartPtr<ListNode> node2(new ListNode);
//
//	cout << "node1.count" << node1.get_count() << endl;
//	cout << "node2.count" << node2.get_count() << endl;
//
//	node1->_next = node2;
//	node2->_prev = node1;
//
//	cout << "node1.count" << node1.get_count() << endl;
//	cout << "node2.count" << node2.get_count() << endl;
//
//	//���ﲢû�е���ListNode��������������Ϊ������ѭ������
//	//node1��next��node2���ڹ���node2����Դ
//	//node2��next��node1���ڹ���node1����Դ
//	//�������ָ������ü�����û�취����0��������㶼û���ͷ�
//}
//
//void cycle_ref2()
//{
//	SmartPtr<ListNode> node1(new ListNode);
//	SmartPtr<ListNode> node2(new ListNode);
//
//	cout << "node1.count" << node1.get_count() << endl;
//	cout << "node2.count" << node2.get_count() << endl;
//
//	node1->_next = node2;
//	node2->_prev = node1;
//
//	cout << "node1.count" << node1.get_count() << endl;
//	cout << "node2.count" << node2.get_count() << endl;
//
//
//}


//void cycle()
//{
//	Fjl::shared_ptr<ListNode> node1(new ListNode);
//	Fjl::shared_ptr<ListNode> node2(new ListNode);
//
//	cout << "node1.count = " << node1.use_count() << endl;
//	cout << "node2.count = " << node2.use_count() << endl;
//
//	node1->_next = node2;
//	node2->_prev = node1;
//
//
//	cout << "node1.count = " << node1.use_count() << endl;
//	cout << "node2.count = " << node2.use_count() << endl;
//}

//auto delete_malloc = [](int* ptr)
//{
//	cout << "free malloc" << endl;
//	free(ptr);
//};
//
//auto delete_file = [](FILE* pf)
//{
//	cout << "fclose file" << endl;
//	fclose(pf);
//};
//
//auto delete_array = [](int* ptr)
//{
//	cout << "delete[] array" << endl;
//	delete[] ptr;
//};
//
//void test_delete()
//{
//	//ͨ���Զ��庯���������ͷŲ�ͬ��ָ������
//	SmartPtr<int> sp1((int*)malloc(4 * sizeof(int)), delete_malloc);
//	SmartPtr<FILE> sp2(fopen("data.txt", "w"), delete_file);
//	SmartPtr<int> sp3(new int[10], delete_array);
//}
//
//
//int main()
//{
//	test_delete();
//	return 0;
//}

////////////////////////////////////////////////////////////////////////////////////
/*
�������ʹ��
*/
#include "special_class.h"
int main()
{
	//NoCopy1 obj1(100);
	//NoCopy1 obj3(200);

	//��ֵ���غͿ������춼����ֹ
	//NoCopy obj2(obj1);
	//obj1 = obj3;

	//OnlyHeap* obj1 = OnlyHeap::create_obj(100);

	OnlyStack1 obj2 = OnlyStack1::create_obj(105);
	//OnlyStack2* obj3 = new OnlyStack2(123);
	//�޷�����operator new
	return 0;
}