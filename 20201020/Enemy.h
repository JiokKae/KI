#pragma once
#include "pch.h"
#include "GameNode.h"

class Enemy : public GameNode
{
private:
	POINTFLOAT pos;
	int size;
	float speed;
	POINTFLOAT velocity;
	bool isAlive;

public:
	HRESULT Init();				// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	void Release();				// �޸� ����
	void Update(POINTFLOAT tankPos);	// ������ ���� ���� ���� ���� (������ ����)
	void Render(HDC hdc);		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	void Appear();
	void Dead();
	int GetSize();
	POINTFLOAT GetPos();
	bool IsAlive() { return isAlive; }
};

