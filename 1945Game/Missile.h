#pragma once
#include "pch.h"
#include "GameNode.h"

class Tank;
class Enemy;
class Missile : public GameNode
{
private:
	// 속도, 좌표, 크기, 발사여부
	POINTFLOAT pos;
	POINTFLOAT direction;
	float speed;
	float angle;
	float size;
	bool isFire;
	Allies allies;
	Pattern pattern;
	static HPEN hPenOutline[2];
	static HBRUSH hBrushInside[2];
	
	int cooltime;
	int shootFrame;

public:
	static int numOfMissile;
	static int currentMissileCount;
	static int GetMissileCount();

	HRESULT Init();
	void Release();
	void Update(Enemy* enemy, int numOfEnemy, Tank* tank, int numOfTank, Missile* missile);
	void Render(HDC hdc);

	bool GetIsFire() { return isFire; }
	void SetIsFire(bool isFire) { this->isFire = isFire; }

	void SetAllies(Allies allies) {	this->allies = allies; }

	void SetPos(POINTFLOAT pos) { this->pos = pos; }

	void SetPattern(Pattern pattern);

	void SetAngle(float degree) {
		this->angle = degree;
		direction.x = cosf(RADIAN(degree));
		direction.y = -sinf(RADIAN(degree));
	}

	void Fired(Allies allies, POINTFLOAT pos, float angle, Pattern pattern, float size = 30.0f, float speed = 10.0f);
	void AdditionalMissile(Missile* missile);
	
};

