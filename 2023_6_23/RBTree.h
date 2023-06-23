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
	
	//�����������������ã�
	//1.����������������ͨ������ʱ���ú������ǹ��캯��
	//2.������������ʱconst������ʱ���ú�����������ͨ����������const������
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
		//���ӵ�������Ҫ�ҵ�������������ڵ�
		//����ڵ��Ҳ�Ϊ�գ���Ҫ�ҵ�����ڵ�
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
			//��Ϊ�գ������ҵ���һ���ڵ�
			//ֱ����ǰ�ڵ��Ǹ��׽�������
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
		//�ݼ�������
		//�ҵ�ǰһ�����
		//�����Ϊ�գ����������������ҽ��
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
			//�����Ϊ�գ����ϲ���
			//�ҵ���ǰ�ڵ��Ǹ��׽����ҽڵ�
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
		//���������
		//���������������ķ�ʽ�ҵ������λ��
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
		//��ѭ��ʱ��curλ�þ���Ҫ����Ľ��λ��
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
		//����λ��
		while (parent && parent->_col == Red)
		{
			Node* grandp = parent->_parent;
			//1.���p��g����
			if (parent && parent == grandp->_left)
			{
				Node* uncle = grandp->_right;
				//1.1 ���u������Ϊ��
				if (uncle && uncle->_col == Red)
				{
					//��u��p��Ϊ�ڣ���g��Ϊ�죬Ȼ��������ϵ���
					uncle->_col = parent->_col = Black;
					grandp->_col = Red;

					cur = grandp;
					parent = cur->_parent;
				}
				//1.2 ���u������Ϊ�� ���� uֱ�Ӳ�����
				else
				{
					//1.2.1 ����
					if (cur == parent->_left)
					{
						//		g
						//	  p   u
						//  c
						//��g������ ��p�ĺڣ�g�ĺ�
						rotateL(grandp);
						parent->_col = Black;
						grandp->_col = Red;
					}
					//1.2.2 ����
					else
					{
						//		g
						//	  p   u
						//     c
						//��p��������Ȼ���g��������c�ĺڣ�g�ĺ�
						rotateL(parent);
						rotateR(grandp);
						cur->_col = Black;
						grandp->_col = Red;
					}
				}
			}
			//2.p��g����
			else
			{
				Node* uncle = grandp->_left;
				//2.1 ���u������Ϊ��
				if (uncle && uncle->_col == Red)
				{
					//��p��u��Ϊ�ڣ�g��Ϊ�죬���ϵ���
					parent->_col = uncle->_col = Black;
					grandp->_col = Red;

					cur = grandp;
					parent = cur->_parent;
				}
				//2.2 ���u������Ϊ�� ���� uֱ�Ӳ�����
				else
				{
					//2.2.1����
					if (cur == parent->_right)
					{
						//		g
						//	 u	   p
						//           c
						//��g��������pΪ�ڣ�gΪ��
						rotateL(grandp);
						parent->_col = Black;
						grandp->_col = Red;
					}
					//2.2.2 ����
					else
					{
						//		g
						//	 u	    p
						//		  c
						//��p��������g��������cΪ�ڣ�gΪ��
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
			cout << "���ڵ���ɫ�Ǻ�ɫ" << endl;
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
				cout << "·����ɫ�ڵ㲻���" << endl;
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
			cout << "���������ĺ�ɫ���" << endl;
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
