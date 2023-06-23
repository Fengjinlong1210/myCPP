#define _CRT_SECURE_NO_WARNINGS 1
#include "RBTree.h"
#include "map.h"
#include "set.h"

using namespace std;

void test_map()
{
	Fjl::map<int, int> m;
	m.insert(make_pair(1, 1));
	m.insert(make_pair(2, 1));
	m.insert(make_pair(3, 1));
	m.insert(make_pair(4, 1));
	m.insert(make_pair(5, 1));
	m.insert(make_pair(6, 1));
	m.isBalance();
	m.MapInOrder();

	Fjl::map<int, int>::iterator it = m.begin();
	while (it != m.end())
	{
		cout << it->first << ":" << it->second << endl;
		++it;
	}

	for (auto& e : m)
	{
		m[e.first]++;
	}

	it = m.begin();

	while (it != m.end())
	{
		cout << it->first << ":" << it->second << endl;
		++it;
	}
}

void test_set()
{
	Fjl::set<int> s;
	s.insert(1);
	s.insert(2);
	s.insert(3);
	s.insert(4);
	s.insert(5);
	s.SetInOrder();
	Fjl::set<int>::iterator it = s.begin();
	while (it != s.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
	//(*it)++;//set的普通迭代器也是const类型，不能更改
}

int main()
{
	test_set();
	return 0;
}