#pragma once
#include <iostream>
#include "RBTree.h"
using namespace std;
namespace Fjl
{
	template<class K, class V>
	class map
	{
	public:
		struct KeyOfValue
		{
			const K& operator()(const pair<const K, V>& kv)
			{
				return kv.first;
			}
		};

		bool insert(const pair<const K, V>& kv)
		{
			return _t.insert(kv);
		}

		void inOrder()
		{
			_t.InOrder();
		}
	private:
		RBTree<K, pair<const K, V>, KeyOfValue> _t;
	};
}