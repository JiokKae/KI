#pragma once
#include "pch.h"
#include "GameNode.h"

class Missile;
class Block;
class Vaus : public GameNode
{
private:
	POINT pos;
	int width, height;
	float speed;

	// �̻���
	int numOfMissile;
	int currentMissileCount;
	Missile* missile;

public:
	// ��� : ����Լ�
	HRESULT Init();				// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	void Release();				// �޸� ����
	void Update();				// ������ ���� ���� ���� ���� (������ ����)
	void LatedUpdate();
	void Render(HDC hdc);		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	void Fire();

	void Move(float dir);

};

