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
		//���ն����������Ĺ��������
		//��������parentָ��
		//Node* newnode = new Node(kv);
		Node* cur = _root;
		Node* parent = nullptr;
		if (_root == nullptr)
		{
			_root = new Node(kv);
		}
		else
		{
			//���մ�С�Ƚϣ�Ȼ�����
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
					//����ˣ�����
					return false;
				}
			}
			//��ѭ��ʱ��cur�ҵ��˸ò����λ��
			cur = new Node(kv);
			if (parent->_kv.first > kv.first)
			{
				//������parent���
				parent->_left = cur;
			}
			else
			{
				//������parent�ұ�
				parent->_right = cur;
			}
			cur->_parent = parent;
		}

		//����ƽ������
		while (parent)  //���²������parent��ʼ���ϼ��ƽ������
		{
			//�ж�newnode������parent��������
			if (parent->_left == cur)
			{
				parent->_bf--;
			}
			else  //�������ұ�
			{
				parent->_bf++;
			}

			if (parent->_bf == 0)
			{
				//bf == 0˵�������parent���ƽ���ˣ�����Ҫ�����ϵ���
				break;
			}
			else if (parent->_bf == -1 || parent->_bf == 1)
			{
				//˵��parentԭ��û�н�㣬�����ֻ��һ���ӽ��, ��Ҫ���ϵ���
				parent = parent->_parent;

				cur = cur->_parent;
			}
			else if (parent->_bf == -2 || parent->_bf == 2)
			{
				//��ʱparent���������߶��Ѿ��������⣬��Ҫ��������
				//�����������ƽ�⣬���͸߶�

				//1.����
				if (parent->_bf == 2 && cur->_bf == 1)
				{
					RotateL(parent);
				}

				//2.����
				else if (parent->_bf == -2 && cur->_bf == -1)
				{
					RotateR(parent);
				}

				//3.�������
				else if (parent->_bf == -2 && cur->_bf == 1)
				{
					RotateLR(parent);
				}

				//4.���Һ���
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
			cout << "���" << root->_kv.first << "ƽ�����ӳ���" << endl;
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
		//�ҵ��������½����뵽�˽ϸߵ���������������ԭ���ͱ���������1������࣬��ʱ�����Ҳ��
		//�������������������ӵ�parent����࣬�ٽ�parent���ӵ����������Ҳ�
		Node* childL = parent->_left;
		Node* childLR = childL->_right;
		Node* ancestor = parent->_parent;

		//�����������ҽڵ��parent
		parent->_left = childLR;
		if (childLR)
			childLR->_parent = parent;

		//����parent��������
		childL->_right = parent;
		parent->_parent = childL;

		//����parent��parent���µĸ�
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

		//����ƽ������
		childL->_bf = parent->_bf = 0;
	}

	void RotateL(Node* parent)
	{
		//���������½����뵽�˽ϸߵ���������������ԭ���ͱ���������1�����Ҳ࣬��ʱ�Ҳ������
		//�������������������ӵ�parent���Ҳ࣬�ٽ�parent���ӵ������������
		Node* childR = parent->_right;
		Node* childRL = childR->_left;
		Node* ancestor = parent->_parent;

		//������������ڵ��parent
		parent->_right = childRL;
		if (childRL)
			childRL->_parent = parent;

		//����parent��������
		childR->_left = parent;
		parent->_parent = childR;

		//����parent��parent���µĸ�
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

		//����ƽ������
		childR->_bf = parent->_bf = 0;
	}

	void RotateLR(Node* parent)
	{
		//������������
		//�½����뵽�˽ϸ����������Ҳࣨԭ��������������������1��
		//�ȶ��������������ٶ����������ڵ�����
		Node* childL = parent->_left;
		Node* childLR = childL->_right;

		int bf = childLR->_bf;
		RotateL(childL);
		RotateR(parent);

		//����ƽ������
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

		//����ƽ������
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