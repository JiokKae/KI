#include "Monster.h"

void Monster::Init(string name, int maxHP, int HP, int earnedExp, int earnedGold)
{
	this->name = name;
	this->maxHP = maxHP;
	this->HP = HP;
	this->earnedExp = earnedExp;
	this->earnedGold = earnedGold;
}