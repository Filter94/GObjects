// Win32Project2.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"

#define EDGESCREEN_SQUARE 20
#define DOC_SIZE_X 1500
#define DOC_SIZE_Y 1000
#define MAX_HOROFFSET 250
#define MAX_VEROFFSET 250
#define MAX_CIRCLE_RADIUS 250
#define MAX_RGB_RANGE 255
#define MAX_LOADSTRING 100
#define F_TRIANGLE 0
#define F_RECTANGLE 1
#define F_CIRCLE 2
#define ID_TIMER 1
#define INVALIDE_RANGE 30

using std::queue;

// Глобальные переменные:
HINSTANCE hInst;								// текущий экземпляр
TCHAR szTitle[MAX_LOADSTRING];					// Текст строки заголовка
TCHAR szWindowClass[MAX_LOADSTRING];			// имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM				MyRegisterClass(HINSTANCE hInstance);
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

	// Выполнить инициализацию приложения:
	if (!InitInstance (hInstance, nCmdShow))
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

	return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  НАЗНАЧЕНИЕ: регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT2));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_WIN32PROJECT2);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//
//   КОММЕНТАРИИ:
//
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
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
	} while(AreCollinear(tCurrentTriangle_.first, tCurrentTriangle_.second) 
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

BOOL MouseInDocument(const POINT& pMouse){
	return (pMouse.x < DOC_SIZE_X && pMouse.y < DOC_SIZE_Y);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HDC          hdcMem;
	static HBITMAP      hbmMem;
	static HANDLE       hOld;

	static BOOL fBlocking;
	static POINT ptBeg, ptEnd, ptBoxBeg, ptBoxEnd;
	srand(rand());
	static POINT pMouse;
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	static HDC hdc;
	static List2 lObjectList;
	static INT iMapMode = MM_ANISOTROPIC;
	static SIZE sClient;
	static INT rgbRectPenColor, rgbRectBrushColor = RGB(255, 255, 255);

	switch (message)
	{
	case WM_CREATE:{
					   SendMessage(hWnd, WM_PAINT, 0, 0);
					   break;
	}
		case WM_COMMAND:
			wmId = LOWORD(wParam);
			wmEvent = HIWORD(wParam);
			switch (wmId)
			{
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

			SelectObject(hdcMem, hOld);
			DeleteObject(hbmMem);
			DeleteDC(hdcMem);

			hdcMem = CreateCompatibleDC(hdc);
			hbmMem = CreateCompatibleBitmap(hdc, sClient.cx, sClient.cy);

			hOld = SelectObject(hdcMem, hbmMem);
			return 0;
		case WM_PAINT:{
			EndPaint(hWnd, &ps);
			hdc = BeginPaint(hWnd, &ps);

			MappingInit(hdcMem, sClient, iMapMode);

			SelectObject(hdc, GetStockObject(DC_PEN));
			SetDCPenColor(hdc, RGB(255,255,255));
			Rectangle(hdcMem, -3, -3, DOC_SIZE_X + 3, DOC_SIZE_Y + 3);
			lObjectList.draw(hdcMem);
			SelectObject(hdcMem, GetStockObject(DC_BRUSH));
			SetDCBrushColor(hdcMem, RGB(255, 255, 255));
			SelectObject(hdcMem, GetStockObject(DC_PEN));
			SetDCPenColor(hdcMem, RGB(0, 0, 0));
			Rectangle(hdcMem, DOC_SIZE_X - (DOC_SIZE_X / EDGESCREEN_SQUARE), DOC_SIZE_Y - (DOC_SIZE_Y / EDGESCREEN_SQUARE), DOC_SIZE_X, DOC_SIZE_Y);

			MappingInit(hdc, sClient, iMapMode);

			BitBlt(hdc, 0, 0, DOC_SIZE_X, DOC_SIZE_Y, hdcMem, 0, 0, SRCCOPY);

			if (iMapMode == MM_ISOTROPIC){
				SelectObject(hdc, GetStockObject(DC_BRUSH));
				SetDCBrushColor(hdc, RGB(0, 0, 0));
				SelectObject(hdc, GetStockObject(DC_PEN));
				SetDCPenColor(hdc, RGB(0, 0, 0));
				Rectangle(hdc, DOC_SIZE_X, 0, DOC_SIZE_X * 10, DOC_SIZE_Y);
				Rectangle(hdc, 0, DOC_SIZE_Y, DOC_SIZE_X, DOC_SIZE_Y * 10);
			}
			break;
		}
		case WM_LBUTTONDBLCLK:{
			Triangle tTriangle = CreateTriangle(pMouse);

			tTriangle.draw(hdc);
			lObjectList.add(&tTriangle);
			KillTimer(hWnd, ID_TIMER);
			break;
		}
		case WM_KEYDOWN:{
							if (wParam == 'O' || wParam == 'T' || wParam == 'R'){
								GObject* object = 0;
								if (!(iMapMode == MM_ISOTROPIC && !MouseInDocument(pMouse))){
									lObjectList.toEnd();
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
													object = new _Rectangle(CreateRectangle(pMouse));
													break;
									}
									}
									object->draw(hdc);
									lObjectList.add(object);
								}
							}
						break;
		}
		case WM_LBUTTONDOWN:{
			ptBeg = ptEnd = pMouse;

			if (!(iMapMode == MM_ISOTROPIC && !MouseInDocument(ptBeg))){
				rgbRectPenColor = RGB(rand() % 255, rand() % 255, rand() % 255);
				rgbRectBrushColor = RGB(rand() % 255, rand() % 255, rand() % 255);
				
				SelectObject(hdc, GetStockObject(DC_BRUSH));
				SelectObject(hdc, GetStockObject(DC_PEN));
				SetDCPenColor(hdc, rgbRectPenColor);
				SetDCBrushColor(hdc, rgbRectBrushColor);
				Rectangle(hdc, ptBeg.x, ptBeg.y, ptEnd.x, ptEnd.y);
				SetCursor(LoadCursor(NULL, IDC_CROSS));

				fBlocking = TRUE;
			}
			break;
		}
		case WM_RBUTTONDOWN:{
			if (!(iMapMode == MM_ISOTROPIC && !MouseInDocument(pMouse))){
				lObjectList.toEnd();
				Ellipsis eEllipse = CreateCircle(pMouse);

				eEllipse.draw(hdc);
				lObjectList.add(&eEllipse);
			}
			break;
		}
		case WM_MOUSEMOVE:{
			pMouse.x = LOWORD(lParam);
			pMouse.y = HIWORD(lParam);

			DPtoLP(hdc, &pMouse, 1);

			if (fBlocking)
			{
				SetCursor(LoadCursor(NULL, IDC_CROSS));

				BitBlt(hdc, ptBeg.x, ptBeg.y, ptEnd.x - ptBeg.x, ptEnd.y - ptBeg.y, hdcMem, ptBeg.x, ptBeg.y, SRCCOPY);

				ptEnd = pMouse;

				SelectObject(hdc, GetStockObject(DC_BRUSH));
				SelectObject(hdc, GetStockObject(DC_PEN));
				SetDCPenColor(hdc, rgbRectPenColor);
				SetDCBrushColor(hdc, rgbRectBrushColor);
				Rectangle(hdc, ptBeg.x, ptBeg.y, ptEnd.x, ptEnd.y);
			}
			break;
		}
		case WM_LBUTTONUP:
			if (fBlocking){
				SetCursor(LoadCursor(NULL, IDC_ARROW));

				fBlocking = FALSE;

				MappingInit(hdc, sClient, iMapMode);

				SelectObject(hdc, GetStockObject(DC_BRUSH));
				SelectObject(hdc, GetStockObject(DC_PEN));
				SetDCPenColor(hdc, rgbRectPenColor);
				SetDCBrushColor(hdc, rgbRectBrushColor);
				Rectangle(hdc, ptBeg.x, ptBeg.y, ptEnd.x, ptEnd.y);

				RECT rCurrentRect;
				rCurrentRect.left = ptBeg.x;
				rCurrentRect.top = ptBeg.y;
				rCurrentRect.right = ptEnd.x;
				rCurrentRect.bottom = ptEnd.y;

				_Rectangle rRectangle(rCurrentRect, rgbRectBrushColor, rgbRectPenColor);

				lObjectList.toEnd();

				lObjectList.add(&rRectangle);

				InvalidateRect(hWnd, NULL, TRUE);
			}
			return 0;
		case WM_MBUTTONDOWN:{
			switch (iMapMode){
				case MM_ANISOTROPIC:{
					iMapMode = MM_ISOTROPIC;
					break;
				}
				case MM_ISOTROPIC:{
					iMapMode = MM_ANISOTROPIC;
					break;
				}
			}
			RECT rWindow;
			GetWindowRect(hWnd, &rWindow);
			MoveWindow(hWnd, rWindow.left, rWindow.top, rWindow.right - rWindow.left, rWindow.bottom - rWindow.top -1, TRUE);
			MoveWindow(hWnd, rWindow.left, rWindow.top, rWindow.right - rWindow.left, rWindow.bottom - rWindow.top +1, TRUE);
			break;
		}
		case WM_ERASEBKGND:{
			break;
		}
		case WM_DESTROY:
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
