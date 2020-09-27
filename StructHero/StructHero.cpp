#include <iostream>
#include <string>
#include <ctime>
#include <conio.h>
using namespace std;

#define WALL	0
#define GRASS	1
#define MUD		2
#define FOREST	3

/*
/////////////////////////////////////////////////////////////////////
//
//	게임 설명
//
/////////////////////////////////////////////////////////////////////

순서도 먼저 그리자.
영웅은 절차적 2: 영웅은 구조적

가로*세로 사이즈 설정할 수 있도록 만들자. (동적할당)

맵 크기에 따라 난이도 변경
5*5 = 25 이하 난이도 1
10*10 = 100 이하 난이도 2
15 * 15 = 225 이하 난이도 3

WASD 이동

배열 / 구조체 / 함수를 최대한 활용해보자.

전투는 가위바위보

타일 : (Vector2Int) 좌표 / (int) 타입 / (char) 모양
타일에 종류가 있다(숲 늪 땅) 마다 만나는 몬스터도 다르다.

플레이어 : (string) 이름 / (int) 최대 HP / (int) HP / (int) 경험치 / (int) 레벨 / (int) 골드 / (Vector2Int) 좌표

포션 : (string) 이름 / (int) 가격 / (int) 회복치

몬스터 : (string) 이름 / (int) 최대 HP / (int) HP / (int) 획득 경험치 / (int) 획득 골드
몬스터는 포켓몬스터처럼 랜덤 인카운터 방식 (타일 이동시 확률 적용)

상점 : (Potion*) 아이템 종류
*/

/////////////////////////////////////////////////////////////////////
//
//	구조체
//
/////////////////////////////////////////////////////////////////////

// 2차원 int 구조체
struct Vector2Int
{
	int y, x;
};

// 타일 : (Vector2Int) 좌표 / (int) 타입 / (int) 인카운터 확률 / (bool) 통과가능여부 / (string) 모양
struct Tile {
	Vector2Int coord;
	int type;
	int encounterPercent;
	bool passable;
	string shape;
};

// 주변 타일 : 주변 타일을 저장하는 배열
struct AroundTiles {
	Tile* tiles[8];
};

// 플레이어 : (string) 이름 / (int) 최대 HP / (int) HP / (int) 경험치 / (int) 레벨 / (int) 골드 / (Vector2Int) 좌표 / (string) 모양
struct Hero
{
	string name;
	int maxHP;
	int HP;
	int exp;
	int level;
	int gold;
	Vector2Int coord;
	string shape;
};

// 포션 : (string) 이름 / (int) 가격 / (int) 회복치
struct Potion {
	string name;
	int price;
	int recoveryPoint;
};

// 몬스터 : (string) 이름 / (int) 최대 HP / (int) HP / (int) 획득 경험치 / (int) 획득 골드
struct Monster {
	string name;
	int MaxHP;
	int HP;
	int earnedExp;
	int earnedGold;
};

// 상점 : (Potion*) 아이템 종류 / (int) 아이템 개수 / (Vector2Int) 좌표 / (string) 지붕 모양 / (string) 모양
struct Shop {
	Potion* potions;
	int length;
	Vector2Int coord;
	string roofShape;
	string shape;
};

// 게임 세팅 : (int) 난이도 / (int) 몬스터의 수
struct GameSetting {
	int difficulty;			// 난이도
	int numOfMonster;		// 몬스터의 수
	int battleCount = 0;	// 전투 진행된 수
};
/////////////////////////////////////////////////////////////////////
//
//	전역 변수
//
/////////////////////////////////////////////////////////////////////

GameSetting gameSetting;	// 전역 변수::게임 세팅
Tile** map = nullptr;		// 전역 변수::타일 맵
Vector2Int mapSize;			// 전역 변수::맵의 크기
Hero hero;					// 전역 변수::용사

/////////////////////////////////////////////////////////////////////
//
//	함수
//
/////////////////////////////////////////////////////////////////////

// 범위 내에서 무작위 정수를 반환하는 함수
int RandomInRange(int start, int end)
{
	return rand() % (end - start + 1) + start;
}

// 문자와 입력된 길이의 문자열로 반환하는 함수
string IntToCharString(int num, string ch)
{
	string str = "";
	for (int i = 0; i < num; i++)
		str += ch;

	return str;
}

// 체력을 문자열로 반환하는 함수
string PrintHP(int HP, int maxHP)
{
	return IntToCharString(HP, "♥") + IntToCharString(maxHP - HP, "♡");
}

// 게임의 로고를 출력하는 함수
void PrintLogo()
{
	cout << "======================================" << endl;
	cout << "                                      " << endl;
	cout << "   영웅은 절차적 2 : 영웅은 구조적    " << endl;
	cout << "                                      " << endl;
	cout << "======================================" << endl;
}

// 게임 메세지를 출력하는 함수
void PrintMSG(string msg)
{
	cout << " << " << msg << " >> " << endl;
}

// 상단 바 출력하는 함수
void PrintTopbar() 
{
	printf("==================================================================\n");
	printf("체력\t=%s=\n", PrintHP(hero.HP, hero.maxHP).c_str());
	printf("[용사] %s\t레벨 : %d (%d / 100)\t골드 : %d\n", hero.name.c_str(), hero.level, hero.exp, hero.gold);
	printf("난이도 : %s\t남은 몬스터 수 : %d\n", IntToCharString(gameSetting.difficulty, "★").c_str(), gameSetting.numOfMonster);
	printf("==================================================================\n");
}

// 엔터를 입력받는 함수
void GetEnter()
{
	cout << endl << "넘어가려면 엔터를 누르세요" << endl;
	getchar(); 
	while (getchar() != '\n');
}

// 주변 타일을 받아오는 함수
bool GetAroundEightTiles(Vector2Int coord, AroundTiles &aroundTiles)
{
	if (coord.x == 0 || coord.y == 0 || coord.x == mapSize.x + 1 || coord.y == mapSize.y + 1)
		return false;

	aroundTiles.tiles[0] = &map[coord.y - 1][coord.x - 1];
	aroundTiles.tiles[1] = &map[coord.y - 1][coord.x];
	aroundTiles.tiles[2] = &map[coord.y - 1][coord.x + 1];
	aroundTiles.tiles[3] = &map[coord.y][coord.x - 1];
	aroundTiles.tiles[4] = &map[coord.y][coord.x + 1];
	aroundTiles.tiles[5] = &map[coord.y + 1][coord.x + 1];
	aroundTiles.tiles[6] = &map[coord.y + 1][coord.x];
	aroundTiles.tiles[7] = &map[coord.y + 1][coord.x - 1];
	
	return true;
}

// 타일을 랜덤으로 생성하는 함수
void PlaceTile(Tile origin, Vector2Int coord, int power)
{
	Tile &currentTile = map[coord.y][coord.x];
	if (currentTile.type != origin.type && currentTile.type != WALL && power >= RandomInRange(0, 100))
	{
		currentTile.encounterPercent = origin.encounterPercent;
		currentTile.shape = origin.shape;
		currentTile.type = origin.type;
		
		for (int i = 0; i < 8; i++)
		{
			AroundTiles aroundTiles;
			if (GetAroundEightTiles(coord, aroundTiles))
			{
				PlaceTile(origin, aroundTiles.tiles[i]->coord, power - 30);
			}
		}
		
	}
	else
		return;
}

// 맵의 타일을 결정해주는 함수
Tile DecideTile(Vector2Int coord) 
{
	Tile Wall =		{ {}, WALL	, 0		, false	, "  " };
	Tile Grass =	{ {}, GRASS	, 10	, true	, "≡" };
	Tile Mud =		{ {}, MUD	, 30	, true	, "~~" };
	Tile Forest =	{ {}, FOREST, 20	, true	, "♧" };
	Tile newTile;
	if (coord.x == 0 || coord.y == 0 || coord.x == mapSize.x + 1 || coord.y == mapSize.y + 1)
	{
		newTile = Wall;
	}
	else 
	{
		newTile = Grass;
	}
	
	newTile.coord = coord;

	return newTile;
}

// 맵을 생성하는 함수 (동적할당 사용)
void CreateMap() 
{
	srand(time(NULL));
	int mudSeed = gameSetting.difficulty - 1;
	int forestSeed = gameSetting.difficulty - 1;
	map = new Tile*[mapSize.y + 2];
	for (int y = 0; y < mapSize.y + 2; y++)
	{
		map[y] = new Tile[mapSize.x + 2];
		for (int x = 0; x < mapSize.x + 2; x++)
		{
			map[y][x] = DecideTile({ y, x });
		}
	}
	Tile Mud = { {}, MUD, 30, true, "~~" };
	Tile Forest = { {}, FOREST, 20, true, "♧" };
	Vector2Int coord;
	while (mudSeed > 0)
	{
		coord.x = RandomInRange(1, mapSize.x);
		coord.y = RandomInRange(1, mapSize.y);
		cout << "mudSeed" << mudSeed << endl;
		PlaceTile(Mud, coord, 100 + mudSeed * 20);
		mudSeed--;
		
	}
	while (forestSeed > 0)
	{
		coord.x = RandomInRange(1, mapSize.x);
		coord.y = RandomInRange(1, mapSize.y);
		cout << "forestSeed" << forestSeed << endl;
		PlaceTile(Forest, coord, 100 + forestSeed * 20);
		forestSeed--;
		
	}
}

// 맵을 출력하는 함수
void PrintMap(Shop shop)
{
	for (int y = 0; y < mapSize.y + 1; y++)
	{
		for (int x = 0; x < mapSize.x + 1; x++)
		{
			if (shop.coord.x == x && shop.coord.y - 1 == y)
				printf("%2s", shop.roofShape.c_str());
			else if(shop.coord.x == x && shop.coord.y == y)
				printf("%2s", shop.shape.c_str());
			else if (hero.coord.x == x && hero.coord.y == y)
				printf("%2s", hero.shape.c_str());
			else
				printf("%2s", map[y][x].shape.c_str());
		}
		cout << endl;
	}
}

// 맵을 삭제하는 함수 (동적할당 해제)
void DeleteMap()
{
	for (int i = 0; i < mapSize.y; i++)
		delete[] map[i];
	delete[] map;
}

// 맵 크기에 따른 난이도 설정 함수
int SizeToDifficulty()
{
	int area = mapSize.x * mapSize.y;

	int difficulty = 1;
	while (area > pow(5 * difficulty, 2))
		difficulty++;

	return difficulty;
}

void HeroLevelup() 
{
	hero.level++;
	hero.exp -= 100;
	hero.HP = ++hero.maxHP;
}

// 용사의 움직임 함수
int HeroMove(char input)
{
	int noise = RandomInRange(1, 100);
	switch (input)
	{
	case 'w': case 'W':
		if (hero.coord.y > 1)
			hero.coord.y--;
		else
			noise = 0;
		break;
	case 'a': case 'A':
		if (hero.coord.x > 1)
			hero.coord.x--;
		else
			noise = 0;
		break;
	case 's': case 'S':
		if (hero.coord.y < mapSize.y)
			hero.coord.y++;
		else
			noise = 0;
		break;
	case 'd': case 'D':
		if (hero.coord.x < mapSize.x)
			hero.coord.x++;
		else
			noise = 0;
		break;
	default:
		noise = 0;
		break;
	}
	return noise;
}

// 상점 초기화 함수
void InitShop(Shop &shop)
{
	shop.length = 4;
	shop.potions = new Potion[shop.length];
	shop.potions[0] = { "힐링포션", 50, 1 };
	shop.potions[1] = { "대량의 힐링포션", 100, 3 };
	shop.potions[2] = { "활력포션", 150, 5 };
	shop.potions[3] = { "대량의 활력포션", 200, 7 };
	shop.roofShape = "△";
	shop.shape = "▣";
	shop.coord.x = RandomInRange(1, mapSize.x);
	shop.coord.y = RandomInRange(1, mapSize.y);
	map[shop.coord.y][shop.coord.x].passable = false;
}

// 상점 UI 출력 함수
void PrintShopUI(Shop &shop)
{
	cout << "┌" << IntToCharString(shop.length * 18 - 1, "─") << "┐" << endl;
	for (int i = 0; i < 3; i++)
	{
		cout << "│";
		for (int j = 0; j < shop.length; j++)
		{
			switch (i)
			{
			case 0:
				printf("%16s │", shop.potions[j].name.c_str());
				break;
			case 1:
				printf("%11d Gold │", shop.potions[j].price);
				break;
			case 2:
				printf("%16s │",  IntToCharString(shop.potions[j].recoveryPoint, "♥").c_str());
				break;
			default:
				break;
			}
			
		}
		cout << endl;
	}
	cout << "└" << IntToCharString(shop.length * 18 - 1, "─") << "┘" << endl;

	for (int i = 0; i < shop.length; i++)
	{
		printf("(%d) %s 구매\n", i + 1, shop.potions[i].name.c_str());
	}
	cout << "(" << shop.length + 1 << ") 나가기" << endl;
}

// 상점 포션 구매 함수
bool BuyPotion(Shop shop, int index)
{
	Potion potion = shop.potions[index];
	if (hero.gold >= potion.price)
	{
		hero.gold -= potion.price;
		hero.HP += potion.recoveryPoint;
		if (hero.HP > hero.maxHP)
			hero.HP = hero.maxHP;

		return true;
	}
	else 
		return false;
}

// 상점의 처리 함수
void ShopProcess(Shop &shop) 
{
	int shopAct;
	bool msg1 = false, msg2 = false;

	while (true)
	{
		system("cls");
		PrintTopbar();
		PrintShopUI(shop);
		if (msg1) 
		{
			cout << "<체력을 " << shop.potions[shopAct - 1].recoveryPoint << " 회복했습니다>" << endl;
			msg1 = false;
		}
		else if (msg2)
		{
			cout << "<골드가 부족합니다>" << endl;
			msg2 = false;
		}
			
		cin >> shopAct;
		if (cin.fail() || shopAct < 1 || shopAct - 1 > shop.length)
		{
			cin.clear();
			cin.ignore(256, '\n');
			continue;
		}
		if (shopAct - 1 == shop.length)
			break;

		if (BuyPotion(shop, shopAct - 1))
			msg1 = true;
		else
			msg2 = true;
	}
}

// 몬스터 상태 출력 함수
void PrintMonster(Monster &monster) {
	printf("==================================================================\n");
	printf("체력\t=%s=\n", PrintHP(monster.HP, monster.MaxHP).c_str());
	printf("[몬스터] %s\n", monster.name.c_str());
	printf("==================================================================\n");
}

// 전투 처리 함수
void BattleProcess(Tile tile){
	int battleAct;
	int monAttack;
	Monster monster;
	bool winMSG = false, defeatMSG = false, drawMSG = false;
	srand(time(NULL));
	gameSetting.battleCount++;

	switch (tile.type)
	{
	case GRASS:
		monster = { "고블린", 2, 2, 20, 40 };
		break;
	case FOREST:
		monster = { "늑대", 5, 5, 70, 15 };
		break;
	case MUD:
		monster = { "슬라임", 3, 3, 35, 35 };
		break;
	}
	PrintMSG(monster.name + "이(가) 출현하였다! 전투 개시!");
	GetEnter();
	
	while (true)
	{
		system("cls");
		PrintTopbar();
		PrintMonster(monster);
		if (winMSG)
		{
			PrintMSG(hero.name + "의 공격! 몬스터의 HP 1 감소!");
			winMSG = false;
		}
		else if (defeatMSG)
		{
			PrintMSG(monster.name + "의 공격! HP 1 감소!");
			defeatMSG = false;
		}
		else if(drawMSG)
		{
			PrintMSG("서로의 공격이 빗겨 나갔다!");
			drawMSG = false;
		}

		// 몬스터 사망 검사
		if (monster.HP <= 0)
		{
			gameSetting.numOfMonster--;
			hero.exp += monster.earnedExp;
				
			hero.gold += monster.earnedGold;
			cout << " << " << monster.name << "이(가) 쓰러졌다! >>" << endl;
			cout << " << 경험치 " << monster.earnedExp << "증가! >>" << endl;
			if (hero.exp >= 100)
			{
				HeroLevelup();
				cout << " << " << hero.name << "용사의 레벨이 " << hero.level << "이(가) 되었다! >>" << endl;
				PrintMSG("체력이 모두 회복되었다!");
				PrintMSG("최대 체력이 1 증가했다!");
			}
			cout << " << " << monster.earnedGold << "골드 획득! >>" << endl;
			GetEnter();
			break;
		}
		// 용사 사망 검사
		else if(hero.HP <= 0)
		{
			GetEnter();
			break;
		}

		cout << "<공격 선택> 1(가위), 2(바위), 3(보) : ";
		cin >> battleAct;
		if (battleAct > 3 || battleAct < 1 || cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
			continue;
		}

		monAttack = rand() % 3;

		int offset = battleAct - 1  - monAttack;
		switch (offset)
		{
		// 무승부 처리
		case 0:
			drawMSG = true;
			break;
		// 승리 처리
		case 1: case -2:
			monster.HP--;
			winMSG = true;
			break;
		// 패배 처리
		case -1: case 2:
			hero.HP--;
			defeatMSG = true;
			break;
		}
	}
}

// 타일의 처리를 하는 함수
void TileProcess(Tile tile, int noise, char heroAct, Shop shop)
{
	// 타일에 상점이 있을 때
	if (shop.coord.x == tile.coord.x && shop.coord.y == tile.coord.y)
	{
		// 상점 처리
		ShopProcess(shop);
	}
	else 
	{
		// 인카운터 계산후 전투 처리
		if (100 - tile.encounterPercent < noise)
		{
			BattleProcess(tile);
		}
		
	}

	// 이동할 수 없는 타일은 밀려남
	if (!tile.passable)
	{
		switch (heroAct)
		{
		case 'w': case 'W':
			hero.coord.y++;
			break;
		case 'a': case 'A':
			hero.coord.x++;
			break;
		case 's': case 'S':
			hero.coord.y--;
			break;
		case 'd': case 'D':
			hero.coord.x--;
			break;
		}
	}
}

void GameEnd() 
{
	cout << "===========================================================" << endl;
	cout << "당신은 게임에서 ";
	if (hero.HP <= 0)
		cout << "패배했습니다." << endl << "패배한 난이도 : ";
	else
		cout << "승리했습니다!" << endl << "클리어 난이도 : ";
	cout << IntToCharString(gameSetting.difficulty, "★") << endl;
	cout << endl;
	cout << "전투한 턴수 : " << gameSetting.battleCount << endl;
	cout << "소지 골드 : " << hero.gold << endl;
	cout << "===========================================================" << endl;
}

/////////////////////////////////////////////////////////////////////
//
//	메인 함수
//
/////////////////////////////////////////////////////////////////////

int main()
{
	// 변수 선언
	Shop shop;		// 상점
	
	// 로고 출력
	PrintLogo();

	// 용사 이름 설정
	PrintMSG("용사의 이름을 입력하세요");
	cin >> hero.name;
	hero.shape = hero.name.substr(0, 2);

	// 맵의 크기 설정
	do {
		cin.clear();
		cin.ignore(256, '\n');
		PrintMSG("맵의 크기를 지정해 주세요 ex) 10 10");
		cin >> mapSize.x >> mapSize.y;
	} while (cin.fail() || mapSize.x < 2 || mapSize.y < 2);
	
	// 게임 초기화
	srand(time(NULL));
	
	gameSetting.difficulty = SizeToDifficulty();
	gameSetting.numOfMonster = 5 + gameSetting.difficulty * gameSetting.difficulty;

	// 맵 생성 (동적할당)
	CreateMap();

	// 상점 초기화
	InitShop(shop);

	// 영웅 초기화
	hero.maxHP = hero.HP = 6 + gameSetting.difficulty;
	hero.level = 1;
	hero.gold = 0;
	hero.exp = 0;
	hero.coord.x = RandomInRange(1, mapSize.x);
	hero.coord.y = RandomInRange(1, mapSize.y);
	
	while (true) 
	{
		system("cls");
		PrintTopbar();
		PrintMap(shop);
		if (hero.HP <= 0 || gameSetting.numOfMonster == 0)
		{
			GameEnd();
			GetEnter();
			break;
		}
		char heroAct = _getch();
		int noise = HeroMove(heroAct);
		TileProcess(map[hero.coord.y][hero.coord.x], noise, heroAct, shop);
	}

	// 상점 삭제 (동적할당 해제
	delete[] shop.potions;

	// 맵 삭제 (동적할당 해제)
	DeleteMap();

	return 0;
}
