#pragma once
#include "pch.h"
#include "GameNode.h"

class Enemy;
class Missile : public GameNode
{
private:
	float baseSpeed;
	POINTFLOAT speed;
	POINTFLOAT pos;
	int size;
	bool isFire;

public:
	HRESULT Init();								// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	void Release();								// �޸� ����
	void Update(Enemy* enemys, int numOfEnemy);	// ������ ���� ���� ���� ���� (������ ����)
	void Render(HDC hdc);						// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	bool IsFire() { return isFire; }
	POINTFLOAT GetPos() { return pos; }
	int GetSize() { return size; }

	void SetIsFire(bool isFire) { this->isFire = isFire; }
	void SetPos(POINTFLOAT pos) { this->pos = pos; }
	void SetSpeed(int angle) { 
		this->speed.x = (float)cos(RADIAN(angle)) * baseSpeed;
		this->speed.y = (float)sin(RADIAN(angle)) * baseSpeed;
	}
};

