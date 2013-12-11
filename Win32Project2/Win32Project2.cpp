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
	SetWindowExtEx(hdc, 1000, 1000, NULL);
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

void CreateThenDrawThenAdd(HDC hdc, SIZE& size, const int iMapMode, const int Figure, POINT& pMouse, List2* list){
	MappingInit(hdc, size, iMapMode);
	DPtoLP(hdc, &pMouse, 1);
	list -> toEnd();
	switch (Figure) {
		case F_CIRCLE:{
			Ellipsis eEllipse = CreateCircle(pMouse);
			
			eEllipse.draw(hdc);
			list -> add(&eEllipse);
			break;
		}
		case F_TRIANGLE:{
			Triangle tTriangle = CreateTriangle(pMouse);

			tTriangle.draw(hdc);
			list -> add(&tTriangle);
			break;
		}
		case F_RECTANGLE:{
			_Rectangle rRectangle = CreateRectangle(pMouse);

			rRectangle.draw(hdc);
			list -> add(&rRectangle);
			break;
		}
	}
}

void DrawBoxOutline(HDC hdc, POINT& ptBeg, POINT& ptEnd)
{
	SetROP2(hdc, R2_COPYPEN);
	Rectangle(hdc, ptBeg.x, ptBeg.y, ptEnd.x, ptEnd.y);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static BOOL fBlocking;
	static POINT ptBeg, ptEnd, ptBoxBeg, ptBoxEnd;
	srand(rand());
	static POINT pMouse, pPrevPoint;
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	static List2 lObjectList;
	static INT iMapMode = MM_ANISOTROPIC;
	static SIZE sClient;
	static INT rgbRectPenColor, rgbRectBrushColor = RGB(255, 255, 255);

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
			MappingInit(hdc, sClient, iMapMode);
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
			CreateThenDrawThenAdd(hdc, sClient, iMapMode, F_TRIANGLE, pMouse, &lObjectList);
			ReleaseDC(hWnd, hdc);
			KillTimer(hWnd, ID_TIMER);
			break;
		}
		case WM_KEYDOWN:{
			hdc = GetDC(hWnd);
			switch (wParam){
				case 'O':{
					CreateThenDrawThenAdd(hdc, sClient, iMapMode, F_CIRCLE, pMouse, &lObjectList);
					break;
				}
				case 'T':{
					CreateThenDrawThenAdd(hdc, sClient, iMapMode, F_TRIANGLE, pMouse, &lObjectList);
					break;
				}
				case 'R':{
					CreateThenDrawThenAdd(hdc, sClient, iMapMode, F_RECTANGLE, pMouse, &lObjectList);
					break;
				}
			}
			break;
		}
		case WM_LBUTTONDOWN:{
			ptBeg.x = ptEnd.x = LOWORD(lParam);
			ptBeg.y = ptEnd.y = HIWORD(lParam);
			rgbRectPenColor = RGB(rand() % 255, rand() % 255, rand() % 255);
			rgbRectBrushColor = RGB(rand() % 255, rand() % 255, rand() % 255);
			hdc = GetDC(hWnd);
			MappingInit(hdc, sClient, iMapMode);
			DPtoLP(hdc, &ptBeg, 1);
			DPtoLP(hdc, &ptEnd, 1);

			SelectObject(hdc, GetStockObject(DC_BRUSH));
			SelectObject(hdc, GetStockObject(DC_PEN));
			SetDCPenColor(hdc, rgbRectPenColor);
			SetDCBrushColor(hdc, rgbRectBrushColor);
			DrawBoxOutline(hdc, ptBeg, ptEnd);
			ReleaseDC(hWnd, hdc);
			SetCursor(LoadCursor(NULL, IDC_CROSS));

			fBlocking = TRUE;
			return 0;
		}
		case WM_RBUTTONDOWN:{
			hdc = GetDC(hWnd);
			CreateThenDrawThenAdd(hdc, sClient, iMapMode, F_CIRCLE, pMouse, &lObjectList);
			ReleaseDC(hWnd, hdc);
			break;
		}
		case WM_MOUSEMOVE:{
			if (fBlocking)
			{
				SetCursor(LoadCursor(NULL, IDC_CROSS));

				hdc = GetDC(hWnd);
				MappingInit(hdc, sClient, iMapMode);

				ptEnd = pMouse;

				DPtoLP(hdc, &ptEnd, 1);

				SelectObject(hdc, GetStockObject(DC_BRUSH));
				SelectObject(hdc, GetStockObject(DC_PEN));
				SetDCPenColor(hdc, rgbRectPenColor);
				SetDCBrushColor(hdc, rgbRectBrushColor);
				DrawBoxOutline(hdc, ptBeg, ptEnd);

				RECT rBot, rTop, rLeft, rRight;
				rBot.left = ptBeg.x;
				rBot.top = ptEnd.y;
				rBot.right = ptEnd.x;
				rBot.bottom = ptEnd.y + INVALIDE_RANGE;

				LPtoDP(hdc, (LPPOINT)&rBot, 2);

				rTop.left = ptBeg.x;
				rTop.top = ptBeg.y - INVALIDE_RANGE;
				rTop.right = ptEnd.x;
				rTop.bottom = ptBeg.y;

				LPtoDP(hdc, (LPPOINT)&rTop, 2);

				rLeft.left = ptBeg.x - INVALIDE_RANGE;
				rLeft.top = ptBeg.y;
				rLeft.right = ptBeg.x;
				rLeft.bottom = ptEnd.y;

				LPtoDP(hdc, (LPPOINT)&rLeft, 2);

				rRight.left = ptEnd.x;
				rRight.top = ptBeg.y;
				rRight.right = ptEnd.x + INVALIDE_RANGE;
				rRight.bottom = ptEnd.y;

				LPtoDP(hdc, (LPPOINT)&rRight, 2);

				InvalidateRect(hWnd, &rBot, TRUE);
				InvalidateRect(hWnd, &rTop, TRUE);
				InvalidateRect(hWnd, &rLeft, TRUE);
				InvalidateRect(hWnd, &rRight, TRUE);

				ReleaseDC(hWnd, hdc);
			}
			pMouse.x = LOWORD(lParam);
			pMouse.y = HIWORD(lParam);
			break;
		}
		case WM_LBUTTONUP:
			if (fBlocking)
			{

				ptBoxBeg = ptBeg;
				ptBoxEnd.x = LOWORD(lParam);
				ptBoxEnd.y = HIWORD(lParam);

				SetCursor(LoadCursor(NULL, IDC_ARROW));

				fBlocking = FALSE;

				hdc = GetDC(hWnd);

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

				lObjectList.add(&rRectangle);

				InvalidateRect(hWnd, NULL, TRUE);
				ReleaseDC(hWnd, hdc);
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
