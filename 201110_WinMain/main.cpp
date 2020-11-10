// main.cpp

/*
	Win32 API
	: Application Programming Interface
	운영체제가 응용프로그램 개발을 위해 제공하는 함수의 집합

	하드웨어 ----------운영체제(Windows)---------- 응용프로그램
						 ( API 함수 )
*/

#include <Windows.h>
#include "MainGame.h"

// 전역변수
HINSTANCE	g_hInstance;		// 프로그램 인스턴스 핸들
HWND		g_hWnd;				// 윈도우 핸들
LPSTR		g_lpszClass = (LPSTR)TEXT("윈메인의 시작");
MainGame	g_mainGame;

void SetWindowSize(int startX, int startY, int sizeX, int sizeY);
void MakeRectangle(HDC hdc, int x, int y, int size);
void MakeStar(HDC hdc, int x, int y, int ratio);

// 선을 그려서 네모를 그린다.
void MakeRectangle(HDC hdc, int x, int y, int size)
{
	MoveToEx(hdc, x, y, NULL);		// 특정좌표로 이동
	LineTo(hdc, x + size, y);
	LineTo(hdc, x + size, y + size);
	LineTo(hdc, x, y + size);
	LineTo(hdc, x, y);
}

// 별을 그리는 함수
void MakeStar(HDC hdc, int x, int y, int ratio)
{
	MoveToEx(hdc, x, y, NULL);
	LineTo(hdc, x + 10 * ratio, y);
	LineTo(hdc, x + 2 * ratio, y + 7 * ratio);
	LineTo(hdc, x + 5 * ratio, y - 4 * ratio);
	LineTo(hdc, x + 8 * ratio, y + 7 * ratio);
	LineTo(hdc, x, y);
}

// 클릭된 좌표가 네모 안에 있는지 확인하는 함수
//bool IsInRect(RECT rc, MOUSE_DATA mouseData)
//{
//	if (rc.left <= mouseData.clickedPosX && mouseData.clickedPosX <= rc.right
//		&& rc.top <= mouseData.clickedPosY && mouseData.clickedPosY <= rc.bottom)
//	{
//		return true;
//	}
//
//	return false;
//}

// 렉트와 렉트의 충돌을 확인하는 함수
bool CheckRectCollision(RECT rc1, RECT rc2)
{
	if (rc1.right < rc2.left ||
		rc1.left > rc2.right ||
		rc1.top > rc2.bottom ||
		rc1.bottom < rc2.top)
	{
		return false;
	}

	return true;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam);

// 메인함수
int APIENTRY WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance,
	LPSTR _lpszCmdParam, int nCmdShow)
{
	// 윈도우를 생성하기 위한 기본셋팅
	g_hInstance = _hInstance;
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;	// 클래스의 여분 메모리
	wndClass.cbWndExtra = 0;	// 윈도우의 여분 메모리
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

	// 윈도우 출력
	ShowWindow(g_hWnd, nCmdShow);

	// 실제 작업 사이즈로 설정
	SetWindowSize(50, 50, WINSIZE_X, WINSIZE_Y);

	g_mainGame.Init();

	// 메시지 큐에 있는 메시지 처리
	MSG message;
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	g_mainGame.Release();

	// 타이머 해제
	KillTimer(g_hWnd, 0);

	return message.wParam;
}

// 콜백함수 : 윈도우 메시지(이벤트)를 처리하는 함수
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, 
	WPARAM wParam, LPARAM lParam)
{
	return g_mainGame.MainProc(hWnd, iMessage,
		wParam, lParam);
}

void SetWindowSize(int startX, int startY, int sizeX, int sizeY)
{
	// 윈도우 작업영역 지정
	RECT rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = sizeX;
	rc.bottom = sizeY;

	// 실제 윈도우 크기 받아오기
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

	// 이동
	MoveWindow(g_hWnd, startX, startY, rc.right - rc.left, rc.bottom - rc.top, true);
}