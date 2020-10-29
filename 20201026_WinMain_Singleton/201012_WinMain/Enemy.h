#pragma once
#include "pch.h"
#include "GameNode.h"

class Image;
class Enemy : public GameNode
{
private:
	int size;
	POINTFLOAT pos;
	float speed;
	bool isDead;
	Image* image;

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

