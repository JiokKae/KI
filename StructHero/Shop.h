#pragma once
#include "StructHeroLibrary.h"
using namespace std;

// ���� : (string) �̸� / (int) ���� / (int) ȸ��ġ
struct Potion {
	string name;
	int price;
	int recoveryPoint;
};

// ���� : (Potion*) ������ ���� / (int) ������ ���� / (Vector2Int) ��ǥ / (string) ���� ��� / (string) ���
class Shop
{
private:
	Potion* potions;
	int length;
	Vector2Int coord;
	string roofShape;
	string shape;
public:

	// ���� ���� (�����Ҵ� ����)
	~Shop() 
	{	
		delete[] potions;
	}

	// getter
	Vector2Int GetCoord()		{ return coord; }
	string GetShape()			{ return shape; }
	string GetRoofShape()		{ return roofShape; }
	Potion GetPotion(int index)	{ return potions[index]; }
	int GetLength()				{ return length; }

	// setter
	void SetCoord(Vector2Int coord) { this->coord = coord; }

	// ���� �ʱ�ȭ �Լ�
	void Init();
	
};

