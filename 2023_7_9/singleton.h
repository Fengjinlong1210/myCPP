#pragma once
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
//单例模式：一个类只能创建一个对象，该实例被所有程序模块共享

/*	1. 饿汉模式: 从程序创建开始就创建一个对象
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
	singleton(){}	//构造函数私有, 防止类外创建对象
	//禁止生成拷贝构造和赋值
	singleton(const singleton&) = delete;
	singleton& operator=(const singleton&) = delete;

private:
	static singleton* _only_instance;

	std::vector<int> _v;
};
singleton* singleton::_only_instance = new singleton;


饿汉模式的优点
	1. 简单方便
缺点:
	1. 导致进程启动慢, 如果有多个饿汉模式的实例化, 无法确定先后顺序
*/

//	2. 懒汉模式: 第一次使用该对象时, 创建对象, 可以自由控制

class singleton
{
public:
	static singleton* get_instance()
	{
		if (!_only_instance)
		{
			_mtx.lock();		//为了保证线程安全, 必须双层检验
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
	//在内部设置一个GC类, 可以手动释放对象
	//内部类默认是外部类的友元
	class GC	
	{
	public:
		~GC()
		{
			delete_instance();
		}
	};
	static GC _gc_obj;
	//这个静态对象再被析构时会自动调用实例的析构函数

private:
	singleton() {}	//构造函数私有, 防止类外创建对象
	//禁止生成拷贝构造和赋值
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
