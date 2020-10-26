#pragma once
#include "pch.h"
#include "GameNode.h"

class Enemy;
class Missile : public GameNode
{
private:
	POINTFLOAT pos;
	float size;
	float speed;
	bool isFire;
	float angle;
	Enemy* target;
	float followRatio;

	POINTFLOAT barrelEnd;
	int barrelSize;
	float barrelAngle;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	bool GetIsFire() { return isFire; }
	void SetIsFire(bool fire) { isFire = fire; }

	POINTFLOAT GetPos() { return pos; }
	void SetPos(POINTFLOAT pos) { this->pos = pos; }

	float GetSize() { return size; }

	void SetAngle(float angle) { this->angle = angle; }

	void SetTarget(Enemy* target) { this->target = target; }

	Missile();
	~Missile();
};

