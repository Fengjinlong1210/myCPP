#pragma once
#include <iostream>
using namespace std;
enum Colour
{
	Red,
	Black
};

template<class ValueType>
struct RBTreeNode
{
	RBTreeNode<ValueType>* _parent;
	RBTreeNode<ValueType>* _left;
	RBTreeNode<ValueType>* _right;
	ValueType _data;
	Colour _col;

	RBTreeNode(ValueType data)
		:_parent(nullptr),
		_left(nullptr),
		_right(nullptr),
		_data(data),
		_col(Red)
	{}
};

template<class K, class ValueType, class KeyOfValue>
class RBTree
{
	typedef RBTreeNode<ValueType> Node;
public:
	~RBTree()
	{
		_DestroyTree(_root);
	}

	Node* find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (kov(cur->_data) > key)
			{
				cur = cur->_left;
			}
			else if (kov(cur->_data) < key)
			{
				cur = cur->_right;
			}
			else
			{
				return cur;
			}
		}
		return nullptr;
	}

	bool insert(const ValueType& data)
	{
		//红黑树的插入：
		//1.按搜索二叉树的规则插入结点
		//2.按照红黑树的规则进行旋转和改变颜色

		//插入
		Node* cur = _root;
		Node* parent = nullptr;
		if (_root == nullptr)
		{
			_root = new Node(data);
			_root->_col = Black;
			return true;
		}
		else
		{
			//按照大小比较，然后插入
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
					//相等了，出错
					return false;
				}
			}
			//出循环时，cur找到了该插入的位置
			cur = new Node(data);
			if (kov(parent->_data) > kov(data))
			{
				//插入在parent左边
				parent->_left = cur;
			}
			else
			{
				//插入在parent右边
				parent->_right = cur;
			}
			cur->_parent = parent;
		}

		//旋转+改色
		//如果新插入的结点的父节点是黑色，则无需做处理
		while (parent && parent->_col == Red)
		{
			Node* grandp = parent->_parent;
			//如果p在g的左
			if (parent == grandp->_left)
			{
				Node* uncle = grandp->_right;
				//三种情况
				//1.叔叔存在且为红
				//改变颜色然后向上调整
				if (uncle && uncle->_col == Red)
				{
					parent->_col = Black;
					uncle->_col = Black;
					grandp->_col = Red;

					//向上调整
					cur = grandp;
					parent = cur->_parent;
				}
				//2.叔叔存在为黑
				//3.叔叔不存在
				else  //第二三种情况
				{
					if (cur == parent->_left)
					{
						//左左情况 ： 对p右旋, 改p为黑，改g为红
						RotateR(grandp);
						parent->_col = Black;
						grandp->_col = Red;
					}
					else
					{
						//左右情况: 对p先左旋再右旋，改cur为黑，g为红
						RotateL(parent);
						RotateR(grandp);

						cur->_col = Black;
						grandp->_col = Red;
					}

					//出来后新的grandp为黑色，无须向上调整
					break;
				}
			}

			//p在g的右
			else
			{
				Node* uncle = grandp->_left;
				//三种情况
				//1.叔叔存在且为红
				//改变颜色然后向上调整
				if (uncle && uncle->_col == Red)
				{
					parent->_col = Black;
					uncle->_col = Black;
					grandp->_col = Red;

					//向上调整
					cur = grandp;
					parent = cur->_parent;
				}
				//2.叔叔存在为黑
				//3.叔叔不存在
				else  //第二三种情况
				{
					if (cur == parent->_right)
					{
						//右右情况 ： 对p左旋, 改p为黑，改g为红
						RotateL(grandp);
						parent->_col = Black;
						grandp->_col = Red;
					}
					else
					{
						//右左情况: 对p先右旋再左旋，改cur为黑，g为红
						RotateR(parent);
						RotateL(grandp);

						cur->_col = Black;
						grandp->_col = Red;
					}

					//出来后新的grandp为黑色，无须向上调整
					break;
				}
			}
		}

		//调整以后，为了保证根节点始终为黑
		_root->_col = Black;

		return true;
	}

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	bool IsBalance()
	{
		if (_root && _root->_col == Red)
		{
			cout << "根节点颜色是红色" << endl;
			return false;
		}

		int benchmark = 0;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_col == Black)
				++benchmark;
			cur = cur->_left;
		}

		// 连续红色节点
		return _Check(_root, 0, benchmark);
	}

private:
	void _DestroyTree(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}

		_DestroyTree(root->_left);
		_DestroyTree(root->_right);

		delete(root);
	}

	bool _Check(Node* root, int blackNum, int benchmark)
	{
		if (root == nullptr)
		{
			if (benchmark != blackNum)
			{
				cout << "某条路径黑色节点的数量不相等" << endl;
				return false;
			}

			return true;
		}

		if (root->_col == Black)
		{
			++blackNum;
		}

		if (root->_col == Red
			&& root->_parent
			&& root->_parent->_col == Red)
		{
			cout << "存在连续的红色节点" << endl;
			return false;
		}

		return _Check(root->_left, blackNum, benchmark)
			&& _Check(root->_right, blackNum, benchmark);
	}

	void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}

		_InOrder(root->_left);
		cout << kov(root->_data) << ":" << root->_data.second << " ";
		_InOrder(root->_right);
	}

	void RotateR(Node* parent)
	{
		//右单旋：当新结点插入到了较高的左子树（左子树原本就比右子树高1）的左侧，此时左侧高右侧低
		//将左子树的右子树链接到parent的左侧，再将parent链接到左子树的右侧
		Node* childL = parent->_left;
		Node* childLR = childL->_right;
		Node* ancestor = parent->_parent;

		//链接左子树右节点和parent
		parent->_left = childLR;
		if (childLR)
			childLR->_parent = parent;

		//链接parent和左子树
		childL->_right = parent;
		parent->_parent = childL;

		//链接parent的parent和新的根
		if (parent == _root)
		{
			childL->_parent = nullptr;
			_root = childL;
		}
		else
		{
			if (ancestor->_left == parent)
			{
				ancestor->_left = childL;
			}
			else
			{
				ancestor->_right = childL;
			}
			childL->_parent = ancestor;
		}

	}

	void RotateL(Node* parent)
	{
		//左单旋：当新结点插入到了较高的右子树（右子树原本就比左子树高1）的右侧，此时右侧高左侧低
		//将右子树的左子树链接到parent的右侧，再将parent链接到右子树的左侧
		Node* childR = parent->_right;
		Node* childRL = childR->_left;
		Node* ancestor = parent->_parent;

		//链接右子树左节点和parent
		parent->_right = childRL;
		if (childRL)
			childRL->_parent = parent;

		//链接parent和右子树
		childR->_left = parent;
		parent->_parent = childR;

		//链接parent的parent和新的根
		if (parent == _root)
		{
			childR->_parent = nullptr;
			_root = childR;
		}
		else
		{
			if (ancestor->_left == parent)
			{
				ancestor->_left = childR;
			}
			else
			{
				ancestor->_right = childR;
			}
			childR->_parent = ancestor;
		}
	}

private:
	Node* _root = nullptr;
	KeyOfValue kov;
};