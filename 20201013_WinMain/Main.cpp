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
#include "StarBox.h"

// ��������
HINSTANCE	g_hInstance;	// ���α׷� �ν��Ͻ� �ڵ�
HWND		g_hWnd;			// ������ �ڵ�
LPSTR		g_lpszClass = (LPSTR)TEXT("�������� ����");

// ���콺 ��ǥ�� �����ϴ� �Լ�
void GetMouseCoord(COORD & coord, LPARAM lParam);
// ��ǥ�� ���ڸ� �׸��� �Լ�
void DrawRectAtCoord(HDC hdc, int x, int y, int width, int height);

// �ڽ��ȿ� ��ǥ�� �ִ��� �˻�
bool IsInBox(int x, int y, StarBox box);

// ���� �׸��� �Լ�
void MakeStar(HDC hdc, int x, int y);

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
	g_hWnd = CreateWindow(g_lpszClass, g_lpszClass, WS_OVERLAPPEDWINDOW, 100, 100, 1200, 900, NULL, NULL, g_hInstance, NULL);

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
	static StarBox boxes[10];
	static int selectedBoxIndex = -1;
	static bool dragging = false;
	static COORD offset;
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
		for (int i = 0; i < 10; i++)
		{
			boxes[i].x = 100 + 75 * i;
			boxes[i].y = 700;
			boxes[i].width = 50;
			boxes[i].height = 50;
		}
		break;

	case WM_MOUSEMOVE:
		GetMouseCoord(mouseCoord, lParam);
		if (dragging)
		{
			boxes[selectedBoxIndex].x = mouseCoord.X - offset.X;
			boxes[selectedBoxIndex].y = mouseCoord.Y - offset.Y;
		}
		InvalidateRect(g_hWnd, NULL, true);
		break;

	case WM_LBUTTONDOWN:
		GetMouseCoord(clickedCoord, lParam);
		for (int i = 0; i < 10; i++)
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
		InvalidateRect(g_hWnd, NULL, true);
		break;

	case WM_LBUTTONUP:
		if (dragging)
		{
			boxes[selectedBoxIndex].isOpened = true;
			dragging = false;
		}
		
		break;

	case WM_RBUTTONDOWN:
		GetMouseCoord(clickedCoord, lParam);
		InvalidateRect(g_hWnd, NULL, true);
		break;

	case WM_PAINT:	// ������ â�� �ٽ� �׷��� �ʿ䰡 ���� �� ȣ��
		HDC hdc;	// �ڵ� : dc (Device Context)
		hdc = BeginPaint(g_hWnd, &ps);

		for (int i = 0; i < 10; i++)
		{
			if(boxes[i].isOpened == false)
				DrawRectAtCoord(hdc, boxes[i].x, boxes[i].y, boxes[i].width, boxes[i].height);
			else 
				MakeStar(hdc, boxes[i].x, boxes[i].y);
		}

		EndPaint(g_hWnd, &ps);

		break;

	case WM_DESTROY:
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

void MakeStar(HDC hdc, int x, int y)
{
	// ���� ����ؼ� �� �� �׸���� �׸� �׸���.
	MoveToEx(hdc, x, y, NULL);	// �׸��� ������ ��ġ�� ����

	LineTo(hdc, x + 200, y);
	LineTo(hdc, x + 35, y + 110);
	LineTo(hdc, x + 100, y - 65);
	LineTo(hdc, x + 165, y + 110);
	LineTo(hdc, x, y);
}