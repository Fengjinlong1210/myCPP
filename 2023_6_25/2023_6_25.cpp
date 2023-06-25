#define _CRT_SECURE_NO_WARNINGS 1
#include "HashBucket.h"
#include "unordered_map.h"
#include <string>
#include <ctime>
using namespace std;

void test_ht()
{
	//HashTable<int, int> t;
	//int a[] = { 12, 59, 86, 3, 1024, 105, 7, 19, 30, 52, 11, 1111 };
	//for (auto& e : a)
	//{
	//	t.insert(make_pair(e, e));
	//}
	//cout << t.find(123) << endl;
	//cout << t.find(12) << endl;
	//cout << t.find(11) << endl;
	//cout << t.erase(12) << endl;
	//cout << t.erase(11) << endl;
	//cout << t.erase(123) << endl;
}

void test_ht2()
{
	//srand((unsigned int)time(0));
	//HashTable<int, int> t;
	//const int N = 100;
	//for (size_t i = 0; i < N; ++i)
	//{
	//	int num = rand() % 200 + i;
	//	t.insert(make_pair(num, num));
	//}

}

void test_map()
{
	Fjl::unordered_map<int, int> m;
	int a[] = { 12, 59, 86, 3, 1024, 105, 7, 19, 30, 52, 11, 1111 };
	for (auto& e : a)
	{
		m.insert(make_pair(e, e));
	}

	Fjl::unordered_map<int, int>::iterator it = m.begin();
	while (it != m.end())
	{
		cout << it->first << ":" << it->second << endl;
		++it;
	}
	cout << endl;
}

void test_map2()
{
	Fjl::unordered_map<int, int> m;
	int a[] = { 12, 59, 86, 3, 1024, 105, 7, 19, 30, 52, 11, 1111 };
	for (auto& e : a)
	{
		m[e]++;
	}

	Fjl::unordered_map<int, int>::iterator it = m.begin();
	while (it != m.end())
	{
		cout << it->first << ":" << it->second << endl;
		++it;
	}
	cout << endl;
}

void test_map3()
{
	Fjl::unordered_map<string, int> m;
	string arr[] = { "西瓜", "西瓜", "苹果", "西瓜", "苹果", "苹果", "西瓜", "苹果", "香蕉", "苹果", "香蕉", "梨" };
	for (auto& e : arr)
	{
		m[e]++;
	}

	Fjl::unordered_map<string, int>::iterator it = m.begin();
	while (it != m.end())
	{
		cout << it->first << ":" << it->second << endl;
		++it;
	}
	cout << endl;
}

int main()
{
	test_map3();
	return 0;
}