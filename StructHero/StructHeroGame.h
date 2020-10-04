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
	Shop shop;			// 상점
	Hero hero;			// 용사
	Map	map;			// 맵
	int difficulty;			// 난이도
	int numOfMonster;		// 몬스터의 수
	int battleCount = 0;	// 전투 진행된 수
	
public:

	// Setter
	void SetDifficulty(int difficulty) { this->difficulty = difficulty; }

	bool IsOver() { return hero.IsDead() || numOfMonster == 0; }

	// 맵 크기에 따른 난이도 설정 함수
	static int SizeToDifficulty(Vector2Int size);

	// 게임의 로고를 출력하는 함수
	void PrintLogo();

	// 용사의 이름을 입력받는 함수
	void InputHeroName();

	// 맵의 크기를 입력받는 함수
	void InputMapSize();

	// 상점을 배치하는 함수
	void PlaceShop(Vector2Int coord);

	// 게임을 초기화 하는 함수
	void Init();

	// 몬스터 상태 출력 함수
	void PrintMonster(Monster& monster);

	// 체력을 문자열로 반환하는 함수
	string PrintHP(int HP, int maxHP);

	// 게임 메세지를 출력하는 함수
	void PrintMSG(string msg);
	
	// 상단 바 출력하는 함수
	void PrintTopbar();
	
	// 맵을 출력하는 함수
	void PrintMap();
	
	// 상점 UI 출력 함수
	void PrintShopUI();

	// 상점의 처리 함수
	void ShopProcess();

	// 전투 처리 함수
	void BattleProcess(Tile tile); 

	// 타일의 처리를 하는 함수
	void TileProcess(Tile tile, int noise, char heroAct);

	// 플레이어의 입력을 받아 처리하는 함수
	void InputProcess();
	
	// 게임 종료 메세지를 출력하는 함수
	void PrintGameEnd();
};
