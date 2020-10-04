#pragma once
#include "StructHeroLibrary.h"
using namespace std;

// ���� : (string) �̸� / (int) �ִ� HP / (int) HP / (int) ȹ�� ����ġ / (int) ȹ�� ���
class Monster {
private:
	string name;
	int maxHP;
	int HP;
	int earnedExp;
	int earnedGold;

public:
	string GetName()	{ return name; }
	int GetHP()			{ return HP; }
	int GetMaxHP()		{ return maxHP; }
	int GetEarnedExp()	{ return earnedExp; }
	int GetEarnedGold() { return earnedGold; }

	void Damaged(int damage) { HP -= damage; }

	bool IsDead() { return HP <= 0; }

	void Init(string name, int maxHP, int HP, int earnedExp, int earnedGold);
};
