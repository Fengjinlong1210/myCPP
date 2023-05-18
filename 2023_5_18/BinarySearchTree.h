#pragma once
#include <iostream>
using namespace std;

template<class K>
struct BSTreeNode
{
	BSTreeNode(const K& key = K())
		:_left(nullptr), _right(nullptr), _key(key)
	{}

	BSTreeNode<K>* _left;
	BSTreeNode<K>* _right;
	K _key;
};

template<class K>
class BSTree
{
	typedef BSTreeNode<K> Node;
public:
	BSTree()
		:_root(nullptr)
	{}

	//����Ԫ��
	bool Insert(const K& val = K())
	{
		if (_root == nullptr)
		{
			_root = new Node(val);
		}
		else
		{
			Node* cur = _root;
			Node* parent = cur;
			while (cur)
			{
				parent = cur;
				if (cur->_key > val)
				{
					//������
					cur = cur->_left;
				}
				else if (cur->_key < val)
				{
					//������
					cur = cur->_right;
				}
				else
				{
					return false;
				}
			}
			//��ѭ��ʱ��cur�ߵ����������²�
			Node* newnode = new Node(val);
			if (parent->_key > val)
			{
				//������
				parent->_left = newnode;
			}
			else
			{
				//������
				parent->_right = newnode;
			}
		}
		return true;
	}

	bool Find(const K& val)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key > val)
			{
				cur = cur->_left;
			}
			else if (cur->_key < val)
			{
				cur = cur->_right;
			}
			else
			{
				//���
				return true;
			}
		}
		return false;
	}

	bool Erase(const K& val)
	{
		//���ҵ��ýڵ��λ��
		if (_root->_left == nullptr && _root->_right == nullptr)
		{
			delete _root;
			_root = nullptr;
			return true;
		}
		Node* cur = _root;
		Node* parent = cur;
		while (cur->_key != val)
		{
			if (cur->_key > val)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				parent = cur;
				cur = cur->_right;
			}
		}
		//��ѭ��ʱ��cur�ҵ���Ҫ��ɾ���Ľ��
		if (cur->_left == nullptr)
		{
			//��Ϊ��
			if (parent->_left == cur)
			{
				parent->_left = cur->_right;
			}
			else
			{
				parent->_right = cur->_right;
			}
			delete cur;
		}
		else if (cur->_right == nullptr)
		{
			//��Ϊ��
			if (parent->_left == cur)
			{
				parent->_left = cur->_left;
			}
			else
			{
				parent->_right = cur->_left;
			}
			delete cur;

		}
		else
		{
			//�ýڵ��������ӽ��
			//�ҵ��ýڵ�������������ڵ���ȡ�����λ��
			Node* minRight = cur->_right;
			Node* pminRight = cur;
			while (minRight->_left != nullptr)
			{
				pminRight = minRight;
				minRight = minRight->_left;
			}
			if (pminRight->_left == minRight)
			{
				pminRight->_left = minRight->_right;
			}
			else
			{
				pminRight->_right = minRight->_right;
			}
			cur->_key = minRight->_key;

			delete minRight;
		}
		return true;
	}

	void InOrder()
	{
		if (_root == nullptr)
			cout << "NULL" << endl;
		_InOrder(_root);
		cout << endl;
	}

	void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		//�������
		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}

private:
	Node* _root;
};