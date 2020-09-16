#include <iostream>
#include "Item.h"
using namespace std;
void Update();
void PrintInventory();
void BuildWizard();
void MiningWizard();

Item IronOre = Item("철광석", ItemCode::IronOre, 50);

int main()
{
	char order;
	while (true)
	{
		cout << "u : 진행, b : 건설, m : 채광";

		cin >> order;
		switch (order)
		{
		case 'b':
			BuildWizard();
			break;

		case 'u':
			break;

		case 'm':
			break;
		}
	}
}

void Update() {

}

void PrintInventory() {

}

void BuildWizard()
{

}

void MiningWizard()
{

}