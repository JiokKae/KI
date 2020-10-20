#pragma once
#include "pch.h"
#include "GameNode.h"

class Missile;
class Tank : public GameNode
{
	// ���� ��ǥ, ũ��
	POINTFLOAT pos;
	int size;
	int shootFrame;
	int cooltime;

	// ����
	int barrelSize;
	int angle;

public:
	
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void Fire(Missile* missile, int& index, int numOfMissile);
	void SetAngle(int angle);
	void RotateBarrel(int delta);
	POINTFLOAT GetBarrelEnd();
	POINTFLOAT GetPos();
};

