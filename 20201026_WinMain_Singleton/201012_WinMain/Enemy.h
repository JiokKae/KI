#pragma once
#include "pch.h"
#include "GameNode.h"

class Enemy : public GameNode
{
private:
	int size;
	POINTFLOAT pos;
	float speed;
	bool isDead;

public:
	HRESULT Init();		
	void Release();		
	void Update();		
	void Render(HDC hdc);

	void AutoMove();

	POINTFLOAT GetPos() { return pos; }

	Enemy();
	~Enemy();
};

