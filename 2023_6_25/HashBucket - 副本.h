#pragma once
#include <iostream>
#include <vector>
using namespace std;

template<class K, class V>
struct HashTableNode
{
	HashTableNode<K, V>* _next;
	pair<K, V> _data;

	HashTableNode(const pair<K, V>& data)
		:_next(nullptr)
		, _data(data)
	{}
};

template<class K, class V>
class HashTable
{
	typedef HashTableNode<K, V> Node;
public:
	bool insert(const pair<K, V>& data)
	{
		//检查容量
		check_capacity();
		size_t hashaddr = get_addr(data.first);

		Node* newnode = new Node(data);
		newnode->_next = _ht[hashaddr];
		_ht[hashaddr] = newnode;

		++_size;
		return true;
	}

	HashTableNode<K, V>* find(const K& key)
	{
		if (_size == 0)
		{
			return nullptr;
		}
		size_t hashaddr = get_addr(key);

		Node* cur = _ht[hashaddr];
		while (cur)
		{
			if (cur->_data.first == key)
			{
				return cur;
			}
			cur = cur->_next;
		}
		return nullptr;
	}

	bool erase(const K& key)
	{
		if (_size == 0)
		{
			return false;
		}
		size_t hashaddr = get_addr(key);
		Node* prev = nullptr;
		Node* cur = _ht[hashaddr];

		while (cur)
		{
			if (cur->_data.first == key)
			{
				if (cur == _ht[hashaddr] && prev == nullptr)
				{
					_ht[hashaddr] = cur->_next;
				}
				else
				{
					prev->_next = cur->_next;
				}
				delete cur;
				--_size;
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
		return key % _ht.capacity();
	}

	void check_capacity()
	{
		if (_size == 0
			|| _size == _ht.capacity())
		{
			//扩容
			size_t newsize = _ht.size() == 0 ? 10 : _ht.capacity() * 2;
			HashTable<K, V> _newht;
			_newht._ht.resize(newsize);
			_newht._size = _size;
			for (auto& cur : _ht)
			{
				//遍历vector，把旧数据全部insert到新表
				while (cur)
				{
					_newht.insert(cur->_data);
					cur = cur->_next;
				}
			}
			_ht.swap(_newht._ht);
		}
	}
private:
	vector<Node*> _ht;
	size_t _size = 0;
};