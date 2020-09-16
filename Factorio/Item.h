#pragma once
#include "Entity.h"
#include <string>
using namespace std;
enum class ItemCode {
	IronOre = 1
};

class Item : Entity {
private:
	string name;
	ItemCode code;
	int stackSize;
	
public:
	
	Item(string name, ItemCode code, int stackSize);
};