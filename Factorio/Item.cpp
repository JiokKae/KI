#include "Item.h"

Item::Item(string name, ItemCode code, int stackSize)
{
	this->name = name;
	this->code = code;
	this->stackSize = stackSize;
}

string Item::GetName()
{
	return name;
}

ItemCode Item::GetItemCode()
{
	return code;
}

int Item::GetStackSize()
{
	return stackSize;
}
