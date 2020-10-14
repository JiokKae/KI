// Main.cpp

/*
	Win32 API
	: Application Programming Interface
	�ü���� �������α׷� ������ ���� �����ϴ� �Լ��� ����
	
	�ϵ���� --------�ü�� (Windows)--------- �������α׷�
						(API �Լ�)

	�ڵ�(Handle) : �����츦 �����ϴ� �� ��ü�� �����ϴ� �ε��� (����)
	�޼���(Message) : �����쿡�� �߻��� �̺�Ʈ�� �ü���� ���� �����쿡�� �����ϴ� ������ ����
*/

#include <Windows.h>
#include <ctime>
#include "StarBox.h"
#include "resource.h"
#include <cmath>
#include <stdio.h>
#pragma warning (disable:4996)

#define NUMBER_OF_BOX	450


// ��������
HINSTANCE	g_hInstance;	// ���α׷� �ν��Ͻ� �ڵ�
HWND		g_hWnd;			// ������ �ڵ�
LPSTR		g_lpszClass = (LPSTR)TEXT("�������� ����");
HBITMAP hbmMem, hbmMemOld;
HDC hdc, hdcMem;
HDC hdc_BackGround;


// ���콺 ��ǥ�� �����ϴ� �Լ�
void GetMouseCoord(COORD & coord, LPARAM lParam);
// ��ǥ�� ���ڸ� �׸��� �Լ�
void DrawRectAtCoord(HDC hdc, int x, int y, int width, int height);

// �ڽ��ȿ� ��ǥ�� �ִ��� �˻�
bool IsInBox(int x, int y, StarBox box);

// ���� �׸��� �Լ�
void MakeStar(HDC hdc, int x, int y, int size);

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

// �����츦 �����ϱ� ���� �Լ�
int APIENTRY WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpszCmdParam, int nCmdShow)
{
	// ������ ������ ���� �⺻ ����
	g_hInstance = _hInstance;
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;		// Ŭ������ ���� �޸�
	wndClass.cbWndExtra = 0;		// �������� ���� �޸�
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = g_hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = g_lpszClass;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	// ������ Ŭ���� ���
	RegisterClass(&wndClass);

	// ������ ����
	g_hWnd = CreateWindow(g_lpszClass, g_lpszClass, WS_OVERLAPPEDWINDOW, 100, 100, 1920, 1080, NULL, NULL, g_hInstance, NULL);

	// ������ ���
	ShowWindow(g_hWnd, nCmdShow);

	// �޼��� ť�� �ִ� �޼��� ó��
	MSG message;
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return message.wParam;
}

// ������ �޼����� ó���ϴ� �Լ� (�ݹ��Լ�)
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
		����
		1. �������� (�Լ� ������ ����)
			���ÿ������� �޸� �Ҵ�
			�Լ� ����� �޸� ����

		2. �������� ( �Լ� �ܺο��� ����)
			�����Ϳ������� �޸� �Ҵ�
			���α׷� ����� �޸� ����

		3. static ���� (�Լ� ������ ����)
			������ �������� �޸� �Ҵ�
			���α׷� ����� �޸� ����
			�Լ� �������� ������ �����ϴ�
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

	case WM_PAINT:	// ������ â�� �ٽ� �׷��� �ʿ䰡 ���� �� ȣ��
		
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
		wsprintf(buf, "���� ������ Ƚ�� : %d", dropCount);
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
	// ���� ����ؼ� �� �� �׸���� �׸� �׸���.
	MoveToEx(hdc, x - 100 * size / 10, y + 20 * size / 10, NULL);	// �׸��� ������ ��ġ�� ����

	LineTo(hdc, x + 100 * size / 10, y + 20 * size / 10);
	LineTo(hdc, x - 65 * size / 10, y + 130 * size / 10);
	LineTo(hdc, x, y - 45 * size / 10);
	LineTo(hdc, x + 65 * size / 10, y + 130 * size / 10);
	LineTo(hdc, x - 100 * size / 10, y + 20 * size / 10);
}