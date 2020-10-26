#pragma once
#include "pch.h"
#include "GameNode.h"

class Missile;
class Enemy;
class Tank : public GameNode
{
private:
	// �Ӽ� : �������
	RECT rc;
	int size;
	float speed;

	// ����
	// ������ ������
	// ������ ����
	POINTFLOAT barrelEnd;
	int barrelSize;
	float barrelAngle;

	// �̻���
	int numOfMissile;
	int currentMissileCount;
	Missile* missile;

	// �� (Ÿ��)
	Enemy* target;

public:
	// ��� : ����Լ�
	HRESULT Init();				// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	void Release();				// �޸� ����
	void Update();				// ������ ���� ���� ���� ���� (������ ����)
	void LatedUpdate();
	void Render(HDC hdc);		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	void Fire();
	void Move();
	void Dead();
	void RotateBarrel(float angle);

	void SetTarget(Enemy* target);

	Tank();
	~Tank();
};

