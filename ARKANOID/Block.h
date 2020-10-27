#pragma once
#include "pch.h"
#include "GameNode.h"

class Block : public GameNode
{
private:
	POINT pos;
	int width, height;
	bool isAlive;

public:
	HRESULT Init();		
	void Release();		
	void Update();		
	void Render(HDC hdc);

	int GetWidth() { return width; }
	int GetHeight() { return height; }
	POINT GetPos() { return pos; }

	void Appear(POINT pos);
};

