#pragma once
#include "RBTree.h"

using namespace std;

namespace Fjl
{
	template<class K>
	class set
	{
		struct KeyOfValue
		{
			const K& operator()(const K& key)
			{
				return key;
			}
		};
	public:
		typedef typename RBTree<K, K, KeyOfValue>::const_iterator iterator;
		typedef typename RBTree<K, K, KeyOfValue>::const_iterator const_iterator;
		
		pair<iterator, bool> insert(const K& key)
		{
			return _t.insert(key);
			//set在插入返回pair时，会通过指针构造普通迭代器，但是set的迭代器是const类型
			//由普通迭代器转换成const迭代器，需要一个构造函数来支持隐式类型转换
		}

		void SetInOrder()
		{
			_t.SetInOrder();
		}

		iterator begin() const
		{
			return _t.begin();
		}

		iterator end() const
		{
			return _t.end();
		}
	private:
		RBTree<K, K, KeyOfValue> _t;
	};
}