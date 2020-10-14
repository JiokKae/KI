// Main.cpp

/*
	Win32 API
	: Application Programming Interface
	운영체제가 응용프로그램 개발을 위해 제공하는 함수의 집합
	
	하드웨어 --------운영체제 (Windows)--------- 응용프로그램
						(API 함수)

	핸들(Handle) : 윈도우를 구성하는 각 객체를 구분하는 인덱스 (정수)
	메세지(Message) : 윈도우에서 발생한 이벤트를 운영체제를 통해 윈도우에게 전달하는 데이터 모음
*/

#include <Windows.h>
#include <ctime>
#include "StarBox.h"
#include "resource.h"
#include <cmath>
#include <stdio.h>
#pragma warning (disable:4996)

#define NUMBER_OF_BOX	450


// 전역변수
HINSTANCE	g_hInstance;	// 프로그램 인스턴스 핸들
HWND		g_hWnd;			// 윈도우 핸들
LPSTR		g_lpszClass = (LPSTR)TEXT("윈메인의 시작");
HBITMAP hbmMem, hbmMemOld;
HDC hdc, hdcMem;
HDC hdc_BackGround;


// 마우스 좌표를 저장하는 함수
void GetMouseCoord(COORD & coord, LPARAM lParam);
// 좌표에 상자를 그리는 함수
void DrawRectAtCoord(HDC hdc, int x, int y, int width, int height);

// 박스안에 좌표가 있는지 검사
bool IsInBox(int x, int y, StarBox box);

// 별을 그리는 함수
void MakeStar(HDC hdc, int x, int y, int size);

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

// 윈도우를 생성하기 위한 함수
int APIENTRY WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpszCmdParam, int nCmdShow)
{
	// 윈도우 생성을 위한 기본 세팅
	g_hInstance = _hInstance;
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;		// 클래스의 여분 메모리
	wndClass.cbWndExtra = 0;		// 윈도우의 여분 메모리
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
	g_hWnd = CreateWindow(g_lpszClass, g_lpszClass, WS_OVERLAPPEDWINDOW, 100, 100, 1920, 1080, NULL, NULL, g_hInstance, NULL);

	// 윈도우 출력
	ShowWindow(g_hWnd, nCmdShow);

	// 메세지 큐에 있는 메세지 처리
	MSG message;
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return message.wParam;
}

// 윈도우 메세지를 처리하는 함수 (콜백함수)
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	static COORD mouseCoord;
	static COORD clickedCoord;
	static StarBox boxes[NUMBER_OF_BOX];
	static int selectedBoxIndex = -1;
	static int dropCount = 350000;
	static bool dragging = false;
	static COORD offset;
	static int ms = 0;
	static HANDLE hTimer;

	/*
		변수
		1. 지역변수 (함수 내에서 선언)
			스택영역에서 메모리 할당
			함수 종료시 메모리 해제

		2. 전역변수 ( 함수 외부에서 선언)
			데이터영역에서 메모리 할당
			프로그램 종료시 메모리 해제

		3. static 변수 (함수 내에서 선언)
			데이터 영역에서 메모리 할당
			프로그램 종료시 메모리 해제
			함수 내에서만 접근이 가능하다
	*/

	switch (iMessage)
	{
	case WM_CREATE:

		hTimer = (HANDLE)SetTimer(hWnd, 1, 1000/70, NULL);

		hdc = GetDC(hWnd);
		hdc_BackGround = CreateCompatibleDC(hdc);
		ReleaseDC(hWnd, hdc);

		HBITMAP bitBackGround;
		bitBackGround = LoadBitmap(g_hInstance, MAKEINTRESOURCE(IDB_BITMAP1));
		SelectObject(hdc_BackGround, bitBackGround);
		DeleteObject(bitBackGround);

		for (int i = 0; i < NUMBER_OF_BOX; i++)
		{
			boxes[i].x = 70 + 60 * (i % 30);
			boxes[i].y = 70 + 60 * (i / 30);
			boxes[i].width = 50;
			boxes[i].height = 50;
		}
		break;
	case WM_TIMER:
		
		if (ms < NUMBER_OF_BOX)
		{
			boxes[ms].isOpened = true;
			boxes[ms].starSize = rand() % 5 + 1;
		}
		ms++;

		InvalidateRect(g_hWnd, NULL, false);
		break;

	case WM_MOUSEMOVE:
		GetMouseCoord(mouseCoord, lParam);
		if (dragging)
		{
			boxes[selectedBoxIndex].x = mouseCoord.X - offset.X;
			boxes[selectedBoxIndex].y = mouseCoord.Y - offset.Y;
		}
		//InvalidateRect(g_hWnd, NULL, false);
		break;

	case WM_LBUTTONDOWN:
		GetMouseCoord(clickedCoord, lParam);
		for (int i = 0; i < NUMBER_OF_BOX; i++)
		{
			if (IsInBox(clickedCoord.X, clickedCoord.Y, boxes[i]))
			{
				selectedBoxIndex = i;
				offset = clickedCoord;
				offset.X -= boxes[i].x;
				offset.Y -= boxes[i].y;
				dragging = true;
				break;
			}
		}
		//InvalidateRect(g_hWnd, NULL, false);
		break;

	case WM_LBUTTONUP:
		if (dragging)
		{
			boxes[selectedBoxIndex].isOpened = true;
			boxes[selectedBoxIndex].starSize = rand() % 5 + 1;
			dragging = false;
		}
		
		//InvalidateRect(g_hWnd, nullptr, false);
		break;

	case WM_RBUTTONDOWN:
		GetMouseCoord(clickedCoord, lParam);
		//InvalidateRect(g_hWnd, NULL, false);
		break;

	case WM_PAINT:	// 윈도우 창이 다시 그려질 필요가 있을 때 호출
		
		hdc = BeginPaint(g_hWnd, &ps);

		hdcMem = CreateCompatibleDC(hdc); //2
		hbmMem = CreateCompatibleBitmap(hdc, 1920, 1100);//3
		hbmMemOld = (HBITMAP)SelectObject(hdcMem, hbmMem);//4

		BitBlt(hdcMem, 0, 0, 1920, 1100, hdc_BackGround, 0, 0, SRCCOPY);

		for (int i = 0; i < NUMBER_OF_BOX; i++)
		{
			if(boxes[i].isOpened == false)
				DrawRectAtCoord(hdcMem, boxes[i].x, boxes[i].y, boxes[i].width, boxes[i].height);
			else 
			{
				int isDrop = ++boxes[i].starSize / 3 / 15;

				if (isDrop)
				{
					dropCount++;
					boxes[i].starSize = boxes[i].starSize % 15 + 1;
				}
				double xoffset = sin((ms + boxes[i].x)/10.0) * 200.0;
				char buf[50];
				
				sprintf(buf, "xoffset : %lf", xoffset);
				TextOut(hdcMem, 0, 20, buf, strlen(buf));

				WORD r = (boxes[i].height + boxes[i].starSize + ms) % 150 + 100;
				WORD g = (boxes[i].height + boxes[i].starSize + ms+r) % 150 + 100;
				WORD b = (boxes[i].height + boxes[i].starSize + ms+g) % 150 + 0;

				HPEN hNewPen = CreatePen(PS_SOLID, 3, RGB(r, g, b));
				HPEN hOldPen = (HPEN)SelectObject(hdcMem, hNewPen);

				MakeStar(hdcMem, boxes[i].x + xoffset, (boxes[i].y += 10) % 1100, boxes[i].starSize / 3);

				DeleteObject(SelectObject(hdcMem, hNewPen));
				(HPEN)SelectObject(hdcMem, hOldPen);
				DeleteObject(SelectObject(hdcMem, hOldPen));

			}
				
		}
		char buf[50];
		wsprintf(buf, "별이 떨어진 횟수 : %d", dropCount);
		TextOut(hdcMem, 0, 0, buf, strlen(buf));

		BitBlt(hdc, 0, 0, 1920, 1100, hdcMem, 0, 0, SRCCOPY);

		SelectObject(hdcMem, hbmMemOld); //-4
		DeleteObject(hbmMem); //-3
		DeleteDC(hdcMem); //-2

		EndPaint(g_hWnd, &ps);

		break;

	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

void GetMouseCoord(COORD & coord, LPARAM lParam)
{
	coord.X = LOWORD(lParam);
	coord.Y = HIWORD(lParam);
}

void DrawRectAtCoord(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

bool IsInBox(int x, int y, StarBox box) 
{
	if (box.isOpened)
		return false;
	if (x >= box.x && x <= box.x + box.width && y >= box.y && y <= box.y + box.height)
		return true;
	else
		return false;
}

void MakeStar(HDC hdc, int x, int y, int size)
{
	// 선을 사용해서 한 붓 그리기로 네모를 그린다.
	MoveToEx(hdc, x - 100 * size / 10, y + 20 * size / 10, NULL);	// 그리기 시작할 위치를 지정

	LineTo(hdc, x + 100 * size / 10, y + 20 * size / 10);
	LineTo(hdc, x - 65 * size / 10, y + 130 * size / 10);
	LineTo(hdc, x, y - 45 * size / 10);
	LineTo(hdc, x + 65 * size / 10, y + 130 * size / 10);
	LineTo(hdc, x - 100 * size / 10, y + 20 * size / 10);
}