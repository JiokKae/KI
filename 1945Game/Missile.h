#pragma once
#include "pch.h"
#include "GameNode.h"

class Missile : public GameNode
{
private:
	// 속도, 좌표, 크기, 발사여부
	float speed;
	POINTFLOAT pos;
	int size;
	bool isFire;
	float angle;
	POINTFLOAT direction;

public:
	HRESULT Init();
	void Release();
	void Update(POINTFLOAT enemyPos, int enemySize);
	void Render(HDC hdc);

	bool GetIsFire() { return isFire; }
	void SetIsFire(bool isFire) { this->isFire = isFire; }

	void SetPos(POINTFLOAT pos) { this->pos = pos; }

	void SetAngle(float angle)
	{
		this->angle = angle;
		direction.x = cos(DEGREE(angle));
		direction.y = -sin(DEGREE(angle));
	}

	Missile();
	~Missile();
};

