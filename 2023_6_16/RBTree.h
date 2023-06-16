#pragma once
#include <iostream>

using namespace std;

enum Colour
{
	Red,
	Black
};

template<class K, class V>
struct RBTreeNode
{
	RBTreeNode<K, V>* _parent;
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	pair<K, V> _kv;
	Colour _col;

	RBTreeNode(const pair<K, V> kv)
		:_parent(nullptr), 
		_left(nullptr), 
		_right(nullptr), 
		_kv(kv), 
		_col(Red)
	{}
};

template<class K, class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	Node* find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first > key)
			{
				cur = cur->_left;
			}
			else if(cur->_kv.first < key)
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

	bool insert(const pair<K, V> kv)
	{
		//������Ĳ��룺
		//1.�������������Ĺ��������
		//2.���պ�����Ĺ��������ת�͸ı���ɫ

		//����
		Node* cur = _root;
		Node* parent = nullptr;
		if (_root == nullptr)
		{
			_root = new Node(kv);
			_root->_col = Black;
			return true;
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

		//��ת+��ɫ
		//����²���Ľ��ĸ��ڵ��Ǻ�ɫ��������������
		while (parent && parent->_col == Red)
		{
			Node* grandp = parent->_parent;
			//���p��g����
			if (parent == grandp->_left)
			{
				Node* uncle = grandp->_right;
				//�������
				//1.���������Ϊ��
				//�ı���ɫȻ�����ϵ���
				if (uncle && uncle->_col == Red)
				{
					parent->_col = Black;
					uncle->_col = Black;
					grandp->_col = Red;

					//���ϵ���
					cur = grandp;
					parent = cur->_parent;
				}
				//2.�������Ϊ��
				//3.���岻����
				else  //�ڶ��������
				{
					if (cur == parent->_left)
					{
						//������� �� ��p����, ��pΪ�ڣ���gΪ��
						RotateR(grandp);
						parent->_col = Black;
						grandp->_col = Red;
					}
					else 
					{
						//�������: ��p����������������curΪ�ڣ�gΪ��
						RotateL(parent);
						RotateR(grandp);

						cur->_col = Black;
						grandp->_col = Red;
					}

					//�������µ�grandpΪ��ɫ���������ϵ���
					break;
				}
			}

			//p��g����
			else
			{
				Node* uncle = grandp->_left;
				//�������
				//1.���������Ϊ��
				//�ı���ɫȻ�����ϵ���
				if (uncle && uncle->_col == Red)
				{
					parent->_col = Black;
					uncle->_col = Black;
					grandp->_col = Red;

					//���ϵ���
					cur = grandp;
					parent = cur->_parent;
				}
				//2.�������Ϊ��
				//3.���岻����
				else  //�ڶ��������
				{
					if (cur == parent->_right)
					{
						//������� �� ��p����, ��pΪ�ڣ���gΪ��
						RotateL(grandp);
						parent->_col = Black;
						grandp->_col = Red;
					}
					else
					{
						//�������: ��p����������������curΪ�ڣ�gΪ��
						RotateR(parent);
						RotateL(grandp);

						cur->_col = Black;
						grandp->_col = Red;
					}

					//�������µ�grandpΪ��ɫ���������ϵ���
					break;
				}
			}
		}

		//�����Ժ�Ϊ�˱�֤���ڵ�ʼ��Ϊ��
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
			cout << "���ڵ���ɫ�Ǻ�ɫ" << endl;
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

		// ������ɫ�ڵ�
		return _Check(_root, 0, benchmark);
	}

	//��������Ƿ���Ϲ���
	//bool IsBalance()
	//{
	//	//ѡȡ����һ��·���������ɫ���ĸ����������һ��·��������ֲ�����������Ͳ�����
	//	if (_root && _root->_col == Red)
	//	{
	//		return false;
	//	}

	//	int mark = 0;
	//	Node* cur = _root;
	//	while (cur)
	//	{
	//		if (cur->_col == Black)
	//		{
	//			++mark;
	//		}
	//		cur = cur->_left;
	//	}

	//	return _Check(_root, 0, mark);
	//}
private:
	//bool _Check(Node* root, int blacknum, int mark)
	//{
	//	if (root == nullptr)
	//	{
	//		if (blacknum != mark)
	//		{
	//			cout << "ĳ��·����ɫ���������ƥ��" << endl;
	//			return false;
	//		}
	//		return true;
	//	}

	//	if (root->_col == Black)
	//	{
	//		blacknum++;
	//	}

	//	if (root->_col == Red &&
	//		root->_parent && 
	//		root->_parent->_col == Red)
	//	{
	//		return false;
	//	}

	//	return _Check(root->_left, blacknum, mark) &&
	//		_Check(root->_right, blacknum, mark);
	//}

	bool _Check(Node* root, int blackNum, int benchmark)
	{
		if (root == nullptr)
		{
			if (benchmark != blackNum)
			{
				cout << "ĳ��·����ɫ�ڵ�����������" << endl;
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
			cout << "���������ĺ�ɫ�ڵ�" << endl;
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
	}

private:
	Node* _root = nullptr;
};