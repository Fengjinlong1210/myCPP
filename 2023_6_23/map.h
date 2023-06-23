#pragma once
#include <iostream>
#include "RBTree.h"
using namespace std;
namespace Fjl
{
	template<class K, class V>
	class map
	{
		struct KeyOfValue
		{
			const K& operator()(const pair<const K, V>& kv)
			{
				return kv.first;
			}
		};

	public:
		typedef typename RBTree<K, pair<const K, V>, KeyOfValue>::iterator iterator;

		iterator begin()
		{
			return _t.begin();
		}

		iterator end()
		{
			return _t.end();
		}

		V& operator[](const K& key)
		{
			pair<iterator, bool> ret = _t.insert(make_pair(key, V()));
			return ret.first->second;
		}

		pair<iterator, bool> insert(const pair<const K, V>& kv)
		{
			return _t.insert(kv);
		}

		void MapInOrder()
		{
			_t.MapInOrder();
		}

		void isBalance()
		{
			if (_t.isBalance())
			{
				cout << "红黑树结构正确" << endl;
			}
			else
			{
				cout << "红黑树结构出现错误" << endl;
			}
		}
	private:
		RBTree<K, pair<const K, V>, KeyOfValue> _t;
	};

}