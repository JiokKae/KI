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

	// ������ ����
	HWND hWnd;
	HINSTANCE hInstance;

	// ������ ����
	int checkFrame;
	int FPS;

	// ���� ����
	HBITMAP hBitmapMem, hBitmapMemOld;
	HDC hdc, hdcMem;
	HDC hdc_BackGround;

	// ��ũ
	Tank* tank1;

	// ��
	int numOfEnemy;
	Enemy* enemy;

	// �̻���
	Missile* missile;

public:
	HRESULT Init(HINSTANCE hInst, HWND hWnd);
	void Release();
	void Update();
	void Render(HDC hdc);

	void SetEnemyWave(int num);

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};
