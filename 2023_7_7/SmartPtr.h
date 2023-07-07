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

	//��ֹ���ɿ�������͸�ֵ�����
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
		_pmtx(new std::mutex)//ÿ�����������Դ����Ҫһ����
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
		if (--(*_pcount) == 0 && _ptr)
		{
			std::cout << "delete" << std::endl;
			delete _ptr;
			delete _pcount;

			//�����ͷ�
		}
		_pmtx->unlock();
	}
private:
	T* _ptr;
	int* _pcount;
	std::mutex* _pmtx;
	//Ϊ��֤�̰߳�ȫ��Ҫ��++�������м���
	//Ϊ������ָ��Ŀ�����Ҫʹ������ָ�룬����ͬһ����Դ�Ĳ�ָͬ�����ʹ��ͬһ������ָ��
};

