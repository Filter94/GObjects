// Win32Project2.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"

#define MAX_HOROFFSET 250
#define MAX_VEROFFSET 250
#define MAX_CIRCLE_RADIUS 250
#define MAX_RGB_RANGE 255
#define MAX_LOADSTRING 100
#define F_TRIANGLE 0
#define F_RECTANGLE 1
#define F_CIRCLE 2
#define ID_TIMER 1

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

void mapping_init(HDC hdc, SIZE& size, const int iAnisotropicOn) {
	switch (iAnisotropicOn){
		case MM_ANISOTROPIC:{
			SetMapMode(hdc, MM_ANISOTROPIC);
			break;
		}
		case MM_ISOTROPIC:{
			SetMapMode(hdc, MM_ISOTROPIC);
			break;
		}
	}
	SetWindowExtEx(hdc, 1000, 1000, NULL);
	SetViewportExtEx(hdc, size.cx, size.cy, NULL);
}

bool are_collinear(const POINT& a, const POINT& b){
	return ((a.x / b.x) == (a.y / b.y));
}

Triangle create_triangle(const POINT& pMouse){
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
	} while(are_collinear(tCurrentTriangle_.first, tCurrentTriangle_.second) 
		&& are_collinear(tCurrentTriangle_.third, tCurrentTriangle_.second));

	Triangle tTriangle(tCurrentTriangle_, RGB(rand() % 255, rand() % 255, rand() % 255), RGB(rand() % 255, rand() % 255, rand() % 255));
	return tTriangle;
}

Ellipsis create_circle(const POINT& pMouse){
	int iRandomR = rand() % MAX_CIRCLE_RADIUS;
	RECT rCurrentRect;

	rCurrentRect.left = pMouse.x;
	rCurrentRect.top = pMouse.y;
	rCurrentRect.right = pMouse.x + iRandomR;
	rCurrentRect.bottom = pMouse.y + iRandomR;
	Ellipsis eEllipse(rCurrentRect, RGB(rand() % MAX_RGB_RANGE, rand() % MAX_RGB_RANGE, rand() % MAX_RGB_RANGE), RGB(rand() % MAX_RGB_RANGE, rand() % MAX_RGB_RANGE, rand() % MAX_RGB_RANGE));

	return eEllipse;
}

_Rectangle create_rectangle(const POINT& pMouse){
	int iRandomH = rand() % MAX_HOROFFSET;
	int iRandomV = rand() % MAX_HOROFFSET;
	RECT rCurrentRect;
	rCurrentRect.left = pMouse.x;
	rCurrentRect.top = pMouse.y;
	rCurrentRect.right = pMouse.x + iRandomH;
	rCurrentRect.bottom = pMouse.y + iRandomV;
	_Rectangle rRectangle(rCurrentRect, RGB(rand() % MAX_RGB_RANGE, rand() % MAX_RGB_RANGE, rand() % MAX_RGB_RANGE), RGB(rand() % MAX_RGB_RANGE, rand() % MAX_RGB_RANGE, rand() % MAX_RGB_RANGE));

	return rRectangle;
}

void create_then_draw_then_add(HDC hdc, SIZE& size, const int iAnisotropicOn, const int Figure, POINT& pMouse, List2* list){
	mapping_init(hdc, size, iAnisotropicOn);
	DPtoLP(hdc, &pMouse, 1);
	list -> toEnd();
	switch (Figure) {
		case F_CIRCLE:{
			Ellipsis eEllipse = create_circle(pMouse);
			
			eEllipse.draw(hdc);
			list -> add(&eEllipse);
			break;
		}
		case F_TRIANGLE:{
			Triangle tTriangle = create_triangle(pMouse);

			tTriangle.draw(hdc);
			list -> add(&tTriangle);
			break;
		}
		case F_RECTANGLE:{
			_Rectangle rRectangle = create_rectangle(pMouse);

			rRectangle.draw(hdc);
			list -> add(&rRectangle);
			break;
		}
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	srand(rand());
	static POINT pMouse, pPrevPoint;
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	static List2 lObjectList;
	static int iAnisotropicOn = MM_ANISOTROPIC;
	static bool timer_up = 0;
	static SIZE sClient;

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
			sClient.cx = LOWORD(lParam);
			sClient.cy = HIWORD(lParam);
			return 0;
		case WM_PAINT:{
			hdc = BeginPaint(hWnd, &ps);
			mapping_init(hdc, sClient, iAnisotropicOn);
			lObjectList.draw(hdc);
			SelectObject(hdc, GetStockObject(DC_BRUSH));
			SetDCBrushColor(hdc, RGB(255,255,255));
			SelectObject(hdc, GetStockObject(DC_PEN));
			SetDCPenColor(hdc, RGB(0,0,0));
			Rectangle(hdc, 900, 900, 1000, 1000);
			EndPaint(hWnd, &ps);
			break;
		}
		case WM_LBUTTONDBLCLK:{
			hdc = GetDC(hWnd);
			create_then_draw_then_add(hdc, sClient, iAnisotropicOn, F_TRIANGLE, pMouse, &lObjectList);
			ReleaseDC(hWnd, hdc);
			KillTimer(hWnd, ID_TIMER);
			break;
		}
		case WM_KEYDOWN:{
			hdc = GetDC(hWnd);
			switch (wParam)
							{
				case 'O':{
					create_then_draw_then_add(hdc, sClient, iAnisotropicOn, F_CIRCLE, pMouse, &lObjectList);
					break;
				}
				case 'T':{
					create_then_draw_then_add(hdc, sClient, iAnisotropicOn, F_TRIANGLE, pMouse, &lObjectList);
					break;
				}
				case 'R':{
					create_then_draw_then_add(hdc, sClient, iAnisotropicOn, F_RECTANGLE, pMouse, &lObjectList);
					break;
				}
			}
			break;
		}
		case WM_LBUTTONDOWN:{
			if (timer_up){
				hdc = GetDC(hWnd);
				KillTimer(hWnd, ID_TIMER);
				timer_up = FALSE;
				create_then_draw_then_add(hdc, sClient, iAnisotropicOn, F_RECTANGLE, pPrevPoint, &lObjectList);
				ReleaseDC(hWnd, hdc);
			}
			pPrevPoint.x = LOWORD(lParam);
			pPrevPoint.y = HIWORD(lParam);
			SetTimer(hWnd, ID_TIMER, GetDoubleClickTime() + 1, (TIMERPROC)NULL);
			timer_up = TRUE;
			break;
		}
		case WM_TIMER:{
			hdc = GetDC(hWnd);
			timer_up = FALSE;
			create_then_draw_then_add(hdc, sClient, iAnisotropicOn, F_RECTANGLE, pPrevPoint, &lObjectList);
			ReleaseDC(hWnd, hdc);
			KillTimer(hWnd, wParam);
			break;
		}
		case WM_RBUTTONDOWN:{
			hdc = GetDC(hWnd);
			create_then_draw_then_add(hdc, sClient, iAnisotropicOn, F_CIRCLE, pMouse, &lObjectList);
			ReleaseDC(hWnd, hdc);
			break;
		}
		case WM_MOUSEMOVE:{
			pMouse.x = LOWORD(lParam);
			pMouse.y = HIWORD(lParam);
			break;
		}
		case WM_MBUTTONDOWN:{
			switch (iAnisotropicOn){
				case MM_ANISOTROPIC:{
					iAnisotropicOn = MM_ISOTROPIC;
					break;
				}
				case MM_ISOTROPIC:{
					iAnisotropicOn = MM_ANISOTROPIC;
					break;
				}
			}
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
