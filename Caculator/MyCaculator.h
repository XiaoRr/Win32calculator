#pragma once
#include "stdafx.h"

class Caculator
{
private:
	long double ans = 0, x = 0;			//操作数a，操作数x (ans ? x = 答案）
	std::wstring c = L" ";				//运算符
	std::wstring xstring;				//输入数的string版
	int flag = 1;						//决定显示ans还是x(1:x 0:ans)
	int digit = -1;						//小数点特判
	int error = 0;							//错误特判
	int flag2 = 1;						//刚按过=号则为0
	int flag3 = 1;						//刚按过符号则为0

public:
	void init();

public:
	void setGroup(int group);
	int getGroup();

private:
	//long double 转字符串
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
		if (flg == 0)		//只有小数点
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
		if (flg == 2)		//有科学计数法
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
