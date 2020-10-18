#include <Windows.h>
#include <ctime>
#include "3BoxLibrary.h"
#include "SmallBox.h"
#include "BigBox.h"
#include "resource.h"

HINSTANCE g_hInstance;
HWND g_hWnd;
LPSTR g_lpszClass = (LPSTR)TEXT("삼 상자");
HBITMAP hbmMem, hbmMemOld;
HDC hdc, hdcMem;
HDC hdc_BackGround;
int bestScore = 0;
int score = 0;
int timeLimit = LIMIT_TIME;

void MoveBigBox(SmallBox &smallBox, BigBox* bigBoxes, RECT worldBox);
void Init(BigBox* bigBoxes, SmallBox* pSmallBox);
void Rectangle(HDC hdc, RECT rect);
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
	static HANDLE hEndGmaeTimer;
	static RECT worldBox { 0, 0, WORLDBOX_SIZE_X + BIGBOX_SIZE, WORLDBOX_SIZE_Y + BIGBOX_SIZE };

	switch (iMessage)
	{
	case WM_CREATE:
		srand((UINT)time(NULL));
		hTimer = (HANDLE)SetTimer(hWnd, 1, 1000 / 70, NULL);
		hEndGmaeTimer = (HANDLE)SetTimer(hWnd, 2, 1000, NULL);

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
		switch (wParam)
		{
		case 1:
			if(timeLimit > 0)
			{
				MoveBigBox(smallBox, bigBoxes, worldBox);
			}
			
			InvalidateRect(g_hWnd, NULL, false);
			break;
			
		case 2:
			if (timeLimit > 0)
				timeLimit--;
			break;
		}
		
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
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

void Init(BigBox* bigBoxes, SmallBox* pSmallBox )
{
	for (int i = 0; i < BIGBOX_MAX_COUNT; i++)
		bigBoxes[i].Init(i);

	pSmallBox->Init(&bigBoxes[0]);
	if (score > bestScore)
		bestScore = score;
	score = 0;
	timeLimit = LIMIT_TIME;
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
	if (GetAsyncKeyState(VK_SPACE) && GAMEMODE & SHOOT_MODE)
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
			if (smallBox.parent->index == i || box.IsDead())
				continue;
			if (BoxCollision(box.GetRect(), smallBox.GetRect()))
			{
				box.hp--;
				if (box.IsDead())
				{
					if (box.special)
						score += 5;
					else
						score++;
				}
				smallBox.position = { smallBox.parent->position.x + smallBox.GetWidth() / 2, smallBox.parent->position.y + smallBox.GetHeight() / 2 };
				smallBox.isLaunch = false;
			}

		}
		// 총알이 세계 밖으로 나갔을 때
		if (!BoxCollision(worldBox, smallBox.GetRect()))
		{
			smallBox.position = { smallBox.parent->position.x + smallBox.GetWidth() / 2, smallBox.parent->position.y + smallBox.GetHeight() / 2 };
			smallBox.isLaunch = false;
		}
	}
	else {
		// 작은 상자 제한 부분
		if (smallBox.position.y + smallBox.GetHeight() > smallBox.parent->position.y + smallBox.parent->GetHeight())
			smallBox.position.y = smallBox.parent->position.y + smallBox.parent->GetHeight() - smallBox.GetHeight();
		else if (smallBox.position.y < smallBox.parent->position.y)
			smallBox.position.y = smallBox.parent->position.y;

		if (smallBox.position.x + smallBox.GetWidth() > smallBox.parent->position.x + smallBox.parent->GetWidth())
			smallBox.position.x = smallBox.parent->position.x + smallBox.parent->GetWidth() - smallBox.GetWidth();
		else if (smallBox.position.x < smallBox.parent->position.x)
			smallBox.position.x = smallBox.parent->position.x;
	}
	
	// 제어중인 큰 상자 제한 부분
	if (smallBox.parent->position.x < 0)
		smallBox.parent->position.x = 0;
	else if (smallBox.parent->position.x + smallBox.parent->GetWidth() > worldBox.right)
		smallBox.parent->position.x = worldBox.right - smallBox.parent->GetWidth();

	if (smallBox.parent->position.y < 0)
		smallBox.parent->position.y = 0;
	else if (smallBox.parent->position.y + smallBox.parent->GetHeight() > worldBox.bottom)
		smallBox.parent->position.y = worldBox.bottom - smallBox.parent->GetHeight();

	// 모든 큰상자 제한 부분
	for (int i = 0; i < BIGBOX_MAX_COUNT; i++)
	{
		BigBox& box = bigBoxes[i];
		if (smallBox.parent->index == i || box.IsDead())
			continue;
		box.position.x += box.velocity.x;
		box.position.y += box.velocity.y;

		if (box.position.x < 0)
		{
			box.position.x = 0;
			box.velocity.x *= -1;
		}
		else if (box.position.x + box.GetWidth() > worldBox.right)
		{
			box.position.x = worldBox.right - box.GetWidth();
			box.velocity.x *= -1;
		}

		if (box.position.y < 0) 
		{
			box.position.y = 0;
			box.velocity.y *= -1;
		}
		else if (box.position.y + box.GetHeight() > worldBox.bottom) 
		{
			box.position.y = worldBox.bottom - box.GetHeight();
			box.velocity.y *= -1;
		}

	}

	if (GAMEMODE & BOX_COLLISION) 
	{
		// 제어 상자와 모든 상자 충돌 검사
		for (int i = 0; i < BIGBOX_MAX_COUNT; i++)
		{
			if (smallBox.parent->index == i || bigBoxes[i].IsDead())
				continue;

			RECT box1 = smallBox.parent->GetRect();
			RECT box2 = bigBoxes[i].GetRect();

			if (int result = BoxCollision(box1, box2))
			{
				switch (result)
				{
				case 1:
					if (box1.right - box2.left < box1.bottom - box2.top)
						smallBox.parent->position.x = box2.left - smallBox.parent->GetWidth() - 1;
					else
						smallBox.parent->position.y = box2.top - smallBox.parent->GetHeight() - 1;
					break;
				case 2:
					if (box2.right - box1.left < box1.bottom - box2.top)
						smallBox.parent->position.x = box2.right + 1;
					else
						smallBox.parent->position.y = box2.top - smallBox.parent->GetHeight() - 1;
					break;
				case 3:
					if (box1.right - box2.left < box2.bottom - box1.top)
						smallBox.parent->position.x = box2.left - smallBox.parent->GetWidth() - 1;
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
					if (GAMEMODE & AUTO_WALL_SWITCH)
					{
						bigBoxes[i].passed = true;
						score++;

						if (bigBoxes[i].special && GAMEMODE & SPECIAL_SWITCH)
							score += 5;
					}
					smallBox.ChangeParent(&bigBoxes[i]);
				}
				else if (!(GAMEMODE & AUTO_WALL_SWITCH))
					smallBox.ChangeParent(&bigBoxes[i]);
			}

		}
	}
}

void Render(HDC hdc, BigBox* bigBoxes, SmallBox smallBox, RECT worldBox) 
{
	HBRUSH redBrush = CreateSolidBrush(RGB(255,0,0));

	Rectangle(hdc, worldBox.left, worldBox.top, worldBox.right, worldBox.bottom);

	int controlledBoxIndex = smallBox.parent->index;
	for (int i = 0; i < BIGBOX_MAX_COUNT; i++)
	{
		BigBox bigBox = bigBoxes[i];
		
		if (i != controlledBoxIndex || bigBox.IsAlive())
		{
			if (bigBox.passed)
				FillRect(hdc, &bigBox.GetRect(), (HBRUSH)GetStockObject(BLACK_BRUSH));
			else if(bigBox.special)
				FillRect(hdc, &bigBox.GetRect(), redBrush);
			else
				Rectangle(hdc, bigBox.position.x, bigBox.position.y, bigBox.position.x + bigBox.GetWidth(), bigBox.position.y + bigBox.GetHeight());
		}
	}

	BigBox &cBox = bigBoxes[controlledBoxIndex];
	if (cBox.passed)
		FillRect(hdc, &cBox.GetRect(), (HBRUSH)GetStockObject(BLACK_BRUSH));
	else if (cBox.special)
		FillRect(hdc, &cBox.GetRect(), redBrush);
	else
		Rectangle(hdc, cBox.GetRect());

	Rectangle(hdc, smallBox.GetRect());
	FillRect(hdc, &smallBox.GetRect(), (HBRUSH)GetStockObject(GRAY_BRUSH));

	char str[50];
	wsprintf(str, "최고 점수 : %d", bestScore * 100);
	TextOut(hdc, 0, 0, str, strlen(str));
	wsprintf(str, "점수 : %d", score * 100);
	TextOut(hdc, 0, 15, str, strlen(str));
	wsprintf(str, "시간 제한 : %d초", timeLimit);
	TextOut(hdc, 0, 30, str, strlen(str));
	wsprintf(str, "재시작 : R키");
	TextOut(hdc, 0, 45, str, strlen(str));

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
	if (IsInRect(box1, { box2.left, box2.top }) || IsInRect(box2, { box1.right, box1.bottom }))
		return 1;
	if(IsInRect(box1, { box2.right, box2.top }) || IsInRect(box2, { box1.left, box1.bottom }))
		return 2;
	if(IsInRect(box1, { box2.left, box2.bottom }) || IsInRect(box2, { box1.right, box1.top }))
		return 3;
	if(IsInRect(box1, { box2.right, box2.bottom }) || IsInRect(box2, { box1.left, box1.top }))
		return 4;

	return 0;
}

void Rectangle(HDC hdc, RECT rect) {
	Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
}