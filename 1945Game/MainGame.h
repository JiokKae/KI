#pragma once
#include "GameNode.h"

class Tank;
class Enemy;
class Missile;
class MainGame : public GameNode
{
private:
	POINT mouse;
	POINT clickedMouse;
	HANDLE hTimer, hTimer2;

	// 윈도우 관련
	HWND hWnd;
	HINSTANCE hInstance;

	// 렌더 관련
	HBITMAP hBitmapMem, hBitmapMemOld;
	HDC hdc, hdcMem;
	HDC hdc_BackGround;

	// 프레임 관련
	int checkFrame;
	int FPS;

	// 탱크
	Tank* tank1;

	// 적
	int numOfEnemy;
	Enemy* enemy;

	// 미사일
	Missile* missile;

public:
	HRESULT Init(HINSTANCE hInst, HWND hWnd);
	void Release();
	void Update();
	void Render(HDC hdc);

	void SetEnemyWave(int num);

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};
