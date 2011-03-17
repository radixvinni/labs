// computergraphics.cpp: определяет точку входа для приложения.
// scene.txt: определяет сцену
/*	Формат файла сцены:
		* координаты камеры в экранных пикселах (x, y, z). Начало системы координат в центре экрана.
		* поворот сцены в радианах, считая от обратного напрвления оси z (вдоль оси y, вдоль оси z)
		* координаты источника света (x,y,z)
		(Полигональная сетка - список вершин)
		* Количество вершин
		* Список координат вершин (x,y,z). Нумерация с нуля
		* Список полигонов (количество вершин, номер первой вершины, номер второй ...)
*/

#include "stdafx.h"
#include "computergraphics.h"
#include <fstream>
#include <conio.h> 
#include <iostream>
#include <cmath>
#include <math.h>
#include <ctime>

#define MAX_POLYS 1000

// Глобальные переменные:
HINSTANCE hInst;								// текущий экземпляр
TCHAR szTitle[] = L"Компьютерная Графика";					// Текст строки заголовка
TCHAR szWindowClass[] = L"COMPUTERGRAPHICS";			// имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
//INT_PTR CALLBACK	DialogProc(HWND, UINT, WPARAM, LPARAM);

HBRUSH bgr;

/*
	Данные сцены:
	*	ox,oy,oz	координаты наблюдателя(камеры)
	*	phi, psi	углы наблюдения
	*	lx,ly,lz	координаты источника света
	*	Полигональная сетка: способ представления: списки вершин
		*	npoints	количество вершин
		*	npolys	количество многоугольников
		*	points	список вершин: x,y,z	координаты
		*	prjpoints	список вершин после преобразования координат. Фактически x,y - координаты точки-проэкции на экране.
		*	polys	список многоугольников: n	количество вершин,	p	номера вершин, maxx,maxy... координаты объемлющей оболочки фигуры на экране
*/
struct Scene {
	float ox, oy, oz, phi, psi, lx,ly, lz;
	struct Mesh {
		int npoints, npolys;
		struct Point{ 
			float x,y,z; 
		} *points;
		struct ProjectPoint
		{
			int x,y;
			float z;
		} *prjpoints;
		struct Poly{
			int n;
			int *p;
			int maxx, maxy, minx, miny;
			int color;
		} *polys;
	} mesh;
} scene;
int startx=0, starty=0;
float psi , phi;
void scene_correct(float phi, float psi);

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int  nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	MSG msg;
	HACCEL hAccelTable;
	WNDCLASSEX wcex;
    HWND hWnd;

	std::ifstream fs("scene.txt");
	int n;
	fs>>scene.ox>>scene.oy>>scene.oz>>scene.phi>>scene.psi>>scene.lx>>scene.ly>>scene.lz>>n;
	scene.mesh.points = new Scene::Mesh::Point[n];
	scene.mesh.prjpoints = new Scene::Mesh::ProjectPoint[n];
	scene.mesh.npoints = n;
	for(int i=0;i<n;i++)
		fs>>scene.mesh.points[i].x>>scene.mesh.points[i].y>>scene.mesh.points[i].z;
	int k=0;
	scene.mesh.polys = new Scene::Mesh::Poly[MAX_POLYS];
	while (!fs.eof()) 
	{
		fs>>scene.mesh.polys[k].n;
		scene.mesh.polys[k].p = new int[scene.mesh.polys[k].n];
		for(int j=0;j<scene.mesh.polys[k].n;j++)
			fs>>scene.mesh.polys[k].p[j];
		
		fs>>scene.mesh.polys[k].color;
		k++;
	}
	scene.mesh.npolys=k;
	scene_correct(scene.phi,scene.psi);
	fs.close();

	bgr = (HBRUSH)GetStockObject(WHITE_BRUSH);

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_COMPUTERGRAPHICS));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_COMPUTERGRAPHICS);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	RegisterClassEx(&wcex);

	// Выполнить инициализацию приложения:
    hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной
    hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
	if (!hWnd) return FALSE;

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_COMPUTERGRAPHICS));

	// Цикл основного сообщения:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	delete[] scene.mesh.points;
	delete[] scene.mesh.prjpoints;
	for(int i=0; i<scene.mesh.npolys;i++) delete[] scene.mesh.polys[i].p;
	delete[] scene.mesh.polys;
	return (int) msg.wParam;
}

// Функция scene_correct проставляет прямоугольные объемлющие оболочки проэкций фигур.
// Функция scene_correct осуществляет преобразование координат
void scene_correct(float phi, float psi)
{
	for(int i=0; i<scene.mesh.npoints; ++i)
	{
		scene.mesh.prjpoints[i].x = cosf(psi)*scene.mesh.points[i].x + sinf(psi)*scene.mesh.points[i].z;
		scene.mesh.prjpoints[i].y = cosf(phi)*scene.mesh.points[i].y + sinf(phi)*(cosf(psi)*scene.mesh.points[i].z - sinf(psi)*scene.mesh.points[i].x);
		scene.mesh.prjpoints[i].z = cosf(phi)*(cosf(psi)*scene.mesh.points[i].z - sinf(psi)*scene.mesh.points[i].x) - sinf(phi)*scene.mesh.points[i].y;
	}
	for(int i=0; i<scene.mesh.npolys; ++i)
	{
		scene.mesh.polys[i].maxx=-0x7ffffffe;
		scene.mesh.polys[i].maxy=-0x7ffffffe;
		scene.mesh.polys[i].minx=0x7ffffffe;
		scene.mesh.polys[i].miny=0x7ffffffe;
		for(int j=0; j<scene.mesh.polys[i].n; ++j)
		{
			Scene::Mesh::ProjectPoint p = scene.mesh.prjpoints[scene.mesh.polys[i].p[j]];
			if(scene.mesh.polys[i].maxx<p.x)scene.mesh.polys[i].maxx=p.x;
			if(scene.mesh.polys[i].minx>p.x)scene.mesh.polys[i].minx=p.x;
			if(scene.mesh.polys[i].maxy<p.y)scene.mesh.polys[i].maxy=p.y;
			if(scene.mesh.polys[i].miny>p.y)scene.mesh.polys[i].miny=p.y;
		}
	}
}
// Функция point_inside определяет, лежит ли точка внутри прямоугольника pol
/*		В основе алгоритма лежит идея подсчёта количества пересечений луча, исходящего из данной точки 
		в направлении горизонтальной оси, со сторонами многоугольника. Если оно чётное, точка не принадлежит 
		многоугольнику. В данном алгоритме луч направлен влево. */
bool point_inside(int x, int y, int pol)
{
	bool c = false;
	int npol = scene.mesh.polys[pol].n;
	for (int i = 0, j = npol - 1; i < npol; j = i++) 
	{
		int ypi = scene.mesh.prjpoints[scene.mesh.polys[pol].p[i]].y;
		int ypj = scene.mesh.prjpoints[scene.mesh.polys[pol].p[j]].y;
		int xpi = scene.mesh.prjpoints[scene.mesh.polys[pol].p[i]].x;
		int xpj = scene.mesh.prjpoints[scene.mesh.polys[pol].p[j]].x;
		if ((((ypi<=y)&&(y<ypj))||((ypj<=y)&&(y<ypi))) && (x>(xpj - xpi)*(y - ypi)/(ypj - ypi)+xpi))
			c = !c;
	}
	return c;
}
// Функция norma нормирует вектор
void norma(Scene::Mesh::Point& l)
{
	float L = sqrtf(l.x*l.x+l.y*l.y+l.z*l.z);
	l.x = l.x / L;
	l.y = l.y / L;
	l.z = l.z / L;
}
// Функция draw_point закрашивает точку экрана с координатами х, у цветом многоугольника
void draw_point(HDC hdc, int x, int y)
{
	// определим, какой многоугольник находится ближе. Перебирая полигоны, смотрим какой ближе.
	float minz = 1000;
	int mini = -1;
	for(int i=0; i<scene.mesh.npolys; ++i)
	{
		if(!point_inside(x,y,i)) continue;
		// построем плоскость по 3м точкам и выразим z через x, y.
		Scene::Mesh::ProjectPoint p1 = scene.mesh.prjpoints[scene.mesh.polys[i].p[0]];
		Scene::Mesh::ProjectPoint p2 = scene.mesh.prjpoints[scene.mesh.polys[i].p[1]];
		Scene::Mesh::ProjectPoint p3 = scene.mesh.prjpoints[scene.mesh.polys[i].p[2]];
		float b = ((p3.z-p1.z)*(p2.x-p1.x)-(p2.z-p1.z)*(p3.x-p1.x))/((p2.y-p1.y)*(p3.x-p1.x)-(p3.y-p1.y)*(p2.x-p1.x));
		float a = (b*(p2.y-p1.y) + p2.z - p1.z)/(p1.x-p2.x);
		float d = -p1.z - a*p1.x - b*p1.y;
		float z = -d - a*x - b*y;
		if ((scene.oz<z)&&(minz>z)) {minz = z; mini = i;}
	}
	if(mini==-1)
	{
		SetPixel(hdc,x,y,RGB(255,255,255));
		return;
	}
	// определим освещенность пиксела
	// l <- направление на источник
	Scene::Mesh::Point l, n, r, e;
	l.x = scene.lx - x;
	l.y = scene.ly - y;
	l.z = scene.lz - minz;
	norma(l);
	Scene::Mesh::ProjectPoint p1 = scene.mesh.prjpoints[scene.mesh.polys[mini].p[0]];
	Scene::Mesh::ProjectPoint p2 = scene.mesh.prjpoints[scene.mesh.polys[mini].p[1]];
	Scene::Mesh::ProjectPoint p3 = scene.mesh.prjpoints[scene.mesh.polys[mini].p[2]];
	// a = p2 - p1, b = p3 - p1, n = [a * b] <- направление нормали
	n.x = (p2.y-p1.y)*(p3.z-p1.z) - (p2.z-p1.z)*(p3.y-p1.y);
	n.y = (p2.z-p1.z)*(p3.x-p1.x) - (p2.x-p1.x)*(p3.z-p1.z);
	n.z = (p2.x-p1.x)*(p3.y-p1.y) - (p2.y-p1.y)*(p3.x-p1.x);
	norma(n);
	// r = 2 (l * n) * n - l <- отраженный луч
	float ln = l.x*n.x + l.y*n.y + l.z*n.z; // (l,n) <- cos(угол между источником и нормалью)
	r.x = 2*ln*n.x - l.x;
	r.y = 2*ln*n.y - l.y;
	r.z = 2*ln*n.z - l.z;
	norma(r);
	// e <- направление на зрителя = 0,0,-1
	e.x = 0;
	e.y = 0;
	e.z = -1;
	//norma(e);
	float er = e.x*r.x + e.y*r.y + e.z*r.z;
	//if (er<0)er=0;
	// I = If*kf + Is*(ks*cos(l,n) + omega*cos^n(e,r)), n=4;
	float I = 200 + 15*(ln+5*er*er*er);
	int i = (I<=255.0)?(int)I:255;
	// закрасим пиксел
	COLORREF cl = RGB(i,i,i);
	if (scene.mesh.polys[mini].color==1) cl = RGB(i,10,10);
	if (scene.mesh.polys[mini].color==2) cl = RGB(10,i,10);
	if (scene.mesh.polys[mini].color==3) cl = RGB(10,10,i);

	SetPixel(hdc,x,y,cl);
}
// Функция is_free возвращает, является ли прямоугольник пустым.
bool is_free(LPRECT r)
{
	for(int i=0; i<scene.mesh.npolys; ++i)
	{
		// bottom - miny, top - maxy, right - maxx, left - minx
		bool intersectx, intersecty;
		if(r->bottom < scene.mesh.polys[i].miny) intersecty = r->top > scene.mesh.polys[i].miny;
		else if(r->top > scene.mesh.polys[i].maxy) intersecty = r->bottom < scene.mesh.polys[i].maxy;
		else intersecty = true;
		
		if(r->left < scene.mesh.polys[i].minx) intersectx = r->right > scene.mesh.polys[i].minx;
		else if(r->right > scene.mesh.polys[i].maxx) intersectx = r->left < scene.mesh.polys[i].maxx;
		else intersectx = true;

		if (intersectx && intersecty) return false;
	}
	return true;
}
// Функция draw_scene рисует сцену методом Варнока
void draw_scene(HDC hdc, LPRECT r)
{
	if (is_free(r)) { r->bottom+=1;r->right+=1; FillRect(hdc,r,bgr); r->bottom-=1;r->right-=1; return; }
	
	LPRECT t = new RECT;
	if (r->bottom<=r->top)
		if (r->left>=r->right) draw_point(hdc,r->left,r->bottom);
		else // left, right
		{
			t->bottom=r->bottom;
			t->left=r->left;
			t->right=(r->right+r->left)>>1;
			t->top=r->top;
			draw_scene(hdc,t);
			t->left=t->right+1;
			t->right=r->right;
			draw_scene(hdc,t);
		}
	else
	{
		if (r->left>=r->right)
		{
			t->bottom=(r->top+r->bottom)>>1;
			t->left=r->left;
			t->right=r->right;
			t->top=r->top;
			draw_scene(hdc,t);
			t->top=t->bottom+1;
			t->bottom=r->bottom;
			draw_scene(hdc,t);
		}
		else
		{
			t->bottom=(r->top+r->bottom)>>1;
			t->left=r->left;
			t->right=(r->right+r->left)>>1;
			t->top=r->top;
			draw_scene(hdc,t);
			t->left=t->right+1;
			t->right=r->right;
			draw_scene(hdc,t);
			t->top=t->bottom+1;
			t->bottom=r->bottom;
			draw_scene(hdc,t);
			t->right=t->left-1;
			t->left=r->left;
			draw_scene(hdc,t);
		}
	}
	delete t;
}
//
//  ФУНКЦИЯ WndProc обрабатывает сообщения в главном окне.
//
//  WM_COMMAND	- обработка меню приложения
//  WM_PAINT	- Закрасить главное окно
//  WM_DESTROY	 - ввести сообщение о выходе и вернуться.
// 
//
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
		case IDM_ABOUT:
			//DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, DialogProc);
			MessageBox(hWnd,L"   Лабораторная работа №2\n   \"Компьютерная графика\"\n   студент Винников Александр\n   группа А-14-07",L"О программе",MB_OK);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		{
			clock_t startpaint = clock ();
			hdc = BeginPaint(hWnd, &ps);
			LPRECT r = new RECT;
			GetClientRect(hWnd,r);
			LPPOINT pt = new POINT;
			int cxClient=(r->left+r->right)>>1;
			int cyClient=(r->bottom+r->top)>>1;
			SetWindowOrgEx(hdc,-cxClient,-cyClient,pt);
			r->top=-cyClient;
			r->left=-cxClient;
			r->bottom=cyClient;
			r->right=cxClient;
			draw_scene(hdc, r);
			delete r;
			delete pt;
			wchar_t ch[65];
			wsprintf(ch,L"phi: %i psi: %i time: %u ms",(int)(phi*100), (int)(psi*100), clock()-startpaint);
			TextOut(hdc,cxClient-190,-cyClient+2,ch,wcslen(ch));
			EndPaint(hWnd, &ps);
			break;
		}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:
		startx=HIWORD(lParam);
		starty=LOWORD(lParam);
		break;
	case WM_LBUTTONUP:
		scene.phi+=(float)(HIWORD(lParam)-startx)/100;
		scene.psi+=(float)(LOWORD(lParam)-starty)/100;
		startx=0;
		starty=0;
		break;
	case WM_MOUSEMOVE:
		if(startx==0&&starty==0)break;
		scene_correct(scene.phi+(float)(HIWORD(lParam)-startx)/100, scene.psi+(float)(LOWORD(lParam)-starty)/100);
		phi = scene.phi+(float)(HIWORD(lParam)-startx)/100;
		psi = scene.psi+(float)(LOWORD(lParam)-starty)/100;
		InvalidateRect(hWnd,0,FALSE);
		//UpdateWindow(hWnd);
		//RedrawWindow(hWnd,0,0,0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Обработчик сообщений для диалог окна. Можно удалить.
/*INT_PTR CALLBACK DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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
*/