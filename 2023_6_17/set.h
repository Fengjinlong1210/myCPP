#pragma once
#include <iostream>
#include "RBTree.h"
using namespace std;
namespace Fjl
{
	template<class K>
	class set
	{
	public:
		struct KeyOfValue
		{
			const K& operator()(const K& k)
			{
				return kv.first;
			}
		};

		bool insert(const K& k)
		{
			return _t.insert(kv);
		}


	private:
		RBTree<K, pair<const K, K>, KeyOfValue> _t;
	};
}