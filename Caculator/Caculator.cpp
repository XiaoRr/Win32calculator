///////////////////////////////////////////////////////////////
// 04FirstWindow.cpp文件

#include "stdafx.h"
#include "MyCaculator.h"
// 窗口函数的函数原形
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);

static HWND btn[20], textview ,textview2;
Caculator cl;

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
		450,		// nHeight，高度			
		NULL,			// hWndParent，父窗口句柄			
		NULL,			// hMenu，菜单句柄		
		hInstance,		// hlnstance，程序实例句柄		
		NULL);			// lpParam，用户数据			

	if (hwnd == NULL)
	{
		MessageBox(NULL, _T("创建窗口出错！"), _T("error"), MB_OK);
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

void analysis(HWND lParam)
{
	char hash[] = "789SC456+-123*/!0.=%";
	for (int i = 0; i < 20; i++)
		if (lParam == btn[i])
			return cl.input(hash[i]);
}

void setText()
{
	SetWindowText(textview, cl.getProcess() .c_str());
	SetWindowText(textview2, cl.getString().c_str());
}
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	const int btnposX[] = { 10,90,170,270,350 };
	const int btnposY[] = { 90,170,250,330 };
	const std::wstring btnText[] = { L"7",L"8",L"9",L"√",L"C",
								L"4",L"5",L"6",L"+",L"-",
								L"1",L"2",L"3",L"*",L"/",
								L"±",L"0",L".",L"=",L"%"};
	switch (message)
	{
	case WM_PAINT: // 窗口客户区需要重画
	{
		PAINTSTRUCT ps;
		// 使无效的客户区变的有效，并取得设备环境句柄
		BeginPaint(hwnd, &ps);
		setText();
		EndPaint(hwnd, &ps);
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
			25,
			hwnd,
			NULL,
			NULL,
			NULL);

		textview2 = CreateWindow(
			_T("EDIT"),
			_T("0"),
			WS_VISIBLE | WS_CHILD | DT_VCENTER | WS_BORDER | ES_RIGHT,
			10,
			40,
			410,
			40,
			hwnd,
			NULL,
			NULL,
			NULL);
		//SendMessage(textview, WM_SETFONT, (WPARAM)显示器字体, 1);
		SendMessage(textview2, WM_SETFONT, (WPARAM)显示器字体, 1);

		for (int i = 0; i < 20; i++)
		{
			btn[i] = CreateWindow(
				_T("BUTTON"),   // predefined class  
				btnText[i].c_str(),       // button text  
				WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // styles    
				btnposX[i % 5],         // starting x position  
				btnposY[i / 5],         // starting y position  
				70,        // button width  
				70,        // button height  
				hwnd,       // parent window  
				NULL,       // No menu  
				(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
				NULL);      // pointer not needed  
		}
		for (int i = 0; i < 20; i++)
			::SendMessage(btn[i], WM_SETFONT, (WPARAM)按键字体, 1);
		return 0;
	}
	case WM_CHAR:
	{
		cl.input((char)wParam);
		setText();
		return 0;
	}
	case WM_DESTROY: // 正在销毁窗口
		PostQuitMessage(0); // 向消息队列投递一个WM_QUIT消息，促使GetMessage函数返回0，结束消息循环wv
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
