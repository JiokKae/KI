#pragma once
#include "pch.h"
#include "GameNode.h"

class Image;
class Missile : public GameNode
{
private:
	POINTFLOAT pos;
	POINTFLOAT direction;
	float size;
	float angle;
	float speed;
	bool isFire;
	Allies allies;
	Pattern pattern;

	int cooltime;
	int shootFrame;

	Image* img;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	bool GetIsFire() { return isFire; }
	void SetIsFire(bool fire) { isFire = fire; }

	void SetPos(POINTFLOAT pos) { this->pos = pos; }
	POINTFLOAT GetPos() { return this->pos; }

	void SetPattern(Pattern pattern);

	void SetAngle(float degree) {
		this->angle = degree;
		direction.x = cosf(RADIAN(degree));
		direction.y = -sinf(RADIAN(degree));
	}

	int GetSize() { return this->size; }

	void SetSpeed(float speed) { this->speed = speed; }

	void Fired(Allies allies, POINTFLOAT pos, float angle, Pattern pattern, float size = 30.0f, float speed = 10.0f);
	void AdditionalMissile();
};

