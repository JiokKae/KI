#include "Shop.h"

void Shop::Init()
{
	length = 4;
	potions = new Potion[length];
	potions[0] = { "��������", 50, 1 };
	potions[1] = { "�뷮�� ��������", 100, 3 };
	potions[2] = { "Ȱ������", 150, 5 };
	potions[3] = { "�뷮�� Ȱ������", 200, 7 };
	roofShape = "��";
	shape = "��";
}
