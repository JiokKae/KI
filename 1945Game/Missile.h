#pragma once
#include "pch.h"
#include "GameNode.h"

class Missile : public GameNode
{
private:
	// �ӵ�, ��ǥ, ũ��, �߻翩��
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

