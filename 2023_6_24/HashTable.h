#pragma once
#include <iostream>
#include <vector>
using namespace std;

namespace ht
{
	enum status
	{
		EMPTY,
		EXIST,
		DELETE
	};

	template<class K, class V>
	struct HashTableNode
	{
		pair<K, V> _val;
		status _sts;

		HashTableNode()
			:_sts(EMPTY)
		{}
	};

	template<class K, class V>
	class HashTable
	{
	public:
		bool insert(const pair<K, V>& kv)
		{
			check_capacity();
			size_t hashaddr = get_addr(kv.first);

			int index = hashaddr;

			while (_ht[index]._sts != EMPTY)
			{
				//线性探测
				if (_ht[hashaddr]._val.first == kv.first)
				{
					return false;
				}

				++index;
				index %= _ht.size();
			}
			_ht[index]._val = kv;
			_ht[index]._sts = EXIST;
			_size++;
			return true;
		}



		void check_capacity()
		{
			if (_ht.size() == 0
				|| ((_size * 10) / _ht.capacity()) >= 7)
			{
				//当ht为空或达到负载因子时扩容
				size_t newsize = (_ht.size() == 0) ? 10 : 2 * _ht.size();

				HashTable<K, V> _newht;
				_newht._ht.resize(newsize);

				for (auto& e : _ht)
				{
					if (e._sts == EXIST)
					{
						_newht.insert(e._val);
					}

				}
				_ht.swap(_newht._ht);
			}
		}

		HashTableNode<K, V>* find(const K& key)
		{
			if (_size == 0)
			{
				return nullptr;
			}
			
			size_t hashaddr = get_addr(key);
			size_t index = hashaddr;
			while (_ht[index]._sts != EMPTY)
			{
				if (_ht[index]._val.first == key && _ht[index]._sts == EXIST)
				{
					return &_ht[index];
				}
				++index;
				index %= _ht.size();

				if (index == hashaddr)
				{
					break;
				}
			}
			return nullptr;
		}

		bool erase(const K& key)
		{
			auto ret = find(key);
			if (ret)
			{
				ret->_sts = DELETE;
				--_size;
				return true;
			}
			else
			{
				return false;
			}

		}
	private:
		size_t get_addr(const K& key)
		{
			return key % _ht.capacity();
		}

	private:
		vector<HashTableNode<K, V>> _ht;
		size_t _size;
	};
}

namespace hb
{
	template<class K, class V>
	struct HashBucketNode
	{
		HashBucketNode<K, V>* _next;
		pair<K, V> _kv;

		HashBucketNode(const pair<K, V>& kv)
			:_next(nullptr)
			, _kv(kv)
		{}
	};


	template<class K, class V>
	class HashBucket
	{
		typedef HashBucketNode<K, V> Node;
	public:
		bool insert(const pair<K, V>& kv)
		{
			if (find(kv.first))
			{
				return false;
			}
			check_capacity();
			size_t hashaddr = get_addr(kv.first);

			Node* newnode = new Node(kv);
			newnode->_next = _hb[hashaddr];
			_hb[hashaddr] = newnode;
			++_size;
			return true;
		}

		HashBucketNode<K, V>* find(const K& key)
		{
			if (_size == 0)
			{
				return nullptr;
			}
			size_t hashaddr = get_addr(key);
			
			Node* cur = _hb[hashaddr];
			while (cur)
			{
				if (cur->_kv.first == key)
				{
					return cur;
				}
				cur = cur->_next;
			}
			return nullptr;
		}

		void check_capacity()
		{
			if (_hb.size() == 0 || _hb.capacity() == _size)
			{
				size_t newsize = _hb.size() == 0 ? 10 : _hb.capacity() * 2;

				HashBucket<K, V> _newhb;
				_newhb._hb.resize(newsize);
				//扩容后把以前的结点全部重新插入到新表
				for (auto& cur : _hb)
				{
					//把以cur为第一个结点的一串单链表全部insert到新表
					while (cur)
					{
						_newhb.insert(cur->_kv);
						cur = cur->_next;
					}
				}

				_hb.swap(_newhb._hb);
			}
		}

		bool erase(const K& key)
		{
			if (_size == 0)
			{
				return false;
			}
			size_t hashaddr = get_addr(key);
			Node* prev = nullptr;
			Node* cur = _hb[hashaddr];
			while (cur)
			{
				if (cur->_kv.first == key)
				{
					if (prev == nullptr)
					{
						//cur是链表的第一个结点
						_hb[hashaddr] = cur->_next;
					}
					else
					{
						prev->_next = cur->_next;
					}
					delete cur;
					return true;
				}
				else
				{
					prev = cur;
					cur = cur->_next;
				}
			}
			return false;
		}

	private:
		size_t get_addr(const K& key)
		{
			return key % _hb.capacity();
		}
	private:
		vector<Node*> _hb;//指针数组，存放单链表的第一个结点
		size_t _size = 0;
	};
}