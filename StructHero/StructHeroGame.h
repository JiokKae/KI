#pragma once
#include <conio.h>
#include "StructHeroLibrary.h"
#include "Shop.h"
#include "Hero.h"
#include "Map.h"
#include "Monster.h"
using namespace std;

class StructHeroGame
{
private:
	Shop shop;			// ����
	Hero hero;			// ���
	Map	map;			// ��
	int difficulty;			// ���̵�
	int numOfMonster;		// ������ ��
	int battleCount = 0;	// ���� ����� ��
	
public:

	// Setter
	void SetDifficulty(int difficulty) { this->difficulty = difficulty; }

	bool IsOver() { return hero.IsDead() || numOfMonster == 0; }

	// �� ũ�⿡ ���� ���̵� ���� �Լ�
	static int SizeToDifficulty(Vector2Int size);

	// ������ �ΰ� ����ϴ� �Լ�
	void PrintLogo();

	// ����� �̸��� �Է¹޴� �Լ�
	void InputHeroName();

	// ���� ũ�⸦ �Է¹޴� �Լ�
	void InputMapSize();

	// ������ ��ġ�ϴ� �Լ�
	void PlaceShop(Vector2Int coord);

	// ������ �ʱ�ȭ �ϴ� �Լ�
	void Init();

	// ���� ���� ��� �Լ�
	void PrintMonster(Monster& monster);

	// ü���� ���ڿ��� ��ȯ�ϴ� �Լ�
	string PrintHP(int HP, int maxHP);

	// ���� �޼����� ����ϴ� �Լ�
	void PrintMSG(string msg);
	
	// ��� �� ����ϴ� �Լ�
	void PrintTopbar();
	
	// ���� ����ϴ� �Լ�
	void PrintMap();
	
	// ���� UI ��� �Լ�
	void PrintShopUI();

	// ������ ó�� �Լ�
	void ShopProcess();

	// ���� ó�� �Լ�
	void BattleProcess(Tile tile); 

	// Ÿ���� ó���� �ϴ� �Լ�
	void TileProcess(Tile tile, int noise, char heroAct);

	// �÷��̾��� �Է��� �޾� ó���ϴ� �Լ�
	void InputProcess();
	
	// ���� ���� �޼����� ����ϴ� �Լ�
	void PrintGameEnd();
};
