#include "StructHeroLibrary.h"

int RandomInRange(int start, int end)
{
	return rand() % (end - start + 1) + start;
}

std::string IntToCharString(int num, std::string ch)
{
	std::string str = "";
	for (int i = 0; i < num; i++)
		str += ch;

	return str;
}

void GetEnter()
{
	std::cout << std::endl << "넘어가려면 엔터를 누르세요" << std::endl;
	getchar();
	while (getchar() != '\n');
}