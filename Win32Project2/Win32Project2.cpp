// Win32Project2.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include <windows.h>

// Глобальные переменные:
HINSTANCE hInst;								// текущий экземпляр
TCHAR szTitle[MAX_LOADSTRING];					// Текст строки заголовка
TCHAR szWindowClass[MAX_LOADSTRING];			// имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM				MyRegisterClass(HINSTANCE hInstance);
ATOM				RegisterClassChild(HINSTANCE hInstance);
LRESULT CALLBACK	WndProcChild(HWND, UINT, WPARAM, LPARAM);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: разместите код здесь.
	MSG msg;
	HACCEL hAccelTable;

	// Инициализация глобальных строк
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WIN32PROJECT2, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);
	RegisterClassChild(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT2));

	// Цикл основного сообщения:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

HINSTANCE g_hInst;

#define IDC_TOOLBAR			13990

HWND OnInitToolbarDialog(HWND hWnd, HWND hWndFocus, LPARAM lParam)
{
	// Load and register Toolbar control class
	INITCOMMONCONTROLSEX iccx;
	iccx.dwSize = sizeof(INITCOMMONCONTROLSEX);
	iccx.dwICC = ICC_BAR_CLASSES;
	if (!InitCommonControlsEx(&iccx))
		return 0;

	// Create the Toolbar control
	RECT rc = { 0, 0, 0, 0 };
	HWND hToolbar = CreateWindowEx(0, TOOLBARCLASSNAME, 0,
		TBSTYLE_FLAT | CCS_ADJUSTABLE | CCS_NODIVIDER | WS_CHILD | WS_VISIBLE,
		rc.left, rc.top, rc.right, rc.bottom,
		hWnd, (HMENU)IDC_TOOLBAR, g_hInst, 0);


	/////////////////////////////////////////////////////////////////////////
	// Setup and add buttons to Toolbar.
	// 

	// If an application uses the CreateWindowEx function to create the 
	// toolbar, the application must send this message to the toolbar before 
	// sending the TB_ADDBITMAP or TB_ADDBUTTONS message. The CreateToolbarEx 
	// function automatically sends TB_BUTTONSTRUCTSIZE, and the size of the 
	// TBBUTTON structure is a parameter of the function.
	SendMessage(hToolbar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);

	// Add images

	TBADDBITMAP tbAddBmp = { 0 };
	tbAddBmp.hInst = HINST_COMMCTRL;
	tbAddBmp.nID = IDB_STD_SMALL_COLOR;

	SendMessage(hToolbar, TB_ADDBITMAP, 0, (WPARAM)&tbAddBmp);

	// Add buttons

	const int numButtons = 7;
	TBBUTTON tbButtons[numButtons] =
	{
		{ MAKELONG(STD_FILENEW, 0), NULL, TBSTATE_ENABLED,
		BTNS_AUTOSIZE, { 0 }, 0, (INT_PTR)L"New" },
		{ MAKELONG(STD_FILEOPEN, 0), NULL, TBSTATE_ENABLED,
		BTNS_AUTOSIZE, { 0 }, 0, (INT_PTR)L"Open" },
		{ MAKELONG(STD_FILESAVE, 0), NULL, 0,
		BTNS_AUTOSIZE, { 0 }, 0, (INT_PTR)L"Save" },
		{ MAKELONG(0, 0), NULL, 0,
		TBSTYLE_SEP, { 0 }, 0, (INT_PTR)L"" }, // Separator
		{ MAKELONG(STD_COPY, 0), NULL, TBSTATE_ENABLED,
		BTNS_AUTOSIZE, { 0 }, 0, (INT_PTR)L"Copy" },
		{ MAKELONG(STD_CUT, 0), NULL, TBSTATE_ENABLED,
		BTNS_AUTOSIZE, { 0 }, 0, (INT_PTR)L"Cut" },
		{ MAKELONG(STD_PASTE, 0), NULL, TBSTATE_ENABLED,
		BTNS_AUTOSIZE, { 0 }, 0, (INT_PTR)L"Paste" }
	};

	SendMessage(hToolbar, TB_ADDBUTTONS, numButtons, (LPARAM)tbButtons);

	// Tell the toolbar to resize itself, and show it.
	SendMessage(hToolbar, TB_AUTOSIZE, 0, 0);

	return hToolbar;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT2));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_WIN32PROJECT2);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}


ATOM RegisterClassChild(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc = WndProcChild;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	//wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));
	//wcex.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR3));
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"Child";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//  WM_COMMAND	- обработка меню приложения
//  WM_PAINT	-Закрасить главное окно
//  WM_DESTROY	 - ввести сообщение о выходе и вернуться.
//
//

void MappingInit(HDC hdc, SIZE& size, const int iMapMode) {
	switch (iMapMode){
	case MM_ANISOTROPIC:{
		SetMapMode(hdc, MM_ANISOTROPIC);
		break;
	}
	case MM_ISOTROPIC:{
		SetMapMode(hdc, MM_ISOTROPIC);
		break;
	}
	}
	SetWindowExtEx(hdc, DOC_SIZE_X, DOC_SIZE_Y, NULL);
	SetViewportExtEx(hdc, size.cx, size.cy, NULL);
}

bool AreCollinear(const POINT& a, const POINT& b){
	return ((a.x / b.x) == (a.y / b.y));
}

Triangle CreateTriangle(const POINT& pMouse){
	int iRandomH = rand() % MAX_HOROFFSET + 1;
	int iRandomV = rand() % MAX_VEROFFSET + 1;
	TRIANGLE_ tCurrentTriangle_;

	do{
		tCurrentTriangle_.first.x = pMouse.x;
		tCurrentTriangle_.first.y = pMouse.y;
		tCurrentTriangle_.second.x = (pMouse.x + (rand() % (2 * iRandomH)) - iRandomH / 2);
		tCurrentTriangle_.second.y = (pMouse.y + (rand() % (2 * iRandomV)) - iRandomV / 2);
		tCurrentTriangle_.third.x = (pMouse.x + (rand() % (2 * iRandomH)) - iRandomH / 2);
		tCurrentTriangle_.third.y = (pMouse.y + (rand() % (2 * iRandomV)) - iRandomV / 2);
	} while (AreCollinear(tCurrentTriangle_.first, tCurrentTriangle_.second)
		&& AreCollinear(tCurrentTriangle_.third, tCurrentTriangle_.second));

	Triangle tTriangle(tCurrentTriangle_, RGB(rand() % 255, rand() % 255, rand() % 255), RGB(rand() % 255, rand() % 255, rand() % 255));
	return tTriangle;
}

Ellipsis CreateCircle(const POINT& pMouse){
	int iRandomR = rand() % MAX_CIRCLE_RADIUS;
	RECT rCurrentRect;

	rCurrentRect.left = pMouse.x;
	rCurrentRect.top = pMouse.y;
	rCurrentRect.right = pMouse.x + iRandomR;
	rCurrentRect.bottom = pMouse.y + iRandomR;
	Ellipsis eEllipse(rCurrentRect, RGB(rand() % 255, rand() % 255, rand() % 255), RGB(rand() % 255, rand() % 255, rand() % 255));

	return eEllipse;
}

_Rectangle CreateRectangle(const POINT& pMouse){
	int iRandomH = rand() % MAX_HOROFFSET;
	int iRandomV = rand() % MAX_HOROFFSET;
	RECT rCurrentRect;
	rCurrentRect.left = pMouse.x;
	rCurrentRect.top = pMouse.y;
	rCurrentRect.right = pMouse.x + iRandomH;
	rCurrentRect.bottom = pMouse.y + iRandomV;
	_Rectangle rRectangle(rCurrentRect, RGB(rand() % 255, rand() % 255, rand() % 255), RGB(rand() % 255, rand() % 255, rand() % 255));

	return rRectangle;
}

BOOL MouseInDocument(const POINT pMouse){
	return (pMouse.y>0 && pMouse.x >0 && pMouse.x < DOC_SIZE_X && pMouse.y < DOC_SIZE_Y);
}

void DrawBoxOutline(HDC hdc, POINT ptBeg, POINT ptEnd)
{
	SetROP2(hdc, R2_NOT);
	SelectObject(hdc, GetStockObject(NULL_BRUSH));
	Rectangle(hdc, ptBeg.x, ptBeg.y, ptEnd.x, ptEnd.y);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hToolbar;
	HDC hdc;
	PAINTSTRUCT ps;
	int wmId, wmEvent, cxClient, cyClient;
	static HWND hwndToolBar, hwndStatusBar, hWndChild;
	static HMENU hMenu;

	switch (message)
	{
	case WM_CREATE:
	{
					  hWndChild = CreateWindow(L"Child", szTitle, WS_CHILD | WS_VISIBLE | WS_VSCROLL, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, hWnd, (HMENU)HWNDCHILD, hInst, NULL);
					  hToolbar = OnInitToolbarDialog(hWnd, hWnd, 0);

					  break;
	}
	case WM_SETFOCUS:
	{
						SetFocus(hWndChild);
						break;
	}
	case WM_COMMAND:
	{
					   wmId = LOWORD(wParam);
					   wmEvent = HIWORD(wParam);
					   break;
	}
	case WM_SIZE:
	{
					cxClient = LOWORD(lParam);
					cyClient = HIWORD(lParam);
					RECT rect;
					GetWindowRect(hwndToolBar, &rect);
					MoveWindow(hWndChild, 0, 0, cxClient, cyClient, TRUE);
					SendMessage(hwndToolBar, WM_SIZE, 0, 0);
					break;
	}
	case WM_PAINT:
	{
					 hdc = BeginPaint(hWnd, &ps);
					 EndPaint(hWnd, &ps);
					 break;
	}
	case WM_DESTROY:
	{
					   PostQuitMessage(0);
					   break;
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK WndProcChild(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HDC          hdcMemDoc, hdcMemBuf;
	static HBITMAP      hbmMemBuf, hbmMemDoc, hOld;

	static BOOL fBlocking;
	static POINT ptBeg, ptEnd, ptBoxBeg, ptBoxEnd;
	srand(rand());
	static POINT pMouse;
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	static HDC hdc;
	static SIZE sClient;
	static INT iVscrollPos, iHscrollPos, cHorScrollMax, cVerScrollMax, iVPos, iHPos = 0;
	static POINT pBeginPoint, pEndPoint;
	switch (message)
	{
	case WM_CREATE:{
		hdc = GetDC(hWnd);
		hdcMemDoc = CreateCompatibleDC(hdc);
		hbmMemDoc = CreateCompatibleBitmap(hdc, DOC_SIZE_X, DOC_SIZE_Y);
		hOld = (HBITMAP)SelectObject(hdcMemDoc, hbmMemDoc);

		SelectObject(hdc, GetStockObject(DC_BRUSH));
		SelectObject(hdc, GetStockObject(DC_PEN));
		SetDCBrushColor(hdc, RGB(255, 255, 255));
		SetDCPenColor(hdc, RGB(255, 255, 255));
		Rectangle(hdcMemDoc, 0, 0, DOC_SIZE_X, DOC_SIZE_Y);

		ReleaseDC(hWnd, hdc);
		break;
	}
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId){
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_SIZE:
		sClient.cx = LOWORD(lParam);
		sClient.cy = HIWORD(lParam);
		cHorScrollMax = (DOC_SIZE_X - sClient.cx) + GAP >= 0 ? (DOC_SIZE_X - sClient.cx) / 2 + GAP : 0;
		cVerScrollMax = (DOC_SIZE_Y - sClient.cy) + GAP >= 0 ? (DOC_SIZE_Y - sClient.cy) / 2 + GAP : 0;
		SetScrollRange(hWnd, SB_HORZ, -cHorScrollMax, cHorScrollMax, TRUE);
		SetScrollRange(hWnd, SB_VERT, -cVerScrollMax, cVerScrollMax, TRUE);
		hdc = GetDC(hWnd);

		SelectObject(hdcMemBuf, hOld);
		DeleteObject(hdcMemBuf);
		DeleteDC(hdcMemBuf);

		hdcMemBuf = CreateCompatibleDC(hdc);
		hbmMemBuf = CreateCompatibleBitmap(hdc, sClient.cx, sClient.cy);

		hOld = (HBITMAP)SelectObject(hdcMemBuf, hbmMemBuf);
		ReleaseDC(hWnd, hdc);
		return 0;
	case WM_PAINT:{
		hdc = BeginPaint(hWnd, &ps);
		
		pBeginPoint.x = (sClient.cx - DOC_SIZE_X) / 2;
		pBeginPoint.y = (sClient.cy - DOC_SIZE_Y) / 2;

		SelectObject(hdcMemBuf, GetStockObject(DC_BRUSH));
		SelectObject(hdcMemBuf, GetStockObject(DC_PEN));
		SetDCBrushColor(hdcMemBuf, RGB(100, 100, 100));
		SetDCPenColor(hdcMemBuf, RGB(100, 100, 100));
		Rectangle(hdcMemBuf, 0, 0, sClient.cx, sClient.cy);

		BitBlt(hdcMemBuf, pBeginPoint.x - iHscrollPos, pBeginPoint.y - iVscrollPos, DOC_SIZE_X, DOC_SIZE_Y, hdcMemDoc, 0, 0, SRCCOPY);

		BitBlt(hdc, 0,0 , sClient.cx, sClient.cy, hdcMemBuf, 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_LBUTTONDBLCLK:{
		if (MouseInDocument(pMouse)){
			Triangle tTriangle = CreateTriangle(pMouse);

			tTriangle.draw(hdcMemDoc);
			KillTimer(hWnd, ID_TIMER);
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;
	}
	case WM_KEYDOWN:{
		if ((wParam == 'O' || wParam == 'T' || wParam == 'R') && MouseInDocument(pMouse)){
			GObject* object = 0;
				switch (wParam){
					case 'O':{
						object = new Ellipsis(CreateCircle(pMouse));
						break;
					}
					case 'T':{
						object = new Triangle(CreateTriangle(pMouse));
						break;
					}
					case 'R':{
						int iRandomH = rand() % MAX_HOROFFSET;
						int iRandomV = rand() % MAX_HOROFFSET;
						RECT rCurrentRect;
						rCurrentRect.left = pMouse.x;
						rCurrentRect.top = pMouse.y;
						rCurrentRect.right = pMouse.x + iRandomH;
						rCurrentRect.bottom = pMouse.y + iRandomV;
						_Rectangle rRectangle(rCurrentRect, RGB(rand() % 255, rand() % 255, rand() % 255), RGB(rand() % 255, rand() % 255, rand() % 255));
						object = new _Rectangle(rRectangle);
						break;
					}
			}
			object->draw(hdcMemDoc);
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;
	}
	case WM_LBUTTONDOWN:{
		ptBeg = ptEnd = pMouse;
		if (MouseInDocument(pMouse)){
			SetCursor(LoadCursor(NULL, IDC_CROSS));
			fBlocking = TRUE;
		}
		break;
	}
	case WM_RBUTTONDOWN:{
		if (MouseInDocument(pMouse)){
			hdc = GetDC(hWnd);
			SetViewportOrgEx(hdc, pBeginPoint.x, pBeginPoint.y, NULL);
			Ellipsis eEllipse = CreateCircle(pMouse);
			eEllipse.draw(hdcMemDoc);

			InvalidateRect(hWnd, NULL, TRUE);
			ReleaseDC(hWnd, hdc);
		}
		break;
	}
	case WM_MOUSEMOVE:{
		pMouse.x = LOWORD(lParam);
		pMouse.y = HIWORD(lParam);
		hdc = GetDC(hWnd);
		SetViewportOrgEx(hdc, pBeginPoint.x - iHscrollPos, pBeginPoint.y - iVscrollPos, NULL);
		DPtoLP(hdc, &pMouse, 1);
		if (fBlocking && MouseInDocument(pMouse))
		{
			SetCursor(LoadCursor(NULL, IDC_CROSS));
			DrawBoxOutline(hdc, ptBeg, ptEnd);

			ptEnd = pMouse;

			DrawBoxOutline(hdc, ptBeg, ptEnd);

		}
		ReleaseDC(hWnd, hdc);
		break;
	}
	case WM_LBUTTONUP:
		if (fBlocking){
			SetCursor(LoadCursor(NULL, IDC_ARROW));

			fBlocking = FALSE;

			SelectObject(hdcMemDoc, GetStockObject(DC_BRUSH));
			SelectObject(hdcMemDoc, GetStockObject(DC_PEN));
			SetDCPenColor(hdcMemDoc, RGB(rand() % 255, rand() % 255, rand() % 255));
			SetDCBrushColor(hdcMemDoc, RGB(rand() % 255, rand() % 255, rand() % 255));

			Rectangle(hdcMemDoc, ptBeg.x, ptBeg.y, ptEnd.x, ptEnd.y);

			InvalidateRect(hWnd, NULL, TRUE);
		}
		return 0;
		break;
	case WM_VSCROLL:{
		switch (LOWORD(wParam))
		{
		case SB_LINEUP:
			if (iVscrollPos > -cVerScrollMax){
				iVscrollPos -= 10;
			}
			break;

		case SB_LINEDOWN:
			if (iVscrollPos < cVerScrollMax){
				iVscrollPos += 10;
			}
			break;

		case SB_PAGEUP:
			if (iVscrollPos - sClient.cy / 4 > -cVerScrollMax){
				iVscrollPos -= sClient.cy / 4;
			}
			break;

		case SB_PAGEDOWN:
			if (iVscrollPos + sClient.cy / 4 < +cVerScrollMax){
				iVscrollPos += sClient.cy / 4;
			}
			break;
		case SB_THUMBTRACK:
			iVscrollPos = (short int)HIWORD(wParam);
			break;
		}
		SetScrollPos(hWnd, SB_VERT, iVscrollPos, TRUE);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	}
	case WM_HSCROLL:{
		switch (LOWORD(wParam))
		{
		case SB_LINEUP:
			if (iHscrollPos > -cHorScrollMax){
				iHscrollPos -= 10;
			}
			break;

		case SB_LINEDOWN:
			if (iHscrollPos < cHorScrollMax){
				iHscrollPos += 10;
			}
			break;

		case SB_PAGEUP:
			if (iHscrollPos - sClient.cx / DOC_SIZE_X > -cHorScrollMax){
				iHscrollPos -= sClient.cx / 4;
			}
				break;

		case SB_PAGEDOWN:
			if (iHscrollPos + sClient.cx / DOC_SIZE_X < +cHorScrollMax){
				iHscrollPos += sClient.cx / 4;
			}
				break;
		case SB_THUMBTRACK:
			iHscrollPos = (short int)HIWORD(wParam);
			break;
			}
			SetScrollPos(hWnd, SB_HORZ, iHscrollPos, TRUE);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
	}
	case WM_ERASEBKGND:{
		break;
	}
	case WM_DESTROY:
		DeleteObject(hbmMemDoc);
		DeleteDC(hdcMemDoc);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
