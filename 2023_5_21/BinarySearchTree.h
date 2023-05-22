#pragma once
#include <iostream>
#include <algorithm>
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

	BSTree(const BSTree<K>& t)
	{
		_root = _copy(t._root);
	}

	BSTree<K>& operator=(const BSTree<K> t)
	{
		swap(_root, t._root);
		return *this;
	}

	~BSTree()
	{
		Destroy(_root);
	}

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

	bool InsertR(const K& val)
	{
		return _InsertR(_root, val);
	}

	bool FindR(const K& val)
	{
		return _FindR(_root, val);
	}

	bool EraseR(const K& val)
	{
		return _EraseR(_root, val);
	}

protected:
	bool _EraseR(Node*& root, const K& val)
	{
		if (root == nullptr)
		{
			return false;
		}

		if (root->_key > val)
		{
			return _EraseR(root->_left, val);
		}
		else if (root->_key < val)
		{
			return _EraseR(root->_right, val);
		}
		else
		{
			Node* del = root;
			//���
			if (root->_left == nullptr)
			{
				root = root->_right;
			}
			else if (root->_right == nullptr)
			{
				root = root->_left;
			}
			else
			{
				//�ҵ������ϵ�����ڵ�������ϵ����ҽ��
				Node* maxLeft = root->_left;
				while (maxLeft->_right)
				{
					maxLeft = maxLeft->_right;
				}

				swap(root->_key, maxLeft->_key);

				return _EraseR(root->_left, val);
			}

			delete del;
			return true;
		}
	}

	Node* _copy(Node*& root)
	{
		if (root == nullptr)
		{
			return nullptr;
		}

		Node* newnode = new Node(root->_key);
		newnode->_left = _copy(root->_left);
		newnode->_right = _copy(root->_right);
		
		return newnode;
	}

	void Destroy(Node*& root)
	{
		if (root == nullptr)
		{
			return;
		}
		//����ɾ��
		Destroy(root->_left);
		Destroy(root->_right);

		delete root;
		root = nullptr;
	}

	bool _FindR(Node* root, const K& val)
	{
		if (root == nullptr)
		{
			return false;
		}

		if (root->_key > val)
		{
			return _FindR(root->_left, val);
		}
		else if (root->_key < val)
		{
			return _FindR(root->_right, val);
		}
		else
		{
			return true;
		}
	}

	bool _InsertR(Node*& root, const K& val)
	{
		if (root == nullptr)
		{
			root = new Node(val);
			return true;
		}

		if (root->_key > val)
		{
			return _InsertR(root->_left, val);
		}
		else if (root->_key < val)
		{
			return _InsertR(root->_right, val);
		}
		else
		{
			return false;
		}
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

	Node* _root;
};