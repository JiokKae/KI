#include "MainGame.h"
#include "Image.h"
#include "EnemyManager.h"
#include "MissileManager.h"
#include "Missile.h"
#include "Ship.h"

HRESULT MainGame::Init()
{
	KeyManager::GetSingleton()->Init();
	MissileManager::GetSingleton()->Init();
	ImageManager::GetSingleton()->Init();

	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);

	// 이미지를 미리 로드한다
	ImageManager::GetSingleton()->AddImage("UFO", "Image/ufo.bmp", 530*2, 64*2, 10, 2, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Missile1", "Image/구슬.bmp", 30, 30, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Missile2", "Image/bullet.bmp", 30, 30, true, RGB(255, 0, 255));

	player = new Ship;
	player->Init();

	enemyMgr = new EnemyManager();
	enemyMgr->Init();
	enemyMgr->AddEnemy(100, 100);

	backBuffer = new Image();
	backBuffer->Init(WINSIZE_X, WINSIZE_Y);

	backGround = new Image();
	if (FAILED(backGround->Init("Image/backGround.bmp", WINSIZE_X, WINSIZE_Y)))
	{
		// 예외처리
		MessageBox(g_hWnd, "빈 비트맵 생성에 실패했습니다.", "실패", MB_OK);
	}

	isInit = true;
	return S_OK;
}

void MainGame::Release()
{
	player->Release();
	delete player;

	backGround->Release();
	delete backGround;

	backBuffer->Release();
	delete backBuffer;
	
	enemyMgr->Release();

	KeyManager::GetSingleton()->Release();
	MissileManager::GetSingleton()->Release();
	ImageManager::GetSingleton()->Release();
}

void MainGame::Update()
{
	enemyMgr->Update(player->GetPos());
	MissileManager::GetSingleton()->Update();
	player->Update();

	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render(HDC hdc)
{
	HDC backDC = backBuffer->GetMemDC();
	backGround->Render(backDC, 0, 0, WINSIZE_X, WINSIZE_Y);

	enemyMgr->Render(backDC);

	player->Render(backDC);
	MissileManager::GetSingleton()->Render(backDC);
	char szText[128] = "";

	wsprintf(szText, "X : %d, Y : %d", mouseData.mousePosX, mouseData.mousePosY);
	TextOut(backDC, 10, 5, szText, strlen(szText));

	wsprintf(szText, "Clicked X : %d, Y : %d",
		mouseData.clickedPosX, mouseData.clickedPosY);
	TextOut(backDC, 10, 30, szText, strlen(szText));

	// 백버퍼 복사(출력)
	backBuffer->Render(hdc, 0, 0, WINSIZE_X, WINSIZE_Y);
}

bool MainGame::CheckCollision(Missile * m1, Missile * m2)
{
	// m1의 반지름 + m2의 반지름 >= m1과 m2사이 거리 (->충돌)
	float halfSize1 = m1->GetSize() / 2.0f;
	float halfSize2 = m2->GetSize() / 2.0f;
	POINTFLOAT pos1 = m1->GetPos();
	POINTFLOAT pos2 = m2->GetPos();

	if (GetDistance(pos1, pos2) <= halfSize1 + halfSize2)
	{
		return true;
	}
	return false;
}

float MainGame::GetDistance(POINTFLOAT pos1, POINTFLOAT pos2)
{
	float dist = sqrtf((pos2.x - pos1.x) * (pos2.x - pos1.x)
		+ (pos2.y - pos1.y) * (pos2.y - pos1.y));

	return dist;
}

float MainGame::GetAngle(POINTFLOAT pos1, POINTFLOAT pos2)
{
	float x = pos2.x - pos1.x;
	float y = pos2.y - pos1.y;

	float angle = atan2f(-y, x);

	return angle;
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
			g_frame++;
		}
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
		if(isInit)
		{
			this->Render(hdc);
		}
		EndPaint(g_hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
