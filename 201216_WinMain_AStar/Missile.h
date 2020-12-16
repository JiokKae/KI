#pragma once
#include "pch.h"
#include "GameNode.h"

class Enemy;
class Missile : public GameNode
{
private:
	FPOINT pos;
	int size;
	float speed;
	float goalTime;
	bool isFire;
	float angle;
	float destAngle;
	Enemy* target;
	float followRatio;

	Enemy* owner;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	bool GetIsFire() { return isFire; }
	void SetIsFire(bool fire);

	void SetPos(FPOINT pos) { this->pos = pos; }
	FPOINT GetPos() { return this->pos; }

	void SetAngle(float angle) { this->angle = angle; }

	void SetTarget(Enemy* target) { this->target = target; }

	int GetSize() { return this->size; }

	void SetSpeed(float speed) { this->speed = speed; }

	void SetOwner(Enemy* owner) { this->owner = owner; }

	Missile();
	~Missile();
};

