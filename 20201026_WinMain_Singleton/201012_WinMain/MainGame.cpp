#include "MainGame.h"
#include "Tank.h"
#include "Enemy.h"
#include "resource.h"
#include "Image.h"
HRESULT MainGame::Init()
{
	KeyManager::GetSingleton()->Init();

	tank1 = new Tank();
	tank1->Init();

	//enemy1 = new Enemy();
	//enemy1->Init();

	//tank1->SetTarget(enemy1);

	emptyImage = new Image[2];
	for (int i = 0; i < 2; i++)
		emptyImage[i].Init(300, 300);

	imagePos[0] = { 800, 300 };
	imagePos[1] = { 800, 800 };

	return S_OK;
}

void MainGame::Release()
{
	tank1->Release();
	delete tank1;

	enemy1->Release();
	delete enemy1;

	for (int i = 0; i < 2; i++)
		emptyImage[i].Release();

	delete[] emptyImage;

	KeyManager::GetSingleton()->Release();
}

void MainGame::Update()
{
	if(tank1)
		tank1->Update();
	//if(enemy1)
	//	enemy1->Update();

	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render(HDC hdc)
{
	hBitmapMem = CreateCompatibleBitmap(hdc, WINSIZE_X, WINSIZE_Y);//3
	hBitmapMemOld = (HBITMAP)SelectObject(hdcMem, hBitmapMem);//4

	BitBlt(hdcMem, 0, 0, WINSIZE_X, WINSIZE_Y, hdc_BackGround, 0, 0, SRCCOPY);

	if(tank1)
		tank1->Render(hdcMem);
	if(enemy1)
		enemy1->Render(hdcMem);

	char szText[128] = "";

	wsprintf(szText, "X : %d, Y : %d", mouseData.mousePosX, mouseData.mousePosY);
	TextOut(hdcMem, 10, 5, szText, strlen(szText));

	wsprintf(szText, "Clicked X : %d, Y : %d",
		mouseData.clickedPosX, mouseData.clickedPosY);
	TextOut(hdcMem, 10, 30, szText, strlen(szText));

	if(emptyImage)
		for (int i = 0; i < 2; i++) 
		{
			emptyImage[i].Render(hdcMem, imagePos[i].x++, imagePos[i].y++);
			if (imagePos[i].x > WINSIZE_X)
				imagePos[i].x = 0;
			if (imagePos[i].y > WINSIZE_Y)
				imagePos[i].y = 0;
		}
		
	BitBlt(hdc, 0, 0, WINSIZE_X, WINSIZE_Y, hdcMem, 0, 0, SRCCOPY);

	SelectObject(hdcMem, hBitmapMemOld); //-4
	DeleteObject(hBitmapMem); //-3
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		hTimer = (HANDLE)SetTimer(hWnd,	0, 1000/70, NULL);

		// 더블 버퍼
		hdc = GetDC(hWnd);
		hdcMem = CreateCompatibleDC(hdc); //2
		hdc_BackGround = CreateCompatibleDC(hdc);
		ReleaseDC(hWnd, hdc);
		HBITMAP bitBackGround;
		bitBackGround = LoadBitmap(g_hInstance, MAKEINTRESOURCE(IDB_BITMAP1));
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
