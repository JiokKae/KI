#include <Windows.h>
#include "MyWinLibrary.h"
#include "resource.h"
#include <ctime>

#define WINDOW_SIZE_X		1920
#define WINDOW_SIZE_Y		1000
#define BIGBOX_SPEED		10
#define BIGBOX_SIZE			300
#define BIGBOX_MARGIN		600

#define BIGBOX_COL			(WINDOW_SIZE_X / (BIGBOX_MARGIN + BIGBOX_SIZE)) 
#define BIGBOX_ROW			(WINDOW_SIZE_Y / (BIGBOX_MARGIN + BIGBOX_SIZE)) 
#define BIGBOX_MAX_COUNT	(BIGBOX_COL * BIGBOX_ROW)

#define BBBOX_SIZE_X		((BIGBOX_COL- 1) * (BIGBOX_SIZE + BIGBOX_MARGIN) + BIGBOX_MARGIN)
#define BBBOX_SIZE_Y		((BIGBOX_ROW - 1) * (BIGBOX_SIZE + BIGBOX_MARGIN) + BIGBOX_MARGIN)

// 게임모드 스위치
#define SPECIAL_SWITCH		0
#define AUTO_WALL_SWITCH	0
#define VELOCITY			0
#define SHOOT_MODE			0

HINSTANCE g_hInstance;
HWND g_hWnd;
LPSTR g_lpszClass = (LPSTR)TEXT("삼 상자");
HBITMAP hbmMem, hbmMemOld;
HDC hdc, hdcMem;
HDC hdc_BackGround;
int passCount = 0;

class BigBox;

class SmallBox
{
public:
	BigBox* parent;
	POINT position;
	int width;
	int height;
	bool isLaunch;

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
	POINT velocity;
	bool passed;
	bool special;
	bool isAlive;

	void Init(int i)
	{
		index = i;
		position.x = BIGBOX_MARGIN + i % BIGBOX_COL * (BIGBOX_SIZE + BIGBOX_MARGIN);
		position.y = BIGBOX_MARGIN + i / BIGBOX_COL * (BIGBOX_SIZE + BIGBOX_MARGIN);
		width = BIGBOX_SIZE;
		height = BIGBOX_SIZE;
		speed = BIGBOX_SPEED;
		isAlive = true;

		if (VELOCITY)
			velocity.y = 1;
		if (!(rand() % 20))
			special = true;
		else
			special = false;
		if (!(rand() % 10))
			passed = true;
		else
			passed = false;
	}

	RECT GetRect() 
	{
		RECT rect;
		rect = { position.x, position.y, position.x + width, position.y + height };
		return rect;
	}
};

void MoveBigBox(SmallBox &smallBox, BigBox* bigBoxes, RECT worldBox);
void Init(BigBox* bigBoxes, SmallBox* pSmallBox);
void Render(HDC hdc, BigBox* bigBoxes, SmallBox smallBox, RECT worldBox);

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

	g_hWnd = CreateWindow(g_lpszClass, g_lpszClass, WS_OVERLAPPEDWINDOW, 0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y + 50 + 9, NULL, NULL, g_hInstance, NULL);

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
	static RECT worldBox { 0, 0, BBBOX_SIZE_X + BIGBOX_SIZE, BBBOX_SIZE_Y + BIGBOX_SIZE };

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
		MoveBigBox(smallBox, bigBoxes, worldBox);
		
		InvalidateRect(g_hWnd, NULL, false);
		break;
	case WM_KEYDOWN:
		if (GetAsyncKeyState(KEY_R))
			Init(bigBoxes, &smallBox);
		
		break;

	case WM_PAINT:
		HDC hdc;
		hdc = BeginPaint(g_hWnd, &ps);

		hdcMem = CreateCompatibleDC(hdc); //2
		hbmMem = CreateCompatibleBitmap(hdc, WINDOW_SIZE_X, WINDOW_SIZE_Y);//3
		hbmMemOld = (HBITMAP)SelectObject(hdcMem, hbmMem);//4

		BitBlt(hdcMem, 0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y, hdc_BackGround, 0, 0, SRCCOPY);

		Render(hdcMem, bigBoxes, smallBox, worldBox);

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
	srand(time(NULL));
	for (int i = 0; i < BIGBOX_MAX_COUNT; i++)
	{
		bigBoxes[i].Init(i);
	}
	pSmallBox->position.x = BIGBOX_MARGIN + BIGBOX_SIZE / 4;
	pSmallBox->position.y = BIGBOX_MARGIN + BIGBOX_SIZE / 4;
	pSmallBox->width = BIGBOX_SIZE / 2;
	pSmallBox->height = BIGBOX_SIZE / 2;
	pSmallBox->parent = &bigBoxes[0];

	passCount = 0;
}

void MoveBigBox(SmallBox &smallBox, BigBox* bigBoxes, RECT worldBox) 
{
	// 키 입력 받기 부분
	if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState(KEY_W)) 
	{
		smallBox.parent->position.y += -smallBox.parent->speed;
	}
	if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(KEY_S)) 
	{
		smallBox.parent->position.y += smallBox.parent->speed;
	}
	if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(KEY_A)) 
	{
		smallBox.parent->position.x += -smallBox.parent->speed;
	}
	if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState(KEY_D)) 
	{
		smallBox.parent->position.x += smallBox.parent->speed;
	}
	if (GetAsyncKeyState(VK_SPACE) && SHOOT_MODE)
	{
		if (smallBox.isLaunch == false)
		{
			smallBox.isLaunch = true;
		}
	}

	if (smallBox.isLaunch) 
	{
		smallBox.position.x += 10;
		for (int i = 0; i < BIGBOX_MAX_COUNT; i++)
		{
			BigBox& box = bigBoxes[i];
			if (smallBox.parent->index == i || !box.isAlive)
				continue;
			if (BoxCollision(box.GetRect(), smallBox.GetRect()))
			{
				if (box.special)
					passCount += 5;
				else
					passCount++;

				box.isAlive = false;
				smallBox.position = { smallBox.parent->position.x + smallBox.width / 2, smallBox.parent->position.y + smallBox.height / 2 };
				smallBox.isLaunch = false;
			}

		}
		if (!BoxCollision(worldBox, smallBox.GetRect()))
		{
			smallBox.position = { smallBox.parent->position.x + smallBox.width / 2, smallBox.parent->position.y + smallBox.height / 2 };
			smallBox.isLaunch = false;
		}
	}
	else {
		// 작은 상자 제한 부분
		if (smallBox.position.y + smallBox.height > smallBox.parent->position.y + smallBox.parent->height)
			smallBox.position.y = smallBox.parent->position.y + smallBox.parent->height - smallBox.height;
		else if (smallBox.position.y < smallBox.parent->position.y)
			smallBox.position.y = smallBox.parent->position.y;

		if (smallBox.position.x + smallBox.width > smallBox.parent->position.x + smallBox.parent->width)
			smallBox.position.x = smallBox.parent->position.x + smallBox.parent->width - smallBox.width;
		else if (smallBox.position.x < smallBox.parent->position.x)
			smallBox.position.x = smallBox.parent->position.x;
	}
	

	// 제어중인 큰 상자 제한 부분
	if (smallBox.parent->position.x < 0)
		smallBox.parent->position.x = 0;
	else if (smallBox.parent->position.x > BBBOX_SIZE_X)
		smallBox.parent->position.x = BBBOX_SIZE_X;

	if (smallBox.parent->position.y < 0)
		smallBox.parent->position.y = 0;
	else if (smallBox.parent->position.y > BBBOX_SIZE_Y)
		smallBox.parent->position.y = BBBOX_SIZE_Y;

	// 모든 큰상자 제한 부분
	for (int i = 0; i < BIGBOX_MAX_COUNT; i++)
	{
		BigBox& box = bigBoxes[i];
		if (smallBox.parent->index == i || !box.isAlive)
			continue;
		box.position.y += box.velocity.y;

		if (box.position.y < 0) 
		{
			box.position.y = 0;
			box.velocity.y *= -1;
		}
		else if (box.position.y > BBBOX_SIZE_Y) 
		{
			box.position.y = BBBOX_SIZE_Y;
			box.velocity.y *= -1;
		}
		if (box.position.x < 0) 
		{
			box.position.x = 0;
			box.velocity.x *= -1;
		}
		else if (box.position.x > BBBOX_SIZE_X) 
		{
			box.position.x = BBBOX_SIZE_X;
			box.velocity.y *= -1;
		}

	}

	// 제어 상자와 모든 상자 충돌 검사
	for (int i = 0; i < BIGBOX_MAX_COUNT; i++)
	{
		if (smallBox.parent->index == i || !bigBoxes[i].isAlive)
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
			if (bigBoxes[i].passed == false)
			{
				if (AUTO_WALL_SWITCH)
				{
					bigBoxes[i].passed = true;
					passCount++;

					if (bigBoxes[i].special && SPECIAL_SWITCH)
						passCount += 5;
				}
				smallBox.parent = &bigBoxes[i];
			}
			else if (!AUTO_WALL_SWITCH)
				smallBox.parent = &bigBoxes[i];
		}

	}
	
}

void Render(HDC hdc, BigBox* bigBoxes, SmallBox smallBox, RECT worldBox) 
{
	HBRUSH redBrush = CreateSolidBrush(RGB(255,0,0));

	Rectangle(hdc, worldBox.left, worldBox.top, worldBox.right, worldBox.bottom);

	for (int i = 0; i < BIGBOX_MAX_COUNT; i++)
	{
		BigBox bigBox = bigBoxes[i];
		if (bigBox.isAlive)
		{
			Rectangle(hdc, bigBox.position.x, bigBox.position.y, bigBox.position.x + bigBox.width, bigBox.position.y + bigBox.height);
			if (bigBox.special && SPECIAL_SWITCH)
				FillRect(hdc, &bigBox.GetRect(), redBrush);
			if (bigBox.passed && AUTO_WALL_SWITCH)
				FillRect(hdc, &bigBox.GetRect(), (HBRUSH)GetStockObject(BLACK_BRUSH));
		}
	}
	RECT rect = smallBox.GetRect();
	Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
	FillRect(hdc, &rect, (HBRUSH)GetStockObject(GRAY_BRUSH));

	char str[50];
	wsprintf(str, "점수 : %d", passCount * 100);
	TextOut(hdc, 0, 0, str, strlen(str));

	DeleteObject(redBrush);
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