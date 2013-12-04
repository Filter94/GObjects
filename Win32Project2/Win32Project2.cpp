// Win32Project2.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"

#define MAX_HOROFFSET 250
#define MAX_VEROFFSET 250
#define MAX_CIRCLE_RADIUS 250
#define MAX_RGB_RANGE 255
#define MAX_LOADSTRING 100

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


void mapping_init(HDC hdc,HWND hWnd, bool bAnisotropicOn) {
	RECT rRect;
	switch (bAnisotropicOn){
		case TRUE:{
					  GetClientRect(hWnd, &rRect);
					  SetMapMode(hdc, MM_ANISOTROPIC);
					  SetWindowExtEx(hdc, 1000, 1000, NULL);
					  SetViewportExtEx(hdc, rRect.right, rRect.bottom, NULL);
					  break;
		}
		case FALSE:{
					   GetClientRect(hWnd, &rRect);
					   SetMapMode(hdc, MM_ISOTROPIC);
					   SetWindowExtEx(hdc, 1000, 1000, NULL);
					   SetViewportExtEx(hdc, rRect.right, rRect.bottom, NULL);
					   break;
	}
	}
}

Triangle draw_triangle(HWND hWnd, POINT pMouse, bool bAnisotropicOn){
	int iRandomH = rand() % MAX_HOROFFSET + 1;
	int iRandomV = rand() % MAX_VEROFFSET + 1;
	TRIANGLE_ tCurrentTriangle_;
	RECT rInvalideRect;

	HDC hdc = GetDC(hWnd);
	mapping_init(hdc, hWnd, bAnisotropicOn);
	DPtoLP(hdc, &pMouse, 1);

	rInvalideRect.left = pMouse.x - 2 * iRandomH;
	rInvalideRect.top = pMouse.y - 2 * iRandomV;
	rInvalideRect.right = (pMouse.x + 2 * iRandomH);
	rInvalideRect.bottom = (pMouse.y + 2 * iRandomV);
	LPtoDP(hdc, (LPPOINT)&rInvalideRect, 4);
	ReleaseDC(hWnd, hdc);

	tCurrentTriangle_.first.x = pMouse.x;
	tCurrentTriangle_.first.y = pMouse.y;
	tCurrentTriangle_.second.x = (pMouse.x + (rand() % (2 * iRandomH)) - iRandomH / 2);
	tCurrentTriangle_.second.y = (pMouse.y + (rand() % (2 * iRandomV)) - iRandomV / 2);
	tCurrentTriangle_.third.x = (pMouse.x + (rand() % (2 * iRandomH)) - iRandomH / 2);
	tCurrentTriangle_.third.y = (pMouse.y + (rand() % (2 * iRandomV)) - iRandomV / 2);

	Triangle tTriangle(tCurrentTriangle_, RGB(rand() % 255, rand() % 255, rand() % 255), RGB(rand() % 255, rand() % 255, rand() % 255));
	InvalidateRect(hWnd, &rInvalideRect, NULL);
	ReleaseDC(hWnd, hdc);
	return tTriangle;
}

Ellipsis draw_circle(HWND hWnd, POINT pMouse, bool bAnisotropicOn){
	int iRandomR = rand() % MAX_CIRCLE_RADIUS;
	RECT rInvalideRect, rCurrentRect, rClientRect;
	HDC hdc = GetDC(hWnd);
	mapping_init(hdc, hWnd, bAnisotropicOn);
	DPtoLP(hdc, &pMouse, 1);

	rInvalideRect.left = pMouse.x;
	rInvalideRect.top = pMouse.y;
	rInvalideRect.right = pMouse.x + iRandomR;
	rInvalideRect.bottom = pMouse.y + iRandomR;

	LPtoDP(hdc, (LPPOINT)&rInvalideRect, 4);
	ReleaseDC(hWnd, hdc);


	rCurrentRect.left = pMouse.x;
	rCurrentRect.top = pMouse.y;
	rCurrentRect.right = pMouse.x + iRandomR;
	rCurrentRect.bottom = pMouse.y + iRandomR;
	InvalidateRect(hWnd, &rInvalideRect, 0);
	Ellipsis eEllipse(rCurrentRect, RGB(rand() % MAX_RGB_RANGE, rand() % MAX_RGB_RANGE, rand() % MAX_RGB_RANGE), RGB(rand() % MAX_RGB_RANGE, rand() % MAX_RGB_RANGE, rand() % MAX_RGB_RANGE));
	return eEllipse;
}

_Rectangle draw_rectangle(HWND hWnd, POINT pMouse, bool bAnisotropicOn){
	int iRandomH = rand() % MAX_HOROFFSET;
	int iRandomV = rand() % MAX_HOROFFSET;
	RECT rInvalideRect, rCurrentRect;

	HDC hdc = GetDC(hWnd);
	mapping_init(hdc, hWnd, bAnisotropicOn);
	DPtoLP(hdc, &pMouse, 1);

	rInvalideRect.left = pMouse.x;
	rInvalideRect.top = pMouse.y;
	rInvalideRect.right = pMouse.x + iRandomH;
	rInvalideRect.bottom = pMouse.y + iRandomV;

	LPtoDP(hdc, (LPPOINT)&rInvalideRect, 4);
	ReleaseDC(hWnd, hdc);


	rCurrentRect.left = pMouse.x;
	rCurrentRect.top = pMouse.y;
	rCurrentRect.right = pMouse.x + iRandomH;
	rCurrentRect.bottom = pMouse.y + iRandomV;
	_Rectangle rRectangle(rCurrentRect, RGB(rand() % MAX_RGB_RANGE, rand() % MAX_RGB_RANGE, rand() % MAX_RGB_RANGE), RGB(rand() % MAX_RGB_RANGE, rand() % MAX_RGB_RANGE, rand() % MAX_RGB_RANGE));

	InvalidateRect(hWnd, &rInvalideRect, 0);
	return rRectangle;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	srand(rand());
	static POINT pMouse;
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	int cxClient = 0;
	int cyClient = 0;
	static List2 lObjectList;
	static BOOL bAnisotropicOn = TRUE;

	static int iTimersAreActive = 0;

	switch (message)
	{
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
			cxClient = LOWORD(lParam);
			cyClient = HIWORD(lParam);
			return 0;
		case WM_PAINT:{
			hdc = BeginPaint(hWnd, &ps);
			mapping_init(hdc, hWnd, bAnisotropicOn);
			Rectangle(hdc, 900, 900, 1000, 1000);
			lObjectList.draw(hdc);
			EndPaint(hWnd, &ps);
			break;
		}
		case WM_LBUTTONDBLCLK:{
				lObjectList.add(&draw_triangle(hWnd, pMouse, bAnisotropicOn));
				KillTimer(hWnd, iTimersAreActive--);
				KillTimer(hWnd, iTimersAreActive--);
				break;
		}
		case WM_KEYDOWN:{
			switch (wParam)
			{
			case 'O':
				lObjectList.add(&draw_circle(hWnd, pMouse, bAnisotropicOn));
				break;
			case 'T':
				lObjectList.add(&draw_triangle(hWnd, pMouse, bAnisotropicOn));
				break;
			case 'R':
				lObjectList.add(&draw_rectangle(hWnd, pMouse, bAnisotropicOn));
				break;
			}
			break;
		}
		case WM_LBUTTONDOWN:{
			SetTimer(hWnd, iTimersAreActive++, GetDoubleClickTime() + 1, (TIMERPROC)NULL);
			pMouse.x = LOWORD(lParam);
			pMouse.y = HIWORD(lParam);
			break;
		}
		case WM_TIMER:{
			
			lObjectList.add(&draw_rectangle(hWnd, pMouse, bAnisotropicOn));
			KillTimer(hWnd, wParam);
			break;
		}
		case WM_RBUTTONDOWN:{
			int iRandomR = rand() % MAX_CIRCLE_RADIUS;
			pMouse.x = LOWORD(lParam);
			pMouse.y = HIWORD(lParam);
			lObjectList.add(&draw_circle(hWnd, pMouse, bAnisotropicOn));
			break;
		}
		case WM_MOUSEMOVE:{
			pMouse.x = LOWORD(lParam);
			pMouse.y = HIWORD(lParam);
			break;
		}
		case WM_MBUTTONDOWN:{
				bAnisotropicOn = !bAnisotropicOn;
				InvalidateRect(hWnd, NULL, TRUE);
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
