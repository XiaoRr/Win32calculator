///////////////////////////////////////////////////////////////
// 04FirstWindow.cpp�ļ�



#include "stdafx.h"

// ���ں����ĺ���ԭ��
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);

static HWND btn[19], textview;
long double ans = 0, x = 0;			//������a��������x (ans ? x = �𰸣�
std::wstring c = L" ";				//�����
std::wstring xstring;				//��������string��
int flag = 1;						//������ʾans����x(1:x 0:ans)
int digit = -1;						//С��������
int error = 0;							//��������
int flag2 = 1;						//�հ���=����Ϊ0
int flag3 = 1;						//�հ���������Ϊ0

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
		430,		// nHeight���߶�			
		NULL,			// hWndParent�������ھ��			
		NULL,			// hMenu���˵����		
		hInstance,		// hlnstance������ʵ�����		
		NULL);			// lpParam���û�����			

	if (hwnd == NULL)
	{
		::MessageBox(NULL, _T("�������ڳ���"), _T("error"), MB_OK);
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
	if(flg == 0)		//ֻ��С����
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
		if(digit == -1)			//ֻ�е�һ��С������Ч
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
		SetWindowText(textview, L"���");
		return;
	}
	if (error == 2)
	{
		SetWindowText(textview, L"��������Ϊ0");
		return;
	}
	if (error == 3)
	{
		SetWindowText(textview, L"�������ܿ���");
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
	const std::wstring btnText[] = { L"7",L"8",L"9",L"��",L"C",
								L"4",L"5",L"6",L"+",L"-",
								L"1",L"2",L"3",L"*",L"/",
								L"0",L" ",L".",L"=",L"%"};
	switch (message)
	{
	case WM_PAINT: // ���ڿͻ�����Ҫ�ػ�
	{
		HDC hdc;
		PAINTSTRUCT ps;
		// ʹ��Ч�Ŀͻ��������Ч����ȡ���豸�������
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

		SendMessage(textview, WM_SETFONT, (WPARAM)��ʾ������, 1);

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
			::SendMessage(btn[i], WM_SETFONT, (WPARAM)��������, 1);
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
	case WM_DESTROY: // �������ٴ���
					 // ����Ϣ����Ͷ��һ��WM_QUIT��Ϣ����ʹGetMessage��������0��������Ϣѭ��wv
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
	// �����ǲ��������Ϣ����ϵͳ��Ĭ�ϴ���
	return ::DefWindowProc(hwnd, message, wParam, lParam);
}
