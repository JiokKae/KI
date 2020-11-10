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

	MissileManager* missileMgr;

	int updateCount;
	int currFrameX = 0;
	int currFrameY = 0;

public:
	HRESULT Init(float posX = 0, float posY = 0);
	void Release();		
	void Update();		
	void Render(HDC hdc);

	void AutoMove();

	FPOINT GetPos() { return pos; }

	Enemy();
	~Enemy();
};

