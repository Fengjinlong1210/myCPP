#define _CRT_SECURE_NO_WARNINGS 1
#include "String.h"

void test1()
{
	Fjl::String str1("hello");
	Fjl::String str2(str1);
	str1.push_back('a');
	str1.push_back('b');
	str1.push_back('c');
	str1.push_back('d');
	str1.push_back('e');
	str1.push_back('f');
	str1.push_back('g');
	str1.push_back('h');
	str1.push_back('i');
	str1.push_back('j');
	str1.push_back('k');
	str1.push_back('l');
	str1.push_back('m');
	str1.push_back('n');
	str1.push_back('o');
	str1.push_back('p');
	str1.push_back('q');
	str1.push_back('r');
	str1.push_back('s');
	str1.push_back('t');
	str1.push_back('u');
	str1.push_back('v');
	str1.push_back('w');
	str1.push_back('x');
}

void test2()
{
	Fjl::String str1;
	Fjl::String str2("hello");
	Fjl::String str3("11.5");

	str1.reserve(10);
	str1.reserve(100);

	str2 += 'a';
	str2 += "abcdefg";
	
	str2 += str3;
	for (size_t i = 0; i < str2.size(); ++i)
	{
		cout << str2[i] << " ";
	}
	cout << endl;
	for (size_t i = 0; i < str2.size(); ++i)
	{
		str2[i]++;
		cout << str2[i] << " ";
	}
	cout << endl;
}

void test3()
{
	Fjl::String str1("hello fjl abcdefghijklmnopqrstuvwxyz");
	Fjl::String str2 = str1;
	Fjl::String str3 = "abcdefg";
	Fjl::String str4(str3, 1, 2);
	Fjl::String str5(str1, 10, 10);
	str1.print();
	str5.print();
}


void test4()
{
	Fjl::String str1 = "abcdefghijklmnopqrstuvwxyz";
	
}

int main()
{
	test3();
	return 0;
}