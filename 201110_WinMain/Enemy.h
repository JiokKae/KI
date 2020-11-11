#pragma once
#include "pch.h"
#include "GameNode.h"

class Image;
class MissileManager;
class Enemy : public GameNode
{
private:
	// ¸öÃ¼
	POINTFLOAT pos;
	POINTFLOAT direction;
	float size;
	float speed;
	bool isAlive;
	Allies aliies;

	// ·»´õ
	Image* img;
	int updateCount;
	int currFrameX = 0;
	int currFrameY = 0;

	// ¹ß»ç
	int cooltime;
	int shootFrame;

public:
	HRESULT Init(float posX = 0, float posY = 0);
	void Release();		
	void Update();		
	void Render(HDC hdc);

	void AutoMove();
	void Fire(POINTFLOAT tankPos, Pattern pattern);

	POINTFLOAT GetPos() { return pos; }

};

