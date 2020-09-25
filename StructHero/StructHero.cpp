#include <iostream>
#include <string>
#include <ctime>
#include <conio.h>
using namespace std;

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

// 상점 : (Potion*) 아이템 종류 / (Vector2Int) 좌표 / (string) 지붕 모양 / (string) 모양
struct Shop {
	Potion* potions;
	Vector2Int coord;
	string roofShape;
	string shape;
};

// 게임 세팅 : (int) 난이도 / (int) 몬스터의 수
struct GameSetting {
	int difficulty;		// 난이도
	int numOfMonster;	// 몬스터의 수
};
/////////////////////////////////////////////////////////////////////
//
//	전역 변수
//
/////////////////////////////////////////////////////////////////////

GameSetting gameSetting;	// 전역 변수::게임 세팅
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

// 문자와 입력된 길이의 문자열로 반환하는 함수
string IntToCharSting(int num, string ch2, string ch1) {
	string str = "";
	for (int i = 0; i < num - 1; i+=2)
		str += ch2;
	if (num % 2 == 1)
		str += ch1;
	return str;
}

// 게임의 로고를 출력하는 함수
void PrintLogo()
{
	cout << "--------------------------------------" << endl;
	cout << "                                      " << endl;
	cout << "   영웅은 절차적 2 : 영웅은 구조적      " << endl;
	cout << "                                      " << endl;
	cout << "--------------------------------------" << endl;
}

// 게임 메세지를 출력하는 함수
void PrintMSG(string msg)
{
	cout << " << " << msg << " >> " << endl;
}

// 상단 바 출력하는 함수
void PrintTopbar() 
{
	printf("===================================================\n");
	printf("%s 용사\t레벨 : %d\t골드 : %d\n", hero.name.c_str(), hero.level, hero.gold);
	printf("난이도 : %s\t남은 몬스터 수 : %d\n", IntToCharString(gameSetting.difficulty, "★").c_str(), gameSetting.numOfMonster);
	printf("===================================================\n");
}

// 주변 타일을 받아오는 함수
Tile** GetAroundEightTiles(Tile** &map, Vector2Int coord, Vector2Int size)
{
	Tile* aroundTiles[8];
	if (coord.x == 0 || coord.y == 0 || coord.x == size.x + 1 || size.y + 1)
		return nullptr;

	aroundTiles[0] = &map[coord.x - 1][coord.y - 1];
	aroundTiles[1] = &map[coord.x - 1][coord.y];
	aroundTiles[2] = &map[coord.x - 1][coord.y + 1];
	aroundTiles[3] = &map[coord.x][coord.y - 1];
	aroundTiles[4] = &map[coord.x][coord.y + 1];
	aroundTiles[5] = &map[coord.x + 1][coord.y + 1];
	aroundTiles[6] = &map[coord.x + 1][coord.y];
	aroundTiles[7] = &map[coord.x + 1][coord.y - 1];
	
	return aroundTiles;
}

// 맵의 타일을 결정해주는 함수
Tile DecideTile(Tile** map, Vector2Int coord, Vector2Int mapSize, int power) 
{
	Tile Wall = { {}, 0, 0, true, "  " };
	Tile Grass = { {}, 1, 10, true, "▤" };
	Tile Mud = { {}, 2, 30,true, "~~" };
	Tile Forest = { {}, 3, 20, true, "♧" };
	Tile newTile = Grass;
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
void CreateMap(Tile** &map, Vector2Int size) 
{
	map = new Tile*[size.y + 2];
	for (int y = 0; y < size.y + 2; y++) 
	{
		map[y] = new Tile[size.x + 2];
		for (int x = 0; x < size.x + 2; x++)
		{
			map[y][x] = DecideTile(map, { y, x }, size, 0);
		}
	}
}

// 맵을 출력하는 함수
void PrintMap(Tile** map, Vector2Int size, Shop shop)
{
	for (int y = 0; y < size.y + 1; y++)
	{
		for (int x = 0; x < size.x + 1; x++)
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
void DeleteMap(Tile** map, Vector2Int size)
{
	for (int i = 0; i < size.y; i++)
		delete[] map[i];
	delete[] map;
}

// 맵 크기에 따른 난이도 설정 함수
int SizeToDifficulty(Vector2Int size)
{
	int area = size.x * size.y;
	if (area <= 25)
		return 1;
	else if (area <= 100)
		return 2;
	else
		return 3;
}

// 용사의 움직임 함수
int HeroMove(char input, Vector2Int mapSize)
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

void PrintShopUI()
{
	cout << "-----------------------------------------------------------" << endl;
	cout << " 용사의 HP : " << hero.HP << "/" << hero.maxHP << endl;
	cout << "(1) 3HP 회복 100Gold (2) 완전 회복 250Gold (3) 나가기" << endl;
	cout << "-----------------------------------------------------------" << endl;
}

// 상점의 처리 함수
void ShopProcess() 
{
	int shopAct;
	bool outShop = false;
	while (!outShop)
	{
		PrintTopbar();
		PrintShopUI();
		cin >> shopAct;
		switch (shopAct)
		{
		case 1:
			if (hero.gold > 100)
			{
				hero.gold -= 100;
				hero.HP += 3;
				if (hero.HP > hero.maxHP)
					hero.HP = hero.maxHP;
				cout << "<체력을 3 회복했습니다>" << endl << endl;
			}
			else
				cout << "<골드가 부족합니다>" << endl << endl;
			break;

		case 2:
			if (hero.gold > 250)
			{
				hero.gold -= 250;
				hero.HP = hero.maxHP;
				cout << "<체력을 전부 회복했습니다>" << endl << endl;
			}
			else
				cout << "<골드가 부족합니다>" << endl << endl;
			break;

		case 3:
			outShop = true;
			break;
		default:
			//cout << "잘못된 입력" << endl;
			break;
		}
	}
}

void BattleProcess(){
	cout << "전투처리";
}

// 타일의 처리를 하는 함수
void TileProcess(Tile tile, int noise, char heroAct, Shop shop)
{
	// 타일에 상점이 있을 때
	if (shop.coord.x == tile.coord.x && shop.coord.y == tile.coord.y)
	{
		// 상점 처리
		ShopProcess();
	}
	else 
	{
		// 인카운터 계산후 전투 처리
		if (100 - tile.encounterPercent < noise)
		{
			BattleProcess();
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
/////////////////////////////////////////////////////////////////////
//
//	메인 함수
//
/////////////////////////////////////////////////////////////////////

int main()
{
	// 변수 선언
	Tile** map = nullptr;	// 타일 구조체
	Vector2Int mapSize;		// 맵의 크기
	
	Shop shop;				// 상점

	// 로고 출력
	PrintLogo();

	// 용사 이름 설정
	PrintMSG("용사의 이름을 입력하세요");
	cin >> hero.name;
	hero.shape = hero.name.substr(0, 2);
	
	// 맵의 크기 설정
	PrintMSG("맵의 크기를 지정해 주세요 ex) 10 10");
	cin >> mapSize.x >> mapSize.y;
	gameSetting.difficulty = SizeToDifficulty(mapSize);
	
	// 맵 생성 (동적할당)
	CreateMap(map, mapSize);

	// 게임 초기화
	srand(time(NULL));
	hero.maxHP = hero.HP = 5 + gameSetting.difficulty / 2;
	hero.level = 1;
	hero.gold = 0;
	hero.exp = 0;
	hero.coord.x = RandomInRange(1, mapSize.x);
	hero.coord.y = RandomInRange(1, mapSize.y);
	shop.roofShape = "△";
	shop.shape = "▣";
	shop.coord.x = RandomInRange(1, mapSize.x);
	shop.coord.y = RandomInRange(1, mapSize.x);
	map[shop.coord.y][shop.coord.x].passable = false;


	gameSetting.numOfMonster = 10 + gameSetting.difficulty * gameSetting.difficulty;

	// 알림
	string msg = "맵의 크기 : " + to_string(mapSize.x) + 'x' + to_string(mapSize.y) + "\t난이도 : " + IntToCharString(gameSetting.difficulty, "★");
	PrintMSG(msg);

	

	while (true) 
	{
		system("cls");
		PrintTopbar();
		PrintMap(map, mapSize, shop);
		char heroAct = _getch();
		int noise = HeroMove(heroAct, mapSize);
		TileProcess(map[hero.coord.y][hero.coord.x], noise, heroAct, shop);
	}

	// 맵 삭제 (동적할당 해제)
	DeleteMap(map, mapSize);

	return 0;
}

/////////////////////////////////////////////////////////////////////
//
//	자료 구조
//
/////////////////////////////////////////////////////////////////////

struct Data {
	Tile* tileRef;
};

struct Node {
	Data data;
	Node* next = nullptr;
};

struct LinkedList
{
	Node* head = nullptr;
	int size = 0;

	Node* CreateNode(Data data)
	{
		Node* newNode = new Node;
		newNode->data = data;
		newNode->next = nullptr;
		return newNode;
	}

	void InsertNode(Data data)
	{
		if (head == nullptr)
		{

		}
	}
};