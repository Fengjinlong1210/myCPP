#define _CRT_SECURE_NO_WARNINGS 1
#include "map.h"
#include <iostream>
using namespace std;
//using namespace Fjl;

int main()
{
	Fjl::map<int, int> m;
	m.insert(make_pair(1, 1));
	m.insert(make_pair(2, 1));
	m.insert(make_pair(3, 1));
	m.insert(make_pair(4, 1));
	m.inOrder();
	return 0;
}