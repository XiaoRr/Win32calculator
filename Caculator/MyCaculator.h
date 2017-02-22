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

public:
	void init();

public:
	void setGroup(int group);
	int getGroup();

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



public:
	static int getTotalGroup();
};
