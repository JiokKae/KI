#include "MainGame.h"
#include "Image.h"
#include "Missile.h"
#include "TitleScene.h"
#include "BattleScene.h"
#include "LoadingScene1.h"

HRESULT MainGame::Init()
{
	MissileManager::GetSingleton()->Init();
	ImageManager::GetSingleton()->Init();
	TimerManager::GetSingleton()->Init();
	KeyManager::GetSingleton()->Init();
	SceneManager::GetSingleton()->Init();

	hdc = GetDC(g_hWnd);

	// 이미지를 미리 로드한다
	ImageManager::GetSingleton()->AddImage("UFO", "Image/ufo.bmp", 530*2, 64*2, 10, 2, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Missile1", "Image/구슬.bmp", 30, 30, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Missile2", "Image/bullet.bmp", 30, 30, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("BackGround", "Image/backGround.bmp", WINSIZE_X, WINSIZE_Y);
	ImageManager::GetSingleton()->AddImage("Rocket", "Image/rocket.bmp", 52, 64, true, RGB(255, 0, 255));

	titleScene = new TitleScene();
	battleScene = new BattleScene();
	loadingScene1 = new LoadingScene1();
	SceneManager::GetSingleton()->AddScene("Title Scene", titleScene);
	SceneManager::GetSingleton()->AddScene("Battle Scene", battleScene);
	SceneManager::GetSingleton()->AddLoadingScene("Loading Scene 1", loadingScene1);

	SceneManager::GetSingleton()->ChangeScene("Title Scene");

	backBuffer = new Image();
	backBuffer->Init(WINSIZE_X, WINSIZE_Y);

	backGround = ImageManager::GetSingleton()->FindImage("BackGround");

	isInit = true;
	return S_OK;
}

void MainGame::Release()
{
	SAFE_RELEASE(backBuffer);

	SceneManager::GetSingleton()->Release();
	MissileManager::GetSingleton()->Release();
	ImageManager::GetSingleton()->Release();
	TimerManager::GetSingleton()->Release();
	KeyManager::GetSingleton()->Release();
	
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
	backGround->Render(backDC, 0, 0, WINSIZE_X, WINSIZE_Y);

	SceneManager::GetSingleton()->Render(backDC);

	char szText[128];

	wsprintf(szText, "X : %d, Y : %d", mouseData.mousePosX, mouseData.mousePosY);
	TextOut(backDC, 10, 5, szText, strlen(szText));

	wsprintf(szText, "Clicked X : %d, Y : %d", mouseData.clickedPosX, mouseData.clickedPosY);
	TextOut(backDC, 10, 30, szText, strlen(szText));

	wsprintf(szText, "g_time : %d", (int)g_time);
	TextOut(backDC, WINSIZE_X - 300, 0, szText, strlen(szText));

	TimerManager::GetSingleton()->Render(backDC);

	// 백버퍼 복사(출력)
	backBuffer->Render(hdc, 0, 0, WINSIZE_X, WINSIZE_Y);
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_MOUSEMOVE:
		mouseData.mousePosX = LOWORD(lParam);
		mouseData.mousePosY = HIWORD(lParam);
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
