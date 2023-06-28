#pragma once
#include <iostream>
#include <string>
#include "bitset.h"
using namespace std;

//	布隆过滤器需要设置数据和表长的倍数关系
//	通过多个哈希函数将key映射成不同的值
//	查找key在与不在的时候, 只需要查这多个映射后的key值在不在
//	如果有一个值不在, 就说明key一定不存在
//	即使这多个值都存在, 也有可能是其他的key值映射出来的, 该key也有可能不存在
//	所以布隆过滤器	可以用来快速判断一个key存不存在, 如果不存在, 就不需要进行后续的查找
//	布隆过滤器适用于与磁盘进行的IO、网络请求或判断昵称存在与否

//	布隆过滤器不支持删除，会导致其他key被影响

struct BKDRHash
{
	size_t operator()(const string& s)
	{
		// BKDR
		size_t value = 0;
		for (auto ch : s)
		{
			value *= 31;
			value += ch;
		}
		return value;
	}
};

struct APHash
{
	size_t operator()(const string& s)
	{
		size_t hash = 0;
		for (long i = 0; i < s.size(); i++)
		{
			if ((i & 1) == 0)
			{
				hash ^= ((hash << 7) ^ s[i] ^ (hash >> 3));
			}
			else
			{
				hash ^= (~((hash << 11) ^ s[i] ^ (hash >> 5)));
			}
		}
		return hash;
	}
};

struct DJBHash
{
	size_t operator()(const string& s)
	{
		size_t hash = 5381;
		for (auto ch : s)
		{
			hash += (hash << 5) + ch;
		}
		return hash;
	}
};

template<size_t N, class K = string, class Hash1 = BKDRHash, class Hash2 = APHash, class Hash3 = DJBHash>
class BloomFilter
{
public:
	void set(string str)
	{
		size_t length = multiple * N;
		size_t address1 = BKDRHash()(str) % length;
		size_t address2 = APHash()(str) % length;
		size_t address3 = DJBHash()(str) % length;

		_bs.set(address1);
		_bs.set(address2);
		_bs.set(address3);
	}

	bool test(string str)
	{
		size_t length = multiple * N;
		size_t address1 = BKDRHash()(str) % length;
		size_t address2 = APHash()(str) % length;
		size_t address3 = DJBHash()(str) % length;

		if (_bs.test(address1) && _bs.test(address2) && _bs.test(address3))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
private:
	//需要一个位图，根据N的个数和倍数计算出过滤器的长度
	static const size_t multiple = 6;
	BitSet<multiple* N> _bs;
};

//给两个文件，分别有100亿个query，我们只有1G内存，如何找到两个文件交集？分别给出精确算法和近似算法

//将两个文件的内容进行哈希切割，分割成N个小文件
//这样就会使相同的内容也进入相同的小文件中
//例如同样的字符串会进入A1文件，也会进入B1文件
//再把两个文件的小文件对应的进行对比，就可以找出交集

//如果存在单个文件过大的情况
//1.有大量重复数据 ： 用set去重
//2.有大量不同数据 ：同样放入set， 如果抛异常，就说明是情况二，需要更换其他哈希函数，再次分割小文件求交集