///////////////////////////////////////////////////////////////
// 04FirstWindow.cpp文件



#include "stdafx.h"

// 窗口函数的函数原形
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);

static HWND btn[19], textview;
long double ans = 0, x = 0;			//操作数a，操作数x (ans ? x = 答案）
std::wstring c = L" ";				//运算符
std::wstring xstring;				//输入数的string版
int flag = 1;						//决定显示ans还是x(1:x 0:ans)
int digit = -1;						//小数点特判
int error = 0;							//错误特判
int flag2 = 1;						//刚按过=号则为0
int flag3 = 1;						//刚按过符号则为0

HFONT 显示器字体 = CreateFont
(
	40, 0,    //高度20, 宽取0表示由系统选择最佳值  
	0, 0,    //文本倾斜，与字体倾斜都为0  
	FW_HEAVY,    //粗体  
	0, 0, 0,        //非斜体，无下划线，无中划线  
	GB2312_CHARSET,    //字符集  
	OUT_DEFAULT_PRECIS,
	CLIP_DEFAULT_PRECIS,
	DEFAULT_QUALITY,        //一系列的默认值  
	DEFAULT_PITCH | FF_DONTCARE,
	(TCHAR*)"微软雅黑"    //字体名称  
);
HFONT 按键字体 = CreateFont
(
	30, 0,    //高度20, 宽取0表示由系统选择最佳值  
	0, 0,    //文本倾斜，与字体倾斜都为0  
	FW_HEAVY,    //粗体  
	0, 0, 0,        //非斜体，无下划线，无中划线  
	GB2312_CHARSET,    //字符集  
	OUT_DEFAULT_PRECIS,
	CLIP_DEFAULT_PRECIS,
	DEFAULT_QUALITY,        //一系列的默认值  
	DEFAULT_PITCH | FF_DONTCARE,
	(TCHAR*)"微软雅黑"    //字体名称  
);

//入口函数
int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	wchar_t szClassName[] = L"MainWClass";
	WNDCLASSEX wndclass;

	// 用描述主窗口的参数填充WNDCLASSEX结构
	wndclass.cbSize = sizeof(wndclass);	// 结构的大小
	wndclass.style = CS_HREDRAW|CS_VREDRAW;	// 指定如果大小改变就重画
	wndclass.lpfnWndProc = MainWndProc;	// 窗口函数指针
	wndclass.cbClsExtra = 0;		// 没有额外的类内存
	wndclass.cbWndExtra = 0;		// 没有额外的窗口内存
	wndclass.hInstance = hInstance;		// 实例句柄 
	wndclass.hIcon = ::LoadIcon(hInstance,
			(LPCWSTR)IDI_ICON1);	// 使用预定义图标
	wndclass.hCursor = ::LoadCursor(NULL,
			IDC_ARROW);		// 使用预定义的光标
	wndclass.hbrBackground = (HBRUSH)
		::GetStockObject(WHITE_BRUSH);	// 使用白色背景画刷
	wndclass.lpszMenuName = NULL;		// 不指定菜单
	wndclass.lpszClassName = szClassName ;	// 窗口类的名称	
	wndclass.hIconSm = ::LoadIcon(hInstance,
		(LPCWSTR)IDI_ICON1);		// 没有类的小图标
	::RegisterClassEx(&wndclass);// 注册这个窗口类

	// 创建主窗口
	HWND hwnd = ::CreateWindowEx(
		0,			// dwExStyle，扩展样式	
		szClassName,		// lpClassName，类名			
		L"计算器",	// lpWindowName，标题		
		WS_OVERLAPPEDWINDOW,	// dwStyle，窗口风格	
		CW_USEDEFAULT,		// X，初始 X 坐标		
		CW_USEDEFAULT,		// Y，初始 Y 坐标		
		450,		// nWidth，宽度			
		430,		// nHeight，高度			
		NULL,			// hWndParent，父窗口句柄			
		NULL,			// hMenu，菜单句柄		
		hInstance,		// hlnstance，程序实例句柄		
		NULL);			// lpParam，用户数据			

	if (hwnd == NULL)
	{
		::MessageBox(NULL, _T("创建窗口出错！"), _T("error"), MB_OK);
		return -1;
	}

	// 显示窗口，刷新窗口客户区
	::ShowWindow(hwnd, nCmdShow);
	::UpdateWindow(hwnd);

	// 从消息堆中取出消息
	MSG msg;
	while (::GetMessage(&msg, NULL, 0, 0))
	{
		// 转化键盘消息
		::TranslateMessage(&msg);
		// 将消息发送到相应的窗口函数
		::DispatchMessage(&msg);
	}

	// 当GetMessage返回0时程序结束
	return msg.wParam;
}

std::wstring LongDoubleToWString(long double tmp)
{
	std::wstring ans, ans2;
	std::wstringstream wss,wss2;
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
	if(flg == 0)		//只有小数点
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
//清除
void CLR()
{
	c = L" ";
	ans = x = error = 0;
	digit = -1;
	flag = flag2 = flag3 = 1;
	xstring = L"";
}
//添加数字
void addNum(int n)
{
	if (!flag2 && flag3) {
		CLR();
	}
	flag = flag2 = flag3 = 1;
	if (xstring.length() > 14)return;
	if (n == -1 && digit > 0)return;
	if(n == -1){
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

//计算
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
	case L"√"[0]:
		ans = sqrt(ans);
	default:
		ans = x;
	}
}

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
	if(flag)ans = x;
	x = 0;
	digit = -1;
	flag = flag3 = 0;
}
void analysis(HWND lParam)
{
	if(lParam == btn[0])	//7
	{
		addNum(7);
		return;
	}
	if (lParam == btn[1])	//8
	{
		addNum(8);
		return;
	}
	if (lParam == btn[2])	//9
	{
		addNum(9);
		return;
	}
	if (lParam == btn[3])	//sqr
	{
		if (flag2 == 0)
		{
			if (ans < 0)error = 3;
			ans = sqrt(ans);
		}
		else {
			if (x < 0)error = 3;
			x = sqrt(x);
			xstring = LongDoubleToWString(x);
			return;
		}
		flag2 = 0;
		return;
	}
	if (lParam == btn[4])	//C
	{
		CLR();
		return;
	}
	if (lParam == btn[5])	//4
	{
		addNum(4);
		return;
	}
	if (lParam == btn[6])	//5
	{
		addNum(5);
		return;
	}
	if (lParam == btn[7])	//6
	{
		addNum(6);
		return;
	}
	if (lParam == btn[8])	//+
	{

		addSign(L"+");
		return;
	}
	if (lParam == btn[9])	//-
	{
		addSign(L"-");
		return;
	}
	if (lParam == btn[10])	//1
	{
		addNum(1);
		return;
	}
	if (lParam == btn[11])	//2
	{
		addNum(2);
		return;
	}
	if (lParam == btn[12])	//3
	{
		addNum(3);
		return;
	}
	if (lParam == btn[13])	//*
	{
		addSign(L"*");
		return;
	}
	if (lParam == btn[14])	// /
	{
		addSign(L"/");
		return;
	}
	if (lParam == btn[15])	//0
	{
		addNum(0);
		return;
	}
	if (lParam == btn[16])	//.
	{
		if(digit == -1)			//只有第一个小数点有效
			addNum(-1);
		return;
	}
	if (lParam == btn[17])	//=
	{
		cal();
		return;
	}
	if (lParam == btn[18])	//%
	{
		if (!flag2)x = 0;
		x = ans*x / 100;
		xstring = LongDoubleToWString(x);
		return;
	}
}

void setText()
{
	if (error == 1)
	{
		SetWindowText(textview, L"溢出");
		return;
	}
	if (error == 2)
	{
		SetWindowText(textview, L"除数不能为0");
		return;
	}
	if (error == 3)
	{
		SetWindowText(textview, L"负数不能开方");
		return;
	}

	std::wstring show;
	if (xstring == L"" && flag == 1) show = L"0";
	else show = flag ? xstring : (LongDoubleToWString(ans));
	SetWindowText(textview, show.c_str());
}
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	const int btnposX[] = { 10,90,170,270,350 };
	const int btnposY[] = { 60,140,220,300 };
	const std::wstring btnText[] = { L"7",L"8",L"9",L"√",L"C",
								L"4",L"5",L"6",L"+",L"-",
								L"1",L"2",L"3",L"*",L"/",
								L"0",L" ",L".",L"=",L"%"};
	switch (message)
	{
	case WM_PAINT: // 窗口客户区需要重画
	{
		HDC hdc;
		PAINTSTRUCT ps;
		// 使无效的客户区变的有效，并取得设备环境句柄
		hdc = ::BeginPaint(hwnd, &ps);

		setText();
		//SetWindowText(textview, (std::to_wstring(x) + L" " + std::to_wstring(ans)).c_str());

		::EndPaint(hwnd, &ps);
		//UpdateWindow(hwnd);
		return 0;
	}
	case WM_CREATE:
	{
		int tmp = 0;
		textview = CreateWindow(
			_T("EDIT"), 
			_T("0"), 
			WS_VISIBLE | WS_CHILD | DT_VCENTER | WS_BORDER | ES_RIGHT, 
			10, 
			10, 
			410, 
			40, 
			hwnd, 
			NULL, 
			NULL, 
			NULL);

		SendMessage(textview, WM_SETFONT, (WPARAM)显示器字体, 1);

		for (int i = 0; i < 20; i++)
		{
			if (i == 16)continue;
			btn[tmp++] = CreateWindow(
				_T("BUTTON"),   // predefined class  
				btnText[i].c_str(),       // button text  
				WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // styles    
				btnposX[i%5],         // starting x position  
				btnposY[i/5],         // starting y position  
				i==15?150:70,        // button width  
				70,        // button height  
				hwnd,       // parent window  
				NULL,       // No menu  
				(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
				NULL);      // pointer not needed  
		}
		for(int i=0;i<19;i++)
			::SendMessage(btn[i], WM_SETFONT, (WPARAM)按键字体, 1);
		return 0;
	}
	case WM_CHAR:
	{
		char tmpChar = (char)wParam ;
		if (tmpChar >= '0' && tmpChar <= '9')
			addNum(tmpChar - '0');
		if (tmpChar == '.')
			analysis(btn[16]);		
		if (tmpChar == '+')
			analysis(btn[8]);		
		if (tmpChar == '-')
			analysis(btn[9]);		
		if (tmpChar == '*')
			analysis(btn[13]);		
		if (tmpChar == '/')
			analysis(btn[14]);
		if (tmpChar == '%')
			analysis(btn[18]);
		if (tmpChar == '=' || tmpChar == 13)
			analysis(btn[17]);
		if (tmpChar == 'c' || tmpChar == 'C')
			analysis(btn[4]);
		
		setText();
		return 0;
	}
	case WM_DESTROY: // 正在销毁窗口
					 // 向消息队列投递一个WM_QUIT消息，促使GetMessage函数返回0，结束消息循环wv
		::PostQuitMessage(0);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDM_EXIT:
			::SendMessage(hwnd, WM_CLOSE, 0, 0);
			break;
		}
		analysis((HWND)lParam);
		SetFocus(hwnd);
		setText();
		return 0;
	}
	// 将我们不处理的消息交给系统做默认处理
	return ::DefWindowProc(hwnd, message, wParam, lParam);
}
