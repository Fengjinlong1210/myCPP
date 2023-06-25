#pragma once
#include <iostream>
#include <vector>
using namespace std;

template<class T>
struct HashTableNode
{
	HashTableNode<T>* _next;
	T _data;

	HashTableNode(const T& data)
		:_next(nullptr)
		, _data(data)
	{}
};

static const int __stl_num_primes = 28;
static const unsigned long __stl_prime_list[50] =
{
  53,         97,         193,       389,       769,
  1543,       3079,       6151,      12289,     24593,
  49157,      98317,      196613,    393241,    786433,
  1572869,    3145739,    6291469,   12582917,  25165843,
  50331653,   100663319,  201326611, 402653189, 805306457,
  1610612741, 3221225473, 4294967291
};

template<class K>
struct HashFunc
{
	size_t operator()(const K& key)
	{
		return key;
	}
};

//ģ����ػ�, ����keyΪstring�����
//����һ��string,����string����������key
template<>
struct HashFunc<string>
{
	size_t operator()(const string& str)
	{
		size_t size = 0;
		for (auto ch : str)
		{
			size += ch;
			size *= 31;
		}
		return size;
	}
};

//Ϊ�˵�������ʹ��HashTable�еĳ�Ա,��Ҫǰ������
template<class K, class T, class KeyOfValue, class HF>
class HashTable;

//HF���ģ��������ܵķº�����������string����ת����size_t
template<class K, class T, class Ref, class Ptr, class KeyOfValue, class HF>
struct __HashTable_iterator
{
	typedef HashTableNode<T> Node;
	typedef HashTable<K, T, KeyOfValue, HF> HT;
	typedef __HashTable_iterator<K, T, Ref, Ptr, KeyOfValue, HF> self;

	Node* _node;
	const HT* _pht;

	__HashTable_iterator(Node* node, const HT* pht)
		:_node(node)
		, _pht(pht)
	{}

	Ref operator*()
	{
		return _node->_data;
	}

	Ptr operator->()
	{
		return &(_node->_data);
	}

	bool operator!=(const self& it)
	{
		return _node != it._node;
	}

	self& operator++()
	{
		Node* cur = _node;
		if (cur->_next)
		{
			_node = _node->_next;
		}
		else
		{
			KeyOfValue kov;
			HF hashfunc;
			//����ҵ���Ϊ�յĽ��
			size_t hashaddr = hashfunc((kov(_node->_data))) % _pht->_ht.size();
			++hashaddr;
			//��kov�õ���keyת����size_t
			while (hashaddr < _pht->_ht.size())
			{
				if (_pht->_ht[hashaddr])
				{
					_node = _pht->_ht[hashaddr];
					break;
				}
				else
				{
					++hashaddr;
				}
			}

			//��ѭ��ʱ, �����û���ҵ���һ��λ��, �ͷ��ؿ�
			//�����������������
			if (hashaddr == _pht->_ht.size())
			{
				_node = nullptr;
			}
		}

		return *this;
	}
};

//template<class K, class V>
template<class K, class T, class KeyOfValue, class HF>
class HashTable
{
public:
	//����Ҫ����ģ��
	template<class K, class T, class Ref, class Ptr, class KeyOfValue, class HF>
	friend struct __HashTable_iterator;

	typedef HashTableNode<T> Node;
	typedef __HashTable_iterator<K, T, T&, T*, KeyOfValue, HF> iterator;
	typedef __HashTable_iterator<K, T, const T&, const T*, KeyOfValue, HF> const_iterator;

	~HashTable()	
	{
		for (auto& cur : _ht)
		{
			Node* next = nullptr;
			while (cur)
			{
				next = cur->_next;
				delete cur;
				cur = next;
			}
			cur = nullptr;
		}
	}

	pair<iterator, bool> insert(const T& data)
	{
		KeyOfValue kov;
		
		iterator ret = find(kov(data));
		if (ret != end())
		{
			return make_pair(ret, false);
		}
		//�������
		check_capacity();
		size_t hashaddr = get_addr(kov(data));

		Node* newnode = new Node(data);
		newnode->_next = _ht[hashaddr];
		_ht[hashaddr] = newnode;

		++_size;
		return make_pair(iterator(newnode, this), true);
	}

	iterator find(const K& key)
	{
		KeyOfValue kov;
		if (_size == 0)
		{
			return iterator(nullptr, this);
		}
		size_t hashaddr = get_addr(key);

		Node* cur = _ht[hashaddr];
		while (cur)
		{
			if (kov(cur->_data) == key)
			{
				return iterator(cur, this);
			}
			cur = cur->_next;
		}
		return iterator(nullptr, this);
	}

	bool erase(const K& key)
	{
		KeyOfValue kov;
		if (_size == 0)
		{
			return false;
		}
		size_t hashaddr = get_addr(key);
		Node* prev = nullptr;
		Node* cur = _ht[hashaddr];

		while (cur)
		{
			if (kov(cur->_data.first) == key)
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

	iterator begin()
	{
		//���ҵ���һ����Ϊ�յ�Ͱ
		size_t hashaddr = 0;
		while (hashaddr < _ht.size())
		{
			if (_ht[hashaddr])
			{
				return iterator(_ht[hashaddr], this);
			}
			++hashaddr;
		}
		return iterator(nullptr, this);
	}

	iterator end()
	{
		return iterator(nullptr, this);
	}

	const_iterator begin() const
	{
		//���ҵ���һ����Ϊ�յ�Ͱ
		size_t hashaddr = 0;
		while (hashaddr < _ht.size())
		{
			if (_ht[hashaddr])
			{
				return const_iterator(_ht[hashaddr], this);
			}
			++hashaddr;
		}
		return const_iterator(nullptr, this);
	}

	const_iterator end() const
	{
		return const_iterator(nullptr, this);
	}

private:
	size_t get_addr(const K& key)
	{
		HF hashfunc;
		return hashfunc(key) % _ht.capacity();
	}

	void check_capacity()
	{
		//��δ��ʼ��ʱ,_size == _ht.size(), �Ὺ��һ��newsize
		if (_size == _ht.size())
		{
			//����
			//size_t newsize = _ht.size() == 0 ? 10 : _ht.capacity() * 2;
			size_t newsize = get_next_size(_ht.size());
			HashTable<K, T, KeyOfValue, HF> _newht;
			_newht._ht.resize(newsize, nullptr);
			_newht._size = _size;
			for (auto& cur : _ht)
			{
				//����vector���Ѿ�����ȫ��insert���±�
				while (cur)
				{
					_newht.insert(cur->_data);
					cur = cur->_next;
				}
			}
			_ht.swap(_newht._ht);
		}
	}

	size_t get_next_size(size_t size)
	{
		size_t i = 0;
		for (i = 0; i < __stl_num_primes; ++i)
		{
			if (size < __stl_prime_list[i])
			{
				return __stl_prime_list[i];
			}
		}
		return __stl_prime_list[i];
	}

private:
	vector<Node*> _ht;
	size_t _size = 0;
};