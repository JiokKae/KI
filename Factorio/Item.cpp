#include "Item.h"

Item::Item(string name, ItemCode code, int stackSize)
{
	this->name = name;
	this->code = code;
	this->stackSize = stackSize;
}
