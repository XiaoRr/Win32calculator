#pragma once
#include "stdafx.h"

class Caculator
{
private:
	long double ans = 0, x = 0;			//操作数a，操作数x (ans ? x = 答案）
	char c = ' ';				//运算符
	std::wstring xstring;				//输入数的string版
	int flag = 1;						//决定显示ans还是x(1:x 0:ans)
	int digit = -1;						//小数点特判
	int error = 0;							//错误特判
	int flag2 = 1;						//刚按过=号则为0
	int flag3 = 1;						//刚按过符号则为0
	int flag4 = 0;						//刚按过根号则为1
	std::wstring prestring;				//表达式

public:
	Caculator()
	{
		CLR();
	}

public:

private:

	//long double 转字符串
	std::wstring LongDoubleToWString(long double tmp)
	{
		std::wstring ans, ans2;
		std::wstringstream wss, wss2;
		wss << tmp;
		wss >> ans;
		if(ans == L"inf")
		{
			error = 1;
			return L"溢出";
		}
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
			int i = ans.length(), j;
			for(j = ans.length() -1;j>=1;j--)
			{
				if (i != ans.length() && ans[j] != L'0' && ans[j] != L'.')break;
				if (ans[j] == L'e')i = j;
				
			}
			return ans.substr(0,j+1) + ans.substr(i,ans.length());
		}
		return ans;
	}

	//清除
	void CLR()
	{
		c = ' ';
		ans = x = error = 0;
		digit = -1;
		flag = flag2 = flag3 = 1;
		prestring = xstring = L"";
	}
	//添加数字
	void addNum(int n)
	{
		do {
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
				break;
			}
			if (xstring == L"0")xstring = L"";
			xstring += (n + L'0');

			if (digit == -1) {
				x = x * 10 + (x<0?-n:n);
				break;
			}
			x = x + (x<0?-1:1)* n * 1.0 / digit;
			digit *= 10;
		} while (0);
		//prestring = xstring;
	}

	//计算
	void cal()
	{
		flag = flag2 = 0;
		flag3 = 1;
		prestring = L"" + LongDoubleToWString(ans) + L' ' + (wchar_t)c + L' ' + LongDoubleToWString(x) + L'=';
		switch (c)
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
		case 'S':
			ans = sqrt(ans);
		default:
			ans = x;
			prestring = LongDoubleToWString(ans) + L'=';
		}
	}

	//添加符号
	void addSign(char tmp)
	{
		flag4 = 0;
		if (!flag3) {
			c = tmp;
			prestring = L"" + LongDoubleToWString(ans) + L' ' + (wchar_t)c ;
			return;
		}
		if (flag2 && c != ' ') {
			cal();
		}
		xstring = L"";
		flag2 = 1;
		c = tmp;
		if (flag)ans = x;
		x = 0;
		digit = -1;
		flag = flag3 = 0;
		prestring = L"" + LongDoubleToWString(ans) + L' ' + (wchar_t)c;
	}

public:
	//获取字符输入（0-9，+，-，*，/，%(百分比)，=，!(符号相反),C(清除)，S(根号)）
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
			addSign('-');
			return;
		case '+':
			addSign('+');
			return;
		case '*':
			addSign('*');
			return;
		case '/':
			addSign('/');
			return;
		case 'C':
		case 'c':
			CLR();
			return;
		case 'S':
		case 's':
			//根号即是对当前显示在屏幕上的数进行暴力处理即可
			if (flag == 0)
			{
				long double tmp = ans;
				if (ans < 0) {
					prestring = L"√" + LongDoubleToWString(tmp) + L"=";
					error = 3;
					return;
				}
				CLR();
				prestring = L"√" + LongDoubleToWString(tmp) + L"=";
				flag = 0;
				ans = sqrt(tmp);
				
			}else
			{
				if (x < 0)error = 3;
				x = sqrt(x);
				xstring = LongDoubleToWString(x);
				//prestring = L"√" + LongDoubleToWString(x) + L"=";
			}
			flag4 = 1;
			return;
		case '.':
			if (digit == -1)			//只有第一个小数点有效
				addNum(-1);
			return;
		case '=':
		case 13: //回车
			cal();
			return;
		case '%':
			if (!flag2)x = 0;
			x = ans*x / 100;
			xstring = LongDoubleToWString(x);
			prestring = LongDoubleToWString(ans) + L"*" + LongDoubleToWString(x) + L"=";
			return;
		case '!':
			if(flag2 == 0)
			{
				ans = -ans;
			}else
			{
				if(x!=0)x = -x;
				xstring = LongDoubleToWString(x);
			}

		default:
			return;
		}
	}

	//获取窗口输出
	std::wstring getString()
	{
		switch (error)
		{
		case 1:
			return L"溢出";	
		case 2: 
			return L"除数不能为0";
		case 3:
			return L"负数不能开方";
		}
		if (xstring == L"" && flag == 1) return L"0";
		return flag ? xstring : (LongDoubleToWString(ans));
	}

	std::wstring getProcess()
	{
		return prestring;
	}
};
