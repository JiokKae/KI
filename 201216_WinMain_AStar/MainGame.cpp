#include "MainGame.h"
#include "Image.h"
#include "TitleScene.h"
#include "BattleScene.h"
#include "TileMapToolScene.h"
#include "PixelCollisionScene.h"
#include "AStar.h"

HRESULT MainGame::Init()
{
	KeyManager::GetSingleton()->Init();
	ImageManager::GetSingleton()->Init();
	TimerManager::GetSingleton()->Init();
	SceneManager::GetSingleton()->Init();

	SceneManager::GetSingleton()->AddScene("타이틀", new TitleScene());
	SceneManager::GetSingleton()->AddScene("전투", new BattleScene());
	SceneManager::GetSingleton()->AddScene("맵툴", new TileMapToolScene());
	SceneManager::GetSingleton()->AddScene("에이스타", new AStar());
	SceneManager::GetSingleton()->AddScene("픽셀충돌확인", new PixelCollisionScene());

	SceneManager::GetSingleton()->ChangeScene("픽셀충돌확인");

	hdc = GetDC(g_hWnd);

	//// 이미지를 미리 로드한다
	//ImageManager::GetSingleton()->AddImage("UFO", "Image/ufo.bmp",
	//	530, 32, 10, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("parent", "Image/parent.bmp", 96, 96, 3, 3, true, RGB(255, 0, 255));

	backBuffer = new Image();
	backBuffer->Init(max(WINSIZE_X, WINSIZE_TILE_MAP_X), max(WINSIZE_Y, WINSIZE_TILE_MAP_Y));

	backGround = new Image();
	if (FAILED(backGround->Init("Image/background.bmp", WINSIZE_X, WINSIZE_Y)))
	{
		// 예외처리
		MessageBox(g_hWnd, "빈 비트맵 생성에 실패했습니다.", "실패", MB_OK);
	}

	isInit = true;

	return S_OK;
}

void MainGame::Release()
{
	backGround->Release();
	delete backGround;

	backBuffer->Release();
	delete backBuffer;

	TimerManager::GetSingleton()->Release();
	KeyManager::GetSingleton()->Release();
	ImageManager::GetSingleton()->Release();
	SceneManager::GetSingleton()->Release();

	ReleaseDC(g_hWnd, hdc);
}

void MainGame::Update()
{
	SceneManager::GetSingleton()->Update();

	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render()
{
	HDC backDC = backBuffer->GetMemDC();
	backGround->Render(backDC, 0, 0);

	//char szText[128] = "";

	//wsprintf(szText, "X : %d, Y : %d", mouseData.mousePosX, mouseData.mousePosY);
	//TextOut(backDC, 10, 5, szText, strlen(szText));

	//wsprintf(szText, "Clicked X : %d, Y : %d",
	//	mouseData.clickedPosX, mouseData.clickedPosY);
	//TextOut(backDC, 10, 30, szText, strlen(szText));

	SceneManager::GetSingleton()->Render(backDC);

	TimerManager::GetSingleton()->Render(backDC);

	// 백버퍼 복사(출력)
	backBuffer->Render(hdc, 0, 0);
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		break;
	case WM_TIMER:
		if (isInit)
		{
			this->Update();
		}
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_UP:
			break;
		case VK_DOWN:
			break;
		}
		break;
	case WM_MOUSEMOVE:
		mouseData.mousePosX = LOWORD(lParam);
		mouseData.mousePosY = HIWORD(lParam);
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_LBUTTONUP:
		break;
	case WM_LBUTTONDOWN:
		mouseData.clickedPosX = LOWORD(lParam);
		mouseData.clickedPosY = HIWORD(lParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

MainGame::MainGame()
{
	isInit = false;
}


MainGame::~MainGame()
{
}
