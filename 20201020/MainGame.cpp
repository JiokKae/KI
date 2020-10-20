#include "MainGame.h"
#include "Tank.h"
#include <cmath>

HRESULT MainGame::Init(HINSTANCE hInst)
{
	hInstance = hInst;

	tank1 = new Tank();
	tank1->Init();
	
	return S_OK;
}

void MainGame::Release()
{
}

void MainGame::Update()
{
	if (tank1) 
	{
		tank1->Update();

		if (GetAsyncKeyState(VK_LEFT))
		{
			tank1->RotateBarrel(-1);
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			tank1->RotateBarrel(1);
		}
		if (GetAsyncKeyState(VK_SPACE))
		{
			tank1->Fire();
		}
	}
	
	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render(HDC hdc)
{
	hbmMem = CreateCompatibleBitmap(hdc, WIN_SIZE_X, WIN_SIZE_Y);//3
	hbmMemOld = (HBITMAP)SelectObject(hdcMem, hbmMem);//4

	BitBlt(hdcMem, 0, 0, WIN_SIZE_X, WIN_SIZE_Y, hdc_BackGround, 0, 0, SRCCOPY);
	
	tank1->Render(hdcMem);

	char szText[128];
	wsprintf(szText, "X : %d, Y : %d", mouseData.mousePosX, mouseData.mousePosY);
	TextOut(hdcMem, 10, 5, szText, strlen(szText));
	wsprintf(szText, "Clicked X : %d, Y : %d", mouseData.clickedPosX, mouseData.clickedPosY);
	TextOut(hdcMem, 10, 30, szText, strlen(szText));

	BitBlt(hdc, 0, 0, WIN_SIZE_X, WIN_SIZE_Y, hdcMem, 0, 0, SRCCOPY);

	SelectObject(hdcMem, hbmMemOld); //-4
	DeleteObject(hbmMem); //-3
	g_Frame++;
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		hTimer = (HANDLE)SetTimer(hWnd, 0, 1000 / 70, NULL);
		hdcMem = CreateCompatibleDC(hdc);

		hdc = GetDC(hWnd);
		hdc_BackGround = CreateCompatibleDC(hdc);
		ReleaseDC(hWnd, hdc);

		HBITMAP bitBackGround;
		bitBackGround = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP1));
		
		SelectObject(hdc_BackGround, bitBackGround);
		DeleteObject(bitBackGround);
		break;

	case WM_TIMER:
		this->Update();
		break;

	case WM_MOUSEMOVE:
		mouseData.mousePosX = LOWORD(lParam);
		mouseData.mousePosY = HIWORD(lParam);
		break;

	case WM_LBUTTONDOWN:
		mouseData.clickedPosX = LOWORD(lParam);
		mouseData.clickedPosY = HIWORD(lParam);
		break;

	case WM_PAINT:
		hdc = BeginPaint(g_hWnd, &ps);
		this->Render(hdc);
		EndPaint(g_hWnd, &ps);
		
		break;

	case WM_DESTROY:
		DeleteDC(hdcMem);
		KillTimer(hWnd, 0);
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

MainGame::MainGame()
{
}


MainGame::~MainGame()
{
}
