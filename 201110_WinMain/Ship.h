#pragma once
#include "pch.h"
#include "GameNode.h"

class Missile;
class Enemy;
class Image;
class Ship : public GameNode
{
private:
	RECT rc;
	Allies allies;
	POINTFLOAT pos;
	POINTFLOAT size;
	float speed;

	Image* image;
	

public:
	HRESULT Init();				// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	void Release();				// �޸� ����
	void Update();				// ������ ���� ���� ���� ���� (������ ����)
	void Render(HDC hdc);		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	POINTFLOAT GetPos() { return pos; }

	void Fire();
	void Move();
	void Dead();

	
};

