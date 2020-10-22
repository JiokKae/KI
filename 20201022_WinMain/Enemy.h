#pragma once
#include "GameNode.h"
class Enemy : public GameNode
{
private:
	FPOINT pos;
	int size;
	FPOINT speed;
public:
	HRESULT Init();				// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	void Release();				// �޸� ����
	void Update();				// ������ ���� ���� ���� ���� (������ ����)
	void Render(HDC hdc);		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)
	
	RECT GetRect();
	FPOINT GetPos();
	int GetSize();
};

