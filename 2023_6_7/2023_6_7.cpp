#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <map>
#include <set>
#include <string>
using namespace std;

//map和set
//属于树形结构的关联式容器
//set存储key值，map存储key-value

/*
set中的key值是唯一的，且不能被修改
底层使用搜索二叉树来实现，中序遍历可以得到有序序列

template<class T, class Compare = less<T>, class Alloc = allocator<T>>
class set
{
};
set的第一个模板参数实际上是<value, value>的键值对	


//set的使用
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
	//重复的元素会插入失败
	for (auto& e : s)
	{
		cout << e << " ";
	}
	cout << endl;

	//使用反向迭代器遍历
	auto rit = s.rbegin();
	while (rit != s.rend())
	{
		cout << *rit << " ";
		rit++;
	}
	cout << endl;

	//输出大小
	cout << s.size() << endl;
	
	//判空
	cout << s.empty() << endl;

	//删除
	auto it = s.begin();
	s.erase(it);		
	for (auto& e : s)
	{
		cout << e << " ";
	}
	cout << endl;

	//find:返回值为key的迭代器
	auto ret = s.find(2);
	s.erase(ret);
	for (auto& e : s)
	{
		cout << e << " ";
	}
	cout << endl;
	//count:返回key值的个数
	cout << s.count(1) << endl;
	cout << s.count(4) << endl;
	return 0;
}*/


//map

/*
map中的元素是K-V对,第一个模板参数被封装成value_type, 又被重定义成pair<const k, v>
对key进行排序
map支持[]操作符，通过key值就可以找到value
*/

int main()
{
	map<string, string> m;
	m.insert(make_pair("zhangsan", "1245"));  //使用make_pair插入
	m.insert(make_pair("lisi", "1246"));
	m.insert(make_pair("wangwu", "2356"));
	m.insert(make_pair("fengjinlong", "123456"));
	m.insert(make_pair("fengjinlong", "23456"));

	for (auto& e : m)
	{
		cout << e.second << " ";
	}
	cout << endl;

	m["shabi"] = "282828";	//[]操作符有多个功能：
							//查找元素，若不存在，就插入；若存在，就返回该key对应的value的引用
	//所以可以用[]操作符实现数据的插入
	return 0;
}