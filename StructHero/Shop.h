#pragma once
#include "StructHeroLibrary.h"
using namespace std;

// 포션 : (string) 이름 / (int) 가격 / (int) 회복치
struct Potion {
	string name;
	int price;
	int recoveryPoint;
};

// 상점 : (Potion*) 아이템 종류 / (int) 아이템 개수 / (Vector2Int) 좌표 / (string) 지붕 모양 / (string) 모양
class Shop
{
private:
	Potion* potions;
	int length;
	Vector2Int coord;
	string roofShape;
	string shape;
public:

	// 상점 삭제 (동적할당 해제)
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

	// 상점 초기화 함수
	void Init();
	
};

