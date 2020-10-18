#pragma once
#include <Windows.h>
#include "3BoxLibrary.h"

class BigBox
{
private:
	int width;
	int height;

public:
	int index;
	int maxHp;
	int hp;
	POINT position;
	int speed;
	POINT velocity;
	bool passed;
	bool special;

	void Init(int i);

	int GetWidth() { return width * hp / maxHp; }
	int GetHeight() { return height * hp / maxHp; };
	RECT GetRect() { return { position.x, position.y, position.x + GetWidth(), position.y + GetHeight() }; }
	bool IsAlive() { return hp > 0; };
	bool IsDead() { return hp <= 0; }
};