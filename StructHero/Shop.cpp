#include "Shop.h"

void Shop::Init()
{
	length = 4;
	potions = new Potion[length];
	potions[0] = { "힐링포션", 50, 1 };
	potions[1] = { "대량의 힐링포션", 100, 3 };
	potions[2] = { "활력포션", 150, 5 };
	potions[3] = { "대량의 활력포션", 200, 7 };
	roofShape = "△";
	shape = "▣";
}
