#define _CRT_SECURE_NO_WARNINGS 1
#include "bitset.h"
#include <Windows.h>
#include "BloomFilter.h"
#include <vector>
#include <ctime>

void test_bitset()
{
	BitSet<-1> bs;
	//int arr[] = { 12, 13, 14, 15, 16, 17, 18, 12, 13, 14, 15, 16 };
	//for (auto& e : arr)
	//{
	//	bs.set(e);
	//}

	//for (size_t i = 0; i < 100; ++i)
	//{
	//	cout << i << ":" << bs.test(i) << endl;
	//}

	while (1)
	{
		Sleep(1000);
	}
}

//void test_doublebitset()
//{
//	int a[] = { 3, 45, 53, 32, 32, 43, 3, 2, 5, 2, 32, 55, 5, 53,43,9,8,7,8 };
//	DoubleBitSet<100> bs;
//	for (auto e : a)
//	{
//		bs.set(e);
//	}
//
//	for (size_t i = 0; i < 100; ++i)
//	{
//		cout << i << ":" << bs.test(i) << endl;
//	}
//}

void test_BloomFilter1()
{
	string arr[] = { "hello", "map", "bloomfilter", "hash", "fjl", "c++", "main", "bf.set()", 
	"size_t length = multiple * N;", "test_BloomFilter"};
	string arr2[] = { "helloh", "maps", "bloomfiltdsr", "hfaash", "fhgl", "cf+", "maian", "bf.sfdt()",
"size_fdngth = multiple * N;", "test_Blk.hlter" };
	const size_t size = sizeof(arr);
	BloomFilter<size> bf;

	for (auto& str : arr)
	{
		bf.set(str);
	}
	
	for (auto& str : arr)
	{
		cout << str << ":" << bf.test(str) << endl;
	}

	cout << endl;

	for (auto& str2 : arr2)
	{
		cout << str2 << ":" << bf.test(str2) << endl;
	}
}

void test_BloomFilter2()
{
	srand((unsigned int)time(nullptr));
	string s1 = "https://gitee.com/bithange/107-issues/blob/master/23%E5%B9%B4-05%E6%9C%8820%E6%97%A5--%E5%B8%83%E9%9A%86%E8%BF%87%E6%BB%A4%E5%99%A8%E5%92%8C%E5%93%88%E5%B8%8C%E5%88%87%E5%88%86--%E4%B8%8B%E5%8D%88/5-20-%E4%B8%8B%E5%8D%88.png";
	static const size_t size = 10000;
	BloomFilter<size> bf;
	vector<string> v;
	//创建多个相似字符放入bf
	for (size_t i = 0; i < size; ++i)
	{
		string str = (s1 + to_string(rand() + i));
		v.push_back(str);
	}

	for (size_t i = 0; i < size; ++i)
	{
		bf.set(v[i]);
	}
	
	//再次创建多个相似但不完全相等的字符
	//然后统计误判次数
	size_t n = 0;
	for (size_t i = 0; i < size; ++i)
	{
		string s1 = "https://gitee.com/bithange/107-issues/blob/master/23%E5%B9%B4-05%E6%9C%8820%E6%97%A5--%E5%B8%83%E9%9A%86%E8%BF%87%E6%BB%A4%E5%99%A8%E5%92%8C%E5%93%88%E5%B8%8C%E5%88%87%E5%88%86--%E4%B8%8B%E5%8D%88/5-20-%E4%B8%8B%E5%8D%88.png";
		s1 += to_string(rand() * i);
		if (bf.test(s1))
		{
			n++;
		}
	}

	printf("出现%d个误判，占%d个总数的%%%0.2lf\n", n, size, ((double)n / (double)size) * 100);

}

void test_BloomFilter3()
{
	srand((unsigned int)time(nullptr));
	string s1 = "https://gitee.com/bithange/107-issues/blob/master/23%E5%B9%B4-05%E6%9C%8820%E6%97%A5--%E5%B8%83%E9%9A%86%E8%BF%87%E6%BB%A4%E5%99%A8%E5%92%8C%E5%93%88%E5%B8%8C%E5%88%87%E5%88%86--%E4%B8%8B%E5%8D%88/5-20-%E4%B8%8B%E5%8D%88.png";
	static const size_t size = 10000;
	BloomFilter<size> bf;
	vector<string> v;
	//创建多个相似字符放入bf
	for (size_t i = 0; i < size; ++i)
	{
		string str = (s1 + to_string(rand() + i));
		v.push_back(str);
	}

	for (size_t i = 0; i < size; ++i)
	{
		bf.set(v[i]);
	}

	//再次创建多个相似但不完全相等的字符
	//然后统计误判次数
	size_t n = 0;
	for (size_t i = 0; i < size; ++i)
	{
		string s1 = "Photo by Gustas Brazaitis on Unsplash";
		s1 += to_string(rand() * i);
		if (bf.test(s1))
		{
			n++;
		}
	}

	printf("出现%d个误判，占%d个总数的%%%0.2lf\n", n, size, ((double)n / (double)size) * 100);
}

int main()
{
	cout << "相似字符串：";
	test_BloomFilter2();
	cout << "不相似字符串：";

	test_BloomFilter3();
	return 0;
}