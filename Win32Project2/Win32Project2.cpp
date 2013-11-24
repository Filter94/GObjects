// Win32Project2.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"

#define MAX_HOROFFSET 250
#define MAX_VEROFFSET 250
#define MAX_CIRCLE_RADIUS 250
#define MAX_RGB_RANGE 255
#define MAX_LOADSTRING 100
#define IDT_ClickTimer 1

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

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	static POINT pMouse;
	static List2 lObjectList;
	static BOOL bAnisotropicOn = TRUE;
	static RECT rInvalideRect;
	int cxClient = 0;
	int cyClient = 0;
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
			RECT rRect;
			switch (bAnisotropicOn){
			case TRUE:{
					GetClientRect(hWnd, &rRect);
					SetMapMode(hdc, MM_ANISOTROPIC);
					SetWindowExtEx(hdc, 1000, 1000, NULL);
					SetViewportExtEx(hdc, rRect.right,  rRect.bottom, NULL);
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
			lObjectList.draw(hdc);
			EndPaint(hWnd, &ps);
			break;
		}
		case WM_LBUTTONDBLCLK:{
				srand(rand());
				int iRandomH = rand() % MAX_HOROFFSET + 1;
				int iRandomV = rand() % MAX_VEROFFSET + 1;
				static RECT rInvalideRect, rClientRect;
				TRIANGLE_ tCurrentTriangle_;
				GetClientRect(hWnd, &rClientRect);
				pMouse.x = LOWORD(lParam);
				pMouse.y = HIWORD(lParam);
				rInvalideRect.left = (pMouse.x * rClientRect.right / 1000 - iRandomH / 2);
				rInvalideRect.top = (pMouse.y * rClientRect.bottom / 1000 - iRandomV / 2);
				rInvalideRect.right = (pMouse.x * rClientRect.right / 1000 + iRandomH / 2);
				rInvalideRect.bottom = (pMouse.y * rClientRect.bottom / 1000 + iRandomV / 2);
				tCurrentTriangle_.first.x = pMouse.x * rClientRect.right / 1000;
				tCurrentTriangle_.first.y = pMouse.y * rClientRect.bottom / 1000;
				tCurrentTriangle_.second.x = (pMouse.x * rClientRect.right / 1000 + (rand() % iRandomH) - iRandomH / 2);
				tCurrentTriangle_.second.y = (pMouse.y * rClientRect.bottom / 1000 + (rand() % iRandomV) - iRandomV / 2);
				tCurrentTriangle_.third.x = (pMouse.x * rClientRect.right / 1000 + (rand() % iRandomH) - iRandomH / 2);
				tCurrentTriangle_.third.y = (pMouse.y * rClientRect.bottom / 1000 + (rand() % iRandomV) - iRandomV / 2);
				Triangle tTriangle(tCurrentTriangle_, RGB(rand() % 255, rand() % 255, rand() % 255), RGB(rand() % 255, rand() % 255, rand() % 255));
				InvalidateRect(hWnd, &rInvalideRect, NULL);
				lObjectList.add(&tTriangle);
				KillTimer(hWnd, IDT_ClickTimer);
				break;
		}
		case WM_LBUTTONDOWN:{
			SetTimer(hWnd, IDT_ClickTimer, GetDoubleClickTime() + 1, (TIMERPROC)NULL);
			pMouse.x = LOWORD(lParam);
			pMouse.y = HIWORD(lParam);
			break;
		}
		case WM_TIMER:{
			int iRandomH = rand() % MAX_HOROFFSET;
			int iRandomV = rand() % MAX_VEROFFSET;
			RECT rInvalideRect, rCurrentRect, rClientRect;
			GetClientRect(hWnd, &rClientRect);
			rInvalideRect.left = pMouse.x * rClientRect.right / 1000;
			rInvalideRect.top = pMouse.y * rClientRect.bottom / 1000;
			rInvalideRect.right = (pMouse.x * rClientRect.right / 1000 + iRandomH);
			rInvalideRect.bottom = (pMouse.y * rClientRect.bottom / 1000 + iRandomV);
			rCurrentRect.left = pMouse.x * rClientRect.right / 1000;
			rCurrentRect.top = pMouse.y * rClientRect.bottom / 1000;
			rCurrentRect.right = (pMouse.x * rClientRect.right / 1000 + iRandomH);
			rCurrentRect.bottom = (pMouse.y * rClientRect.bottom / 1000 + iRandomV);
			_Rectangle sRectangle(rCurrentRect, RGB(rand() % MAX_RGB_RANGE, rand() % MAX_RGB_RANGE, rand() % MAX_RGB_RANGE), RGB(rand() % MAX_RGB_RANGE, rand() % MAX_RGB_RANGE, rand() % MAX_RGB_RANGE));

			InvalidateRect(hWnd, &rInvalideRect, 0);
			InvalidateRect(hWnd, NULL, TRUE);
			lObjectList.add(&sRectangle);
			KillTimer(hWnd, IDT_ClickTimer);
			break;
		}
		case WM_RBUTTONDOWN:{
			pMouse.x = LOWORD(lParam);
			pMouse.y = HIWORD(lParam);
			int iRandomR = rand() % MAX_CIRCLE_RADIUS;
			RECT rInvalideRect,rCurrentRect, rClientRect;
			GetClientRect(hWnd, &rClientRect);
			rInvalideRect.left = pMouse.x * 1000 / rClientRect.right;
			rInvalideRect.top = pMouse.y * rClientRect.bottom / 1000;
			rInvalideRect.right = (pMouse.x * 1000 / rClientRect.right + iRandomR);
			rInvalideRect.bottom = (pMouse.y * rClientRect.bottom / 1000 + iRandomR);
			rCurrentRect.left = pMouse.x * 1000 / rClientRect.right;
			rCurrentRect.top = pMouse.y * rClientRect.bottom / 1000;
			rCurrentRect.right = (pMouse.x * 1000 / rClientRect.right + iRandomR);
			rCurrentRect.bottom = (pMouse.y * rClientRect.bottom / 1000 + iRandomR);
			Ellipsis eCircle(rCurrentRect, RGB(rand() % MAX_RGB_RANGE, rand() % MAX_RGB_RANGE, rand() % MAX_RGB_RANGE), RGB(rand() % MAX_RGB_RANGE, rand() % MAX_RGB_RANGE, rand() % MAX_RGB_RANGE));
		
			InvalidateRect(hWnd, &rInvalideRect, 0);
			lObjectList.add(&eCircle);
			break;
		}
		case WM_MBUTTONDOWN:{
				bAnisotropicOn = !bAnisotropicOn;
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
