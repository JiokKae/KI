#pragma once
#include "pch.h"
#include "GameNode.h"

class Missile;
class Tank : public GameNode
{
private:
	// ¸öÅë ÁÂÇ¥, Å©±â
	POINTFLOAT pos;
	float speed;
	float size;
	HPEN hPenOutline;
	HBRUSH hBrushInside;
	Allies aliies;

	// Æ÷½Å
	POINTFLOAT barrelEnd;
	int barrelSize;
	float barrelAngle;
	float barrelSpeed;
	int cooltime;
	int shootFrame;

public:
	static int hitCount;
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void Fire(POINTFLOAT enemyPos, Missile* missile);
	void RotateBarrel(float angle);
	void Move(POINTFLOAT delta);

	POINTFLOAT GetPos();
	float GetSize() { return size; }
};

