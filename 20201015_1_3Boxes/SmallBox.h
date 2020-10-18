#pragma once
#include <Windows.h>
#include "3BoxLibrary.h"
#include "BigBox.h"

class SmallBox
{
private:
	int width;
	int height;
public:
	BigBox* parent;
	POINT position;

	void Init(BigBox* _parent);
	
	void ChangeParent(BigBox* _parent);


	bool isLaunch;
	int GetWidth() { return width; }
	int GetHeight() { return height; };
	RECT GetRect() { return { position.x, position.y, position.x + width, position.y + height }; }
};
