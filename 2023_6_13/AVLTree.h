#pragma once
#include <iostream>
#include <cassert>

using namespace std;

template<class K, class V>
struct AVLTreeNode
{
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;
	pair<K, V> _kv;
	int _bf;

	AVLTreeNode(const pair<K,V>& kv)
		:_left(nullptr), _right(nullptr), _parent(nullptr), _kv(kv), _bf(0)
	{}
};

template<class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	bool insert(const pair<K, V>& kv)
	{
		//按照二叉搜索树的规则插入结点
		//插入后更新parent指针
		//Node* newnode = new Node(kv);
		Node* cur = _root;
		Node* parent = nullptr;
		if (_root == nullptr)
		{
			_root = new Node(kv);
		}
		else
		{
			//按照大小比较，然后插入
			while (cur)
			{
				if (cur->_kv.first > kv.first)
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (cur->_kv.first < kv.first)
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
			cur = new Node(kv);
			if (parent->_kv.first > kv.first)
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

		//更新平衡因子
		while (parent)  //从新插入结点的parent开始向上检查平衡因子
		{
			//判断newnode插入在parent的左还是右
			if (parent->_left == cur)
			{
				parent->_bf--;
			}
			else  //插入在右边
			{
				parent->_bf++;
			}

			if (parent->_bf == 0)
			{
				//bf == 0说明插入后parent结点平衡了，不需要再向上调整
				break;
			}
			else if (parent->_bf == -1 || parent->_bf == 1)
			{
				//说明parent原本没有结点，插入后只有一个子结点, 需要向上调整
				parent = parent->_parent;

				cur = cur->_parent;
			}
			else if (parent->_bf == -2 || parent->_bf == 2)
			{
				//此时parent左右子树高度已经出现问题，需要立即调整
				//保持这颗树的平衡，降低高度

				//1.左旋
				if (parent->_bf == 2 && cur->_bf == 1)
				{
					RotateL(parent);
				}

				//2.右旋
				else if (parent->_bf == -2 && cur->_bf == -1)
				{
					RotateR(parent);
				}

				//3.先左后右
				else if (parent->_bf == -2 && cur->_bf == 1)
				{
					RotateLR(parent);
				}

				//4.先右后左
				else if (parent->_bf == 2 && cur->_bf == -1)
				{
					RotateRL(parent);
				}

				else
				{
					assert(false);
				}
				
				break;
			}
			else
			{
				assert(false);
			}
		}
		return true;
	}

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	int Height()
	{
		return _Height(_root);
	}

	bool isBalance()
	{
		return _isBalance(_root);
	}

	bool TestIsAVL()
	{
		Node* parent = new Node(make_pair(1, 1));
		Node* child1 = new Node(make_pair(2, 1));
		Node* child2 = new Node(make_pair(3, 1));
		Node* child3 = new Node(make_pair(4, 1));

		parent->_left = child1;
		child1->_parent = parent;

		child1->_right = child2;
		child2->_parent = child1;

		child3->_parent = child2;
		child2->_left = child3;

		return _isBalance(parent);
	}

private:
	int _Height(Node* root)
	{
		if (root == nullptr)
		{
			return 0;
		}

		int LeftH = _Height(root->_left);
		int RightH = _Height(root->_right);

		if (abs(LeftH - RightH) > 2)
		{
			cout << "结点" << root->_kv.first << "平衡因子出错" << endl;
		}

		return LeftH > RightH ? LeftH + 1 : RightH + 1;
	}

	bool _isBalance(Node* root)
	{
		if (root == nullptr)
		{
			return true;
		}

		int LeftH = _Height(root->_left);
		int RightH = _Height(root->_right);

		return abs(LeftH - RightH) < 2 &&
			_isBalance(root->_left) &&
			_isBalance(root->_right);
	}

	void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}

		_InOrder(root->_left);
		cout << root->_kv.first << " ";
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

		//更新平衡因子
		childL->_bf = parent->_bf = 0;
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

		//更新平衡因子
		childR->_bf = parent->_bf = 0;
	}

	void RotateLR(Node* parent)
	{
		//先左旋再右旋
		//新结点插入到了较高左子树的右侧（原本的左子树比右子树高1）
		//先对左子树左旋，再对左旋后的左节点右旋
		Node* childL = parent->_left;
		Node* childLR = childL->_right;

		int bf = childLR->_bf;
		RotateL(childL);
		RotateR(parent);

		//更新平衡因子
		if (bf == 0)
		{
			parent->_bf = childL->_bf = childLR->_bf = 0;
		}
		else if (bf == -1)
		{
			childL->_bf = 0;
			parent->_bf = 1;
			childLR->_bf = 0;
		}
		else if (bf == 1)
		{
			childL->_bf = -1;
			parent->_bf = 0;
			childLR->_bf = 0;
		}
	}

	void RotateRL(Node* parent)
	{

		Node* childR = parent->_right;
		Node* childRL = childR->_left;

		int bf = childRL->_bf;
		RotateR(childR);
		RotateL(parent);

		//更新平衡因子
		if (bf == 0)
		{
			parent->_bf = childR->_bf = childRL->_bf = 0;
		}
		else if (bf == -1)
		{
			childR->_bf = 1;
			parent->_bf = 0;
			childRL->_bf = 0;
		}
		else if (bf == 1)
		{
			childR->_bf = 0;
			parent->_bf = -1;
			childRL->_bf = 0;
		}
	}

private:
	Node* _root = nullptr;
};