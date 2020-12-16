#pragma once
#include "pch.h"
#include "GameNode.h"

class Image;
class MissileManager;
class Enemy : public GameNode
{
private:
	int size;
	FPOINT pos;
	float speed;
	bool isDead;
	Image* img;

	int updateCount;
	int currFrameX, currFrameY;

	// 미사일 매니저
	MissileManager* missileMgr;
	int fireCount;
	float fireTime;

public:
	HRESULT Init(float posX = 0.0f, float posY = 0.0f);		
	void Release();		
	void Update();		
	void Render(HDC hdc);

	void AutoMove();

	FPOINT GetPos() { return pos; }

	Enemy();
	~Enemy();
};

