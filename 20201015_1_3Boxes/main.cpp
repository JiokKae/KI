#include <Windows.h>
#include <ctime>
#include "3BoxLibrary.h"
#include "SmallBox.h"
#include "BigBox.h"
#include "resource.h"
#include <cmath>

HINSTANCE g_hInstance;
HWND g_hWnd;
LPSTR g_lpszClass = (LPSTR)TEXT("삼 상자");
HBITMAP hbmMem, hbmMemOld;
HDC hdc, hdcMem;
HDC hdc_BackGround;
int bestScore = 0;
int score = 0;
int timeLimit = LIMIT_TIME;
int frame = 0;

void LimitBigBoxes(BigBox* bigBoxes, SmallBox* smallBox, RECT worldBox);
void MoveBigBox(SmallBox *smallBox,int sbIndex, BigBox* bigBoxes, RECT worldBox);
void Init(BigBox* bigBoxes, SmallBox* pSmallBox);
void Rectangle(HDC hdc, RECT rect);
void Render(HDC hdc, BigBox* bigBoxes, SmallBox* smallBox, RECT worldBox);
void RainbowCircle(HDC hdc, RECT pos, int num, int T, int sizeT, int dir, int _size);
void RainboxRings(HDC hdc, RECT pos, int num);

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
	static SmallBox smallBox[2];
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

		Init(bigBoxes, smallBox);

		break;
	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			if(timeLimit > 0)
			{
				MoveBigBox(smallBox, 0, bigBoxes, worldBox);
				MoveBigBox(smallBox, 1, bigBoxes, worldBox);
				LimitBigBoxes(bigBoxes, smallBox, worldBox);
			}
			frame++;
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
			Init(bigBoxes, smallBox);
		
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

void Init(BigBox* bigBoxes, SmallBox* SmallBoxes )
{
	for (int i = 0; i < BIGBOX_MAX_COUNT; i++)
		bigBoxes[i].Init(i);

	for (int i = 0; i < 2; i++)
	{
		SmallBoxes[i].Init(&bigBoxes[i]);
	}
	
	if (score > bestScore)
		bestScore = score;
	score = 0;
	timeLimit = LIMIT_TIME;
}

void MoveBigBox(SmallBox *smallBox, int sbIndex, BigBox* bigBoxes, RECT worldBox)
{
	switch (sbIndex)
	{
	case 0:
		if (GetAsyncKeyState(KEY_W))
		{
			smallBox[sbIndex].parent->position.y += -smallBox[sbIndex].parent->speed;
		}
		if ( GetAsyncKeyState(KEY_S))
		{
			smallBox[sbIndex].parent->position.y += smallBox[sbIndex].parent->speed;
		}
		if ( GetAsyncKeyState(KEY_A))
		{
			smallBox[sbIndex].parent->position.x += -smallBox[sbIndex].parent->speed;
		}
		if ( GetAsyncKeyState(KEY_D))
		{
			smallBox[sbIndex].parent->position.x += smallBox[sbIndex].parent->speed;
		}
		if (GetAsyncKeyState(VK_SPACE) && GAMEMODE & SHOOT_MODE)
		{
			if (smallBox[sbIndex].isLaunch == false)
			{
				smallBox[sbIndex].isLaunch = true;
			}
		}
		break;
	case 1:
		if (GetAsyncKeyState(KEY_W))
		{
			smallBox[sbIndex].parent->position.y += -smallBox[sbIndex].parent->speed;
		}
		if (GetAsyncKeyState(KEY_S))
		{
			smallBox[sbIndex].parent->position.y += smallBox[sbIndex].parent->speed;
		}
		if (GetAsyncKeyState(KEY_A))
		{
			smallBox[sbIndex].parent->position.x += -smallBox[sbIndex].parent->speed;
		}
		if (GetAsyncKeyState(KEY_D))
		{
			smallBox[sbIndex].parent->position.x += smallBox[sbIndex].parent->speed;
		}
		if (GetAsyncKeyState(VK_NUMPAD1) && GAMEMODE & SHOOT_MODE)
		{
			if (smallBox[sbIndex].isLaunch == false)
			{
				smallBox[sbIndex].isLaunch = true;
			}
		}
		break;
	}
	// 키 입력 받기 부분
	

	if (smallBox[sbIndex].isLaunch)
	{
		smallBox[sbIndex].position.x += 10;
		for (int i = 0; i < BIGBOX_MAX_COUNT; i++)
		{
			BigBox& box = bigBoxes[i];
			if (smallBox[sbIndex].parent->index == i || box.IsDead())
				continue;
			if (BoxCollision(box.GetRect(), smallBox[sbIndex].GetRect()))
			{
				box.hp--;
				if (box.IsDead())
				{
					if (box.special)
						score += 5;
					else
						score++;
				}
				smallBox[sbIndex].position = { smallBox[sbIndex].parent->position.x + smallBox[sbIndex].GetWidth() / 2, smallBox[sbIndex].parent->position.y + smallBox[sbIndex].GetHeight() / 2 };
				smallBox[sbIndex].isLaunch = false;
			}

		}
		// 총알이 세계 밖으로 나갔을 때
		if (!BoxCollision(worldBox, smallBox[sbIndex].GetRect()))
		{
			smallBox[sbIndex].position = { smallBox[sbIndex].parent->position.x + smallBox[sbIndex].GetWidth() / 2, smallBox[sbIndex].parent->position.y + smallBox[sbIndex].GetHeight() / 2 };
			smallBox[sbIndex].isLaunch = false;
		}
	}
	else {
		// 작은 상자 제한 부분
		if (smallBox[sbIndex].position.y + smallBox[sbIndex].GetHeight() > smallBox[sbIndex].parent->position.y + smallBox[sbIndex].parent->GetHeight())
			smallBox[sbIndex].position.y = smallBox[sbIndex].parent->position.y + smallBox[sbIndex].parent->GetHeight() - smallBox[sbIndex].GetHeight();
		else if (smallBox[sbIndex].position.y < smallBox[sbIndex].parent->position.y)
			smallBox[sbIndex].position.y = smallBox[sbIndex].parent->position.y;

		if (smallBox[sbIndex].position.x + smallBox[sbIndex].GetWidth() > smallBox[sbIndex].parent->position.x + smallBox[sbIndex].parent->GetWidth())
			smallBox[sbIndex].position.x = smallBox[sbIndex].parent->position.x + smallBox[sbIndex].parent->GetWidth() - smallBox[sbIndex].GetWidth();
		else if (smallBox[sbIndex].position.x < smallBox[sbIndex].parent->position.x)
			smallBox[sbIndex].position.x = smallBox[sbIndex].parent->position.x;
	}
	
	// 제어중인 큰 상자 제한 부분
	if (smallBox[sbIndex].parent->position.x < 0)
		smallBox[sbIndex].parent->position.x = 0;
	else if (smallBox[sbIndex].parent->position.x + smallBox[sbIndex].parent->GetWidth() > worldBox.right)
		smallBox[sbIndex].parent->position.x = worldBox.right - smallBox[sbIndex].parent->GetWidth();

	if (smallBox[sbIndex].parent->position.y < 0)
		smallBox[sbIndex].parent->position.y = 0;
	else if (smallBox[sbIndex].parent->position.y + smallBox[sbIndex].parent->GetHeight() > worldBox.bottom)
		smallBox[sbIndex].parent->position.y = worldBox.bottom - smallBox[sbIndex].parent->GetHeight();

	if (GAMEMODE & BOX_COLLISION) 
	{
		// 제어 상자와 모든 상자 충돌 검사
		for (int i = 0; i < BIGBOX_MAX_COUNT; i++)
		{
			if (smallBox[sbIndex].parent->index == i || bigBoxes[i].IsDead())
				continue;

			RECT box1 = smallBox[sbIndex].parent->GetRect();
			RECT box2 = bigBoxes[i].GetRect();

			if (int result = BoxCollision(box1, box2))
			{
				switch (result)
				{
				case 1:
					if (box1.right - box2.left < box1.bottom - box2.top)
						smallBox[sbIndex].parent->position.x = box2.left - smallBox[sbIndex].parent->GetWidth() - 1;
					else
						smallBox[sbIndex].parent->position.y = box2.top - smallBox[sbIndex].parent->GetHeight() - 1;
					break;
				case 2:
					if (box2.right - box1.left < box1.bottom - box2.top)
						smallBox[sbIndex].parent->position.x = box2.right + 1;
					else
						smallBox[sbIndex].parent->position.y = box2.top - smallBox[sbIndex].parent->GetHeight() - 1;
					break;
				case 3:
					if (box1.right - box2.left < box2.bottom - box1.top)
						smallBox[sbIndex].parent->position.x = box2.left - smallBox[sbIndex].parent->GetWidth() - 1;
					else
						smallBox[sbIndex].parent->position.y = box2.bottom + 1;
					break;
				case 4:
					if (box2.right - box1.left < box2.bottom - box1.top)
						smallBox[sbIndex].parent->position.x = box2.right + 1;
					else
						smallBox[sbIndex].parent->position.y = box2.bottom + 1;
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
					smallBox[sbIndex].ChangeParent(&bigBoxes[i]);
				}
				else if (!(GAMEMODE & AUTO_WALL_SWITCH))
					smallBox[sbIndex].ChangeParent(&bigBoxes[i]);
			}

		}
	}
}

void Render(HDC hdc, BigBox* bigBoxes, SmallBox* smallBox, RECT worldBox) 
{
	HBRUSH redBrush = CreateSolidBrush(RGB(255,0,0));

	Rectangle(hdc, worldBox.left, worldBox.top, worldBox.right, worldBox.bottom);

	int controlledBoxIndex[2] = { smallBox[0].parent->index, smallBox[1].parent->index };

	for (int i = 0; i < BIGBOX_MAX_COUNT; i++)
	{
		BigBox bigBox = bigBoxes[i];
		
		if (i != controlledBoxIndex[0] || i != controlledBoxIndex[1] || bigBox.IsAlive())
		{
			if (bigBox.passed)
				FillRect(hdc, &bigBox.GetRect(), (HBRUSH)GetStockObject(BLACK_BRUSH));
			else if(bigBox.special)
				FillRect(hdc, &bigBox.GetRect(), redBrush);
			else
				Rectangle(hdc, bigBox.position.x, bigBox.position.y, bigBox.position.x + bigBox.GetWidth(), bigBox.position.y + bigBox.GetHeight());
		}
	}

	for (int i = 0; i < 2; i++)
	{
		BigBox &cBox = bigBoxes[controlledBoxIndex[i]];
		if (cBox.passed)
			FillRect(hdc, &cBox.GetRect(), (HBRUSH)GetStockObject(BLACK_BRUSH));
		else if (cBox.special)
			FillRect(hdc, &cBox.GetRect(), redBrush);
		else
			Rectangle(hdc, cBox.GetRect());

		Rectangle(hdc, smallBox[i].GetRect());
		FillRect(hdc, &smallBox[i].GetRect(), (HBRUSH)GetStockObject(GRAY_BRUSH));

	}

	
	char str[50];
	wsprintf(str, "최고 점수 : %d", bestScore * 100);
	TextOut(hdc, 0, 0, str, strlen(str));
	wsprintf(str, "점수 : %d", score * 100);
	TextOut(hdc, 0, 15, str, strlen(str));
	wsprintf(str, "시간 제한 : %d초", timeLimit);
	TextOut(hdc, 0, 30, str, strlen(str));
	wsprintf(str, "재시작 : R키");
	TextOut(hdc, 0, 45, str, strlen(str));

	RECT r = {0,0,WINDOW_SIZE_X ,WINDOW_SIZE_Y };
	FillRect(hdc, &r, (HBRUSH)GetStockObject(BLACK_BRUSH));

	//double speed = 20.0;
	//double size = 100;
	//RECT r1 = { 700 + sin(frame / speed)* size, 600 + cos(frame / speed) * size, 800 + sin(frame / speed) * size, 700 + sin(frame / speed) * size };
	//RECT r2 = { 1100 + sin(frame / 20.0)* 400.0, 600 + cos(frame / 20.0) * 400, 1200 + sin(frame / 20.0) * 400, 700 + cos(frame / 20.0) * 400 };
	//RECT r3 = { 900 + sin(frame / 20.0)* 400.0, 250 + cos(frame / 20.0) * 400, 1000 + sin(frame / 20.0) * 400, 350 + cos(frame / 20.0) * 400 };
	//RECT r1 = { 700, 600, 800, 700 };
	//RECT r2 = { 1100, 600, 1200, 700 };
	//RECT r3 = { 900, 250, 1000, 350};
	//
	//RainbowCircle(hdc, r1 , 54, 0);
	//RainbowCircle(hdc, r2, 54, 50);
	//RainbowCircle(hdc, r3, 54, 100);

	
	int num = 1;
	double radian = 360 / num * (3.141592 / 180);
	double speed = 500.0;
	double size = sin(frame / 40.0 + 16) * 100 + 458;
	for (int i = 0; i < num; i++)
	{
		RECT rect = { 850 + sin(-frame / speed + i * radian) * size,
			450 + cos(-frame / speed + i * radian) * size,
			920 + sin(-frame / speed + i * radian) * size,
			520 + cos(-frame / speed + i * radian) * size };

		RainboxRings(hdc, rect, 1);

	}
	RainbowCircle(hdc, { 850,450,920,520 }, 72, 100, 16, -1,100);
	

	/*
	for (int i = 6; i < 10; i++)
	{
		RainbowCircle(hdc, { 850,450,920,520 }, 72+(72*i), 100, 16, pow(-1,i%2), 100 + 65*i);
	}
	*/

	/*
	RECT rect = { 850,450,950,550 };
	RainboxRings(hdc, rect, 3);
	*/


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

void RainbowCircle(HDC hdc, RECT pos, int num, int T, int sizeT, int dir, int _size)
{
	double radian = 360 / 72 * (3.141592 / 180);
	double size = sin(frame/40.0 + sizeT) * 20 + _size;

	for (int i = 0; i < num; i++)
	{
		RECT rect = { pos.left + sin(frame * dir / 20.0 + i * radian) * size,
			pos.top + cos(frame * dir / 20.0 + i * radian) * size,
			pos.right + sin(frame * dir / 20.0 + i * radian) * size,
			pos.bottom + cos(frame * dir / 20.0 + i * radian) * size };

		HBRUSH brush = CreateSolidBrush(
			RGB(
				cos(frame * dir / 15.0 + (i + T) * radian) * 127 + 128,
				sin(frame * dir / 15.0 + (i + T) * radian) * 127 + 128,
				sin(frame * dir / 15.0 + ((i + T) + 50) * radian) * 127 + 128)
		);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);

		HPEN pen = CreatePen(PS_NULL, 1, RGB(0, 0, 0));
		HBRUSH oldPen = (HBRUSH)SelectObject(hdc, pen);

		//FillRect(hdc, &rect, brush);
		Ellipse(hdc, rect.left, rect.top, rect.right, rect.bottom);

		DeleteObject(SelectObject(hdc, oldBrush));
		DeleteObject(SelectObject(hdc, oldPen));

	}
}

void RainboxRings(HDC hdc, RECT pos, int num)
{
	double radian = 360 / num * (3.141592 / 180);
	double size = 90;
	for (int i = 0; i < num; i++)
	{
		RECT rect = { pos.left + sin(frame / 50.0 + i * radian) * size,
			pos.top + cos(frame / 50.0 + i * radian) * size,
			pos.right + sin(frame / 50.0 + i * radian) * size,
			pos.bottom + cos(frame / 50.0 + i * radian) * size };

		RainbowCircle(hdc, rect, 72, 100, 0, 1, 100);

	}
}

void LimitBigBoxes(BigBox* bigBoxes, SmallBox* smallBox, RECT worldBox) 
{
	// 모든 큰상자 제한 부분
	for (int i = 0; i < BIGBOX_MAX_COUNT; i++)
	{
		BigBox& box = bigBoxes[i];

		if (smallBox[0].parent->index == i || box.IsDead())
			continue;
		if (smallBox[1].parent->index == i)
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
}