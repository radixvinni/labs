// Lab2.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include "Lab2.h"
#include "..\\Graf.hpp"

#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#define ID_STATUSBAR 200

#pragma warning( disable : 4996 )

#include <cmath>
#include <commctrl.h>
#include <commdlg.h>

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;								// текущий экземпляр приложения
HWND  hStatus;
TCHAR szTitle[MAX_LOADSTRING];					// Текст строки заголовка
TCHAR szWindowClass[MAX_LOADSTRING];			// имя класса главного окна
TCHAR szPathFound[MAX_LOADSTRING];				// надпись Путь найден
TCHAR szPathNotFound[MAX_LOADSTRING];			// надпись Путь не найден
TCHAR szFilter[] = L"Graf (*.graf)\0*.graf\0";	// Фильтр
TCHAR szPath[256];
TCHAR szFileTitle[40];
TCHAR szAboutTitle[MAX_LOADSTRING];
TCHAR szAboutText[MAX_LOADSTRING];
TCHAR szTask[MAX_LOADSTRING];
TCHAR szCurrDir[256];

// Отправить объявления функций, включенных в этот модуль кода:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	DialogGo(HWND, UINT, WPARAM, LPARAM);

// Класс для представления графа
Graf graf;
int temp;
unsigned curA;
unsigned curC;
unsigned curD;

struct WinGDrawer
{
	HDC hdc;
	int mx,my,cx,cy;
	int n,b,r,R;
	double step;
	WinGDrawer(HDC hdc_, int nGrafNodes,int ClientWidth, int ClientHeight):n(nGrafNodes), mx(ClientWidth), my(ClientHeight), hdc(hdc_)
	{
		cx=mx/2;
		cy=my/2;
		int rr=(cx<cy?cx:cy);
		b=(rr/n)>>1;
		R= (int)(rr/(1+sin(M_PI/n)));
		r= rr-R-b;
		step=2*M_PI/n;
	}
	void line(int x,int y,int xx,int yy)
	{
		MoveToEx(hdc,xx,yy, 0);
		LineTo(hdc,x,y);
	}
	void nodeline(int i,int j)
	{
		int x=(int)(cx+R*cos(step*j)), y=(int)(cy+R*sin(step*j));
		int xx=(int)(cx+R*cos(step*i)), yy=(int)(cy+R*sin(step*i));
		line(x,y,xx,yy);
	}
	void node(int j)
	{
		int x=(int)(cx+R*cos(step*j)), y=(int)(cy+R*sin(step*j));
		Ellipse(hdc,x-r,y-r,x+r,y+r);
		TCHAR buf[10];
		_ltow(j,buf,10);
		TEXTMETRIC tm;
		GetTextMetrics (hdc, &tm);
		int l=wcslen(buf);
		int dx=l*tm.tmMaxCharWidth>>2, dy=tm.tmHeight>>1;
		TextOut(hdc,x-dx,y-dy,(LPCWSTR)buf,l);
	}
};

int APIENTRY _tWinMain(HINSTANCE hInstance,
		     HINSTANCE hPrevInstance,
		     LPTSTR    lpCmdLine,
		     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	MSG msg;
	HACCEL hAccelTable;

	// Инициализация глобальных строк
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_LAB2, szWindowClass, MAX_LOADSTRING);
	LoadString(hInstance, IDS_PATH_FOUND, szPathFound, MAX_LOADSTRING);
	LoadString(hInstance, IDS_PATH_NOT_FOUND, szPathNotFound, MAX_LOADSTRING);
	LoadString(hInstance, IDS_ABOUT_TITLE, szAboutTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDS_ABOUT_TEXT, szAboutText, MAX_LOADSTRING);
	LoadString(hInstance, IDS_TASK, szTask, MAX_LOADSTRING);
	curA=0;
	curC=0;
	curD=0;
	MyRegisterClass(hInstance);
	GetCurrentDirectory(256,szCurrDir);
	// Выполнить инициализацию приложения:
	//InitCommonControls();
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB2));

	
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



ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB2));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_LAB2);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

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

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId)
		{
		case IDM_NEW:
			graf.n=0;
			graf.clear();
			InvalidateRect(hWnd,0,TRUE);break;
		case IDM_NEW_NODE:
			graf.newA();
			InvalidateRect(hWnd,0,TRUE);break;
		case IDM_DEL_NODE:
			graf.n=graf.n-1;
			InvalidateRect(hWnd,0,TRUE);break;
		case IDM_OPEN:
			{
				OPENFILENAME ofn;
				memset(&ofn,0,sizeof(ofn));
				ofn.lStructSize = sizeof(ofn);
				ofn.hwndOwner = hWnd;
				ofn.hInstance = hInst;
				ofn.lpstrFilter = (LPCWSTR)szFilter;
				ofn.lpstrFile = szPath;
				ofn.nMaxFile = 256;
				ofn.lpstrFileTitle = szFileTitle;
				ofn.nMaxFileTitle = 40;
				ofn.Flags = OFN_PATHMUSTEXIST  | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
				ofn.lpstrDefExt = TEXT("graf");
				ofn.lpstrInitialDir = szCurrDir;
				if (GetOpenFileName(&ofn) != 0)
				{
					char* mbPath = (char*)malloc(256);
					wcstombs(mbPath,szPath, 256);
					graf.fload(mbPath);
					free(mbPath);
				}
				InvalidateRect(hWnd,0,TRUE);break;
			}
		case IDM_SAVE_AS:
			{
				OPENFILENAME ofn;
				memset(&ofn,0,sizeof(ofn));
				ofn.lStructSize = sizeof(ofn);
				ofn.hwndOwner = hWnd;
				ofn.hInstance = hInst;
				ofn.lpstrFilter = szFilter;
				ofn.lpstrFile = szPath;
				ofn.nMaxFile = 256;
				ofn.lpstrFileTitle = szFileTitle;
				ofn.nMaxFileTitle = 40;
				ofn.Flags = OFN_PATHMUSTEXIST;
				ofn.lpstrDefExt = TEXT("graf");
				ofn.lpstrInitialDir = szCurrDir;
				if (GetSaveFileName(&ofn) != 0)
				{
					char* mbPath = (char*)malloc(256);
					wcstombs(mbPath,szPath,256);
					graf.fsave(mbPath);
					free(mbPath);
				}
				InvalidateRect(hWnd,0,TRUE);break;
			}
		case IDM_GO:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DialogGo);
			InvalidateRect(hWnd,0,TRUE);
			break;
		case IDM_ABOUT:
			MessageBox(hWnd,szAboutText, szAboutTitle,MB_OK);
			break;
		case IDM_TASK:
			MessageBox(hWnd,szTask, szAboutTitle,MB_OK);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	//case WM_CREATE:
		//hStatus = CreateWindowEx(0, STATUSCLASSNAME, (LPWSTR)0, SBARS_SIZEGRIP|WS_CHILD|WS_VISIBLE, 0, 0, 0, 0, hWnd , (HMENU)ID_STATUSBAR, hInst, NULL);	
	case WM_LBUTTONDOWN:
	{
		if(!graf.n){graf.newA(); InvalidateRect(hWnd,0,TRUE); break;}
		int Y = HIWORD (lParam); 
		int X = LOWORD (lParam);
		RECT rect;
		GetClientRect(hWnd,&rect);
		int mx=rect.right-rect.left;
		int my=rect.bottom-rect.top;
		int cx=mx/2, cy=my/2;
		int rr=(cx<cy?cx:cy);
		int n=graf.n;
		int b=(rr/n)>>1;
		int R= (int)(rr/(1+sin(M_PI/n)));
		int r= rr-R-b;
		double step=2*M_PI/n;
		double a=0;
		int res=-1;
		for(int j=0;j<n;j++)
		{
			int x=(int)(cx+R*cos(a)), y=(int)(cy+R*sin(a));
			if((X-x)*(X-x)+(Y-y)*(Y-y)<=r*r)
			res=j;
			a+=step;
		}
		if(res==-1) { graf.newA(); InvalidateRect(hWnd,0,TRUE); }
		else temp=res;
		break;
	}
	case WM_LBUTTONUP:
	{
		if(!graf.n)break;
		int Y = HIWORD (lParam); 
		int X = LOWORD (lParam);
		RECT rect;
		GetClientRect(hWnd,&rect);
		int mx=rect.right-rect.left;
		int my=rect.bottom-rect.top;
		int cx=mx/2, cy=my/2;
		int rr=(cx<cy?cx:cy);
		int n=graf.n;
		int b=(rr/n)>>1;
		int R= (int)(rr/(1+sin(M_PI/n)));
		int r= rr-R-b;
		double step=2*M_PI/n;
		double a=0;
		int res=-1;
		for(int j=0;j<n;j++)
		{
			int x=(int)(cx+R*cos(a)), y=(int)(cy+R*sin(a));
			if((X-x)*(X-x)+(Y-y)*(Y-y)<=r*r)
			res=j;
			a+=step;
		}
		if(res!=-1&&temp!=-1) {graf.setAB(res,temp); temp=-1; }
		InvalidateRect(hWnd,0,TRUE);
		break;
	}
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		RECT rect;
		if(graf.n==0)return EndPaint(hWnd, &ps);
		GetClientRect(hWnd,&rect);
		WinGDrawer dr(hdc,graf.n,rect.right-rect.left,rect.bottom-rect.top);
		double step=2*M_PI/graf.n;
		double a=0;
		for(unsigned j=0;j<graf.n;j++)
		{
			int x=(int)(dr.cx+dr.R*cos(a)), y=(int)(dr.cy+dr.R*sin(a));
			for (unsigned k=0;k<graf.n;k++)
			if(graf.touchingAB(j,k))
				dr.line((int)(dr.cx+dr.R*cos(k*step)),(int)(dr.cy+dr.R*sin(k*step)),x,y);
			a+=step;
		}
		if(curA!=0||curC!=0||curD!=0)
		{
			HGDIOBJ oldPen;
			HPEN myPen = CreatePen(PS_SOLID,4,RGB(100,100,100));
			oldPen = SelectObject(hdc,(HGDIOBJ) myPen);
			int a = graf.searchPath<WinGDrawer>(dr,curA,curC,curD);
			if(a==0)TextOut(hdc,0,0,szPathNotFound,wcslen(szPathNotFound));
			SelectObject(hdc, oldPen);
			DeleteObject(myPen);
		}
		for(unsigned j=0;j<graf.n;j++)
                dr.node(j);
        EndPaint(hWnd, &ps);
		break;
	}
	case WM_SIZE: 
		//SendMessage(GetDlgItem(hWnd, ID_STATUSBAR), WM_SIZE, 0, 0);
		InvalidateRect(hWnd,0,TRUE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

INT_PTR CALLBACK DialogGo(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		SendDlgItemMessage(hDlg,IDC_A,CB_RESETCONTENT,0,0);
		SendDlgItemMessage(hDlg,IDC_C,CB_RESETCONTENT,0,0);
		SendDlgItemMessage(hDlg,IDC_D,CB_RESETCONTENT,0,0);
		for(unsigned i=0;i<graf.n;i++)
		{
			TCHAR t[4];
			_ultow(i,t,10);
			SendDlgItemMessage(hDlg,IDC_A,CB_ADDSTRING,0,(LPARAM)t);
			SendDlgItemMessage(hDlg,IDC_D,CB_ADDSTRING,0,(LPARAM)t);
			SendDlgItemMessage(hDlg,IDC_C,CB_ADDSTRING,0,(LPARAM)t);
		}
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		curA = GetDlgItemInt(hDlg,IDC_A,0,FALSE);
		curC = GetDlgItemInt(hDlg,IDC_C,0,FALSE);
		curD = GetDlgItemInt(hDlg,IDC_D,0,FALSE);
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
