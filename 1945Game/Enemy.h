#pragma once
#include "GameNode.h"
#include "pch.h"

class Missile;
class Enemy : public GameNode
{
private:
	// ��ü
	POINTFLOAT pos;
	POINTFLOAT direction;
	float speed;
	float size;
	bool isAlive;
	Allies aliies;
	
	// �߻�
	int cooltime;
	int shootFrame;

public:
	static HPEN hPenOutline;
	static HBRUSH hBrushInside;
	static int currentEnemyCount;

	HRESULT Init(POINTFLOAT tankPos);	// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	void Release();						// �޸� ����
	void Update(POINTFLOAT tankPos);	// ������ ���� ���� ���� ���� (������ ����)
	void Render(HDC hdc);				// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	void Fire(POINTFLOAT tankPos, Missile* missile, Pattern pattern);
	RECT GetRect();
	POINTFLOAT GetPos();
	int GetSize();
	bool IsAlive() { return isAlive; }
	void Appear();
	void Dead();

	
};

