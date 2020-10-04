#pragma once
#include "StructHeroLibrary.h"
#include "Shop.h"

using namespace std;

// 플레이어 : (string) 이름 / (int) 최대 HP / (int) HP / (int) 최대 경험치/ (int) 경험치 / (int) 레벨 / (int) 골드 / (Vector2Int) 좌표 / (string) 모양
class Hero
{
private:
	string name;
	int maxHP;
	int HP;
	int maxExp;
	int exp;
	int level;
	int gold;
	Vector2Int coord;
	string shape;

public:
	Hero();

	void SetHP(int HP) {
		this->HP = HP;

	}
	void SetName(string name) 
	{	
		this->name = name; 
		shape = name.substr(0, 2);
	}

	Vector2Int GetCoord()	{ return coord; }
	string GetShape()		{ return shape; }
	string GetName()		{ return name; }
	int GetLevel()			{ return level; }
	int GetHP()				{ return HP; }
	int GetMaxHP()			{ return maxHP; }
	int GetExp()			{ return exp; }
	int GetMaxExp()			{ return maxExp; }
	int GetGold()			{ return gold; }

	void SetCoord(Vector2Int coord) { this->coord = coord; }

	void AddExp(int exp)		{ this->exp += exp; }
	void AddGold(int gold)		{ this->gold += gold; }
	void Damaged(int damage)	{ HP -= damage; }

	bool IsDead()	{ return HP <= 0; }

	// 초기화 함수
	void Init(int difficulty);
	
	// 레벨업 처리 함수
	void Levelup();

	// 용사의 움직임 함수
	int Move(char input, Vector2Int mapSize);

	// 뒤로 돌아가는 움직임 함수
	void MoveBack(char heroAct);

	// 상점 포션 구매 함수
	bool BuyPotion(Potion potion);
	
};

