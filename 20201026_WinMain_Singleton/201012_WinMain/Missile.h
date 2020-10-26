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

	// 현재 방향
	POINTFLOAT barrelEnd;
	int barrelSize;
	float barrelAngle;

	// 과거 방향
	POINTFLOAT barrelEnd2;
	int barrelSize2;
	float barrelAngle2;
	float angle2;
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

	float GetAngle() { return angle; }
	void SetAngle(float angle) 
	{ 
		this->angle2 = this->angle;
		this->angle = angle; 
	}

	void SetTarget(Enemy* target) { this->target = target; }

	void Move(float angle, float distance);

	Missile();
	~Missile();
};

