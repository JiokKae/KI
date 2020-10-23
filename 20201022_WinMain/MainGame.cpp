#include "MainGame.h"
#include "Tank.h"
#include "Enemy.h"
#include "resource.h"

#define KEY_A 0x41 
#define KEY_B 0x42
#define KEY_C 0x43
#define KEY_D 0x44
#define KEY_E 0x45
#define KEY_F 0x46
#define KEY_G 0x47
#define KEY_H 0x48
#define KEY_I 0x49
#define KEY_J 0x4A
#define KEY_K 0x4B
#define KEY_L 0x4C
#define KEY_M 0x4D
#define KEY_N 0x4E
#define KEY_O 0x4F
#define KEY_P 0x50
#define KEY_Q 0x51
#define KEY_R 0x52
#define KEY_S 0x53
#define KEY_T 0x54
#define KEY_U 0x55
#define KEY_V 0x56
#define KEY_W 0x57
#define KEY_X 0x58
#define KEY_Y 0x59
#define KEY_Z 0x5A

HRESULT MainGame::Init(HINSTANCE hInst, HWND hWnd)
{
	hInstance = hInst;
	hTimer = (HANDLE)SetTimer(
		g_hWnd,	// 윈도우의 핸들
		0,		// 이벤트 아이디
		10,		// 호출 주기 ( 뭐가 호출되는지? : WM_TIMER )
		NULL);	// 호출할 함수를 등록

	tank1 = new Tank();
	tank1->Init();

	enemy = new Enemy();
	enemy->Init();

	return S_OK;
}

void MainGame::Release()
{
	tank1->Release();
	delete tank1;
	
	enemy->Release();
	delete enemy;

	// 타이머 삭제
	KillTimer(g_hWnd, 0);
}

void MainGame::Update()
{
	if (enemy)
	{
		enemy->Update();
	}

	if (GetAsyncKeyState(KEY_W))
	{
		tank1->Move({0,-1});
	}
	if (GetAsyncKeyState(KEY_S))
	{
		tank1->Move({ 0,1 });
	}
	if (GetAsyncKeyState(KEY_A))
	{
		tank1->Move({ -1,0 });
	}
	if (GetAsyncKeyState(KEY_D))
	{
		tank1->Move({ 1,0 });
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		tank1->RotateBarrel(1);
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		tank1->RotateBarrel(-1);
	}
	if (GetAsyncKeyState(VK_SPACE))
	{
		tank1->Fire(enemy->GetPos());
	}

	if (tank1)
	{
		tank1->Update(enemy->GetPos(), enemy->GetSize());
	}

}

void MainGame::Render(HDC hdc)
{
	hbmMem = CreateCompatibleBitmap(hdc, WINSIZE_X, WINSIZE_Y);//3
	hbmMemOld = (HBITMAP)SelectObject(hdcMem, hbmMem);//4

	BitBlt(hdcMem, 0, 0, WINSIZE_X, WINSIZE_Y, hdc_BackGround, 0, 0, SRCCOPY);

	if (tank1)
	{
		tank1->Render(hdcMem);
	}
	if (enemy)
	{
		enemy->Render(hdcMem);
	}

	char szText[128] = "";
	wsprintf(szText, "X : %d, Y : %d", mouseData.posX, mouseData.posY);
	TextOut(hdcMem, mouseData.posX, mouseData.posY, szText, strlen(szText));

	wsprintf(szText, "Clicked X : %d, Y : %d",
		mouseData.clickedPosX, mouseData.clickedPosY);
	TextOut(hdcMem, 10, 30, szText, strlen(szText));

	BitBlt(hdc, 0, 0, WINSIZE_X, WINSIZE_Y, hdcMem, 0, 0, SRCCOPY);

	SelectObject(hdcMem, hbmMemOld); //-4
	DeleteObject(hbmMem); //-3
	g_Frame++;
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_CREATE:
		hdc = GetDC(hWnd);
		hdcMem = CreateCompatibleDC(hdc);
		hdc_BackGround = CreateCompatibleDC(hdc);
		ReleaseDC(hWnd, hdc);

		HBITMAP bitBackGround;
		bitBackGround = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP1));

		SelectObject(hdc_BackGround, bitBackGround);
		DeleteObject(bitBackGround);

		break;
	case WM_TIMER:
		this->Update();
		InvalidateRect(g_hWnd, NULL, false);
		break;

	case WM_MOUSEMOVE:
		mouseData.posX = LOWORD(lParam);
		mouseData.posY = HIWORD(lParam);
		break;

	case WM_LBUTTONDOWN:
		mouseData.clickedPosX = LOWORD(lParam);
		mouseData.clickedPosY = HIWORD(lParam);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		this->Render(hdc);

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

// 렉트와 렉트의 충돌확인
bool MainGame::CheckRectCollision(RECT rc1, RECT rc2)
{
	if (rc1.left > rc2.right ||
		rc1.right < rc2.left ||
		rc1.top > rc2.bottom ||
		rc1.bottom < rc2.top)
	{
		return false;
	}

	return true;
}

MainGame::MainGame()
{
}


MainGame::~MainGame()
{
}
