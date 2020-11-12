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
	HRESULT Init();				// 멤버 변수 초기화, 메모리 할당
	void Release();				// 메모리 해제
	void Update();				// 프레임 단위 게임 로직 실행 (데이터 변경)
	void Render();				// 프레임 단위 출력 (이미지, 텍스트 등)

	bool CheckCollision(Missile* m1, Missile* m2);	// 미사일끼리 충돌확인
	float GetDistance(POINTFLOAT pos1, POINTFLOAT pos2);
	float GetAngle(POINTFLOAT pos1, POINTFLOAT pos2);

	LRESULT MainProc(HWND hWnd, UINT iMessage,
		WPARAM wParam, LPARAM lParam);

};

