// server.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include "server.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>

#include "bulletinboard.h"

#pragma comment(lib, "Ws2_32.lib")

#define MAX_LOADSTRING 100
#define WSA_ACCEPT (WM_USER+1)
#define WSA_NETEVENT (WM_USER+2)

SOCKET srv_socket;
SOCKET rab_socket;
SOCKADDR_IN acc_sin;

// Глобальные переменные:
HINSTANCE hInst;								// текущий экземпляр
HWND hLst;
TCHAR szTitle[MAX_LOADSTRING];					// Текст строки заголовка
TCHAR szWindowClass[MAX_LOADSTRING];			// имя класса главного окна
TCHAR port[5]=TEXT("70");

// Отправить объявления функций, включенных в этот модуль кода:
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Options(HWND, UINT, WPARAM, LPARAM);

// Регистрирует класс окна.
//    Эта функция и ее использование необходимы только в случае, если нужно, чтобы данный код
//    был совместим с системами Win32, не имеющими функции RegisterClassEx'
//    которая была добавлена в Windows 95. Вызов этой функции важен для того,
//    чтобы приложение получило "качественные" мелкие значки и установило связь
//    с ними.
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SERVER));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_SERVER);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	return RegisterClassEx(&wcex);
}

//  Сохраняет обработку экземпляра и создает главное окно.
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;
   hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной
   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      300, 300, 300, 300, NULL, NULL, hInstance, NULL);
   if (!hWnd)
      return FALSE;
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   hLst=CreateWindow(TEXT("listbox"), NULL,
	   WS_CHILD | WS_VISIBLE | LBS_NOTIFY | WS_VSCROLL | WS_BORDER |
         LBS_WANTKEYBOARDINPUT,
         0, 0, 300, 300,
         hWnd, (HMENU) 0, hInst, NULL);
   return TRUE;
}


// Точка входа для приложения
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
	LoadString(hInstance, IDC_SERVER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);
	// Выполнить инициализацию приложения:
	if (!InitInstance (hInstance, nCmdShow))
		return FALSE;
	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SERVER));
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

BOOL OnCreate()
{
	int rc;
	WSADATA WSAData;
	rc = WSAStartup(MAKEWORD(2,2),&WSAData);
	if(rc!=0)
	{
		MessageBox(0,TEXT("WSAStartup failed"),TEXT("Ошибка"),MB_OK);
		return FALSE;
	}
	return TRUE;
}

BOOL ServerStart(HWND hWnd)
{
	struct sockaddr_in srv_address;
	int rc;
	srv_socket = socket(AF_INET,SOCK_STREAM,0);
	if(srv_socket==INVALID_SOCKET)
	{
		MessageBox(0,TEXT("Не удалось создать сокет"),TEXT("Ошибка"),MB_OK);
		return FALSE;
	}
	srv_address.sin_family = AF_INET;
	srv_address.sin_addr.s_addr = INADDR_ANY;
	
	srv_address.sin_port = htons(_ttoi(port));
	if(bind(srv_socket,(LPSOCKADDR) &srv_address, sizeof(srv_address))==SOCKET_ERROR)
	{
		MessageBox(0,TEXT("Произошла ошибка при инициализации сокета"),TEXT("Ошибка"),MB_OK);
		closesocket(srv_socket);
		return FALSE;
	}
	if(listen(srv_socket,8) == SOCKET_ERROR)
	{
		MessageBox(0,TEXT("Ошибка сокета при ожидании"),TEXT("Ошибка"),MB_OK);
		closesocket(srv_socket);
		return FALSE;
	}
	rc = WSAAsyncSelect(srv_socket, hWnd, WSA_ACCEPT, FD_ACCEPT);
	if(rc>0)
	{
		MessageBox(0,TEXT("Не удалось запустить асинхронный обмен"),TEXT("Ошибка"),MB_OK);
		closesocket(srv_socket);
		return FALSE;
	}
}

void ServerStop(HWND hWnd)
{
	WSAAsyncSelect(srv_socket, hWnd, 0, 0);
	if(srv_socket!=INVALID_SOCKET)
		closesocket(srv_socket);
}

BOOL OnWSAAccept(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	int rc;
	if(WSAGETSELECTERROR(lParam)!=0)
	{
		MessageBox(0,TEXT("Ошибка при получении асинхронного запроса[1]"),TEXT("Ошибка"),MB_OK);
		ServerStop(hWnd);
		return FALSE;
	}
	int acc_sin_len = sizeof(acc_sin);
	rab_socket = accept(srv_socket,(LPSOCKADDR) &acc_sin,(int FAR*) &acc_sin_len);
	if(rab_socket == INVALID_SOCKET)
	{
		MessageBox(0,TEXT("Ошибка при получении асинхронного запроса[2]"),TEXT("Ошибка"),MB_OK);
		ServerStop(hWnd);
		return FALSE;
	}
	rc = WSAAsyncSelect(rab_socket,hWnd,WSA_NETEVENT,FD_READ|FD_CLOSE);
	if(rc>0)
	{
		MessageBox(0,TEXT("Ошибка при получении асинхронного запроса[3]"),TEXT("Ошибка"),MB_OK);
		ServerStop(hWnd);
		return FALSE;
	}
	TCHAR wtmp[255];
	wsprintf(wtmp,TEXT("[%lu] Хост %lu подключён"), clock(), acc_sin.sin_addr.s_addr);
	SendMessage(hLst,LB_ADDSTRING,0,(LPARAM)wtmp);
}

void SendReply(HWND hWnd, SOCKET sock, char szMsg[])
{
	char szBuf[5000];
	szBuf[0]=0;
	if(strcmp(szMsg,"\n")==0)
	{
		// sending list
		for(int i=0; i<ARRAYSIZE(Board);i++)
		{
			strcat(szBuf,Board[i].Name);
			strcat(szBuf,"\n");
		}
		TCHAR wtmp[255];
		wsprintf(wtmp,TEXT("[%lu] Хост %lu запросил список объявлений"), clock(), acc_sin.sin_addr.s_addr);
		SendMessage(hLst,LB_ADDSTRING,0,(LPARAM)wtmp);
	}
	else {
		int i = atoi(szMsg);
		strcat(szBuf,Board[i].Description);
		TCHAR wtmp[255];
		wsprintf(wtmp,TEXT("[%lu] Хост %lu запросил содержимое объявления %d"),clock(), acc_sin.sin_addr.s_addr,i);
		SendMessage(hLst,LB_ADDSTRING,0,(LPARAM)wtmp);
	}
	send(sock,szBuf,strlen(szBuf),0);
}

void OnWSANetEvent(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	int rc;
	char szTemp[256];
	szTemp[0]=0;
	SOCKET sock = (SOCKET) wParam;
	if(WSAGETSELECTEVENT(lParam) == FD_READ)
	{
		int acc_sin_len = sizeof(acc_sin);
		getpeername(sock,(LPSOCKADDR) &acc_sin,(int FAR*) &acc_sin_len);
		rc = recv(sock,szTemp,256,0);
		szTemp[rc]=0;
		if(rc)
			SendReply(hWnd,sock,szTemp);
		//closesocket(sock);
	}
	else if(WSAGETSELECTEVENT(lParam)==FD_CLOSE)
	{
		int acc_sin_len = sizeof(acc_sin);
		getpeername(sock,(LPSOCKADDR) &acc_sin,(int FAR*) &acc_sin_len);
		TCHAR wtmp[255];
		wsprintf(wtmp,TEXT("[%lu] Хост %lu завершил соединение"),clock(), acc_sin.sin_addr.s_addr);
		SendMessage(hLst,LB_ADDSTRING,0,(LPARAM)wtmp);
		closesocket(sock);
	}
}

//  Oбрабатывает сообщения в главном окне.
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
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case IDM_START:
			ServerStart(hWnd);
			break;
		case IDM_STOP:
			ServerStop(hWnd);
			break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_OPTIONS:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_OPTIONS), hWnd, Options);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: добавьте любой код отрисовки...
		EndPaint(hWnd, &ps);
		break;
	case WM_CREATE:
		OnCreate();
		break;
	case WM_SIZE:
		MoveWindow(hLst,0,0,LOWORD(lParam),HIWORD(lParam),TRUE);
		break;
	case WSA_ACCEPT:
		OnWSAAccept(hWnd,message,wParam,lParam);
		break;
	case WSA_NETEVENT:
		OnWSANetEvent(hWnd,message,wParam,lParam);
		break;
	case WM_DESTROY:
		WSACleanup();
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

// Обработчик сообщений для окна "Настройки".
INT_PTR CALLBACK Options(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		SendDlgItemMessage(hDlg, IDC_PORT, WM_SETTEXT, 0, (LPARAM) port); 
		for(int i=0; i<ARRAYSIZE(Board);i++)
		{
			TCHAR wtemp[255];
			wtemp[0]=0;
			MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,Board[i].Name,-1,wtemp,sizeof(wtemp)/sizeof(wtemp[0]));
			SendDlgItemMessage(hDlg,IDC_LIST,LB_ADDSTRING,0,(LPARAM)wtemp);
		}
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (HIWORD(wParam) == LBN_SELCHANGE)
		{
			int sel = SendDlgItemMessage(hDlg,IDC_LIST,LB_GETCURSEL,0,0);
			if(sel==LB_ERR)break;
			TCHAR wtemp[255];
			wtemp[0]=0;
			MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,Board[sel].Name,-1,wtemp,sizeof(wtemp)/sizeof(wtemp[0]));
			SendDlgItemMessage(hDlg, IDC_TITLE, WM_SETTEXT, 0, (LPARAM) wtemp); 
			wtemp[0]=0;
			MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,Board[sel].Description,-1,wtemp,sizeof(wtemp)/sizeof(wtemp[0]));
			SendDlgItemMessage(hDlg, IDC_DESCR, WM_SETTEXT, 0, (LPARAM) wtemp); 
		}
		if (LOWORD(wParam) == IDC_TITLE)
		{
			TCHAR wtemp[255];
			int sel = SendDlgItemMessage(hDlg,IDC_LIST,LB_GETCURSEL,0,0);
			if(sel==LB_ERR)break;
			HWND hWndEdit = GetDlgItem(hDlg, IDC_TITLE);
            GetWindowText(hWndEdit, wtemp, 255);
			WideCharToMultiByte(CP_ACP,WC_COMPOSITECHECK,wtemp,-1,Board[sel].Name,255,0,0);
		}
		if (LOWORD(wParam) == IDC_DESCR)
		{
			TCHAR wtemp[255];
			int sel = SendDlgItemMessage(hDlg,IDC_LIST,LB_GETCURSEL,0,0);
			if(sel==LB_ERR)break;
			HWND hWndEdit = GetDlgItem(hDlg, IDC_DESCR);
            GetWindowText(hWndEdit, wtemp, 255);
			WideCharToMultiByte(CP_ACP,WC_COMPOSITECHECK,wtemp,-1,Board[sel].Description,255,0,0);
		}
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			HWND hWndEdit = GetDlgItem(hDlg, IDC_PORT);
            GetWindowText(hWndEdit, port, 5);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
