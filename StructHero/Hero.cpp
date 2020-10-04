#include "Hero.h"

Hero::Hero()
{
	level = 1;
	gold = 0;
	maxExp = 100;
	exp = 0;
}

void Hero::Init(int difficulty)
{
	maxHP = HP = 6 + difficulty;
	level = 1;
	gold = 0;
	maxExp = 100;
	exp = 0;
}

void Hero::Levelup()
{
	level++;
	exp -= maxExp;
	HP = ++maxHP;
	maxExp += 10;
}

int Hero::Move(char input, Vector2Int mapSize)
{
	int noise = RandomInRange(1, 100);
	switch (input)
	{
	case 'w': case 'W':
		if (coord.y > 1)
			coord.y--;
		else
			noise = 0;
		break;
	case 'a': case 'A':
		if (coord.x > 1)
			coord.x--;
		else
			noise = 0;
		break;
	case 's': case 'S':
		if (coord.y < mapSize.y)
			coord.y++;
		else
			noise = 0;
		break;
	case 'd': case 'D':
		if (coord.x < mapSize.x)
			coord.x++;
		else
			noise = 0;
		break;
	default:
		noise = 0;
		break;
	}
	return noise;
}

void Hero::MoveBack(char heroAct)
{
	switch (heroAct)
	{
	case 'w': case 'W':
		coord.y++;
		break;
	case 'a': case 'A':
		coord.x++;
		break;
	case 's': case 'S':
		coord.y--;
		break;
	case 'd': case 'D':
		coord.x--;
		break;
	}
}

bool Hero::BuyPotion(Potion potion)
{
	if (gold >= potion.price)
	{
		gold -= potion.price;
		HP += potion.recoveryPoint;
		if (HP > maxHP)
			HP = maxHP;

		return true;
	}
	else
		return false;
}
