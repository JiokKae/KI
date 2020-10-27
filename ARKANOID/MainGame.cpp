#include "MainGame.h"
#include "Vaus.h"
#include "Block.h"
#include "resource.h"

HRESULT MainGame::Init()
{
	KeyManager::GetSingleton()->Init();

	tank1 = new Vaus();
	tank1->Init();

	numOfBlock = currentBlockCount = 200;
	block = new Block[numOfBlock];
	for (int i = 0; i < numOfBlock; i++) 
	{
		block[i].Init();
	}
		
	SetBlock();

	return S_OK;
}

void MainGame::Release()
{
	tank1->Release();
	delete tank1;

	for (int i = 0; i < numOfBlock; i++)
		block[i].Release();
	delete[] block;

	KeyManager::GetSingleton()->Release();
}

void MainGame::Update()
{
	if(tank1)
		tank1->Update();

	if (block) 
	{
		for (int i = 0; i < numOfBlock; i++)
			block[i].Update();
	}
		
	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render(HDC hdc)
{
	hBitmapMem = CreateCompatibleBitmap(hdc, WINSIZE_X, WINSIZE_Y);//3
	hBitmapMemOld = (HBITMAP)SelectObject(hdcMem, hBitmapMem);//4

	BitBlt(hdcMem, 0, 0, WINSIZE_X, WINSIZE_Y, hdc_BackGround, 0, 0, SRCCOPY);

	if(tank1)
		tank1->Render(hdcMem);

	if (block) 
	{
		for (int i = 0; i < numOfBlock; i++)
			block[i].Render(hdcMem);
	}
	
	char szText[128] = "";

	wsprintf(szText, "X : %d, Y : %d", mouseData.mousePosX, mouseData.mousePosY);
	TextOut(hdcMem, 10, 5, szText, strlen(szText));

	wsprintf(szText, "Clicked X : %d, Y : %d",
		mouseData.clickedPosX, mouseData.clickedPosY);
	TextOut(hdcMem, 10, 30, szText, strlen(szText));

	BitBlt(hdc, 0, 0, WINSIZE_X, WINSIZE_Y, hdcMem, 0, 0, SRCCOPY);

	SelectObject(hdcMem, hBitmapMemOld); //-4
	DeleteObject(hBitmapMem); //-3
}

void MainGame::SetBlock()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			POINT pos;
			pos.x = i * block[i * 10 + j].GetWidth() + (WINSIZE_X / 2 - 5 * block[i * 10 + j].GetWidth());
			pos.y = j * block[i * 10 + j].GetHeight() + (WINSIZE_Y / 2 - 5 * block[i * 10 + j].GetHeight());

			block[i * 10 + j].Appear(pos);
		}
	}
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
