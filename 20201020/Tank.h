#pragma once
#include "pch.h"
#include "GameNode.h"

class Missile;
class Tank : public GameNode
{
	// ���� ��ǥ, ũ��
	POINT pos;
	int size;

	// ����
	int barrelSize;
	int angle;

	// �̻���
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

