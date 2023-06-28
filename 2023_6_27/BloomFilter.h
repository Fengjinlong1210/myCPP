#pragma once
#include <iostream>
#include <string>
#include "bitset.h"
using namespace std;

//	��¡��������Ҫ�������ݺͱ��ı�����ϵ
//	ͨ�������ϣ������keyӳ��ɲ�ͬ��ֵ
//	����key���벻�ڵ�ʱ��, ֻ��Ҫ������ӳ����keyֵ�ڲ���
//	�����һ��ֵ����, ��˵��keyһ��������
//	��ʹ����ֵ������, Ҳ�п�����������keyֵӳ�������, ��keyҲ�п��ܲ�����
//	���Բ�¡������	�������������ж�һ��key�治����, ���������, �Ͳ���Ҫ���к����Ĳ���
//	��¡����������������̽��е�IO������������ж��ǳƴ������

//	��¡��������֧��ɾ�����ᵼ������key��Ӱ��

struct BKDRHash
{
	size_t operator()(const string& s)
	{
		// BKDR
		size_t value = 0;
		for (auto ch : s)
		{
			value *= 31;
			value += ch;
		}
		return value;
	}
};

struct APHash
{
	size_t operator()(const string& s)
	{
		size_t hash = 0;
		for (long i = 0; i < s.size(); i++)
		{
			if ((i & 1) == 0)
			{
				hash ^= ((hash << 7) ^ s[i] ^ (hash >> 3));
			}
			else
			{
				hash ^= (~((hash << 11) ^ s[i] ^ (hash >> 5)));
			}
		}
		return hash;
	}
};

struct DJBHash
{
	size_t operator()(const string& s)
	{
		size_t hash = 5381;
		for (auto ch : s)
		{
			hash += (hash << 5) + ch;
		}
		return hash;
	}
};

template<size_t N, class K = string, class Hash1 = BKDRHash, class Hash2 = APHash, class Hash3 = DJBHash>
class BloomFilter
{
public:
	void set(string str)
	{
		size_t length = multiple * N;
		size_t address1 = BKDRHash()(str) % length;
		size_t address2 = APHash()(str) % length;
		size_t address3 = DJBHash()(str) % length;

		_bs.set(address1);
		_bs.set(address2);
		_bs.set(address3);
	}

	bool test(string str)
	{
		size_t length = multiple * N;
		size_t address1 = BKDRHash()(str) % length;
		size_t address2 = APHash()(str) % length;
		size_t address3 = DJBHash()(str) % length;

		if (_bs.test(address1) && _bs.test(address2) && _bs.test(address3))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
private:
	//��Ҫһ��λͼ������N�ĸ����ͱ���������������ĳ���
	static const size_t multiple = 6;
	BitSet<multiple* N> _bs;
};

//�������ļ����ֱ���100�ڸ�query������ֻ��1G�ڴ棬����ҵ������ļ��������ֱ������ȷ�㷨�ͽ����㷨

//�������ļ������ݽ��й�ϣ�и�ָ��N��С�ļ�
//�����ͻ�ʹ��ͬ������Ҳ������ͬ��С�ļ���
//����ͬ�����ַ��������A1�ļ���Ҳ�����B1�ļ�
//�ٰ������ļ���С�ļ���Ӧ�Ľ��жԱȣ��Ϳ����ҳ�����

//������ڵ����ļ���������
//1.�д����ظ����� �� ��setȥ��
//2.�д�����ͬ���� ��ͬ������set�� ������쳣����˵�������������Ҫ����������ϣ�������ٴηָ�С�ļ��󽻼�