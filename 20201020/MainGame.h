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

	// 미사일
	Missile* missile;
	int numOfMissile;
	int currentMissileIndex;

	bool isInit;

public:
	HRESULT Init(HINSTANCE hInst);	// 멤버 변수 초기화, 메모리 할당
	void Release();					// 메모리 해제
	void Update();					// 프레임 단위 게임 로직 실행 (데이터 변경)
	void Render(HDC hdc);			// 프레임 단위 출력 (이미지, 텍스트 등)
	
	void SetEnemyWave(int n);

	LRESULT MainProc(HWND hWnd, UINT iMessage,
		WPARAM wParam, LPARAM lParam);

};

