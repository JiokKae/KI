#pragma once
#include "GameNode.h"

class Tank;
class Enemy;
class MainGame : public GameNode
{
private:
	struct MouseData
	{
		int posX, posY;
		int clickedPosX, clickedPosY;
	};

	HINSTANCE hInstance;
	HDC hdc, hdcMem;
	HDC hdc_BackGround;
	HBITMAP hbmMem, hbmMemOld;
	PAINTSTRUCT ps;

	MouseData mouseData;
	HANDLE hTimer;

	Tank* tank1;
	Enemy* enemy;
public:
	// 오버로딩
	// 오버라이딩

	HRESULT Init(HINSTANCE hInst);
	void Release();
	void Update();
	void Render(HDC hdc);

	bool CheckRectCollision(RECT rc1, RECT rc2);

	LRESULT MainProc(HWND hWnd, UINT iMessage,
		WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

