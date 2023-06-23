#pragma once
#include <iostream>

using namespace std;

enum Colour
{
	Red,
	Black
};

template<class Value>
struct RBTreeNode
{
	typedef RBTreeNode<Value> Node;

	RBTreeNode<Value>* _parent;
	RBTreeNode<Value>* _right;
	RBTreeNode<Value>* _left;
	Value _data;
	Colour _col;

	RBTreeNode(Value data)
		:_parent(nullptr),
		_right(nullptr),
		_left(nullptr),
		_data(data),
		_col(Red)
	{}
};

template<class Value, class Ref, class Ptr>
struct __RBTree_iterator
{
	typedef RBTreeNode<Value> Node;
	typedef __RBTree_iterator<Value, Ref, Ptr> self;
	typedef __RBTree_iterator<Value, Value&, Value*> iterator;
	typedef __RBTree_iterator<Value, const Value&, const Value*> const_iterator;

	Node* _node;

	__RBTree_iterator(Node* node)
		:_node(node)
	{}
	
	//这个构造具有两个作用：
	//1.当迭代器类型是普通迭代器时，该函数就是构造函数
	//2.当迭代器类型时const迭代器时，该函数可以用普通迭代器构造const迭代器
	__RBTree_iterator(const iterator& it)
		:_node(it._node)
	{}

	Ref operator*()
	{
		return _node->_data;
	}

	Ptr operator->()
	{
		return &_node->_data;
	}

	bool operator!=(const self& it)
	{
		return _node != it._node;
	}

	self& operator++()
	{
		increment();
		return *this;
	}

	self& operator--()
	{
		decrement();
		return *this;
	}

	void increment()
	{
		//增加迭代器需要找到右子树的最左节点
		//如果节点右不为空，就要找到最左节点
		if (_node->_right)
		{
			Node* Rmin = _node->_right;
			while (Rmin->_left)
			{
				Rmin = Rmin->_left;
			}
			_node = Rmin;
		}
		else
		{
			//右为空，向上找到下一个节点
			//直到当前节点是父亲结点的左结点
			Node* cur = _node;
			Node* parent = _node->_parent;
			while (parent && cur != parent->_left)
			{
				cur = parent;
				parent = cur->_parent;
			}
			_node = parent;
		}
	}

	void decrement()
	{
		//递减迭代器
		//找到前一个结点
		//如果左不为空，就找左子树的最右结点
		if (_node->_left)
		{
			Node* Lmax = _node->_left;
			while (Lmax->_right)
			{
				Lmax = Lmax->_right;
			}
		}
		else
		{
			//如果左为空，向上查找
			//找到当前节点是父亲结点的右节点
			Node* cur = _node;
			Node* parent = _node->_parent;
			while (parent && cur != parent->_right)
			{
				cur = parent;
				parent = cur->_parent;
			}
			_node = parent;
		}
	}

};

template<class K, class Value, class KeyOfValue>
class RBTree
{
	typedef RBTreeNode<Value> Node;

public:
	typedef __RBTree_iterator<Value, Value&, Value*> iterator;
	typedef __RBTree_iterator<Value, const Value&, const Value*> const_iterator;

	~RBTree()
	{
		_destroy(_root);
	}

	pair<iterator, bool> insert(const Value& data)
	{
		//红黑树插入
		//按照搜索二叉树的方式找到插入的位置
		Node* cur = _root;
		Node* parent = nullptr;
		if (_root == nullptr)
		{
			_root = new Node(data);
			_root->_col = Black;
			return make_pair(iterator(_root), true);
		}
		while (cur)
		{
			if (kov(cur->_data) > kov(data))
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (kov(cur->_data) < kov(data))
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return make_pair(iterator(cur), false);
			}
		}
		//出循环时，cur位置就是要插入的结点位置
		cur = new Node(data);
		if (kov(data) < kov(parent->_data))
		{
			parent->_left = cur;
		}
		else
		{
			parent->_right = cur;
		}
		cur->_parent = parent;
		//调整位置
		while (parent && parent->_col == Red)
		{
			Node* grandp = parent->_parent;
			//1.如果p在g的左
			if (parent && parent == grandp->_left)
			{
				Node* uncle = grandp->_right;
				//1.1 如果u存在且为红
				if (uncle && uncle->_col == Red)
				{
					//把u和p改为黑，把g改为红，然后继续向上调整
					uncle->_col = parent->_col = Black;
					grandp->_col = Red;

					cur = grandp;
					parent = cur->_parent;
				}
				//1.2 如果u存在且为黑 或者 u直接不存在
				else
				{
					//1.2.1 左左
					if (cur == parent->_left)
					{
						//		g
						//	  p   u
						//  c
						//对g左旋， 把p改黑，g改红
						rotateL(grandp);
						parent->_col = Black;
						grandp->_col = Red;
					}
					//1.2.2 左右
					else
					{
						//		g
						//	  p   u
						//     c
						//对p先左旋，然后对g右旋，把c改黑，g改红
						rotateL(parent);
						rotateR(grandp);
						cur->_col = Black;
						grandp->_col = Red;
					}
				}
			}
			//2.p在g的右
			else
			{
				Node* uncle = grandp->_left;
				//2.1 如果u存在且为红
				if (uncle && uncle->_col == Red)
				{
					//把p和u改为黑，g改为红，向上调整
					parent->_col = uncle->_col = Black;
					grandp->_col = Red;

					cur = grandp;
					parent = cur->_parent;
				}
				//2.2 如果u存在且为黑 或者 u直接不存在
				else
				{
					//2.2.1右右
					if (cur == parent->_right)
					{
						//		g
						//	 u	   p
						//           c
						//对g左旋，改p为黑，g为红
						rotateL(grandp);
						parent->_col = Black;
						grandp->_col = Red;
					}
					//2.2.2 右左
					else
					{
						//		g
						//	 u	    p
						//		  c
						//对p右旋，对g左旋，改c为黑，g为红
						rotateR(parent);
						rotateL(grandp);
						cur->_col = Black;
						grandp->_col = Red;
					}

				}
			}
		}
		_root->_col = Black;
		return make_pair(iterator(cur), true);
	}

	iterator begin()
	{
		Node* cur = _root;
		while (cur->_left)
		{
			cur = cur->_left;
		}
		return iterator(cur);
	}

	iterator end()
	{
		return iterator(nullptr);
	}

	const_iterator begin() const
	{
		Node* cur = _root;
		while (cur->_left)
		{
			cur = cur->_left;
		}
		return const_iterator(cur);
	}

	const_iterator end() const
	{
		return const_iterator(nullptr);
	}

	void MapInOrder()
	{
		_MapInOrder(_root);
		cout << endl;
	}

	void SetInOrder()
	{
		_SetInOrder(_root);
		cout << endl;
	}

	bool isBalance()
	{
		if (_root->_col == Red)
		{
			cout << "根节点颜色是红色" << endl;
			return false;
		}
		int mark = 0;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_col == Black)
			{
				++mark;
			}
			cur = cur->_left;
		}

		return _check(_root, 0, mark);
	}

private:
	bool _check(Node* root, int blacknum, int mark)
	{
		if (root == nullptr)
		{
			if (blacknum != mark)
			{
				cout << "路径黑色节点不相等" << endl;
				return false;
			}
			return true;
		}
		if (root->_col == Black)
		{
			++blacknum;
		}

		if (root->_col == Red
			&& root->_parent
			&& root->_parent->_col == Red)
		{
			cout << "存在连续的红色结点" << endl;
		}

		return _check(root->_left, blacknum, mark)
			&& _check(root->_right, blacknum, mark);
	}

	void _destroy(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}

		_destroy(root->_left);
		_destroy(root->_right);
		delete root;
	}

	void _MapInOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}

		_MapInOrder(root->_left);
		cout << root->_data.first << ":" << root->_data.second << endl;
		_MapInOrder(root->_right);
	}

	void _SetInOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}

		_SetInOrder(root->_left);
		cout << root->_data << " ";
		_SetInOrder(root->_right);
	}

	void rotateR(Node* parent)
	{
		Node* childL = parent->_left;
		Node* childLR = childL->_right;
		Node* grandp = parent->_parent;


		parent->_left = childLR;
		if (childLR)
		{
			childLR->_parent = parent;
		}

		childL->_right = parent;
		parent->_parent = childL;

		if (parent == _root)
		{
			childL->_parent = nullptr;

			_root = childL;
		}
		else
		{
			childL->_parent = grandp;
			if (grandp->_left == parent)
			{
				grandp->_left = childL;
			}
			else
			{
				grandp->_right = childL;
			}
		}
	}

	void rotateL(Node* parent)
	{
		Node* childR = parent->_right;
		Node* childRL = childR->_left;
		Node* grandp = parent->_parent;


		parent->_right = childRL;
		if (childRL)
		{
			childRL->_parent = parent;
		}

		childR->_left = parent;
		parent->_parent = childR;

		if (parent == _root)
		{
			childR->_parent = nullptr;

			_root = childR;
		}
		else
		{
			childR->_parent = grandp;
			if (grandp->_left == parent)
			{
				grandp->_left = childR;
			}
			else
			{
				grandp->_right = childR;
			}
		}
	}

private:
	Node* _root = nullptr;
	KeyOfValue kov;
};
