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
	int x, y;
};

// 타일 : (Vector2Int) 좌표 / (int) 타입 / (string) 모양
struct Tile {
	Vector2Int coord;
	int type;
	string shape;
};

// 주변 타일 구조체
struct AroundTiles {
	Tile** tiles;
	int size;
};

// 플레이어 : (string) 이름 / (int) 최대 HP / (int) HP / (int) 경험치 / (int) 레벨 / (int) 골드 / (Vector2Int) 좌표 
struct Hero
{
	string name;
	int maxHP;
	int HP;
	int exp;
	int level;
	int gold;
	Vector2Int coord;
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

// 상점 : (Potion*) 아이템 종류
struct Shop {
	Potion* potions;
};

/////////////////////////////////////////////////////////////////////
//
//	함수
//
/////////////////////////////////////////////////////////////////////

// 게임의 로고를 출력하는 함수
void PrintLogo()
{
	cout << "--------------------------------------" << endl;
	cout << "                                      " << endl;
	cout << "   영웅은 절차적 2 : 영웅은 구조적      " << endl;
	cout << "                                      " << endl;
	cout << "--------------------------------------" << endl;
}

// 메세지를 출력하는 함수
void PrintMSG(string msg)
{
	cout << " << " << msg << " >> " << endl;
}

AroundTiles GetAroundEightTiles(Tile** &map, Vector2Int coord, Vector2Int size)
{
	AroundTiles aroundtiles;
	if (coord.x == 0)
	{
		if (coord.y == 0)
		{
			aroundtiles.tiles = new Tile*[3];
			aroundtiles.tiles[0] = &map[coord.x + 1][coord.y + 1];
			aroundtiles.tiles[1] = &map[coord.x + 1][coord.y];
			aroundtiles.tiles[2] = &map[coord.x][coord.y + 1];
		}
		else if (coord.y == size.y - 1)
		{
			aroundtiles.tiles = new Tile*[3];
			aroundtiles.tiles[0] = &map[coord.x + 1][coord.y - 1];
			aroundtiles.tiles[1] = &map[coord.x + 1][coord.y];
			aroundtiles.tiles[2] = &map[coord.x][coord.y - 1];
		}
		else
		{
			aroundtiles.tiles = new Tile*[5];
			aroundtiles.tiles[0] = &map[coord.x + 1][coord.y - 1];
			aroundtiles.tiles[1] = &map[coord.x][coord.y - 1];
			aroundtiles.tiles[2] = &map[coord.x + 1][coord.y];
			aroundtiles.tiles[3] = &map[coord.x + 1][coord.y + 1];
			aroundtiles.tiles[4] = &map[coord.x][coord.y + 1];
		}
	}
	else if(coord.x == size.x - 1)
	{
		if (coord.y == 0)
		{
			aroundtiles.tiles = new Tile*[3];
			aroundtiles.tiles[0] = &map[coord.x - 1][coord.y + 1];
			aroundtiles.tiles[1] = &map[coord.x][coord.y + 1];
			aroundtiles.tiles[2] = &map[coord.x - 1][coord.y];
		}
		else if (coord.y == size.y - 1)
		{
			aroundtiles.tiles = new Tile*[3];
			aroundtiles.tiles[0] = &map[coord.x - 1][coord.y - 1];
			aroundtiles.tiles[1] = &map[coord.x][coord.y - 1];
			aroundtiles.tiles[2] = &map[coord.x - 1][coord.y];
		}
		else
		{
			aroundtiles.tiles = new Tile*[5];
			aroundtiles.tiles[0] = &map[coord.x - 1][coord.y + 1];
			aroundtiles.tiles[1] = &map[coord.x][coord.y + 1];
			aroundtiles.tiles[2] = &map[coord.x - 1][coord.y];
			aroundtiles.tiles[3] = &map[coord.x - 1][coord.y - 1];
			aroundtiles.tiles[4] = &map[coord.x][coord.y - 1];
		}
	}
	else 
	{
		if (coord.y == 0)
		{
			aroundtiles.tiles = new Tile*[5];
			aroundtiles.tiles[0] = &map[coord.x - 1][coord.y];
			aroundtiles.tiles[1] = &map[coord.x - 1][coord.y + 1];
			aroundtiles.tiles[2] = &map[coord.x][coord.y + 1];
			aroundtiles.tiles[3] = &map[coord.x + 1][coord.y + 1];
			aroundtiles.tiles[4] = &map[coord.x + 1][coord.y];

		}
		else if (coord.y == size.y - 1)
		{
			aroundtiles.tiles = new Tile*[5];
			aroundtiles.tiles[0] = &map[coord.x - 1][coord.y];
			aroundtiles.tiles[1] = &map[coord.x - 1][coord.y - 1];
			aroundtiles.tiles[2] = &map[coord.x][coord.y - 1];
			aroundtiles.tiles[3] = &map[coord.x + 1][coord.y - 1];
			aroundtiles.tiles[4] = &map[coord.x + 1][coord.y];
		}
		else
		{
			aroundtiles.tiles = new Tile*[8];
			aroundtiles.tiles[0] = &map[coord.x - 1][coord.y];
			aroundtiles.tiles[1] = &map[coord.x - 1][coord.y - 1];
			aroundtiles.tiles[2] = &map[coord.x][coord.y - 1];
			aroundtiles.tiles[3] = &map[coord.x + 1][coord.y - 1];
			aroundtiles.tiles[4] = &map[coord.x + 1][coord.y];
			aroundtiles.tiles[5] = &map[coord.x - 1][coord.y + 1];
			aroundtiles.tiles[6] = &map[coord.x][coord.y + 1];
			aroundtiles.tiles[7] = &map[coord.x + 1][coord.y + 1];
		}
	}
	aroundtiles.size = sizeof(aroundtiles.tiles) / sizeof(Tile*);
	cout << aroundtiles.size << endl;
	return aroundtiles;
}

// 주변 타일에 의해 타일이 결정되는 함수
void DecideTile(Tile** map, Vector2Int coord) {

}

// 맵을 생성하는 함수 (동적할당 사용)
void CreateMap(Tile** &map, Vector2Int size) 
{
	map = new Tile*[size.y];
	for (int i = 0; i < size.y; i++) 
	{
		map[i] = new Tile[size.x];
		for (int j = 0; j < size.y; j++)
		{
			//map[i][j].;
		}
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

// 난이도를 별문자열로 바꿔주는 함수
string DifficultyToStar(int difficulty)
{
	string stars = "";
	for (int i = 0; i < difficulty; i++)
		stars += "★";

	return stars;
}

/////////////////////////////////////////////////////////////////////
//
//	메인 함수
//
/////////////////////////////////////////////////////////////////////

int main()
{
	Tile Grass = { {}, 0, "▤" };
	Tile Mud = { {}, 1, "~~" };
	Tile Forest = { {}, 2, "♧" };

	// 변수 선언
	Hero hero;				// 용사 구조체
	Tile** map = nullptr;	// 타일 구조체
	Vector2Int mapSize;		// 맵의 크기
	int difficulty;			// 난이도
	int numOfMonster;		// 몬스터의 수

	// 로고 출력
	PrintLogo();

	// 용사 이름 설정
	PrintMSG("용사의 이름을 입력하세요");
	cin >> hero.name;
	
	// 맵의 크기 설정
	PrintMSG("맵의 크기를 지정해 주세요 ex) 10 10");
	cin >> mapSize.x >> mapSize.y;
	difficulty = SizeToDifficulty(mapSize);
	
	// 맵 생성 (동적할당)
	CreateMap(map, mapSize);

	// 게임 초기화
	hero.maxHP = hero.HP = 5 + difficulty / 2;
	hero.level = 1;
	hero.gold = 0;
	hero.exp = 0;

	numOfMonster = 10 + difficulty * difficulty;

	// 알림
	string msg = "맵의 크기 : " + to_string(mapSize.x) + 'x' + to_string(mapSize.y) + "\t난이도 : " + DifficultyToStar(difficulty);
	PrintMSG(msg);

	GetAroundEightTiles(map, {}, mapSize);
	
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