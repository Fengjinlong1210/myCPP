#pragma once
#include <iostream>
#include <vector>
using namespace std;

// ����100�ڸ�����������㷨�ҵ�ֻ����һ�ε�����
// :�ŵ�λͼ�б�ʾ�������

template<size_t N>
class BitSet
{
public:
	BitSet()
	{
		_bits.resize(N / 8 + 1, 0);
	}

	void set()
	{
		_bits.resize(0);
		_bits.resize(N / 8 + 1, 0xFF);
	}

	void set(size_t num)
	{
		size_t i = num / 8;
		//num����vector�еĵ�ַ
		size_t j = num % 8;
		//num��char�еĵڼ�λ

		_bits[i] |= (1 << j);
	}

	void reset(size_t num)
	{
		size_t i = num / 8;
		//num����vector�еĵ�ַ
		size_t j = num % 8;
		//num��char�еĵڼ�λ

		_bits[i] &= ~(1 << j);
	}

	bool test(size_t num)
	{
		size_t i = num / 8;
		//num����vector�еĵ�ַ
		size_t j = num % 8;
		//num��char�еĵڼ�λ

		return _bits[i] & (1 << j);
	}
private:

private:
	vector<char> _bits;
};

//λͼ��Ӧ�ã�
//1. ���ٲ���һ�������ڲ���������
//2. ���� + ȥ��
//3. ���������ϵĽ���������
//4. ����ϵͳ�д��̿�ı��

//ʵ��һ���ܰ�������int��λͼ, ��Ҫ512MB�ڴ�

//�������ļ����ֱ���100�ڸ�����������ֻ��1G�ڴ棬����ҵ������ļ�������

//	����1:
// ��������λͼ, �ֱ��ʾ�����ļ�������
// ����λͼ�ҵ���ͬ���ڵ�����

// ����2:
// ֻ�ѵ�һ���ļ�����������λͼ, Ȼ������ڶ����ļ�
// ����ڶ����ļ��е����ִ�����λͼ, ��˵���ǽ���
// ��¼��һ�����ֺ�, ��λͼ�϶�Ӧ��λ����Ϊ0, ����һ�����ֱ���μ�¼�ɽ���


//  1���ļ���100�ڸ�int��1G�ڴ棬����㷨�ҵ����ִ���������2�ε���������
//  �������: ��������λͼ, ��һ��λͼ��¼�����ֳ�û���ֹ�, �ڶ���λͼ��¼���ִ����ǲ���һ��
//	����, ����һ��ʱ, ������λͼ���ó�01, �ڶ���ʱ, ���ó�10, ������11, ͨ�����ַ�ʽ
//	���Լ�¼���ֵĴ���, ֻ��Ҫ����λͼ����

template<size_t N>
class DoubleBitSet
{
public:
	void set(size_t num)
	{
		if (_bits1.test(num) == 0 && _bits2.test(num) == 0) //00->01
		{
			//�����ֻ�û�б���¼��
			_bits1.set(num);
		}
		else if (_bits1.test(num) == 1 && _bits2.test(num) == 0) // 01->10
		{
			//����¼��һ��
			_bits1.reset(num);
			_bits2.set(num);
		}
		else if (_bits1.test(num) == 0 && _bits2.test(num) == 1) // 10->11
		{
			_bits1.set(num);
		}
		else
		{
			return;
		}

	}

	int test(size_t num)
	{
		return _bits1.test(num) + 2 * _bits2.test(num);
	}
private:
	BitSet<N> _bits1;
	BitSet<N> _bits2;
};