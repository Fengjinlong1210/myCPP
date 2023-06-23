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
			//set�ڲ��뷵��pairʱ����ͨ��ָ�빹����ͨ������������set�ĵ�������const����
			//����ͨ������ת����const����������Ҫһ�����캯����֧����ʽ����ת��
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