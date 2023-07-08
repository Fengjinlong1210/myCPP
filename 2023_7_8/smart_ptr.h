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
			_pmtx(new std::mutex)//每个被管理的资源都需要一把锁
		{}

		template<class DEL>
		SmartPtr(T* ptr, DEL del)
			: _ptr(ptr),
			_pcount(new int(1)),
			_pmtx(new std::mutex),
			_del(del)
		{}

		//拷贝构造
		SmartPtr(const SmartPtr& sp)
			:_ptr(sp._ptr), _pcount(sp._pcount), _pmtx(sp._pmtx)
		{
			//两个对象指向同一块空间，引用计数++
			AddCount();
		}

		SmartPtr<T>& operator=(const SmartPtr& sp)
		{
			if (this != &sp)//不是同一个对象
			{
				//this被赋值之前，this原本管理的资源要先被--
				Release();

				_ptr = sp._ptr;
				_pcount = sp._pcount;
				_pmtx = sp._pmtx;		//拷贝和赋值都用的是同一把锁
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
					//调用删除器进行删除
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
		//为保证线程安全，要对++操作进行加锁
		//为了智能指针的拷贝，要使用锁的指针，管理同一个资源的不同指针可以使用同一把锁的指针

		std::function<void(T*)> _del = [](T* ptr)
		{
			cout << "function delete" << endl;
			delete ptr;
		};

	};

	//这里智能指针++操作是线程安全的，但是当不同线程去访问智能指针管理的资源时，会出现线程安全问题

	//智能指针的循环引用

	//weak_ptr获得资源的观测权，不会引起shared_ptr的引用计数增加
	//不能用来直接定义指向原始指针的对象
	template<class T>
	class WeakPtr
	{
	public:
		WeakPtr()
		{}

		WeakPtr(T* ptr)				//weakptr的默认构造函数是无参的
			:_ptr(ptr)
		{}

		//WeakPtr(const SmartPtr<T>& wp)//weakptr用sharedptr或weakptr进行初始化
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

		//默认生成的构造函数，对于自定义类型，会去调用自定义类型的默认构造函数
		//而weak如果不提供默认构造，就会无法初始化
		WeakPtr<ListNode> _next;	//需要提供默认构造函数，否则ListNode的默认构造函数不可用
		WeakPtr<ListNode> _prev;
		int _val;

		~ListNode()
		{
			std::cout << "~ListNode()" << std::endl;
		}
	};
}

//删除器：对于不是new出来的对象，要通过仿函数进行传递释放函数的对象，在类内部调用释放函数来释放