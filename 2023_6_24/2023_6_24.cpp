#define _CRT_SECURE_NO_WARNINGS 1
#include "HashTable.h"

using namespace ht;

void test_hashtable()
{
	ht::HashTable<int, int> h;
	int a[] = { 3, 33, 2, 13, 5, 12, 1002, 28, 65, 18, 109, 20 };

	for (auto e : a)
	{
		h.insert(make_pair(e, e));
	}

	auto ret = h.find(33);
	h.erase(109);
}

void test_hashbucket()
{
	hb::HashBucket<int, int> h;
	int a[] = { 3, 33, 2, 13, 5, 12, 1002, 28, 65, 18, 109, 20 };
	for (auto e : a)
	{
		h.insert(make_pair(e, e));
	}

	auto ret = h.find(109);
	h.erase(109);
}

int main()
{
	//test_hashtable();
	test_hashbucket();
	return 0;
}