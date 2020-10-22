#pragma once
#include "pch.h"
#include "GameNode.h"

class Missile;
class Tank : public GameNode
{
private:
	// ���� ��ǥ, ũ��
	POINT pos;
	float speed;
	int size;

	// ����
	FPOINT barrelEnd;
	int barrelSize;
	float barrelAngle;

	// �̻���
	int numOfMissile;
	int currentMissileCount;
	Missile* missile;
	int cooltime;
	int shootFrame;

public:
	HRESULT Init();		
	void Release();		
	void Update(FPOINT enemyPos, int enemySize);
	void Render(HDC hdc);

	void Fire(FPOINT enemyPos);
	void RotateBarrel(float angle);
	void Move(FPOINT delta);
	Tank();
	~Tank();
};

