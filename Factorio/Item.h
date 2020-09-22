#pragma once
#include "Entity.h"
#include <string>
using namespace std;
enum class ItemCode {
	IronOre,
	StoneFurnace
};

class Item : Entity {
private:
	string name;
	ItemCode code;
	int stackSize;
	
public:
	Item(string name, ItemCode code, int stackSize);

	// getter
	string GetName();
	ItemCode GetItemCode();
	int GetStackSize();
};