#pragma once
#include "GameNode.h"
class Enemy : public GameNode
{
private:
	POINTFLOAT pos;
	int size;
	POINTFLOAT speed;
public:
	HRESULT Init();				// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	void Release();				// �޸� ����
	void Update();				// ������ ���� ���� ���� ���� (������ ����)
	void Render(HDC hdc);		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	RECT GetRect();
	POINTFLOAT GetPos();
	int GetSize();
};

