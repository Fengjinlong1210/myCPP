#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <map>
#include <set>
#include <string>
using namespace std;

//map��set
//�������νṹ�Ĺ���ʽ����
//set�洢keyֵ��map�洢key-value

/*
set�е�keyֵ��Ψһ�ģ��Ҳ��ܱ��޸�
�ײ�ʹ��������������ʵ�֣�����������Եõ���������

template<class T, class Compare = less<T>, class Alloc = allocator<T>>
class set
{
};
set�ĵ�һ��ģ�����ʵ������<value, value>�ļ�ֵ��	


//set��ʹ��
int main()
{
	set<int> s;
	s.insert(1);
	s.insert(2);
	s.insert(3);
	s.insert(4);
	s.insert(1);
	s.insert(2);
	s.insert(3);
	//�ظ���Ԫ�ػ����ʧ��
	for (auto& e : s)
	{
		cout << e << " ";
	}
	cout << endl;

	//ʹ�÷������������
	auto rit = s.rbegin();
	while (rit != s.rend())
	{
		cout << *rit << " ";
		rit++;
	}
	cout << endl;

	//�����С
	cout << s.size() << endl;
	
	//�п�
	cout << s.empty() << endl;

	//ɾ��
	auto it = s.begin();
	s.erase(it);		
	for (auto& e : s)
	{
		cout << e << " ";
	}
	cout << endl;

	//find:����ֵΪkey�ĵ�����
	auto ret = s.find(2);
	s.erase(ret);
	for (auto& e : s)
	{
		cout << e << " ";
	}
	cout << endl;
	//count:����keyֵ�ĸ���
	cout << s.count(1) << endl;
	cout << s.count(4) << endl;
	return 0;
}*/


//map

/*
map�е�Ԫ����K-V��,��һ��ģ���������װ��value_type, �ֱ��ض����pair<const k, v>
��key��������
map֧��[]��������ͨ��keyֵ�Ϳ����ҵ�value
*/

int main()
{
	map<string, string> m;
	m.insert(make_pair("zhangsan", "1245"));  //ʹ��make_pair����
	m.insert(make_pair("lisi", "1246"));
	m.insert(make_pair("wangwu", "2356"));
	m.insert(make_pair("fengjinlong", "123456"));
	m.insert(make_pair("fengjinlong", "23456"));

	for (auto& e : m)
	{
		cout << e.second << " ";
	}
	cout << endl;

	m["shabi"] = "282828";	//[]�������ж�����ܣ�
							//����Ԫ�أ��������ڣ��Ͳ��룻�����ڣ��ͷ��ظ�key��Ӧ��value������
	//���Կ�����[]������ʵ�����ݵĲ���
	return 0;
}