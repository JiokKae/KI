#pragma once

#include "GameNode.h"

class Ship;
class Enemy;
class EnemyManager;
class Missile;
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
	PAINTSTRUCT ps;
	MOUSE_DATA mouseData;
	bool isInit;

	Image* backBuffer;
	Image* backGround;
	EnemyManager* enemyMgr;

	Ship* player;

public:
	HRESULT Init();				// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	void Release();				// �޸� ����
	void Update();				// ������ ���� ���� ���� ���� (������ ����)
	void Render();				// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	bool CheckCollision(Missile* m1, Missile* m2);	// �̻��ϳ��� �浹Ȯ��
	float GetDistance(POINTFLOAT pos1, POINTFLOAT pos2);
	float GetAngle(POINTFLOAT pos1, POINTFLOAT pos2);

	LRESULT MainProc(HWND hWnd, UINT iMessage,
		WPARAM wParam, LPARAM lParam);

};

