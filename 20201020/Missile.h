#pragma once
#include "pch.h"
#include "GameNode.h"

class Missile : public GameNode
{
private:
	float baseSpeed;
	POINTFLOAT speed;
	POINT pos;
	int size;
	bool isFire;

public:
	HRESULT Init();				// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	void Release();				// �޸� ����
	void Update();				// ������ ���� ���� ���� ���� (������ ����)
	void Render(HDC hdc);		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	bool IsFire() { return isFire; }

	void SetIsFire(bool isFire) { this->isFire = isFire; }
	void SetPos(POINT pos) { this->pos = pos; }
	void SetSpeed(int angle) { 
		this->speed.x = cos(RADIAN(angle)) * baseSpeed; 	
		this->speed.y = sin(RADIAN(angle)) * baseSpeed;
	}
};

