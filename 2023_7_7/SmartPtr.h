#pragma once
#include <iostream>
#include <thread>
#include <string>
#include <mutex>

template<class T>
class UniquePtr
{
public:
	UniquePtr(const T& ptr)
		:_ptr(ptr)
	{}

	//禁止生成拷贝构造和赋值运算符
	UniquePtr(UniquePtr<T>& ps) = delete;
	UniquePtr<T>& operator=(UniquePtr<T>& ps) = delete;

	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}

	~UniquePtr()
	{
		delete _ptr;
	}
private:
	T* _ptr;
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
		if (--(*_pcount) == 0 && _ptr)
		{
			std::cout << "delete" << std::endl;
			delete _ptr;
			delete _pcount;

			//锁的释放
		}
		_pmtx->unlock();
	}
private:
	T* _ptr;
	int* _pcount;
	std::mutex* _pmtx;
	//为保证线程安全，要对++操作进行加锁
	//为了智能指针的拷贝，要使用锁的指针，管理同一个资源的不同指针可以使用同一把锁的指针
};

