#pragma once
#include "pch.h"

class Circle
{
	POINTFLOAT pos;
	float radius;

public:
	HRESULT Init();				// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	void Release();				// �޸� ����
	void Update();				// ������ ���� ���� ���� ���� (������ ����)
	void Render(HDC hdc);		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	POINTFLOAT GetPos() { return pos; }
	void SetPos(POINTFLOAT pos) { this->pos = pos; }
};

