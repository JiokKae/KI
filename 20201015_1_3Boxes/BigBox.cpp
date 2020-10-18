#include "BigBox.h"

void BigBox::Init(int i)
{
	index = i;
	maxHp = hp = 3;

	position.x = BIGBOX_MARGIN + i % BIGBOX_COL * (BIGBOX_SIZE + BIGBOX_MARGIN);
	position.y = BIGBOX_MARGIN + i / BIGBOX_COL * (BIGBOX_SIZE + BIGBOX_MARGIN);
	width = BIGBOX_SIZE;
	height = BIGBOX_SIZE;
	speed = BIGBOX_SPEED;

	
	if (GAMEMODE & VELOCITY)
	{
		velocity = { rand() % 7 - 3, rand() % 7 - 3 };
	}
		
	if (GAMEMODE & SPECIAL_SWITCH)
	{
		if (!(rand() % 20))
			special = true;
		else
			special = false;
	}

	if (GAMEMODE & AUTO_WALL_SWITCH)
	{
		if (!(rand() % 10))
			passed = true;
		else
			passed = false;
	}
}
