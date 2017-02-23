///////////////////////////////////////////////////////////////
// 04FirstWindow.cpp�ļ�

#include "stdafx.h"
#include "MyCaculator.h"
// ���ں����ĺ���ԭ��
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);

static HWND btn[20], textview ,textview2;
Caculator cl;

HFONT ��ʾ������ = CreateFont
(
	40, 0,    //�߶�20, ��ȡ0��ʾ��ϵͳѡ�����ֵ  
	0, 0,    //�ı���б����������б��Ϊ0  
	FW_HEAVY,    //����  
	0, 0, 0,        //��б�壬���»��ߣ����л���  
	GB2312_CHARSET,    //�ַ���  
	OUT_DEFAULT_PRECIS,
	CLIP_DEFAULT_PRECIS,
	DEFAULT_QUALITY,        //һϵ�е�Ĭ��ֵ  
	DEFAULT_PITCH | FF_DONTCARE,
	(TCHAR*)"΢���ź�"    //��������  
);
HFONT �������� = CreateFont
(
	30, 0,    //�߶�20, ��ȡ0��ʾ��ϵͳѡ�����ֵ  
	0, 0,    //�ı���б����������б��Ϊ0  
	FW_HEAVY,    //����  
	0, 0, 0,        //��б�壬���»��ߣ����л���  
	GB2312_CHARSET,    //�ַ���  
	OUT_DEFAULT_PRECIS,
	CLIP_DEFAULT_PRECIS,
	DEFAULT_QUALITY,        //һϵ�е�Ĭ��ֵ  
	DEFAULT_PITCH | FF_DONTCARE,
	(TCHAR*)"΢���ź�"    //��������  
);

//��ں���
int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	wchar_t szClassName[] = L"MainWClass";
	WNDCLASSEX wndclass;

	// �����������ڵĲ������WNDCLASSEX�ṹ
	wndclass.cbSize = sizeof(wndclass);	// �ṹ�Ĵ�С
	wndclass.style = CS_HREDRAW|CS_VREDRAW;	// ָ�������С�ı���ػ�
	wndclass.lpfnWndProc = MainWndProc;	// ���ں���ָ��
	wndclass.cbClsExtra = 0;		// û�ж�������ڴ�
	wndclass.cbWndExtra = 0;		// û�ж���Ĵ����ڴ�
	wndclass.hInstance = hInstance;		// ʵ����� 
	wndclass.hIcon = ::LoadIcon(hInstance,
			(LPCWSTR)IDI_ICON1);	// ʹ��Ԥ����ͼ��
	wndclass.hCursor = ::LoadCursor(NULL,
			IDC_ARROW);		// ʹ��Ԥ����Ĺ��
	wndclass.hbrBackground = (HBRUSH)
		::GetStockObject(WHITE_BRUSH);	// ʹ�ð�ɫ������ˢ
	wndclass.lpszMenuName = NULL;		// ��ָ���˵�
	wndclass.lpszClassName = szClassName ;	// �����������	
	wndclass.hIconSm = ::LoadIcon(hInstance,
		(LPCWSTR)IDI_ICON1);		// û�����Сͼ��
	::RegisterClassEx(&wndclass);// ע�����������

	// ����������
	HWND hwnd = ::CreateWindowEx(
		0,			// dwExStyle����չ��ʽ	
		szClassName,		// lpClassName������			
		L"������",	// lpWindowName������		
		WS_OVERLAPPEDWINDOW,	// dwStyle�����ڷ��	
		CW_USEDEFAULT,		// X����ʼ X ����		
		CW_USEDEFAULT,		// Y����ʼ Y ����		
		450,		// nWidth�����			
		450,		// nHeight���߶�			
		NULL,			// hWndParent�������ھ��			
		NULL,			// hMenu���˵����		
		hInstance,		// hlnstance������ʵ�����		
		NULL);			// lpParam���û�����			

	if (hwnd == NULL)
	{
		MessageBox(NULL, _T("�������ڳ���"), _T("error"), MB_OK);
		return -1;
	}

	// ��ʾ���ڣ�ˢ�´��ڿͻ���
	::ShowWindow(hwnd, nCmdShow);
	::UpdateWindow(hwnd);

	// ����Ϣ����ȡ����Ϣ
	MSG msg;
	while (::GetMessage(&msg, NULL, 0, 0))
	{
		// ת��������Ϣ
		::TranslateMessage(&msg);
		// ����Ϣ���͵���Ӧ�Ĵ��ں���
		::DispatchMessage(&msg);
	}

	// ��GetMessage����0ʱ�������
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
	const std::wstring btnText[] = { L"7",L"8",L"9",L"��",L"C",
								L"4",L"5",L"6",L"+",L"-",
								L"1",L"2",L"3",L"*",L"/",
								L"��",L"0",L".",L"=",L"%"};
	switch (message)
	{
	case WM_PAINT: // ���ڿͻ�����Ҫ�ػ�
	{
		PAINTSTRUCT ps;
		// ʹ��Ч�Ŀͻ��������Ч����ȡ���豸�������
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
		//SendMessage(textview, WM_SETFONT, (WPARAM)��ʾ������, 1);
		SendMessage(textview2, WM_SETFONT, (WPARAM)��ʾ������, 1);

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
			::SendMessage(btn[i], WM_SETFONT, (WPARAM)��������, 1);
		return 0;
	}
	case WM_CHAR:
	{
		cl.input((char)wParam);
		setText();
		return 0;
	}
	case WM_DESTROY: // �������ٴ���
		PostQuitMessage(0); // ����Ϣ����Ͷ��һ��WM_QUIT��Ϣ����ʹGetMessage��������0��������Ϣѭ��wv
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
	// �����ǲ��������Ϣ����ϵͳ��Ĭ�ϴ���
	return ::DefWindowProc(hwnd, message, wParam, lParam);
}
