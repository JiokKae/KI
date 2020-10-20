#pragma once
#include "pch.h"
#include "GameNode.h"

class Missile;
class Tank : public GameNode
{
	// 몸통 좌표, 크기
	POINT pos;
	int size;

	// 포신
	int barrelSize;
	int angle;

	// 미사일
	Missile* missile;
	int numOfMissile;
	int currentMissileIndex;

public:
	
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void Fire();
	void SetAngle(int angle);
	void RotateBarrel(int delta);
	POINT GetBarrelEnd();
};

