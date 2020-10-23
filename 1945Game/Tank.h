#pragma once
#include "pch.h"
#include "GameNode.h"

class Missile;
class Tank : public GameNode
{
private:
	// 몸통 좌표, 크기
	POINT pos;
	float speed;
	int size;

	// 포신
	POINTFLOAT barrelEnd;
	int barrelSize;
	float barrelAngle;

	// 미사일
	int numOfMissile;
	int currentMissileCount;
	Missile* missile;
	int cooltime;
	int shootFrame;

public:
	HRESULT Init();
	void Release();
	void Update(POINTFLOAT enemyPos, int enemySize);
	void Render(HDC hdc);

	void Fire(POINTFLOAT enemyPos);
	void RotateBarrel(float angle);
	void Move(POINTFLOAT delta);

};

