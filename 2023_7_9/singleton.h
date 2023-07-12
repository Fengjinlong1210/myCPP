#pragma once
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
//����ģʽ��һ����ֻ�ܴ���һ�����󣬸�ʵ�������г���ģ�鹲��

/*	1. ����ģʽ: �ӳ��򴴽���ʼ�ʹ���һ������
class singleton
{
public:
	static singleton* get_instance()
	{
		return _only_instance;
	}

	void push(int data)
	{
		_v.push_back(data);
	}

	void print()
	{
		for (auto& e : _v)
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;
	}
private:
	singleton(){}	//���캯��˽��, ��ֹ���ⴴ������
	//��ֹ���ɿ�������͸�ֵ
	singleton(const singleton&) = delete;
	singleton& operator=(const singleton&) = delete;

private:
	static singleton* _only_instance;

	std::vector<int> _v;
};
singleton* singleton::_only_instance = new singleton;


����ģʽ���ŵ�
	1. �򵥷���
ȱ��:
	1. ���½���������, ����ж������ģʽ��ʵ����, �޷�ȷ���Ⱥ�˳��
*/

//	2. ����ģʽ: ��һ��ʹ�øö���ʱ, ��������, �������ɿ���

class singleton
{
public:
	static singleton* get_instance()
	{
		if (!_only_instance)
		{
			_mtx.lock();		//Ϊ�˱�֤�̰߳�ȫ, ����˫�����
			if (!_only_instance)
			{
				_only_instance = new singleton;
			}
			_mtx.unlock();
		}
		return _only_instance;
	}

	void push(int data)
	{
		_mtx.lock();
		_v.push_back(data);
		_mtx.unlock();
	}

	void print()
	{
		_mtx.lock();
		for (auto& e : _v)
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;
		_mtx.unlock();
	}

	static void delete_instance()
	{
		_mtx.lock();
		if (_only_instance)
		{
			delete _only_instance;
			_only_instance = nullptr;
		}
		_mtx.unlock();
	}

public:
	//���ڲ�����һ��GC��, �����ֶ��ͷŶ���
	//�ڲ���Ĭ�����ⲿ�����Ԫ
	class GC	
	{
	public:
		~GC()
		{
			delete_instance();
		}
	};
	static GC _gc_obj;
	//�����̬�����ٱ�����ʱ���Զ�����ʵ������������

private:
	singleton() {}	//���캯��˽��, ��ֹ���ⴴ������
	//��ֹ���ɿ�������͸�ֵ
	singleton(const singleton&) = delete;
	singleton& operator=(const singleton&) = delete;

private:
	static singleton* _only_instance;
	static std::mutex _mtx;
	std::vector<int> _v;
};
singleton* singleton::_only_instance = nullptr;
std::mutex singleton::_mtx;
singleton::GC singleton::_gc_obj;
