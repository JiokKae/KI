#pragma once

/*
	���漱��, ��ó���� #include

	1. is a ���� : �ҳ�Ÿ�� ����.					-> #include
	2. has a ���� : �ҳ�Ÿ�� ������ ������ �ִ�.	-> ���漱��
*/
#include "GameNode.h"

class Tank;
class Enemy;
class Image;
class MainGame : public GameNode
{
private:
	struct MOUSE_DATA
	{
		int mousePosX, mousePosY;
		int clickedPosX, clickedPosY;
	};

	// ������ ����
	HWND hWnd;
	HINSTANCE hInstance;

	// ���� ����
	HBITMAP hBitmapMem, hBitmapMemOld;
	HDC hdc, hdcMem;
	HDC hdc_BackGround;
	
	PAINTSTRUCT ps;
	HANDLE hTimer;
	MOUSE_DATA mouseData;

	Tank* tank1;
	Enemy* enemy1;

	// �̹���
	Image* emptyImage;
	POINT imagePos[2];
	Image* fileImage;
	Image* ioriAni;
	Image* backbuffer;
	Image* backGround;
	
	bool isInit = false;

	int x[8] = { };

public:
	HRESULT Init();				// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	void Release();				// �޸� ����
	void Update();				// ������ ���� ���� ���� ���� (������ ����)
	void Render(HDC hdc);		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	LRESULT MainProc(HWND hWnd, UINT iMessage,
		WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

