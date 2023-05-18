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

	//插入元素
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
					//向左走
					cur = cur->_left;
				}
				else if (cur->_key < val)
				{
					//向右走
					cur = cur->_right;
				}
				else
				{
					return false;
				}
			}
			//出循环时，cur走到了树的最下层
			Node* newnode = new Node(val);
			if (parent->_key > val)
			{
				//左子树
				parent->_left = newnode;
			}
			else
			{
				//右子树
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
				//相等
				return true;
			}
		}
		return false;
	}

	bool Erase(const K& val)
	{
		//先找到该节点的位置
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
		//出循环时，cur找到了要被删除的结点
		if (cur->_left == nullptr)
		{
			//左为空
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
			//右为空
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
			//该节点有两个子结点
			//找到该节点右子树的最左节点来取代这个位置
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
		//中序遍历
		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}

private:
	Node* _root;
};