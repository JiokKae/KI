#pragma once
#include "StructHeroLibrary.h"
#include "Shop.h"

using namespace std;

// �÷��̾� : (string) �̸� / (int) �ִ� HP / (int) HP / (int) �ִ� ����ġ/ (int) ����ġ / (int) ���� / (int) ��� / (Vector2Int) ��ǥ / (string) ���
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

	// �ʱ�ȭ �Լ�
	void Init(int difficulty);
	
	// ������ ó�� �Լ�
	void Levelup();

	// ����� ������ �Լ�
	int Move(char input, Vector2Int mapSize);

	// �ڷ� ���ư��� ������ �Լ�
	void MoveBack(char heroAct);

	// ���� ���� ���� �Լ�
	bool BuyPotion(Potion potion);
	
};

