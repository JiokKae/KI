#pragma once
#include "GameNode.h"

class Image;
class Animation;
class Camel : public GameNode
{
private:
	POINTFLOAT pos;
	Image* img;
	Animation* ani1;
	Animation* ani2;
	Animation* ani3;
	Animation* playAni;

public:
	HRESULT Init(float posX = 0.0f, float posY = 0.0f);
	void Release();
	void Update();
	void Render(HDC hdc);
};

