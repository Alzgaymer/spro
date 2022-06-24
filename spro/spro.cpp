#include <windows.h>
#include <xstring>
#include <string>
#include <tchar.h>
#include "resource.h"
#include <Font.h>

#define ID_MODE1 10
#define ID_MODE2 20
#define COMBOBOX_A_LAB_CHOSEN 8026
#define COMBOBOX_B_LAB_CHOSEN 8027
#define COMBOBOX_C_LAB_CHOSEN 8028
#define COMBOBOX_D_LAB_CHOSEN 8029
using std::wstring; using std::string;

static TCHAR szWindowClass[] = _T("Title");
static const auto MaxPixelsFSX = GetSystemMetrics(SM_CXFULLSCREEN);
static const auto MaxPixelsFSY = GetSystemMetrics(SM_CYFULLSCREEN);
HWND comboBoxA, comboBoxB, comboBoxC, comboBoxD;
HWND comboBoxAButton, comboBoxBButton, comboBoxCButton, comboBoxDButton;
HWND lb1, lb2, lb3, lb4, lb5, lb6, lb7, lb8, lb9, last;
RECT rt;
HINSTANCE hInst;
bool Destroyed = false;
HDC WindowDC, TemporaryDC;
HBITMAP BitmapDC;

void ShowLab1(HWND hWnd, int x, int y, int width, int height);
void ShowLab2(HWND hWnd, int x, int y, int width, int height);
void ShowLab3(HWND hWnd, int x, int y, int width, int height);
void ShowLab4(HWND hWnd, int x, int y, int width, int height);
void ShowLab5(HWND hWnd, int x, int y, int width, int height);
void ShowLab6(HWND hWnd, int x, int y, int width, int height);
void ShowLab7(HWND hWnd, int x, int y, int width, int height);
void ShowLab8(HWND hWnd, int x, int y, int width, int height);
void ShowLab9(HWND hWnd, int x, int y, int width, int height);

LRESULT CALLBACK WndProc(_In_ HWND   hWnd, _In_ UINT   message, _In_ WPARAM wParam, _In_ LPARAM lParam);
LRESULT CALLBACK WndProc1(_In_ HWND   hWnd, _In_ UINT   message, _In_ WPARAM wParam, _In_ LPARAM lParam);
LRESULT CALLBACK WndProc2(_In_ HWND   hWnd, _In_ UINT   message, _In_ WPARAM wParam, _In_ LPARAM lParam);
LRESULT CALLBACK WndProc3(_In_ HWND   hWnd, _In_ UINT   message, _In_ WPARAM wParam, _In_ LPARAM lParam);
LRESULT CALLBACK WndProc4(_In_ HWND   hWnd, _In_ UINT   message, _In_ WPARAM wParam, _In_ LPARAM lParam);
LRESULT CALLBACK WndProc5(_In_ HWND   hWnd, _In_ UINT   message, _In_ WPARAM wParam, _In_ LPARAM lParam);
LRESULT CALLBACK WndProc6(_In_ HWND   hWnd, _In_ UINT   message, _In_ WPARAM wParam, _In_ LPARAM lParam);
LRESULT CALLBACK WndProc7(_In_ HWND   hWnd, _In_ UINT   message, _In_ WPARAM wParam, _In_ LPARAM lParam);
LRESULT CALLBACK WndProc8(_In_ HWND   hWnd, _In_ UINT   message, _In_ WPARAM wParam, _In_ LPARAM lParam);
LRESULT CALLBACK WndProc9(_In_ HWND   hWnd, _In_ UINT   message, _In_ WPARAM wParam, _In_ LPARAM lParam);

void AddComboBoxes(HWND hWnd);

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
{
	WNDCLASSEX wcex;
	//fill window class
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDI_SMALL);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);
	//register main window 
	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Windows Desktop Guided Tour"),
			NULL);
		throw;
	}
	hInst = hInstance;
	HWND hwnd;
	hwnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		szWindowClass,
		_T("WinProject"),
		WS_OVERLAPPEDWINDOW,
		//centerized window
		50 , 0 ,
		1920 -45, 1080,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hwnd)
	{
		MessageBox(NULL,
			_T("Call to project::Create_Window failed!"),
			_T("Windows Desktop Guided Tour"),
			NULL);
		
	}

	ShowWindow(hwnd,
		nCmdShow);
	UpdateWindow(hwnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}
HWND fb, sb;
void InitButtons(HWND hWnd)
{
	fb = CreateWindow(
		L"BUTTON",  // Predefined class; Unicode assumed 
		L"MODE 1",      // Button text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
		10,         // x position 
		10,         // y position 
		100,        // Button width
		100,        // Button height
		hWnd,     // Parent window
		(HMENU)ID_MODE1,       // No menu.
		(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
		NULL);      // Pointer not needed.

	sb = CreateWindow(
		L"BUTTON",  // Predefined class; Unicode assumed 
		L"MODE 2",      // Button text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
		110,         // x position 
		10,         // y position 
		100,        // Button width
		100,        // Button height
		hWnd,     // Parent window
		(HMENU)ID_MODE2,       // No menu.
		(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
		NULL);      // Pointer not needed.
}
void CheckWin()
{
	if (!Destroyed)
		DestroyWindow(last);
}
LRESULT CALLBACK WndProc(
	_In_ HWND   hWnd,
	_In_ UINT   message,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
)
{

	switch (message)
	{
	case WM_CREATE:
		InitButtons(hWnd);
		break;
	case WM_COMMAND:

		switch (wParam)
		{
		case ID_MODE1:
			DestroyWindow(fb);
			DestroyWindow(sb);
			SetMenu(hWnd, LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU1)));
			break;
		case ID_MODE2:
			DestroyWindow(fb);
			DestroyWindow(sb);
			AddComboBoxes(hWnd);
			break;
		case ID_LB_1:
			CheckWin();
			ShowLab1(hWnd, 0, 0, 910, 450);
			last = lb1;
			Destroyed = false;

			break;
		case ID_LB_2:
			CheckWin();
			ShowLab2(hWnd, 0, 0, 910, 450);
			last = lb2; Destroyed = false;
			break;
		case ID_LB_3:
			CheckWin();
			ShowLab3(hWnd, 0, 0, 910, 450);
			last = lb3; Destroyed = false;
			break;
		case ID_LB_4:
			CheckWin();
			ShowLab4(hWnd, 0, 0, 910, 450);
			last = lb4; Destroyed = false;
			break;
		case ID_LB_5:
			CheckWin();
			ShowLab5(hWnd, 0, 0, 910, 450);
			last = lb5; Destroyed = false;
			break;
		case ID_LB_6:
			CheckWin();
			ShowLab6(hWnd, 0, 0, 910, 450);
			last = lb6; Destroyed = false;
			break;
		case ID_LB_7:
			CheckWin();
			ShowLab7(hWnd, 0, 0, 910, 450);
			last = lb7; Destroyed = false;
			break;
		case ID_LB_8:
			CheckWin();
			ShowLab8(hWnd, 0, 0, 910, 450);
			last = lb8; Destroyed = false;
			break;
		case ID_LB_9:
			CheckWin();
			ShowLab9(hWnd, 0, 0, 910, 450);
			last = lb9; Destroyed = false;
			break;
		case ID_BACK:
			InitButtons(hWnd);
			SetMenu(hWnd, LoadMenu(hInst, MAKEINTRESOURCE(IDI_SMALL)));
			break;
		case COMBOBOX_A_LAB_CHOSEN:
		{
			if (lb1 != NULL)
				DestroyWindow(lb1);
			if (lb2 != NULL)
				DestroyWindow(lb2);
			if (lb3 != NULL)
				DestroyWindow(lb3);

			int index = SendMessage(comboBoxA, CB_GETCURSEL, 0, 0);
			if (index == 0)
				ShowLab1(hWnd, 0, 24, 760, 376);
			else if (index == 1)
				ShowLab2(hWnd, 0, 24, 760, 376);
			else
				ShowLab3(hWnd, 0, 24, 760, 376);
			break;
		}
		case COMBOBOX_B_LAB_CHOSEN:
		{
			if (lb4 != NULL)
				DestroyWindow(lb4);
			if (lb5 != NULL)
				DestroyWindow(lb5);

			int index = SendMessage(comboBoxB, CB_GETCURSEL, 0, 0);
			if (index == 0)
				ShowLab4(hWnd, 761, 24, 775, 376);
			else
				ShowLab5(hWnd, 761, 24, 775, 376);
			break;
		}
		case COMBOBOX_C_LAB_CHOSEN:
		{
			if (lb6 != NULL)
				DestroyWindow(lb6);
			if (lb7 != NULL)
				DestroyWindow(lb7);

			int index = SendMessage(comboBoxC, CB_GETCURSEL, 0, 0);
			if (index == 0)
				ShowLab6(hWnd, 0, 424, 760, 376);
			else
				ShowLab7(hWnd, 0, 424, 760, 376);
			break;
		}
		case COMBOBOX_D_LAB_CHOSEN:
		{
			if (lb8 != NULL)
				DestroyWindow(lb8);
			if (lb9 != NULL)
				DestroyWindow(lb9);

			int index = SendMessage(comboBoxD, CB_GETCURSEL, 0, 0);
			if (index == 0)
				ShowLab8(hWnd, 761, 424, 775, 376);
			else
				ShowLab9(hWnd, 761, 424, 775, 376);
			break;
		}
		}

	
	break;
	case WM_DESTROY:
		PostQuitMessage(69);

		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
}
//lb1
void ShowLab1(HWND hWnd, int x, int y, int width, int height)
{
	WNDCLASS wc;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = NULL;
	wc.lpszClassName = L"Lab1";
	wc.lpszMenuName = MAKEINTRESOURCE(MENU1);
	wc.lpfnWndProc = WndProc1;
	RegisterClassW(&wc);

	lb1 = CreateWindowW(L"Lab1", L"Window Application", WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_VISIBLE | WS_CLIPSIBLINGS,
		x, y, width, height, NULL, NULL, NULL, NULL);
	SetParent(lb1, hWnd);
	ShowWindow(lb1, SW_SHOWNORMAL);
}
LRESULT CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDMORE) {
			MessageBox(hDlg, L"Members of the group: Herasymchuk, Kuznietsov, Zalitskiy", L"More", MB_OK);

			return (INT_PTR)TRUE;
		}
		break;
	}
	return FALSE;
}

LRESULT CALLBACK WndProc1(_In_ HWND   hWnd, _In_ UINT   message, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rt;

	switch (message)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_CHANGEBACKGROUND_BLACK:
			SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(0, 0, 0)));
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case ID_CHANGEBACKGROUND_WHITE:
			SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(255, 255, 255)));
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case ID_CHANGEBACKGROUND_RED:
			SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(255, 0, 0)));
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case ID_CHANGEBACKGROUND_GREEN:
			SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(0, 255, 0)));
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case ID_CHANGEBACKGROUND_BLUE:
			SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(0, 0, 255)));
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case ID_CHANGESIZEOFWINDOW_FULLSCREEN:
			SetWindowPos(hWnd, NULL, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CXSCREEN), SWP_SHOWWINDOW);
			break;
		case ID_CHANGESIZEOFWINDOW_480X320:
			SetWindowPos(hWnd, NULL, 0, 0, 480, 320, SWP_SHOWWINDOW);
			break;
		case ID_CHANGESIZEOFWINDOW_250X200:
			SetWindowPos(hWnd, NULL, 0, 0, 250, 200, SWP_SHOWWINDOW);
			break;
		case ID_CHANGESIZEOFWINDOW_500X501:
			SetWindowPos(hWnd, NULL, 0, 0, 500, 500, SWP_SHOWWINDOW);
			break;
		case ID_ABOUT_ABOUTAPP:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG3), hWnd, (DLGPROC)DlgProc);
			break;
		}
	case WM_CREATE: 				//Повідомлення приходить при створенні вікна
		break;
	case WM_LBUTTONDBLCLK:
		MessageBox(hWnd, L"Double click processed!", L"Double click", MB_OK);
		break;
	case WM_PAINT: 				//Перемалювати вікно
		hdc = BeginPaint(hWnd, &ps); 	//Почати графічний вивід	
		GetClientRect(hWnd, &rt); 		//Область вікна для малювання
		DrawText(hdc, L"Hello world!", -1, &rt, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hWnd, &ps); 		//Закінчити графічний вивід	
		break;
	case WM_CLOSE:
		if (MessageBox(hWnd, L"Ви впевнені?", L"Exit", MB_YESNO) == IDYES) {
			Destroyed = true;
			DestroyWindow(hWnd);

		}
		break;
	default:
		//Обробка повідомлень, які не оброблені користувачем
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;

	return 0;
}

//lb2
void ShowLab2(HWND hWnd, int x, int y, int width, int height)
{
	WNDCLASS wc;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = NULL;
	wc.lpszClassName = L"Lab2";
	wc.lpszMenuName = 0;
	wc.lpfnWndProc = WndProc2;
	RegisterClassW(&wc);

	lb2 = CreateWindowW(L"Lab2", L"Window Application", WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_VISIBLE | WS_CLIPSIBLINGS,
		x, y, width, height, NULL, NULL, NULL, NULL);
	SetParent(lb2, hWnd);
	ShowWindow(lb2, SW_SHOWNORMAL);
}
void Metrics(HDC hdc, LPWSTR buffer, TEXTMETRIC tm) {
	SetBkMode(hdc, TRANSPARENT);
	TextOut(hdc, 20, 0, buffer, wsprintf(buffer, L"DoubleClickX: %5d", GetSystemMetrics(SM_CXDOUBLECLK)));
	TextOut(hdc, 20, 30, buffer, wsprintf(buffer, L"DoubleClickY: %5d", GetSystemMetrics(SM_CYDOUBLECLK)));
	TextOut(hdc, 20, 60, buffer, wsprintf(buffer, L"SmallIconX: %5d", GetSystemMetrics(SM_CXSMICON)));
	TextOut(hdc, 20, 90, buffer, wsprintf(buffer, L"SmallIconY: %5d", GetSystemMetrics(SM_CYSMICON)));
	TextOut(hdc, 20, 120, buffer, wsprintf(buffer, L"MaxIconX: %5d", GetSystemMetrics(SM_CXICON)));
	TextOut(hdc, 20, 150, buffer, wsprintf(buffer, L"MaxIconY: %5d", GetSystemMetrics(SM_CYICON)));
	TextOut(hdc, 20, 180, buffer, wsprintf(buffer, L"ScreenX: %5d", GetDeviceCaps(hdc, HORZRES)));
	TextOut(hdc, 20, 210, buffer, wsprintf(buffer, L"ScreenY: %5d", GetDeviceCaps(hdc, VERTRES)));
	TextOut(hdc, 20, 240, buffer, wsprintf(buffer, L"AveragedSizeText: %5d", tm.tmAveCharWidth));
	TextOut(hdc, 20, 270, buffer, wsprintf(buffer, L"SizeSpaceUnderChar: %5d", tm.tmInternalLeading));
}

LRESULT CALLBACK WndProc2(_In_ HWND   hWnd, _In_ UINT   message, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	static TCHAR ch;
	wchar_t buffer[100];
	TEXTMETRIC tm;
	RECT rectWindow;
	POINT pt;
	RECT t_rect;
	RECT lastPointRect;
	static bool flag = 0;
	GetWindowRect(hWnd, &rectWindow);
	hdc = GetDC(hWnd);
	GetTextMetrics(hdc, &tm);
	HBRUSH brush = GetSysColorBrush(5);
	static int X = 0, Y = 0;
	static int x = 0, y = 0;

	switch (message)
	{
	case WM_CREATE: 				//Повідомлення приходить при створенні вікна
		break;
	case WM_LBUTTONDOWN:
		Metrics(hdc, buffer, tm);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_NUMPAD5 && !flag) {
			hdc = GetDC(hWnd);
			lastPointRect.top = Y;
			lastPointRect.left = X;
			lastPointRect.right = X + 20;
			lastPointRect.bottom = Y + 20;
			FillRect(hdc, &lastPointRect, brush);
			flag = 1;
			x = 0;
			y = 0;
			ReleaseDC(hWnd, hdc);
		}
		if (wParam == VK_NUMPAD0 && flag) {
			flag = 0;
			X = x;
			Y = y;
		}
		break;
	case WM_MOUSEMOVE:
		if (flag) {
			hdc = GetDC(hWnd);
			t_rect.top = y;
			t_rect.left = x;
			t_rect.right = x + 20;
			t_rect.bottom = y + 20;
			FillRect(hdc, &t_rect, brush);
			GetCursorPos(&pt);
			x = pt.x - 15; y = pt.y - 40;
			SetBkMode(hdc, TRANSPARENT);
			TextOut(hdc, x, y, &ch, 1);
			ReleaseDC(hWnd, hdc);
		}
		break;
	case WM_CHAR:
		if (!flag) {
			ch = (TCHAR)wParam;
			hdc = GetDC(hWnd);
			X = rand() % rectWindow.right;
			Y = rand() % rectWindow.bottom;
			SetBkMode(hdc, TRANSPARENT);
			TextOut(hdc, X + 100, Y, &ch, 1);
			ReleaseDC(hWnd, hdc);
		}
		break;
	case WM_PAINT: //Перемалювати вікно
		hdc = BeginPaint(hWnd, &ps); //Почати графічний вивід
		GetClientRect(hWnd, &rectWindow); //Область вікна для малювання
		EndPaint(hWnd, &ps); //Закінчити графічний вивід
		break;
	case WM_DESTROY: //Завершення роботи
		Destroyed = true;

		DestroyWindow(hWnd);
		break;
	default:
		//Обробка повідомлень, які не оброблені користувачем
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

//lb3
struct square {
	int numb;
	COLORREF clr;
	int x, y;
};
void ToChar(int num, wchar_t t[4]) {
	int temp;

	for (int i = 0; i < 4; i++) {
		temp = (num / pow(10, 3 - i));
		t[i] = (temp % 10) + 48;
	}
}
void ShowLab3(HWND hWnd, int x, int y, int width, int height)
{
	WNDCLASS wc;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = NULL;
	wc.lpszClassName = L"Lab3";
	wc.lpszMenuName = 0;
	wc.lpfnWndProc = WndProc3;
	RegisterClassW(&wc);

	lb3 = CreateWindowW(L"Lab3", L"Window Application", WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_VISIBLE | WS_CLIPSIBLINGS,
		x, y, width, height, NULL, NULL, NULL, NULL);
	SetParent(lb3, hWnd);
	ShowWindow(lb3, SW_SHOWNORMAL);
}
LRESULT CALLBACK WndProc3(_In_ HWND   hWnd, _In_ UINT   message, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	static PAINTSTRUCT ps;
	HDC hdc;
	HDC Txthdc;
	RECT rt;
	LOGFONT fnt;
	HBRUSH hbr;
	static POINT Mouse1{ 0,0 };
	static POINT Mouse2{ 0,0 };


	static LOGFONT lf;
	lf.lfPitchAndFamily = VARIABLE_PITCH;
	lf.lfHeight = 15;
	static HFONT hf;

	static square tSquare;
	static bool MouseFlag = 0;
	static int clck = 1;
	static int r, g, b;
	static int sizeX = GetSystemMetrics(SM_CXFULLSCREEN);
	static int sizeY = GetSystemMetrics(SM_CYFULLSCREEN);
	static int flag = 1;
	wchar_t text[4]{ L' ',L' ',L' ',L' ' };

	const int size = 50;
	static square** arr = new square * [sizeY / size];
	if (flag) {
		for (int i = 0; i < sizeY / size; i++)
			arr[i] = new  square[sizeX / size];
		flag = 0;
	}

	switch (message)
	{
	case WM_SIZE:
		GetClientRect(hWnd, &rt);
		break;
	case WM_CREATE: //Повідомлення приходить при створенні вікна
		for (int i = 0; i < sizeY / size; i++) {
			for (int j = 0; j < sizeX / size; j++) {
				r = rand() % 254;
				g = rand() % 254;
				b = rand() % 254;
				arr[i][j].clr = RGB(r, g, b);
				arr[i][j].numb = 0;
				arr[i][j].y = i + 1;
				arr[i][j].x = j + 1;
			}
		}
		break;
	case WM_PAINT:
		GetClientRect(hWnd, &rt);
		hdc = BeginPaint(hWnd, &ps);
		TemporaryDC = CreateCompatibleDC(hdc);
		BitmapDC = CreateCompatibleBitmap(hdc, rt.right - rt.left, rt.bottom - rt.top);
		//take bitmap as a dc
		SelectObject(TemporaryDC, BitmapDC);
		GetClientRect(hWnd, &rt);
		hf = CreateFontIndirect(&lf);
		SetBkMode(TemporaryDC, TRANSPARENT);
		SelectObject(TemporaryDC, hf);
		for (int i = 0; i < rt.bottom / size; i++) {
			for (int j = 0; j < rt.right / size; j++) {
				if (arr[i][j].numb <= 0) {
					arr[i][j].numb = clck++;
				}
				hbr = CreateSolidBrush(arr[i][j].clr);
				SelectObject(TemporaryDC, hbr);
				Rectangle(TemporaryDC, int(arr[i][j].x - 1) * size, int(arr[i][j].y - 1) * size, int(arr[i][j].x) * size, int(arr[i][j].y) * size);
				DeleteObject(hbr);
				ToChar(arr[i][j].numb, text);
				TextOut(TemporaryDC, (arr[i][j].x - 1) * size + 2, (arr[i][j].y - 1) * size + 2, text, 4);
			}
		}
		DeleteObject(hf);
		
		BitBlt(hdc, 0, 0, rt.right - rt.left, rt.bottom - rt.top, TemporaryDC, 0, 0, SRCCOPY);
		DeleteDC(hdc);
		//release memory
		DeleteDC(TemporaryDC);
		DeleteObject(BitmapDC);
		EndPaint(hWnd, &ps); //Закінчити графічний вивід
		break;
	case WM_LBUTTONDOWN:
		if (MouseFlag) {
			Mouse2.x = LOWORD(lParam);
			Mouse2.y = HIWORD(lParam);

			tSquare.numb = arr[Mouse1.y / size][Mouse1.x / size].numb;
			tSquare.clr = arr[Mouse1.y / size][Mouse1.x / size].clr;
			arr[Mouse1.y / size][Mouse1.x / size].numb = arr[Mouse2.y / size][Mouse2.x / size].numb;
			arr[Mouse1.y / size][Mouse1.x / size].clr = arr[Mouse2.y / size][Mouse2.x / size].clr;
			arr[Mouse2.y / size][Mouse2.x / size].clr = tSquare.clr;
			arr[Mouse2.y / size][Mouse2.x / size].numb = tSquare.numb;
			MouseFlag = 0;
			RECT t_rt;
			t_rt.left = (Mouse1.x / size) * size;
			t_rt.right = (Mouse1.x / size) * size + size;
			t_rt.top = (Mouse1.y / size) * size;
			t_rt.bottom = (Mouse1.y / size) * size + size;
			InvalidateRect(hWnd, &t_rt, TRUE);
			t_rt.left = (Mouse2.x / size) * size;
			t_rt.right = (Mouse2.x / size) * size + size;
			t_rt.top = (Mouse2.y / size) * size;
			t_rt.bottom = (Mouse2.y / size) * size + size;
			InvalidateRect(hWnd, &t_rt, TRUE);
		}
		else {
			MouseFlag = 1;
			Mouse1.x = LOWORD(lParam);
			Mouse1.y = HIWORD(lParam);
		}
		break;
	
	case WM_DESTROY: //Завершення роботи
		Destroyed = true;

		DestroyWindow(hWnd);
		break;
	default:
		//Обробка повідомлень, які не оброблені користувачем
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
//lb4
void ShowLab4(HWND hWnd, int x, int y, int width, int height)
{
	WNDCLASS wc;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = NULL;
	wc.lpszClassName = L"Lab4";
	wc.lpszMenuName = MAKEINTRESOURCE(MENU5);
	wc.lpfnWndProc = WndProc4;
	RegisterClassW(&wc);

	lb4 = CreateWindowW(L"Lab4", L"Window Application", WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_VISIBLE | WS_CLIPSIBLINGS,
		x, y, width, height, NULL, NULL, NULL, NULL);
	SetParent(lb4, hWnd);
	ShowWindow(lb4, SW_SHOWNORMAL);
}
LRESULT CALLBACK WndProc4(_In_ HWND   hWnd, _In_ UINT   message, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	HICON hIcon = (HICON)LoadImage(
		NULL,
		L"small.ico",
		IMAGE_ICON,
		0,
		0,
		LR_LOADFROMFILE |
		LR_DEFAULTSIZE |
		LR_SHARED
	);

	PAINTSTRUCT ps;
	HDC hdc;
	RECT rt;
	static TCHAR ch;
	HBRUSH hbr = CreateSolidBrush(RGB(100, 150, 100));
	static HWND twnd[12];
	static LPDRAWITEMSTRUCT drw;
	HWND tt;

	TEXTMETRIC tm;
	RECT rect;
	POINT pt[3];
	int cx, cy;
	static bool flag[3] = { 0,0,0 };
	static TCHAR buff1[50];
	static TCHAR buff2[50];
	static TCHAR buff3[50];

	switch (message)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case 10:
			GetWindowText(twnd[9], buff1, 12);
			SetWindowText(twnd[0], buff1);
			rt = { 100, 100, 100, 50 };
			InvalidateRect(hWnd, &rt, 1);
			break;
		case 11:
			GetWindowText(twnd[10], buff2, 12);
			SetWindowText(twnd[1], buff2);
			rt = { 300, 100, 100, 50 };
			InvalidateRect(hWnd, &rt, 1);
			break;
		case 12:
			GetWindowText(twnd[11], buff3, 12);
			SetWindowText(twnd[2], buff3);
			rt = { 500, 100, 100, 50 };
			InvalidateRect(hWnd, &rt, 1);
			break;
		case 7:
			ShowWindow(twnd[0], SendMessage(twnd[6], BM_GETCHECK, 1, 0));
			break;
		case 8:
			ShowWindow(twnd[1], SendMessage(twnd[7], BM_GETCHECK, 1, 0));
			break;
		case 9:
			ShowWindow(twnd[2], SendMessage(twnd[8], BM_GETCHECK, 1, 0));
			break;
		case 4:
			break;
		}
		break;
	case WM_DRAWITEM:
		drw = (LPDRAWITEMSTRUCT)lParam;
		FillRect(drw->hDC, &drw->rcItem,
			(HBRUSH)GetStockObject(WHITE_BRUSH));
		FrameRect(drw->hDC, &drw->rcItem,
			(HBRUSH)GetStockObject(BLACK_BRUSH));
		cx = (drw->rcItem.right - drw->rcItem.left) / 2;
		cy = (drw->rcItem.bottom - drw->rcItem.top) / 2;

		if (drw->itemState & ODS_SELECTED) {
			FillRect(drw->hDC, &drw->rcItem,
				CreateSolidBrush(RGB(220, 220, 220)));
			FrameRect(drw->hDC, &drw->rcItem,
				(HBRUSH)GetStockObject(BLACK_BRUSH));
		}

		switch (drw->CtlID) {
		case 1:
			SetBkMode(drw->hDC, TRANSPARENT);
			hdc = GetDC(hWnd);
			SelectObject(drw->hDC, hbr);
			if (SendMessage(twnd[3], BM_GETCHECK, 1, 0)) {
				DrawIconEx(drw->hDC, 10, 10, hIcon, 32, 32, 0, NULL, DI_NORMAL);
			}
			else DrawText(drw->hDC, buff1, -1, &drw->rcItem, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			break;
		case 2:
			SetBkMode(drw->hDC, TRANSPARENT);
			hdc = GetDC(hWnd);
			SelectObject(drw->hDC, hbr);
			if (SendMessage(twnd[4], BM_GETCHECK, 1, 0)) {
				DrawIconEx(drw->hDC, 10, 10, hIcon, 32, 32, 0, NULL, DI_NORMAL);
			}
			else DrawText(drw->hDC, buff2, -1, &drw->rcItem, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			break;
		case 3:
			SetBkMode(drw->hDC, TRANSPARENT);
			hdc = GetDC(hWnd);
			SelectObject(drw->hDC, hbr);
			if (SendMessage(twnd[5], BM_GETCHECK, 1, 0)) {
				DrawIconEx(drw->hDC, 10, 10, hIcon, 32, 32, 0, NULL, DI_NORMAL);
			}
			else DrawText(drw->hDC, buff3, -1, &drw->rcItem, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			break;

		}

		break;
	case WM_CREATE: //Повідомлення приходить при створенні вікна
		twnd[3] = CreateWindow(L"button", L"Icon", WS_CHILD | BS_AUTORADIOBUTTON | WS_VISIBLE, 120, 170, 55, 13, hWnd, (HMENU)4, hInst, NULL);
		twnd[4] = CreateWindow(L"button", L"Icon", WS_CHILD | BS_AUTORADIOBUTTON | WS_VISIBLE, 320, 170, 55, 13, hWnd, (HMENU)5, hInst, NULL);
		twnd[5] = CreateWindow(L"button", L"Icon", WS_CHILD | BS_AUTORADIOBUTTON | WS_VISIBLE, 520, 170, 55, 13, hWnd, (HMENU)6, hInst, NULL);

		twnd[6] = CreateWindow(L"button", buff3, WS_CHILD | BS_AUTOCHECKBOX | WS_VISIBLE, 80, 120, 13, 13, hWnd, (HMENU)7, hInst, NULL);
		twnd[7] = CreateWindow(L"button", buff3, WS_CHILD | BS_AUTOCHECKBOX | WS_VISIBLE, 280, 120, 13, 13, hWnd, (HMENU)8, hInst, NULL);
		twnd[8] = CreateWindow(L"button", buff3, WS_CHILD | BS_AUTOCHECKBOX | WS_VISIBLE, 480, 120, 13, 13, hWnd, (HMENU)9, hInst, NULL);
		SendMessage(twnd[6], BM_SETCHECK, 1, 0);
		SendMessage(twnd[7], BM_SETCHECK, 1, 0);
		SendMessage(twnd[8], BM_SETCHECK, 1, 0);

		twnd[9] = CreateWindow(L"edit", buff1, WS_CHILD | WS_VISIBLE, 110, 60, 80, 20, hWnd, (HMENU)10, hInst, NULL);
		twnd[10] = CreateWindow(L"edit", buff2, WS_CHILD | WS_VISIBLE, 310, 60, 80, 20, hWnd, (HMENU)11, hInst, NULL);
		twnd[11] = CreateWindow(L"edit", buff3, WS_CHILD | WS_VISIBLE, 510, 60, 80, 20, hWnd, (HMENU)12, hInst, NULL);

		twnd[0] = CreateWindow(L"button", buff1, WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, 100, 100, 100, 50, hWnd, (HMENU)1, hInst, NULL);
		twnd[1] = CreateWindow(L"button", buff2, WS_CHILD | BS_OWNERDRAW | WS_VISIBLE, 300, 100, 100, 50, hWnd, (HMENU)2, hInst, NULL);
		twnd[2] = CreateWindow(L"button", buff3, WS_CHILD | BS_OWNERDRAW | WS_VISIBLE, 500, 100, 100, 50, hWnd, (HMENU)3, hInst, NULL);
		break;
	case WM_PAINT: //Перемалювати вікно
		hdc = BeginPaint(hWnd, &ps); //Почати графічний вивід
		GetClientRect(hWnd, &rt); //Область вікна для малювання

		EndPaint(hWnd, &ps); //Закінчити графічний вивід
		break;
	case WM_DESTROY: //Завершення роботи
		Destroyed = true;

		DestroyWindow(hWnd);
		break;
	default:
		//Обробка повідомлень, які не оброблені користувачем
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
//lb5
void ShowLab5(HWND hWnd, int x, int y, int width, int height)
{
	WNDCLASS wc;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = NULL;
	wc.lpszClassName = L"Lab5";
	wc.lpszMenuName = MAKEINTRESOURCE(MENU5);
	wc.lpfnWndProc = WndProc5;
	RegisterClassW(&wc);

	lb5 = CreateWindowW(L"Lab5", L"Window Application", WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_VISIBLE | WS_CLIPSIBLINGS,
		x, y, width, height, NULL, NULL, NULL, NULL);
	SetParent(lb5, hWnd);
	ShowWindow(lb5, SW_SHOWNORMAL);
}
#include <thread>
STARTUPINFO si;
PROCESS_INFORMATION pi;
bool ProcessOpened = false;
bool isexit = false;
HWND hwndHandle;
CRITICAL_SECTION cs;
struct time {

	std::wstring wstr;

} t;
DWORD WINAPI TimeOut(CONST LPVOID lParam)
{
	using namespace std::chrono_literals;


	while (!isexit)
	{
		//get window dc
		HDC WindowDC = GetDC((HWND)lParam);

		HDC TemporaryDC = CreateCompatibleDC(WindowDC);

		HBITMAP BitmapDC = CreateCompatibleBitmap(WindowDC, rt.right - rt.left, rt.bottom - rt.top);
		//take bitmap as a dc
		SelectObject(TemporaryDC, BitmapDC);

		//SelectObject(dc, GetStockObject(DC_PEN));
		//SetDCPenColor(dc, RGB(255, 255, 0));
		EnterCriticalSection(&cs);
		//								gitting wstr size by subtraction pointers
		TextOut(TemporaryDC, 0, 0, t.wstr.c_str(), t.wstr.end() - t.wstr.begin());
		//copy dc(bitmap) to hdc(our screen)
		BitBlt(WindowDC, 0, 0, rt.right - rt.left, rt.bottom - rt.top, TemporaryDC, 0, 0, SRCCOPY);
		LeaveCriticalSection(&cs);
		//release memory
		DeleteDC(TemporaryDC);
		DeleteObject(BitmapDC);

	}
	ExitThread(25);
}

DWORD WINAPI RefreshTime(CONST LPVOID)
{
	while (isexit == false)
	{


#pragma warning(disable : 4996)
		//C style define time
		const size_t buffersize = 14;
		char buffer[buffersize];
		time_t seconds = time(NULL);
		tm* timeinfo = localtime(&seconds);
		const char* format = "%Y %I:%M:%S";
		strftime(buffer, buffersize, format, timeinfo);
		std::wstring wstr2(buffersize, L'#');
		mbstowcs(&wstr2[0], buffer, buffersize);
		//entering critical section
		EnterCriticalSection(&cs);
		t.wstr = wstr2;

		LeaveCriticalSection(&cs);
	}

	ExitThread(26);
}
LRESULT CALLBACK WndProc5(_In_ HWND   hWnd, _In_ UINT   message, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
switch (message)
	{
	case WM_COMMAND:

		switch (wParam)
		{
		case ID_CREATE_PROCESS:
			if (!ProcessOpened)
			{
				ProcessOpened = true;

				CreateProcess(
					_T("C:\\Windows\\System32\\notepad.exe"), NULL, NULL, NULL, TRUE, NULL, NULL, NULL,
					&si,
					&pi
				);
			}
			break;
		case ID_CLOSE_PROCESS:
			if (ProcessOpened)
			{
				ProcessOpened = false;
				TerminateProcess(pi.hProcess, 1);
			}
			else MessageBox(hWnd,
				_T("There is no process"),
				_T("Process menu warning"), MB_OK);
			break;
		case ID_EXIT_PROCESS:
			if (ProcessOpened)
			{
				TerminateProcess(pi.hProcess, 1);
				ProcessOpened = false;
			}
			SendMessage(hWnd, WM_CLOSE, wParam, lParam);
			break;
		default:
			break;
		}
		break;
	case WM_CREATE:
		InitializeCriticalSection(&cs);
		
		CreateThread(0, 0, &RefreshTime, 0, 0, 0);
		CreateThread(0, 0, &TimeOut,hWnd, 0, 0);
		break;
	case WM_SIZE:
		GetClientRect(hWnd, &rt);
		break;
	case WM_CLOSE:
		Destroyed = true;

		isexit = true;
		using namespace std::chrono_literals;
		std::this_thread::sleep_for(1s);
		DestroyWindow(hWnd);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
return 0;
}

//lb6
void ShowLab6(HWND hWnd, int x, int y, int width, int height)
{
	WNDCLASS wc;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = NULL;
	wc.lpszClassName = L"Lab6";
	wc.lpszMenuName = MAKEINTRESOURCE(MENU6);
	wc.lpfnWndProc = WndProc6;
	RegisterClassW(&wc);

	lb6 = CreateWindowW(L"Lab6", L"Window Application", WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_VISIBLE | WS_CLIPSIBLINGS,
		x, y, width, height, NULL, NULL, NULL, NULL);
	SetParent(lb6, hWnd);
	ShowWindow(lb6, SW_SHOWNORMAL);
}
HWND hwnd_textpox;
HWND main_text_box;
#define ID_TEXTBOX 001
bool someFileIsOpen = false;
TCHAR FileName[32];
wstring wFileName;
HANDLE hFileCreate = nullptr;
WIN32_FIND_DATA FileData;

HANDLE hFileFind = nullptr;
void DeleteFileByFormat(HWND hWnd, int format)
{
	OPENFILENAME ofn;       // common dialog box structure 
	TCHAR szFile[260];       // buffer for file name 
	HANDLE hf; // open file handle 

	// Initialize OPENFILENAME 
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	if (format == 0x000)
		ofn.lpstrFilter = L"Execution files\0*.exe";
	else if (format == 0x001)
		ofn.lpstrFilter = L"Text files\0*.txt";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (GetOpenFileName(&ofn) == TRUE)
	{
		hf = CreateFile(ofn.lpstrFile, GENERIC_READ,
			0, (LPSECURITY_ATTRIBUTES)NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
			(HANDLE)NULL);

		CloseHandle(hf);
		if (format == 0x003)
		{
			wFileName = ofn.lpstrFile;
			return;
		}
		if (format == 0x104)
		{

			using std::to_wstring;
			WIN32_FILE_ATTRIBUTE_DATA fInfo;
			GetFileAttributesEx(ofn.lpstrFile, GetFileExInfoStandard, &fInfo);
			SYSTEMTIME stCreation, stAccess;
			FileTimeToSystemTime(&(fInfo.ftCreationTime), &stCreation);
			FileTimeToSystemTime(&(fInfo.ftLastWriteTime), &stAccess);
			wstring output;
			output += L"File attiributes: " + to_wstring(fInfo.dwFileAttributes);
			output += L"\r\n\r\n";
			output += L"Creating time: " + to_wstring(stCreation.wDay) + L"/" + to_wstring(stCreation.wMonth) + L"/" + to_wstring(stCreation.wYear) + L"  " + to_wstring(stCreation.wHour) + L":" + to_wstring(stCreation.wSecond) + L":" + to_wstring(stCreation.wMilliseconds);
			output += L"\r\n\r\n";
			output += L"Last write time: " + to_wstring(stAccess.wDay) + L"/" + to_wstring(stAccess.wMonth) + L"/" + to_wstring(stAccess.wYear) + L"  " + to_wstring(stAccess.wHour) + L":" + to_wstring(stAccess.wSecond) + L":" + to_wstring(stAccess.wMilliseconds);
			

			MessageBox(hWnd, output.c_str(), L"File info", MB_OK);
			return;
		}
		DeleteFile(ofn.lpstrFile);
	}
}
bool CheckFileName(const wstring& str)
//checks if file name correct
//if successful returns TRUE(1)
{	//(if it is empty) (if the dot was NOT found) (if the file extension after (.) was NOT declared)
	if (str.empty() || str.find(_T(".")) == -1 || str.substr(str.find(_T(".")) + 1, str.size() - str.find(_T("."))) == _T("\0"))
	{
		return FALSE;
	}
	return TRUE;
}

INT_PTR CALLBACK DlgProc_forCreate(	_In_ HWND   hWnd,_In_ UINT   message,_In_ WPARAM wParam,_In_ LPARAM lParam)
{

	switch (message)
	{
		//initializing the dialog window
	case WM_INITDIALOG:
		::hwnd_textpox = CreateWindow(
			_T("edit"),										//textbox
			_T(".txt"),										//value which shows by start
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT,
			90, 50,
			110, 20,
			hWnd, (HMENU)ID_TEXTBOX, 0, 0);
		break;
	case WM_COMMAND:
		switch (wParam)
		{
		case IDOK:
			//clear the buff
			wFileName.clear();
			//get text from textbox
			GetWindowText(hwnd_textpox, FileName, 32);
			//copying TCHAR to std::wstring
			wFileName = FileName;
			//check if file name correct
			if (CheckFileName(wFileName) == FALSE)
			{
				MessageBox(
					hWnd,
					_T("Wrong file name!"),
					_T("Create file error"),
					MB_OK | MB_ICONWARNING
				);
			}
			//adding to the file path the desktop path (for correct work if need change `Notebook` to your username)
			wFileName = _T("C:\\Users\\slawz\\Desktop\\Новая папка\\") + wFileName;
			//finding file, if it`s exist - end the dilog
			hFileFind = FindFirstFile(&wFileName[0], &FileData);
			//checks if file is already exist
			if (hFileFind != INVALID_HANDLE_VALUE)
			{
				int returnMessage;
				returnMessage = MessageBox(
					hWnd,
					_T("File is already exist! Would u like to rewrite it!"),
					_T("Create file error"),
					MB_YESNO | MB_ICONWARNING
				);
				if ( returnMessage == IDYES)
				{
					FindClose(hFileFind);

					DeleteFile(&wFileName[0]);

					auto h = CreateFile(
						&wFileName[0],
						GENERIC_WRITE, 0, NULL,
						CREATE_ALWAYS,
						FILE_ATTRIBUTE_NORMAL, NULL);

					//end dialog
					CloseHandle(h);
					SendMessage(hWnd, WM_CLOSE, wParam, lParam);
				}
				FindClose(hFileFind);

				//end dialog
				SendMessage(hWnd, WM_CLOSE, wParam, lParam);
				/*return 0;*/
				break;
			}
			//creating file
			hFileCreate = CreateFile(
				&wFileName[0],
				GENERIC_WRITE, 0, NULL,
				CREATE_NEW,
				FILE_ATTRIBUTE_NORMAL, NULL);
			//checks if file wasn`t created
			if (INVALID_HANDLE_VALUE == hFileCreate)
			{
				MessageBox(
					hWnd,
					_T("File hasn`t created!"),
					_T("Create file error"),
					MB_OK | MB_ICONWARNING
				);

				//end dialog
				SendMessage(hWnd, WM_CLOSE, wParam, lParam);
			}
			CloseHandle(hFileCreate);
			//end dialog
			SendMessage(hWnd, WM_CLOSE, wParam, lParam);
			break;
		case IDCANCEL:
			//end dialog
			SendMessage(hWnd, WM_CLOSE, wParam, lParam);
			break;
		default:
			break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return FALSE;
		break;
	}
	return FALSE;
}
INT_PTR CALLBACK DlgProc_forDelete(	_In_ HWND hWnd,_In_ UINT   message,_In_ WPARAM wParam,_In_ LPARAM lParam)
{
	switch (message)
	{
		//initializing a dialog win 
	case WM_INITDIALOG:
		//initializing a textbox
		::hwnd_textpox = CreateWindow(
			_T("edit"),										//textbox								
			_T(".txt"),										//value which shows by start
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT,
			90, 50,
			110, 20,
			hWnd, (HMENU)ID_TEXTBOX, 0, 0);
		break;
	case WM_COMMAND:
		switch (wParam)
		{
		case IDOK:
			//clear the buff
			wFileName.clear();
			//get text from textbox
			GetWindowText(hwnd_textpox, FileName, 32);
			//copying TCHAR to std::wstring
			wFileName = FileName;
			//setting up the path to the desktop
			wFileName = _T("C:\\Users\\slawz\\Desktop\\Новая папка\\") + wFileName;
			//finding file
			hFileFind = FindFirstFile(&wFileName[0], &FileData);
			//if NOT found repeat dialog delete box
			if (hFileFind == INVALID_HANDLE_VALUE)
			{
				MessageBox(
					hWnd,
					_T("File doesn`t exist!"),
					_T("Delete file error"),
					MB_OK | MB_ICONWARNING
				);
				FindClose(hFileFind);
				//end dialog
				return FALSE;
				break;
			}
			//deletes file (&wFileName[0] is a converting a wstring to LPCWSTR)
			DeleteFile(&wFileName[0]);
			//throws a message box about succesfull deleting
			MessageBox(
				hWnd,
				_T("File succesfully deleted!"),
				_T("Delete file info"),
				MB_OK | MB_ICONINFORMATION
			);
			CloseHandle(hFileCreate);
			//end dialog
			SendMessage(hWnd, WM_CLOSE, wParam, lParam);
			break;
		case IDCANCEL:
			//end dialog
			SendMessage(hWnd, WM_CLOSE, wParam, lParam);
			break;
		default:
			break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return FALSE;
		break;
	}
	return FALSE;
}
LRESULT CALLBACK WndProc6(_In_ HWND   hWnd, _In_ UINT   message, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	string initialLocation, newLocation;
	wstring wCutLocation, wNewLocation;
	int backslashPos;
	const wchar_t* wcNewLocation = nullptr;
	const wchar_t* wcOldLocation = nullptr;
	switch (message)
	{
	case WM_COMMAND:

		switch (wParam)
		{
		case ID_CREATE_FILE:
			DialogBoxParam(
				hInst,
				MAKEINTRESOURCE(IDD_DIALOG1),
				hWnd,
				DlgProc_forCreate,
				0
			);
			break;
		case ID_DELETEFILE_ONLYEXE:
			DeleteFileByFormat(hWnd, 0);
			break;
		case ID_DELETEFILE_ONLYTXT:
			DeleteFileByFormat(hWnd, 1);
			break;
		case ID_DELETE_FILE:
			DialogBoxParam(
				hInst,
				MAKEINTRESOURCE(IDD_DIALOG2),
				hWnd,
				DlgProc_forDelete,
				0
			);
			break;
		case ID_FILE_MOVE:
			DeleteFileByFormat(hWnd, 3);
			initialLocation = std::string(wFileName.begin(), wFileName.end());
			backslashPos = initialLocation.find_last_of("\\", wFileName.size() - 1);
			wCutLocation = wFileName.substr(backslashPos + 1, wFileName.size() - backslashPos);
			newLocation = "C:\\Users\\slawz\\Desktop\\" + std::string(wCutLocation.begin(), wCutLocation.end());
			wNewLocation = std::wstring(newLocation.begin(), newLocation.end());
			wcNewLocation = wNewLocation.c_str();
			wcOldLocation = wFileName.c_str();
			MoveFile(wcOldLocation, wcNewLocation);
			break;
		case ID_FILE_FILEINFO:
			DeleteFileByFormat(hWnd, 0x104);

			break;
		default:
			break;
		}
		break;
	case WM_SIZE:
		GetClientRect(hWnd, &rt);
		break;
	case WM_DESTROY:
		Destroyed = true;

		DestroyWindow(hWnd);

		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return 0;
}
//lb7
wstring KeyboardBuffer;

void Draw(HDC WindowDC)
{
	HINSTANCE dllC = LoadLibrary(_T("dllColor.dll"));

	if (!dllC)
	{
		MessageBox(0, L"Cannot open dll", L"spro_lb3 error", MB_ICONSTOP);
	}
	typedef void (*dllColor) (HDC);


	dllColor randomTextColour;
	randomTextColour = (dllColor)GetProcAddress(dllC, "RandomTextColour");
	TemporaryDC = CreateCompatibleDC(WindowDC);

	BitmapDC = CreateCompatibleBitmap(WindowDC, rt.right - rt.left, rt.bottom - rt.top);

	//take bitmap as a dc
	SelectObject(TemporaryDC, BitmapDC);

	randomTextColour(TemporaryDC);
	DrawText(TemporaryDC, &KeyboardBuffer[0], KeyboardBuffer.size(), &rt, 0);

	BitBlt(WindowDC, 0, 0, rt.right - rt.left, rt.bottom - rt.top, TemporaryDC, 0, 0, SRCCOPY);

	DeleteDC(TemporaryDC);
	DeleteObject(BitmapDC);
	FreeLibrary(dllC);
}
void ShowLab7(HWND hWnd, int x, int y, int width, int height)
{
	WNDCLASS wc;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = NULL;
	wc.lpszClassName = L"Lab7";
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = WndProc7;
	RegisterClassW(&wc);

	lb7 = CreateWindowW(L"Lab7", L"Window Application", WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_VISIBLE | WS_CLIPSIBLINGS,
		x, y, width, height, NULL, NULL, NULL, NULL);
	SetParent(lb7, hWnd);
	ShowWindow(lb7, SW_SHOWNORMAL);
}
LRESULT CALLBACK WndProc7(_In_ HWND   hWnd, _In_ UINT   message, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	HDC WindowDC;
	WindowDC = GetDC(hWnd);
	switch (message)
	{
	case WM_CREATE:

		break;
	case WM_CHAR:
		switch (wParam)
		{
		case 0x08:
			if (KeyboardBuffer.size() != 0)
			{
				KeyboardBuffer.pop_back();
				KeyboardBuffer.replace(KeyboardBuffer.end() - 2, KeyboardBuffer.end() - 1, L"\0");
			}

			break;
		}
		KeyboardBuffer.push_back(ChangeCase(wParam == 0x08 && KeyboardBuffer.size() != 0 ? L'\0' : (TCHAR)wParam));

		Draw(WindowDC);
		//set the window title to check the uotputting text
		SetWindowText(hWnd, &KeyboardBuffer[0]);
		//FreeLibrary(dllF);

		break;
	case WM_SIZE:
		GetClientRect(hWnd, &rt);
		Draw(WindowDC);
		break;
	case WM_DESTROY:
		Destroyed = true;

		DestroyWindow(hWnd);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return 0;
}

#include <string>
typedef std::basic_string<TCHAR, std::char_traits<TCHAR>,
	std::allocator<TCHAR> > String;
//lb8
void ShowLab8(HWND hWnd, int x, int y, int width, int height)
{
	WNDCLASS wc;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = NULL;
	wc.lpszClassName = L"Lab8";
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = WndProc8;
	RegisterClassW(&wc);

	lb8 = CreateWindowW(L"Lab8", L"Window Application", WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_VISIBLE | WS_CLIPSIBLINGS,
		x, y, width, height, NULL, NULL, NULL, NULL);
	SetParent(lb8, hWnd);
	ShowWindow(lb8, SW_SHOWNORMAL);
}
HWND firstEdit8, secondEdit8, conButton8, disButton8, xorButton8, outputText8;
int s[32];
#define ID_NUM18 44
#define ID_NUM28 55
#define ID_CON 666
#define ID_DIS 777
#define ID_XOR 999
#define ID_OUTPUT 888
int doCon(int x, int y)
{
	int res;
	_asm {
		mov eax, x
		mov edx, y
		and eax, edx
		mov res, eax
	}
	return res;
}
int doDis(int x, int y)
{
	int res;
	_asm
	{
		mov eax, x
		mov ebx, y
		or eax, ebx
		mov res, eax
	}
	return res;
}
int doXor(int x, int y)
{
	int res;
	_asm {
		mov eax, x
		mov edx, y
		xor eax, edx
		mov res, eax
	}
	return res;
}
int dec2bin(int num) {
	int N = num;
	memset(&s, 0, 32);

	__asm {
		mov eax, num
		test eax, eax
		jns start
		neg num
		start :
		mov eax, 2
			mov ebx, 2
			mov edx, 0
			mov esi, 31
			WhileLoop :
			mov eax, num
			div ebx
			mov[s + esi * 4], edx
			dec esi
			mov edx, 0
			mov num, eax
			cmp num, 0
			jnz WhileLoop
			mov eax, N
			test eax, eax
			jns endf
			mov ecx, 0
			InvertLoop:
		cmp[s + ecx * 4], 0
			jne eqNull
			jz eqOne
			eqOne :
		mov[s + ecx * 4], 1
			inc ecx
			jmp endInvLoop
			eqNull :
		mov[s + ecx * 4], 0
			inc ecx
			endInvLoop :
		cmp ecx, 31
			jbe InvertLoop
			mov ecx, 31
			PlusOneLoop :
			cmp[s + ecx * 4], 0
			jz point2
			mov[s + ecx * 4], 0
			dec ecx
			cmp ecx, 0
			jge PlusOneLoop
			point2 :
		mov[s + ecx * 4], 1
			mov[s], 1
			endf :
	}

	return 0;
}
wstring formString(int num) {
	int p[32];
	wstring result;
	dec2bin(num);
	for (int i = 0; i < 32; i++)
		p[i] = char(s[i]);
	for (int i = 0; i < 32; i++)
		result += std::to_wstring(p[i]);
	return result;
}
LRESULT CALLBACK WndProc8(_In_ HWND   hWnd, _In_ UINT   message, _In_ WPARAM wParam, _In_ LPARAM lParam) 
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rt;

	int size;
	wchar_t* X;
	wchar_t* Y;
	String res, num;
	int* pointer;
	char p[32];
	string result;

	for (int i = 0; i < 32; i++)
		s[i] = 0;

	switch (message)
	{
	case WM_CREATE:
		firstEdit8 = CreateWindow(L"edit", L"0", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER, 90, 25, 70, 25, hWnd, (HMENU)ID_NUM18, NULL, NULL);
		secondEdit8 = CreateWindow(L"edit", L"0", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER, 220, 25, 70, 25, hWnd, (HMENU)ID_NUM28, NULL, NULL);
		conButton8 = CreateWindow(L"button", L"*", WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON, 165, 10, 50, 25, hWnd, (HMENU)ID_CON, NULL, NULL);
		disButton8 = CreateWindow(L"button", L"+", WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON, 165, 40, 50, 25, hWnd, (HMENU)ID_DIS, NULL, NULL);
		xorButton8 = CreateWindow(L"button", L"(+)", WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON, 165, 70, 50, 25, hWnd, (HMENU)ID_XOR, NULL, NULL);
		outputText8 = CreateWindow(L"static", L"Press button", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, 10, 100, 360, 270, hWnd, (HMENU)ID_OUTPUT, NULL, NULL);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);
		break;
	case WM_COMMAND:
		switch (wParam) {
		case ID_CON:

			size = GetWindowTextLength(firstEdit8) * 4;
			X = new wchar_t[size];
			GetWindowText(firstEdit8, X, size);

			size = GetWindowTextLength(secondEdit8) * 4;
			Y = new wchar_t[size];
			GetWindowText(secondEdit8, Y, size);

			//res = formString(7); 

			res = res + L"X: " + formString(_wtol(X)) + L'\n' + L"Y: " + formString(_wtol(Y)) + L"\n";

			res = res + L"Сonjunction: " + formString(doCon(_wtol(X), _wtol(Y)));

			SetWindowText(outputText8, res.data());
			break;

		case ID_DIS:
			size = GetWindowTextLength(firstEdit8) * 4;
			X = new wchar_t[size];
			GetWindowText(firstEdit8, X, size);

			size = GetWindowTextLength(secondEdit8) * 4;
			Y = new wchar_t[size];
			GetWindowText(secondEdit8, Y, size);

			res = res + L"X: " + formString(_wtol(X)) + L'\n' + L"Y: " + formString(_wtol(Y)) + L"\n";

			res = res + L"Disjunction: " + formString(doDis(_wtol(X), _wtol(Y)));

			SetWindowText(outputText8, res.data());
			break;


		case ID_XOR:

			size = GetWindowTextLength(firstEdit8) * 4;
			X = new wchar_t[size];
			GetWindowText(firstEdit8, X, size);

			size = GetWindowTextLength(secondEdit8) * 4;
			Y = new wchar_t[size];
			GetWindowText(secondEdit8, Y, size);

			res = res + L"X: " + formString(_wtol(X)) + L'\n' + L"Y: " + formString(_wtol(Y)) + L"\n";

			res = res + L"By module 2: " + formString(doXor(_wtol(X), _wtol(Y)));

			SetWindowText(outputText8, res.data());
			break;
		}

		break;
	case WM_DESTROY:
		Destroyed = true;

		DestroyWindow(hWnd);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


//lb9
void ShowLab9(HWND hWnd, int x, int y, int width, int height)
{
	WNDCLASS wc;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = NULL;
	wc.lpszClassName = L"Lab9";
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = WndProc9;	
	RegisterClassW(&wc);

	lb9 = CreateWindowW(L"Lab9", L"Window Application", WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_VISIBLE | WS_CLIPSIBLINGS,
		x, y, width, height, NULL, NULL, NULL, NULL);
	SetParent(lb9, hWnd);
	ShowWindow(lb9, SW_SHOWNORMAL);
}

int Sum(int num)
{
	__asm
	{
		mov eax, num
		mov ebx, 0
		mov ecx, eax
		c :
		add ebx, ecx
			loop c
			mov eax, ebx

	}
}
int doSum(int num)
{
	int result;
	__asm
	{
		mov eax, num
		push eax
		call[Sum]
		mov result, eax
		pop eax
	}
	return result;
}
int Fib(unsigned int num)
{
	__asm
	{

		mov eax, num
		mov ebx, 0
		mov edx, 1
		mov ecx, eax
		//0 1 1 2 3 5 8 13 21 
		c :
		mov eax, edx
			add edx, ebx
			mov ebx, eax

			loop c
			mov eax, edx

	}
}
int doFib(int num)
{
	int result;
	__asm
	{
		mov eax, num

		push eax

		call[Fib]
		mov result, eax

		pop eax

	}
	return result;
}
int Fac(unsigned int num)
{
	__asm
	{
		mov eax, num
		mov ebx, 1
		mov ecx, eax
		c :
		imul ebx, ecx
			loop c
			mov eax, ebx
	}
}
int doFac(int num)
{
	int result;
	__asm
	{
		mov eax, num

		push eax

		call[Fac]
		mov result, eax

		pop eax

	}
	return result;
}
#define ID_NUM1 444
#define ID_NUM2 555
#define ID_SUM 666
#define ID_FIB 777
#define ID_FAC 999
HWND firstEdit, secondEdit, sumButton, fibButton, facButton;
LRESULT CALLBACK WndProc9(_In_ HWND   hWnd, _In_ UINT   message, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rt;

	wstring get, result;



	switch (message)
	{
	case WM_CREATE:
		firstEdit = CreateWindow(L"edit", L"0", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER, 90, 40, 70, 25, hWnd, (HMENU)ID_NUM1, NULL, NULL);
		secondEdit = CreateWindow(L"edit", L"0", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER, 220, 40, 70, 25, hWnd, (HMENU)ID_NUM2, NULL, NULL);
		sumButton = CreateWindow(L"button", L"sum", WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON, 165, 10, 50, 25, hWnd, (HMENU)ID_SUM, NULL, NULL);
		fibButton = CreateWindow(L"button", L"fib", WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON, 165, 40, 50, 25, hWnd, (HMENU)ID_FIB, NULL, NULL);
		facButton = CreateWindow(L"button", L"fac", WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON, 165, 70, 50, 25, hWnd, (HMENU)ID_FAC, NULL, NULL);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);
		break;
	case WM_COMMAND:
		switch (wParam) {
		case ID_SUM:
			GetWindowText(firstEdit, &get[0], 3);

			result = std::to_wstring(doSum(stoi(get)));

			SetWindowText(secondEdit, &result[0]);
			break;

		case ID_FIB:
			GetWindowText(firstEdit, &get[0], 3);

			result = std::to_wstring(doFib(stoi(get)));

			SetWindowText(secondEdit, &result[0]);
			break;


		case ID_FAC:
			GetWindowText(firstEdit, &get[0], 3);

			result = std::to_wstring(doFac(stoi(get)));

			SetWindowText(secondEdit, &result[0]);
			break;
		}

		break;
	case WM_DESTROY:
		Destroyed = true;

		DestroyWindow(hWnd);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
//
void AddComboBoxes(HWND hWnd)
{
	comboBoxA = CreateWindow(L"Combobox", NULL,
		CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
		0, 0, 100, 100, hWnd, NULL, NULL,
		NULL);

	const TCHAR* ComboBoxItems[] = { _T("Lab 1"), _T("Lab 2"), _T("Lab 3") };
	SendMessage(comboBoxA, (UINT)CB_ADDSTRING, 0, (LPARAM)ComboBoxItems[0]);
	SendMessage(comboBoxA, (UINT)CB_ADDSTRING, 0, (LPARAM)ComboBoxItems[1]);
	SendMessage(comboBoxA, (UINT)CB_ADDSTRING, 0, (LPARAM)ComboBoxItems[2]);

	int nIndex = SendMessage(comboBoxA, CB_GETCURSEL, 0, 0);
	TCHAR F[3];
	SendMessage(comboBoxA, CB_GETLBTEXT, (WPARAM)nIndex, (LPARAM)F);

	HMENU comboBoxALabChosen = (HMENU)COMBOBOX_A_LAB_CHOSEN;
	comboBoxAButton = CreateWindowExW(0L, L"Button", L"Run", WS_VISIBLE | WS_CHILD, 125, 0, 50, 23, hWnd, comboBoxALabChosen, NULL, NULL);


	comboBoxB = CreateWindow(L"Combobox", NULL,
		CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
		760, 0, 100, 100, hWnd, NULL, NULL,
		NULL);
	const TCHAR* ComboBoxItems2[] = { _T("Lab 4"), _T("Lab 5") };
	SendMessage(comboBoxB, (UINT)CB_ADDSTRING, 0, (LPARAM)ComboBoxItems2[0]);
	SendMessage(comboBoxB, (UINT)CB_ADDSTRING, 0, (LPARAM)ComboBoxItems2[1]);

	nIndex = SendMessage(comboBoxB, CB_GETCURSEL, 0, 0);
	TCHAR F2[2];
	SendMessage(comboBoxB, CB_GETLBTEXT, (WPARAM)nIndex, (LPARAM)F2);

	HMENU comboBoxBLabChosen = (HMENU)COMBOBOX_B_LAB_CHOSEN;
	comboBoxBButton = CreateWindowExW(0L, L"Button", L"Run", WS_VISIBLE | WS_CHILD, 895, 0, 50, 23, hWnd, comboBoxBLabChosen, NULL, NULL);


	comboBoxC = CreateWindow(L"Combobox", NULL,
		CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
		0, 400, 100, 100, hWnd, NULL, NULL,
		NULL);
	const TCHAR* ComboBoxItems3[] = { _T("Lab 6"), _T("Lab 7") };
	SendMessage(comboBoxC, (UINT)CB_ADDSTRING, 0, (LPARAM)ComboBoxItems3[0]);
	SendMessage(comboBoxC, (UINT)CB_ADDSTRING, 0, (LPARAM)ComboBoxItems3[1]);

	nIndex = SendMessage(comboBoxC, CB_GETCURSEL, 0, 0);
	TCHAR F3[2];
	SendMessage(comboBoxC, CB_GETLBTEXT, (WPARAM)nIndex, (LPARAM)F3);

	HMENU comboBoxCLabChosen = (HMENU)COMBOBOX_C_LAB_CHOSEN;
	comboBoxCButton = CreateWindowExW(0L, L"Button", L"Run", WS_VISIBLE | WS_CHILD, 125, 400, 50, 23, hWnd, comboBoxCLabChosen, NULL, NULL);


	comboBoxD = CreateWindow(L"Combobox", NULL,
		CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
		760, 400, 100, 100, hWnd, NULL, NULL,
		NULL);
	const TCHAR* ComboBoxItems4[] = { _T("Lab 8"), _T("Lab 9") };
	SendMessage(comboBoxD, (UINT)CB_ADDSTRING, 0, (LPARAM)ComboBoxItems4[0]);
	SendMessage(comboBoxD, (UINT)CB_ADDSTRING, 0, (LPARAM)ComboBoxItems4[1]);

	nIndex = SendMessage(comboBoxD, CB_GETCURSEL, 0, 0);
	TCHAR F4[2];
	SendMessage(comboBoxC, CB_GETLBTEXT, (WPARAM)nIndex, (LPARAM)F4);

	HMENU comboBoxDLabChosen = (HMENU)COMBOBOX_D_LAB_CHOSEN;
	comboBoxDButton = CreateWindowExW(0L, L"Button", L"Run", WS_VISIBLE | WS_CHILD|BS_PUSHBUTTON, 895, 400, 50, 23, hWnd, comboBoxDLabChosen, NULL, NULL);
}