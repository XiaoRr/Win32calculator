#pragma once
#include "stdafx.h"

class Caculator
{
private:
	long double ans = 0, x = 0;			//������a��������x (ans ? x = �𰸣�
	std::wstring c = L" ";				//�����
	std::wstring xstring;				//��������string��
	int flag = 1;						//������ʾans����x(1:x 0:ans)
	int digit = -1;						//С��������
	int error = 0;							//��������
	int flag2 = 1;						//�հ���=����Ϊ0
	int flag3 = 1;						//�հ���������Ϊ0
	int flag4 = 0;						//�հ���������Ϊ1

public:
	Caculator()
	{
		CLR();
	}

public:

private:

	//long double ת�ַ���
	std::wstring LongDoubleToWString(long double tmp)
	{
		std::wstring ans, ans2;
		std::wstringstream wss, wss2;
		wss << tmp;
		wss >> ans;
		int flg = 1;
		for (int i = 0; i<ans.length(); i++)
		{
			if (ans[i] == L'.')
			{
				flg = 0;
			}
			if (ans[i] == L'e')
			{
				flg = 2;
			}
		}
		if (flg == 0)		//ֻ��С����
		{
			wss2 << std::fixed << std::setprecision(9) << tmp;
			wss2 >> ans;
			int j;
			for (j = ans.length() - 1; j >= 1; j--)
			{
				if (ans[j] != L'0' && ans[j] != L'.')break;
			}
			return ans.substr(0, j + 1);
		}
		if (flg == 2)		//�п�ѧ������
		{
			wss2 << std::scientific << std::setprecision(9) << tmp;
			wss2 >> ans;
			return ans;
		}
		return ans;
	}

	//���
	void CLR()
	{
		c = L" ";
		ans = x = error = 0;
		digit = -1;
		flag = flag2 = flag3 = 1;
		xstring = L"";
	}
	//�������
	void addNum(int n)
	{
		if (!flag2 && flag3 || flag4) {
			CLR();
		}
		flag = flag2 = flag3 = 1;
		flag4 = 0;
		if (xstring.length() > 14)return;
		if (n == -1 && digit > 0)return;
		if (n == -1) {
			if (xstring == L"")xstring += L'0';
			xstring += '.';
			digit = 10;
			return;
		}
		if (xstring == L"0")xstring = L"";
		xstring += (n + L'0');

		if (digit == -1) {
			x = x * 10 + n;
			return;
		}
		x = x + n * 1.0 / digit;
		digit *= 10;
	}

	//����
	void cal()
	{
		flag = flag2 = 0;
		flag3 = 1;
		switch (c[0])
		{
		case '*':
			ans *= x;
			break;
		case '/':
			if (x == 0) {
				error = 2; break;
			}
			ans /= x;
			break;
		case '-':
			ans -= x;
			break;
		case '+':
			ans += x;
			break;
		case L"��"[0]:
			ans = sqrt(ans);
		default:
			ans = x;
		}
	}

	//��ӷ���
	void addSign(std::wstring tmp)
	{
		if (!flag3) {
			c = tmp;
			return;
		}
		if (flag2 && c != L" ") {
			cal();
		}
		xstring = L"";
		flag2 = 1;
		c = tmp;
		if (flag)ans = x;
		x = 0;
		digit = -1;
		flag = flag3 = 0;
	}

public:
	//��ȡ�ַ����루0-9��+��-��*��/��%(�ٷֱ�)��=��C(���)��S(����)��
	void input(char type)
	{
		if (type >= '0' && type <= '9')
		{
			addNum(type - '0');
			return;
		}
		switch (type)
		{
		case '-':
			addSign(L"-");
			return;
		case '+':
			addSign(L"+");
			return;
		case '*':
			addSign(L"*");
			return;
		case '/':
			addSign(L"/");
			return;
		case 'C':
		case 'c':
			CLR();
			return;
		case 'S':
		case 's':
			flag4 = 1;
			if (flag2 == 0)
			{
				if (ans < 0)error = 3;
				//ans = sqrt(ans);
				//flag3 = 1;
				//flag = 0;
				//return;
				x = sqrt(ans);
				c = L" ";
				xstring = LongDoubleToWString(x);
				flag3 = 1;
				flag2 = 1;
				ans = x;
				return;
			}
			 {
				if (x < 0)error = 3;
				x = sqrt(x);
				xstring = LongDoubleToWString(x);
				flag3 = 1;
				flag = 1;
				//flag2 = 0;
				//if (c == L" ")flag2 = 0;
				return;
			}
			
			return;
		case '.':
			if (digit == -1)			//ֻ�е�һ��С������Ч
				addNum(-1);
			return;
		case '=':
			cal();
			return;
		case '%':
			if (!flag2)x = 0;
			x = ans*x / 100;
			xstring = LongDoubleToWString(x);
			return;
		default:
			return;
		}
	}

	//��ȡ�������
	std::wstring getString()
	{
		switch (error)
		{
		case 1:
			return L"���";	
		case 2: 
			return L"��������Ϊ0";
		case 3:
			return L"�������ܿ���";
		}
		if (xstring == L"" && flag == 1) return L"0";
		return flag ? xstring : (LongDoubleToWString(ans));
	}
};
