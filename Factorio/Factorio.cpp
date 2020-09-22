#include <iostream>
#include <map>
#include <array>
#include "Item.h"

using namespace std;

struct InventoryItem {
	Item item;
	int number;
};


void Update();
void PrintInventory();
void BuildWizard();
void MiningWizard();



Item IronOre = Item("철광석", ItemCode::IronOre, 50);
Item StoneFurnace = Item("돌 용광로", ItemCode::StoneFurnace, 50);

array<Item, 1> OreArray = {IronOre};

map<ItemCode, InventoryItem> Inventory;

int main()
{
	
	char order;
	while (true)
	{
		cout << "u : 진행, b : 건설, m : 채광" << endl;
		PrintInventory();

		cin >> order;
		switch (order)
		{
		case 'b':
			BuildWizard();
			break;

		case 'u':
			break;

		case 'm':
			MiningWizard();
			break;
		}
	}
}

void Update() {

}

void PrintInventory() {
	map<ItemCode, InventoryItem>::iterator it;

	for (it = Inventory.begin(); it != Inventory.end(); it++)
	{
		cout << it->second.item.GetName() << "x" << it->second.number << endl;
	}
	
}

void BuildWizard()
{

}

void MiningWizard()
{
	for (int i = 0; i < OreArray.size(); i++)
	{
		cout << i << ". " << OreArray.at(i).GetName() << endl;
	}
	
	int order;
	cin >> order;
	switch (order)
	{
	case 0:
	{
		Item ore = OreArray.at(0);
		ItemCode code = ore.GetItemCode();

		map<ItemCode, InventoryItem>::iterator it;
		it = Inventory.find(code);
		if (it == Inventory.end())
		{
			InventoryItem item = { OreArray.at(0), 1 };
			Inventory.insert({ code, item });
		}
		else {
			it->second.number++;
		}
	}
		
	default:
		break;
	}
}