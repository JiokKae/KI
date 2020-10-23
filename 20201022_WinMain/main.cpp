// main.cpp

/*
	Win32 API
	: Application Programming Interface
	운영체제가 응용프로그램 개발을 위해 제공해는 함수의 집합

	하드웨어 ----------운영체제 (Windows)---------- 응용프로그램
						(API 함수)
*/

#include <Windows.h>
#include "MainGame.h"

// 전역변수
HINSTANCE	g_hInstance;	// 프로그램 인스턴스 핸들
HWND		g_hWnd;			// 윈도우 핸들
LPSTR		g_lpszClass = (LPSTR)TEXT("윈메인의 시작");
MainGame	g_mainGame;
int			g_Frame;

void SetWindowSize(int startX, int startY, int sizeX, int sizeY);
void MakeRectangle(HDC hdc, int x, int y, int size);
void MakeStar(HDC hdc, int x, int y);

void MakeRectangle(HDC hdc, int x, int y, int size)
{
	MoveToEx(hdc, x, y, NULL);
	LineTo(hdc, x + size, y);
	LineTo(hdc, x + size, y + size);
	LineTo(hdc, x, y + size);
	LineTo(hdc, x, y);
}

void MakeStar(HDC hdc, int x, int y)
{
	MoveToEx(hdc, x, y, NULL);		// 그리기 시작할 위치를 지정
	LineTo(hdc, x + 30, y);
	LineTo(hdc, x + 5, y + 20);
	LineTo(hdc, x + 15, y - 10);
	LineTo(hdc, x + 25, y + 20);
	LineTo(hdc, x, y);
}

// 포인트와 렉트의 충돌확인
bool IsInRect(RECT rc, POINT pt)
{
	//if (pt.x < rc.left || pt.x > rc.right 
	//	|| pt.y < rc.top || pt.y > rc.bottom)
	//{
	//	return false;
	//}

	//return true;


	// 마우스 x좌표가 left보다 크다 &&
	// 마우스 x좌표가 right보다 작다 &&
	// 마우스 y좌표가 top보다 크다 &&
	// 마우스 y좌표가 bottom보다 작다
	if (rc.left < pt.x && pt.x < rc.right 
		&& rc.top < pt.y && pt.y < rc.bottom)
	{
		return true;
	}

	return false;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

// 윈도우를 생성하기 위한 함수
int APIENTRY WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpszCmdParam, int nCmdShow)
{
	// 윈도우 생성을 위한 기본셋팅
	g_hInstance = _hInstance;
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;	// 클래스 여분 메모리
	wndClass.cbWndExtra = 0;	// 윈도우 여분 메모리
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = g_hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = g_lpszClass;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	// 윈도우 클래스 등록
	RegisterClass(&wndClass);

	// 윈도우 생성
	g_hWnd = CreateWindow(g_lpszClass, g_lpszClass,
		WS_OVERLAPPEDWINDOW,
		50, 50, WINSIZE_X, WINSIZE_Y,
		NULL, NULL, g_hInstance, NULL);

	// 윈도우 실작업영역 재설정
	SetWindowSize(0, 0, WINSIZE_X, WINSIZE_Y);

	// 윈도우 출력
	ShowWindow(g_hWnd, nCmdShow);

	g_mainGame.Init(g_hInstance, g_hWnd);

	// 메시지 큐에 있는 메시지 처리
	MSG message;
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	g_mainGame.Release();


	return message.wParam;
}

// 윈도우 메세지를 처리하는 함수 (콜백함수)
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, 
	WPARAM wParam, LPARAM lParam)
{
	return g_mainGame.MainProc(hWnd, iMessage, wParam, lParam);
}

void SetWindowSize(int startX, int startY, int sizeX, int sizeY)
{
	// 윈도우 작업영역 지정
	RECT rc;
	rc.left = 0; rc.top = 0;
	rc.right = sizeX; rc.bottom = sizeY;

	// 실제 윈도우 크기 받아온다.
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

	// 이동
	MoveWindow(g_hWnd, startX, startY, rc.right - rc.left,
		rc.bottom - rc.top, true);
}