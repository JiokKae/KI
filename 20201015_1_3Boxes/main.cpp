#include <Windows.h>
#include "MyWinLibrary.h"
#include "resource.h"

#define BIGBOX_MAX_COUNT	100
#define BIGBOX_SPEED		5
#define WINDOW_SIZE_X		1920
#define WINDOW_SIZE_Y		1080
HINSTANCE g_hInstance;
HWND g_hWnd;
LPSTR g_lpszClass = (LPSTR)TEXT("삼 상자");
HBITMAP hbmMem, hbmMemOld;
HDC hdc, hdcMem;
HDC hdc_BackGround;

struct BigBox;

class SmallBox
{
public:
	BigBox* parent;
	POINT position;
	int width;
	int height;

	RECT GetRect()
	{
		RECT rect;
		rect = { position.x, position.y, position.x + width, position.y + height };
		return rect;
	}
};

class BigBox
{
public:
	int index;
	POINT position;
	int width;
	int height;
	int speed;

	RECT GetRect() 
	{
		RECT rect;
		rect = { position.x, position.y, position.x + width, position.y + height };
		return rect;
	}
};

void MoveBigBox(SmallBox &smallBox, BigBox* bigBoxes);
void Init(BigBox* bigBoxes, SmallBox* pSmallBox);
void Render(HDC hdc, BigBox* bigBoxes, SmallBox smallBox);

// 박스의 충돌 검사
int BoxCollision(RECT box1, RECT box2);

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpszCmdParam, int nCmdShow)
{
	g_hInstance = _hInstance;

	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = g_hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = g_lpszClass;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_VREDRAW | CS_HREDRAW;
	
	RegisterClass(&wndClass);

	g_hWnd = CreateWindow(g_lpszClass, g_lpszClass, WS_OVERLAPPEDWINDOW, 50, 50, WINDOW_SIZE_X, WINDOW_SIZE_Y, NULL, NULL, g_hInstance, NULL);

	ShowWindow(g_hWnd, nCmdShow);

	MSG message;
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;

	static BigBox bigBoxes[BIGBOX_MAX_COUNT];
	static SmallBox smallBox;
	static HANDLE hTimer;
	switch (iMessage)
	{
	case WM_CREATE:
		hTimer = (HANDLE)SetTimer(hWnd, 1, 1000 / 70, NULL);

		hdc = GetDC(hWnd);
		hdc_BackGround = CreateCompatibleDC(hdc);
		ReleaseDC(hWnd, hdc);

		HBITMAP bitBackGround;
		bitBackGround = LoadBitmap(g_hInstance, MAKEINTRESOURCE(IDB_BITMAP1));
		SelectObject(hdc_BackGround, bitBackGround);
		DeleteObject(bitBackGround);

		Init(bigBoxes, &smallBox);

		break;
	case WM_TIMER:
		MoveBigBox(smallBox, bigBoxes);
		
		InvalidateRect(g_hWnd, NULL, false);
		break;
	case WM_KEYDOWN:
		
		
		break;

	case WM_PAINT:
		HDC hdc;
		hdc = BeginPaint(g_hWnd, &ps);


		hdcMem = CreateCompatibleDC(hdc); //2
		hbmMem = CreateCompatibleBitmap(hdc, WINDOW_SIZE_X, WINDOW_SIZE_Y);//3
		hbmMemOld = (HBITMAP)SelectObject(hdcMem, hbmMem);//4

		BitBlt(hdcMem, 0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y, hdc_BackGround, 0, 0, SRCCOPY);

		Render(hdcMem, bigBoxes, smallBox);

		BitBlt(hdc, 0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y, hdcMem, 0, 0, SRCCOPY);

		SelectObject(hdcMem, hbmMemOld); //-4
		DeleteObject(hbmMem); //-3
		DeleteDC(hdcMem); //-2
		

		EndPaint(g_hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

void Init(BigBox* bigBoxes, SmallBox* pSmallBox )
{
	for (int i = 0; i < BIGBOX_MAX_COUNT; i++)
	{
		bigBoxes[i].index = i;
		bigBoxes[i].position.x = 50 + i%10 * 150;
		bigBoxes[i].position.y = 50 + i/10 * 150;
		bigBoxes[i].width = 100;
		bigBoxes[i].height = 100;
		bigBoxes[i].speed = BIGBOX_SPEED;
	}
	pSmallBox->position.x = 50 + 25;
	pSmallBox->position.y = 50 + 25;
	pSmallBox->width = 50;
	pSmallBox->height = 50;
	pSmallBox->parent = &bigBoxes[0];
}

void MoveBigBox(SmallBox &smallBox, BigBox* bigBoxes) 
{
	bool keyDown = false;
	if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState(KEY_W)) 
	{
		smallBox.parent->position.y += -smallBox.parent->speed;
		keyDown = true;
	}
	if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(KEY_S)) 
	{
		smallBox.parent->position.y += smallBox.parent->speed;
		keyDown = true;
	}
	if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(KEY_A)) 
	{
		smallBox.parent->position.x += -smallBox.parent->speed;
		keyDown = true;
	}
	if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState(KEY_D)) 
	{
		smallBox.parent->position.x += smallBox.parent->speed;
		keyDown = true;
	}

	if (smallBox.position.y + smallBox.height > smallBox.parent->position.y + smallBox.parent->height)
		smallBox.position.y = smallBox.parent->position.y + smallBox.parent->height - smallBox.height;
	else if (smallBox.position.y < smallBox.parent->position.y)
		smallBox.position.y = smallBox.parent->position.y;

	if (smallBox.position.x + smallBox.width > smallBox.parent->position.x + smallBox.parent->width)
		smallBox.position.x = smallBox.parent->position.x + smallBox.parent->width - smallBox.width;
	else if (smallBox.position.x < smallBox.parent->position.x)
		smallBox.position.x = smallBox.parent->position.x;

	if (keyDown)
	{
		// 충돌
		for (int i = 0; i < BIGBOX_MAX_COUNT; i++)
		{
			if (smallBox.parent->index == i)
				continue;
			RECT box1 = smallBox.parent->GetRect();
			RECT box2 = bigBoxes[i].GetRect();

			if (int result = BoxCollision(box1, box2))
			{
				switch (result)
				{
				case 1:
					if (box1.right - box2.left < box1.bottom - box2.top)
						smallBox.parent->position.x = box2.left - smallBox.parent->width - 1;
					else
						smallBox.parent->position.y = box2.top - smallBox.parent->height - 1;
					break;
				case 2:
					if (box2.right - box1.left < box1.bottom - box2.top)
						smallBox.parent->position.x = box2.right + 1;
					else
						smallBox.parent->position.y = box2.top - smallBox.parent->height - 1;
					break;
				case 3:
					if (box1.right - box2.left < box2.bottom - box1.top)
						smallBox.parent->position.x = box2.left - smallBox.parent->width - 1;
					else
						smallBox.parent->position.y = box2.bottom + 1;
					break;
				case 4:
					if (box2.right - box1.left < box2.bottom - box1.top)
						smallBox.parent->position.x = box2.right + 1;
					else
						smallBox.parent->position.y = box2.bottom + 1;
					break;
				}
				smallBox.parent = &bigBoxes[i];
			}

		}
	}
	
}

void Render(HDC hdc, BigBox* bigBoxes, SmallBox smallBox) 
{
	for (int i = 0; i < BIGBOX_MAX_COUNT; i++)
	{
		BigBox bigBox = bigBoxes[i];
		Rectangle(hdc, bigBox.position.x, bigBox.position.y, bigBox.position.x + bigBox.width, bigBox.position.y + bigBox.height);
	}
	RECT rect = smallBox.GetRect();
	Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
	FillRect(hdc, &rect, (HBRUSH)GetStockObject(GRAY_BRUSH));
}

bool IsInRect(RECT rc, POINT pt)
{
	if (rc.left <= pt.x && pt.x <= rc.right && rc.top <= pt.y && pt.y <= rc.bottom)
		return true;
	else
		return false;
}

int BoxCollision(RECT box1, RECT box2)
{
	if (IsInRect(box1, { box2.left, box2.top }))
		return 1;
	if(IsInRect(box1, { box2.right, box2.top }))
		return 2;
	if(IsInRect(box1, { box2.left, box2.bottom }))
		return 3;
	if(IsInRect(box1, { box2.right, box2.bottom }))
		return 4;

	return 0;
}