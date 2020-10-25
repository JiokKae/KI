#include "framework.h"
#include "MainGame.h"
#include "Resource.h"
#include "Tank.h"
#include "Enemy.h"
#include "Missile.h"
#include <string>

HRESULT MainGame::Init(HINSTANCE hInst, HWND hWnd)
{
	hInstance = hInst;
	hTimer = (HANDLE)SetTimer(hWnd, 0, 1000 / 70, NULL);
	hTimer2 = (HANDLE)SetTimer(hWnd, 1, 1000, NULL);

	tank1 = new Tank();
	tank1->Init();

	// 적
	Enemy::currentEnemyCount = numOfEnemy = 1;
	enemy = new Enemy[numOfEnemy];
	
	for (int i = 0; i < numOfEnemy; i++)
		enemy[i].Init(tank1->GetPos());

	// 미사일
	Missile::numOfMissile = 5000;
	Missile::currentMissileCount = 0;
	missile = new Missile[Missile::numOfMissile];
	for (int i = 0; i < Missile::numOfMissile; i++)
		missile[i].Init();

	return S_OK;
}

void MainGame::Update()
{
	for (int i = 0; i < numOfEnemy; i++)
	{
		enemy[i].Update(tank1->GetPos());
		enemy[i].Fire(tank1->GetPos(), missile, (Pattern)(rand() % 6));
	}

	if (GetAsyncKeyState(VK_SPACE))
	{
		tank1->Fire(enemy->GetPos(), missile);
	}
	tank1->Update();

	for (int i = 0; i < Missile::numOfMissile; i++)
		missile[i].Update(enemy, numOfEnemy, tank1, 1, missile);
	
	if (Enemy::currentEnemyCount <= 0)
		SetEnemyWave(numOfEnemy);
}

void MainGame::Render(HDC hdc)
{
	hBitmapMem = CreateCompatibleBitmap(hdc, WINDOW_SIZE_X, WINDOW_SIZE_Y);//3
	hBitmapMemOld = (HBITMAP)SelectObject(hdcMem, hBitmapMem);//4

	BitBlt(hdcMem, 0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y, hdc_BackGround, 0, 0, SRCCOPY);

	// 탱크
	tank1->Render(hdcMem);

	// 적
	for (int i = 0; i < numOfEnemy; i++)
		enemy[i].Render(hdcMem);

	// 미사일
	if (missile)
	{
		for (int i = 0; i < Missile::numOfMissile; i++)
			missile[i].Render(hdcMem);
	}
	
	char buf[50];

	wsprintf(buf, "g_Frame : %d", g_Frame);
	TextOut(hdcMem, 0, 0, buf, strlen(buf));

	wsprintf(buf, "X : %d, Y : %d", mouse.x, mouse.y);
	TextOut(hdcMem, 0, 20, buf, strlen(buf));

	wsprintf(buf, "FPS : %d", FPS);
	TextOut(hdcMem, 0, 40, buf, strlen(buf));

	wsprintf(buf, "적의 수 : %d / %d", Enemy::currentEnemyCount, numOfEnemy);
	TextOut(hdcMem, 0, 60, buf, strlen(buf));

	wsprintf(buf, "피격 횟수 : %d회", Tank::hitCount);
	TextOut(hdcMem, 0, 60, buf, strlen(buf));

	BitBlt(hdc, 0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y, hdcMem, 0, 0, SRCCOPY);

	SelectObject(hdcMem, hBitmapMemOld); //-4
	DeleteObject(hBitmapMem); //-3
}

void MainGame::SetEnemyWave(int num)
{
	if (enemy)
	{
		delete[] enemy;
	}

	enemy = new Enemy[num];
	for (int i = 0; i < num; i++) {
		enemy[i].Init(tank1->GetPos());
		enemy[i].Appear();
	}

	numOfEnemy = Enemy::currentEnemyCount = num;
}

void MainGame::Release()
{
	tank1->Release();
	delete tank1;

	for (int i = 0; i < numOfEnemy; i++)
		enemy[i].Release();
	delete[] enemy;

	for (int i = 0; i < Missile::numOfMissile; i++)
		missile[i].Release();
	delete[] missile;

	// 타이머 삭제
	KillTimer(hWnd, 0);
	KillTimer(hWnd, 1);

	// Object 삭제
	DeleteObject(Enemy::hPenOutline);
	DeleteObject(Enemy::hBrushInside);
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_TIMER:
		switch (wParam)
		{
		case 0:
			this->Update();
			InvalidateRect(hWnd, NULL, false);
			break;

		case 1:
			FPS = g_Frame - checkFrame;
			checkFrame = g_Frame;
			break;
		}

		break;

	case WM_CREATE:
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
	case WM_MOUSEMOVE:
		mouse.x = LOWORD(lParam);
		mouse.y = HIWORD(lParam);
		break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		hdc = BeginPaint(hWnd, &ps);

		this->Render(hdc);

		EndPaint(hWnd, &ps);
		g_Frame++;
	}
	break;

	case WM_DESTROY:
		DeleteDC(hdcMem); //-2
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, iMessage, wParam, lParam);
	}
	return 0;
}
