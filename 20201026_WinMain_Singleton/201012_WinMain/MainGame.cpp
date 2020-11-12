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

	enemy1 = new Enemy();
	enemy1->Init();

	//tank1->SetTarget(enemy1);

	emptyImage = new Image[2];
	for (int i = 0; i < 2; i++)
		emptyImage[i].Init(300, 300);

	imagePos[0] = { 800, 300 };
	imagePos[1] = { 800, 800 };

	fileImage = new Image();
	if (FAILED(fileImage->Init("Image/구슬.bmp", 300, 300)))
	{
		// 예외처리
		MessageBox(g_hWnd, "파일로부터 비트맵 생성에 실패했습니다.", "실패", MB_OK);
	}
	
	ioriAni = new Image();
	if (FAILED(ioriAni->Init("Image/Iori_walk.bmp", 612, 104, true, RGB(255,0,255), true, 9)))
	{
		// 예외처리
		MessageBox(g_hWnd, "파일로부터 비트맵 생성에 실패했습니다.", "실패", MB_OK);
	}
	backbuffer = new Image();
	backbuffer->Init(WINSIZE_X, WINSIZE_Y);
	
	backGround = new Image();
	if (FAILED(backGround->Init("Image/mapImage.bmp", WINSIZE_X, WINSIZE_Y)))
	{
		// 예외처리
		MessageBox(g_hWnd, "파일로부터 비트맵 생성에 실패했습니다.", "실패", MB_OK);
	}

	isInit = true;

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

	fileImage->Release();
	delete fileImage;

	ioriAni->Release();
	delete ioriAni;

	backbuffer->Release();
	delete backbuffer;

	backGround->Release();
	delete backGround;
	KeyManager::GetSingleton()->Release();
}

void MainGame::Update()
{
	tank1->Update();
	enemy1->Update();

	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render(HDC hdc)
{
	HDC hdcMem =  backbuffer->GetHMemDC();
	backGround->Render(hdcMem, 0, 0);

	tank1->Render(hdcMem);
	enemy1->Render(hdcMem);

	char szText[128] = "";

	wsprintf(szText, "X : %d, Y : %d", mouseData.mousePosX, mouseData.mousePosY);
	TextOut(hdcMem, 10, 5, szText, strlen(szText));

	wsprintf(szText, "Clicked X : %d, Y : %d",
		mouseData.clickedPosX, mouseData.clickedPosY);
	TextOut(hdcMem, 10, 30, szText, strlen(szText));

	for (int i = 0; i < 2; i++) 
	{
		emptyImage[i].Render(hdcMem, imagePos[i].x++, imagePos[i].y++);
		if (imagePos[i].x > WINSIZE_X)
			imagePos[i].x = 0;
		if (imagePos[i].y > WINSIZE_Y)
			imagePos[i].y = 0;
	}
	/* 이오리 많이 나옴
	for (int i = 0; i < 8; i++)
	{
		ioriAni->Render(hdcMem, 700 + (90 + 10 * x[i]%9 + 100 * sin(x[i] / 40.0f)) * i, 100,  1 + 1 * i , x[i]++/2 % 9);
		ioriAni->Render(hdcMem, 700 - (90 + 10 * x[i]%9 + 100 * sin(x[i] / 40.0f)) * i, 100,  1 + 1 * i , x[i]++/2 % 9);
	}
	*/
	backbuffer->Render(hdc, 0, 0);
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
		if(isInit)	
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
		if (isInit)
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
