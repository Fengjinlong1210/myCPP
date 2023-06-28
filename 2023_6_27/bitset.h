#pragma once
#include <iostream>
#include <vector>
using namespace std;

// 给定100亿个整数，设计算法找到只出现一次的整数
// :放到位图中表示存在与否

template<size_t N>
class BitSet
{
public:
	BitSet()
	{
		_bits.resize(N / 8 + 1, 0);
	}

	void set()
	{
		_bits.resize(0);
		_bits.resize(N / 8 + 1, 0xFF);
	}

	void set(size_t num)
	{
		size_t i = num / 8;
		//num所在vector中的地址
		size_t j = num % 8;
		//num在char中的第几位

		_bits[i] |= (1 << j);
	}

	void reset(size_t num)
	{
		size_t i = num / 8;
		//num所在vector中的地址
		size_t j = num % 8;
		//num在char中的第几位

		_bits[i] &= ~(1 << j);
	}

	bool test(size_t num)
	{
		size_t i = num / 8;
		//num所在vector中的地址
		size_t j = num % 8;
		//num在char中的第几位

		return _bits[i] & (1 << j);
	}
private:

private:
	vector<char> _bits;
};

//位图的应用：
//1. 快速查找一个数字在不在序列中
//2. 排序 + 去重
//3. 找两个集合的交集、并集
//4. 操作系统中磁盘块的标记

//实现一个能包含所有int的位图, 需要512MB内存

//给两个文件，分别有100亿个整数，我们只有1G内存，如何找到两个文件交集？

//	方案1:
// 设置两个位图, 分别表示两个文件的整数
// 遍历位图找到共同存在的整数

// 方案2:
// 只把第一个文件的整数放入位图, 然后遍历第二个文件
// 如果第二个文件中的数字存在于位图, 就说明是交集
// 记录完一个数字后, 把位图上对应的位置置为0, 放置一个数字被多次记录成交集


//  1个文件有100亿个int，1G内存，设计算法找到出现次数不超过2次的所有整数
//  解决方案: 设置两个位图, 第一个位图记录该数字出没出现过, 第二个位图记录出现次数是不是一次
//	或者, 出现一次时, 把两个位图设置成01, 第二次时, 设置成10, 第三次11, 通过这种方式
//	可以记录出现的次数, 只需要增加位图即可

template<size_t N>
class DoubleBitSet
{
public:
	void set(size_t num)
	{
		if (_bits1.test(num) == 0 && _bits2.test(num) == 0) //00->01
		{
			//该数字还没有被记录过
			_bits1.set(num);
		}
		else if (_bits1.test(num) == 1 && _bits2.test(num) == 0) // 01->10
		{
			//被记录过一次
			_bits1.reset(num);
			_bits2.set(num);
		}
		else if (_bits1.test(num) == 0 && _bits2.test(num) == 1) // 10->11
		{
			_bits1.set(num);
		}
		else
		{
			return;
		}

	}

	int test(size_t num)
	{
		return _bits1.test(num) + 2 * _bits2.test(num);
	}
private:
	BitSet<N> _bits1;
	BitSet<N> _bits2;
};