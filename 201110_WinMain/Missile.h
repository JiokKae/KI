#pragma once
#include "pch.h"
#include "GameNode.h"

class EnemyManager;
class Image;
class Missile : public GameNode
{
private:
	FPOINT pos;
	int size;
	float speed;
	bool isFire;
	float angle;
	float destAngle;
	Image* img;
	EnemyManager* enemyMgr;
	float followRatio;
	int time;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	bool GetIsFire() { return isFire; }
	void SetIsFire(bool fire) { isFire = fire; }

	void SetPos(FPOINT pos) { this->pos = pos; }
	FPOINT GetPos() { return this->pos; }

	void SetAngle(float angle) { this->angle = angle; }

	int GetSize() { return this->size; }

	void SetSpeed(float speed) { this->speed = speed; }

	Missile();
	~Missile();
};

