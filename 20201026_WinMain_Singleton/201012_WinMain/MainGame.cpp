#include "MainGame.h"
#include "Tank.h"
#include "Enemy.h"

HRESULT MainGame::Init()
{
	KeyManager::GetSingleton()->Init();

	tank1 = new Tank();
	tank1->Init();

	//enemy1 = new Enemy();
	//enemy1->Init();

	//tank1->SetTarget(enemy1);

	return S_OK;
}

void MainGame::Release()
{
	tank1->Release();
	delete tank1;

	enemy1->Release();
	delete enemy1;

	KeyManager::GetSingleton()->Release();
}

void MainGame::Update()
{
	if(tank1)
		tank1->Update();
	//if(enemy1)
	//	enemy1->Update();

	InvalidateRect(g_hWnd, NULL, true);
}

void MainGame::Render(HDC hdc)
{
	if(tank1)
		tank1->Render(hdc);
	if(enemy1)
		enemy1->Render(hdc);

	char szText[128] = "";

	wsprintf(szText, "X : %d, Y : %d", mouseData.mousePosX, mouseData.mousePosY);
	TextOut(hdc, 10, 5, szText, strlen(szText));

	wsprintf(szText, "Clicked X : %d, Y : %d",
		mouseData.clickedPosX, mouseData.clickedPosY);
	TextOut(hdc, 10, 30, szText, strlen(szText));
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		hTimer = (HANDLE)SetTimer(hWnd,	// 윈도우 핸들
			0,			// 이벤트 아이디
			1000/70,		// 호출 주기 ( 뭘 호출할까? )
			NULL);		// 호출 함수 포인터
		break;
	case WM_TIMER:
		this->Update();
		break;

	case WM_MOUSEMOVE:
		mouseData.mousePosX = LOWORD(lParam);
		mouseData.mousePosY = HIWORD(lParam);

		InvalidateRect(g_hWnd, NULL, true);
		break;

	case WM_RBUTTONDOWN:
		
		InvalidateRect(g_hWnd, NULL, true);
		break;

	case WM_LBUTTONUP:
		InvalidateRect(g_hWnd, NULL, true);
		break;

	case WM_LBUTTONDOWN:
		mouseData.clickedPosX = LOWORD(lParam);
		mouseData.clickedPosY = HIWORD(lParam);

		InvalidateRect(g_hWnd, NULL, true);
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
