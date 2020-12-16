#pragma once
#include "GameNode.h"

class Image;
class SpaceShip : public GameNode
{
private:
	FPOINT pos;
	Image* img;
	float speed;

public:
	HRESULT Init();		
	void Release();		
	void Update();		
	void Render(HDC hdc);
};

