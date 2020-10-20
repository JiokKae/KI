#pragma once
#include "GameNode.h"

class Tank;
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

public:
	HRESULT Init(HINSTANCE hInst);	// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	void Release();					// �޸� ����
	void Update();					// ������ ���� ���� ���� ���� (������ ����)
	void Render(HDC hdc);			// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)
	
	LRESULT MainProc(HWND hWnd, UINT iMessage,
		WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

