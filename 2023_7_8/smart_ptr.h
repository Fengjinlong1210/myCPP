#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <functional>

namespace Fjl
{
	struct Date
	{
		Date(int year = 0, int month = 0, int day = 0)
			:_year(year), _month(month), _day(day)
		{}

		int _year;
		int _month;
		int _day;
	};

	template<class T>
	class SmartPtr
	{
	public:
		SmartPtr(T* ptr)
			:_ptr(ptr),
			_pcount(new int(1)),
			_pmtx(new std::mutex)//ÿ�����������Դ����Ҫһ����
		{}

		template<class DEL>
		SmartPtr(T* ptr, DEL del)
			: _ptr(ptr),
			_pcount(new int(1)),
			_pmtx(new std::mutex),
			_del(del)
		{}

		//��������
		SmartPtr(const SmartPtr& sp)
			:_ptr(sp._ptr), _pcount(sp._pcount), _pmtx(sp._pmtx)
		{
			//��������ָ��ͬһ��ռ䣬���ü���++
			AddCount();
		}

		SmartPtr<T>& operator=(const SmartPtr& sp)
		{
			if (this != &sp)//����ͬһ������
			{
				//this����ֵ֮ǰ��thisԭ���������ԴҪ�ȱ�--
				Release();

				_ptr = sp._ptr;
				_pcount = sp._pcount;
				_pmtx = sp._pmtx;		//�����͸�ֵ���õ���ͬһ����
				AddCount();
			}
			return *this;
		}

		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

		~SmartPtr()
		{
			Release();
		}

		T* get_ptr() const
		{
			return _ptr;
		}

		int get_count() const
		{
			return *_pcount;
		}
	private:
		void AddCount()
		{
			_pmtx->lock();
			++(*_pcount);
			_pmtx->unlock();
		}

		void Release()
		{
			_pmtx->lock();
			bool flag = false;
			if (--(*_pcount) == 0)
			{
				if (_ptr)
				{
					std::cout << "delete" << std::endl;
					//����ɾ��������ɾ��
					_del(_ptr);
				}
				flag = true;
				delete _pcount;
			}
			_pmtx->unlock();
			if (flag)
			{
				delete _pmtx;
			}
		}
	private:
		T* _ptr;
		int* _pcount;
		std::mutex* _pmtx;
		//Ϊ��֤�̰߳�ȫ��Ҫ��++�������м���
		//Ϊ������ָ��Ŀ�����Ҫʹ������ָ�룬����ͬһ����Դ�Ĳ�ָͬ�����ʹ��ͬһ������ָ��

		std::function<void(T*)> _del = [](T* ptr)
		{
			cout << "function delete" << endl;
			delete ptr;
		};

	};

	//��������ָ��++�������̰߳�ȫ�ģ����ǵ���ͬ�߳�ȥ��������ָ��������Դʱ��������̰߳�ȫ����

	//����ָ���ѭ������

	//weak_ptr�����Դ�Ĺ۲�Ȩ����������shared_ptr�����ü�������
	//��������ֱ�Ӷ���ָ��ԭʼָ��Ķ���
	template<class T>
	class WeakPtr
	{
	public:
		WeakPtr()
		{}

		WeakPtr(T* ptr)				//weakptr��Ĭ�Ϲ��캯�����޲ε�
			:_ptr(ptr)
		{}

		//WeakPtr(const SmartPtr<T>& wp)//weakptr��sharedptr��weakptr���г�ʼ��
		//{
		//	_ptr = wp.get_ptr();
		//}

		//WeakPtr<T>& operator=(const SmartPtr<T>& wp)
		//{
		//	_ptr = wp.get_ptr();
		//	return *this;
		//}

		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

	private:
		T* _ptr;
	};

	struct ListNode
	{
		//ListNode(int val)
		//	:_val(val),
		//	_next(nullptr), 
		//	_prev(nullptr)
		//{}

		//Ĭ�����ɵĹ��캯���������Զ������ͣ���ȥ�����Զ������͵�Ĭ�Ϲ��캯��
		//��weak������ṩĬ�Ϲ��죬�ͻ��޷���ʼ��
		WeakPtr<ListNode> _next;	//��Ҫ�ṩĬ�Ϲ��캯��������ListNode��Ĭ�Ϲ��캯��������
		WeakPtr<ListNode> _prev;
		int _val;

		~ListNode()
		{
			std::cout << "~ListNode()" << std::endl;
		}
	};
}

//ɾ���������ڲ���new�����Ķ���Ҫͨ���º������д����ͷź����Ķ��������ڲ������ͷź������ͷ�