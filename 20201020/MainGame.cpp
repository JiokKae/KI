#include "pch.h"
#include "MainGame.h"
#include "Tank.h"
#include "Enemy.h"
#include "Missile.h"
#include "MacroFunction.h"

inline bool Collision(Missile missile, Enemy enemy)
{
	return Distance(missile.GetPos(), enemy.GetPos()) < ((enemy.GetSize() / 2) + (missile.GetSize() / 2));
}

HRESULT MainGame::Init(HINSTANCE hInst)
{
	hInstance = hInst;

	tank1 = new Tank();
	tank1->Init();

	numOfEnemy = currentEnemyCount = 1;
	
	enemys = new Enemy[numOfEnemy];
	for (int i = 0; i < numOfEnemy; i++) {
		enemys[i].Init();
		enemys[i].Appear();
	}
	
	// 미사일
	numOfMissile = 100;
	missile = new Missile[numOfMissile];
	for (int i = 0; i < numOfMissile; i++)
		missile[i].Init();

	return S_OK;
}

void MainGame::Release()
{
	tank1->Release();
	delete tank1;

	for (int i = 0; i < numOfEnemy; i++)
		enemys[i].Release();
	delete[] enemys;

	for (int i = 0; i < numOfMissile; i++)
		missile[i].Release();
	delete[] missile;
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
			tank1->Fire(missile, currentMissileIndex, numOfMissile);
		}

		for (int i = 0; i < numOfEnemy; i++)
		{
			if (enemys)
			{
				enemys[i].Update(tank1->GetPos());
			}
		}
	}
	if (missile)
	{
		for (int i = 0; i < numOfMissile; i++)
		{
			if (missile[i].IsFire())
			{
				missile[i].Update(enemys, numOfEnemy);
				// 적과의 충돌 검사
				if (enemys)
				{
					for (int j = 0; j < numOfEnemy; j++)
					{
						if (enemys[j].IsAlive())
						{
							if (Collision(missile[i],enemys[j]))
							{
								enemys[j].Dead();
								missile[i].SetIsFire(false);
								currentEnemyCount--;
							}
						}
					}
				}
			}
			
		}
	}
	
	if (currentEnemyCount <= 0)
		SetEnemyWave(numOfEnemy + 1);
	
	InvalidateRect(g_hWnd, NULL, false);
}

int x = 1100, y = 0;
int vx = -2, vy = +5;
void MainGame::Render(HDC hdc)
{
	hbmMem = CreateCompatibleBitmap(hdc, WIN_SIZE_X, WIN_SIZE_Y);//3
	hbmMemOld = (HBITMAP)SelectObject(hdcMem, hbmMem);//4

	BitBlt(hdcMem, 0, 0, WIN_SIZE_X, WIN_SIZE_Y, hdc_BackGround, 0, 0, SRCCOPY);
	
	// 탱크 렌더
	tank1->Render(hdcMem);
	// 적 렌더
	for (int i = 0; i < numOfEnemy; i++)
		enemys[i].Render(hdcMem);
	// 미사일 렌더
	for (int i = 0; i < numOfMissile; i++)
		missile[i].Render(hdcMem);

	
	Ellipse(hdcMem, x, y, x + 100, y + 100);
	vx = -g_Frame * 3;
	vy = g_Frame * 2;
	//x += vx + cos(g_Frame);
	//y += vy + sin(g_Frame);
	
	x = cos(g_Frame/30.0) * (300.0 - ((float)g_Frame/2)) + 1000 + vx;
	y = sin(g_Frame/30.0) * (200.0 - ((float)g_Frame/2)) + 100 + vy;

	char szText[128];
	wsprintf(szText, "X : %d, Y : %d", mouseData.mousePosX, mouseData.mousePosY);
	TextOut(hdcMem, 10, 5, szText, strlen(szText));
	wsprintf(szText, "Clicked X : %d, Y : %d", mouseData.clickedPosX, mouseData.clickedPosY);
	TextOut(hdcMem, 10, 30, szText, strlen(szText));
	wsprintf(szText, "g_Frame : %d", g_Frame);
	TextOut(hdcMem, 10, 55, szText, strlen(szText));
	BitBlt(hdc, 0, 0, WIN_SIZE_X, WIN_SIZE_Y, hdcMem, 0, 0, SRCCOPY);

	SelectObject(hdcMem, hbmMemOld); //-4
	DeleteObject(hbmMem); //-3
	g_Frame++;
}

void MainGame::SetEnemyWave(int num)
{
	if (enemys) 
	{
		delete[] enemys;
	}
		
	enemys = new Enemy[num];
	for (int i = 0; i < num; i++) {
		enemys[i].Init();
		enemys[i].Appear();
	}

	numOfEnemy = currentEnemyCount = num;
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
