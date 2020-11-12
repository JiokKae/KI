#pragma once
#include "GameNode.h"

class Tank;
class Missile;
class Enemy;
class MainGame : public GameNode
{
private:
	struct MOUSE_DATA
	{
		int mousePosX, mousePosY;
		int clickedPosX, clickedPosY;
	};

	HINSTANCE hInstance;
	HDC hdc, hdcMem;
	HDC hdc_BackGround;
	HBITMAP hbmMem, hbmMemOld;
	PAINTSTRUCT ps;

	HANDLE hTimer;
	MOUSE_DATA mouseData;

	Tank *tank1;
	Enemy* enemys;
	int numOfEnemy;
	int currentEnemyCount;

	// �̻���
	Missile* missile;
	int numOfMissile;
	int currentMissileIndex;

	bool isInit;

public:
	HRESULT Init(HINSTANCE hInst);	// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	void Release();					// �޸� ����
	void Update();					// ������ ���� ���� ���� ���� (������ ����)
	void Render(HDC hdc);			// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)
	
	void SetEnemyWave(int n);

	LRESULT MainProc(HWND hWnd, UINT iMessage,
		WPARAM wParam, LPARAM lParam);

};

