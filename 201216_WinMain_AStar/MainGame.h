#pragma once

/*
	���漱��, ��ó���� #include

	1. is a ���� : �ҳ�Ÿ�� ����.					-> #include
	2. has a ���� : �ҳ�Ÿ�� ������ ������ �ִ�.	-> ���漱��
*/
#include "GameNode.h"

class Image;
class MainGame : public GameNode
{
private:
	struct MOUSE_DATA
	{
		int mousePosX, mousePosY;
		int clickedPosX, clickedPosY;
	};

	HDC hdc;
	MOUSE_DATA mouseData;
	bool isInit;

	Image* backBuffer;
	Image* backGround;

public:
	HRESULT Init();				// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	void Release();				// �޸� ����
	void Update();				// ������ ���� ���� ���� ���� (������ ����)
	void Render();				// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	LRESULT MainProc(HWND hWnd, UINT iMessage,
		WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

