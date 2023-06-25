#pragma once
#include "HashBucket.h"

namespace Fjl
{
	template<class K, class V, class Hash = HashFunc<K>>
	class unordered_map
	{
		struct KeyOfT
		{
			const K& operator()(const pair<K, V>& kv)
			{
				return kv.first;
			}
		};

	public:
		typedef typename HashTable<K, pair<K, V>, KeyOfT, Hash>::iterator iterator;
		typedef typename HashTable<K, pair<K, V>, KeyOfT, Hash>::const_iterator const_iterator;

		pair<iterator, bool> insert(const pair<K, V>& kv)
		{
			return _ht.insert(kv);
		}

		iterator find(const K& key)
		{
			return _ht.find(key);
		}

		bool erase(const K& key)
		{
			return _ht.erase(key);
		}

		V& operator[](const K& key)
		{
			pair<iterator, bool> ret = insert(make_pair(key, V()));
			return ret.first->second;
		}

		iterator begin()
		{
			return _ht.begin();
		}

		iterator end()
		{
			return _ht.end();
		}

		const_iterator begin() const
		{
			return _ht.begin();
		}

		const_iterator end() const
		{
			return _ht.end();
		}
	private:
		HashTable<K, pair<K, V>, KeyOfT, Hash> _ht;
	};
}