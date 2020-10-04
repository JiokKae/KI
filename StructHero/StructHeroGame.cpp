#include "StructHeroGame.h"

void StructHeroGame::PrintLogo()
{
	cout << "======================================" << endl;
	cout << "                                      " << endl;
	cout << "   영웅은 절차적 2 : 영웅은 구조적    " << endl;
	cout << "                                      " << endl;
	cout << "======================================" << endl;
}

void StructHeroGame::InputHeroName()
{
	string newName;

	PrintMSG("용사의 이름을 입력하세요");
	cin >> newName;
	hero.SetName(newName);
}

void StructHeroGame::InputMapSize() {
	Vector2Int newMapSize;

	do {
		cin.clear();
		cin.ignore(256, '\n');

		PrintMSG("맵의 크기를 지정해 주세요 ex) 10 10");
		cin >> newMapSize.x >> newMapSize.y;
	} while (cin.fail() || newMapSize.x < 2 || newMapSize.y < 2);

	map.SetSize(newMapSize);
}

void StructHeroGame::PlaceShop(Vector2Int coord)
{
	shop.SetCoord(coord);
	//RandomInRange(1, mapSize.x)

	map.GetTileRef(coord.y, coord.x).passable = false;
}

void StructHeroGame::Init()
{
	srand((unsigned int)time(NULL));

	difficulty = SizeToDifficulty(map.GetSize());
	numOfMonster = 3 + difficulty * difficulty;

	// 맵 생성 (동적할당)
	map.CreateMap(difficulty);

	// 상점 초기화
	shop.Init();

	Tile shopTile;
	do { shopTile = map.GetRandomTile(); } while (shopTile.passable != true);
	
	PlaceShop(shopTile.coord);

	// 영웅 초기화
	hero.Init(difficulty);

	Tile heroTile;
	do { heroTile = map.GetRandomTile(); } while (heroTile.passable != true);
	hero.SetCoord(heroTile.coord);
}

void StructHeroGame::PrintTopbar()
{
	printf("==================================================================\n");
	printf("체력\t=%s=\n", PrintHP(hero.GetHP(), hero.GetMaxHP()).c_str());
	printf("[용사] %s\t레벨 : %d (%d / %d)\t골드 : %d\n", hero.GetName().c_str(), hero.GetLevel(), hero.GetExp(), hero.GetMaxExp(), hero.GetGold());
	printf("난이도 : %s\t남은 몬스터 수 : %d\n", IntToCharString(difficulty, "★").c_str(), numOfMonster);
	printf("==================================================================\n");
}

void StructHeroGame::PrintMap()
{
	for (int y = 0; y < map.GetSize().y + 1; y++)
	{
		for (int x = 0; x < map.GetSize().x + 1; x++)
		{
			if (shop.GetCoord().x == x && shop.GetCoord().y - 1 == y)
				printf("%2s", shop.GetRoofShape().c_str());
			else if (shop.GetCoord().x == x && shop.GetCoord().y == y)
				printf("%2s", shop.GetShape().c_str());
			else if (hero.GetCoord().x == x && hero.GetCoord().y == y)
				printf("%2s", hero.GetShape().c_str());
			else
				printf("%2s", map.GetTile(y, x).shape.c_str());
		}
		cout << endl;
	}
}

void StructHeroGame::PrintShopUI() {
	cout << "┌" << IntToCharString(shop.GetLength() * 18 - 1, "─") << "┐" << endl;
	for (int i = 0; i < 3; i++)
	{
		cout << "│";
		for (int j = 0; j < shop.GetLength(); j++)
		{
			Potion potion = shop.GetPotion(j);
			switch (i)
			{
			case 0:
				printf("%16s │", potion.name.c_str());
				break;
			case 1:
				printf("%11d Gold │", potion.price);
				break;
			case 2:
				printf("%16s │", IntToCharString(potion.recoveryPoint, "♥").c_str());
				break;
			default:
				break;
			}

		}
		cout << endl;
	}
	cout << "└" << IntToCharString(shop.GetLength() * 18 - 1, "─") << "┘" << endl;

	for (int i = 0; i < shop.GetLength(); i++)
	{
		printf("(%d) %s 구매\n", i + 1, shop.GetPotion(i).name.c_str());
	}
	cout << "(" << shop.GetLength() + 1 << ") 나가기" << endl;
}

void StructHeroGame::ShopProcess()
{
	int shopAct;
	bool msg1 = false, msg2 = false;

	while (true)
	{
		system("cls");
		PrintTopbar();
		PrintShopUI();
		if (msg1)
		{
			cout << "<체력을 " << shop.GetPotion(shopAct - 1).recoveryPoint << " 회복했습니다>" << endl;
			msg1 = false;
		}
		else if (msg2)
		{
			cout << "<골드가 부족합니다>" << endl;
			msg2 = false;
		}

		cin >> shopAct;
		if (cin.fail() || shopAct < 1 || shopAct - 1 > shop.GetLength())
		{
			cin.clear();
			cin.ignore(256, '\n');
			continue;
		}
		if (shopAct - 1 == shop.GetLength())
			break;

		if (hero.BuyPotion(shop.GetPotion(shopAct - 1)))
			msg1 = true;
		else
			msg2 = true;
	}
}

void StructHeroGame::BattleProcess(Tile tile)
{
	int battleAct;
	int monAttack;
	Monster monster;
	bool winMSG = false, defeatMSG = false, drawMSG = false;
	srand((unsigned int)time(NULL));
	battleCount++;

	switch (tile.type)
	{
	case GRASS:
		monster.Init( "고블린", 2, 2, 20, 40 );
		break;
	case FOREST:
		monster.Init( "늑대", 5, 5, 65, 20 );
		break;
	case MUD:
		monster.Init( "슬라임", 3, 3, 35, 35 );
		break;
	}
	PrintMSG(monster.GetName() + "이(가) 출현하였다! 전투 개시!");
	GetEnter();

	while (true)
	{
		system("cls");
		PrintTopbar();
		PrintMonster(monster);
		if (winMSG)
		{
			PrintMSG(hero.GetName() + "의 공격! 몬스터의 HP 1 감소!");
			winMSG = false;
		}
		else if (defeatMSG)
		{
			PrintMSG(monster.GetName() + "의 공격! HP 1 감소!");
			defeatMSG = false;
		}
		else if (drawMSG)
		{
			PrintMSG("서로의 공격이 빗겨 나갔다!");
			drawMSG = false;
		}

		// 몬스터 사망 검사
		if (monster.IsDead())
		{
			numOfMonster--;
			hero.AddExp(monster.GetEarnedExp());
			hero.AddGold(monster.GetEarnedGold());
			cout << " << " << monster.GetName() << "이(가) 쓰러졌다! >>" << endl;
			cout << " << 경험치 " << monster.GetEarnedExp() << "증가! >>" << endl;
			if (hero.GetExp() >= hero.GetMaxExp())
			{
				hero.Levelup();
				cout << " << " << hero.GetName() << "용사의 레벨이 " << hero.GetLevel() << "이(가) 되었다! >>" << endl;
				PrintMSG("체력이 모두 회복되었다!");
				PrintMSG("최대 체력이 1 증가했다!");
			}
			cout << " << " << monster.GetEarnedGold() << "골드 획득! >>" << endl;
			GetEnter();
			break;
		}
		// 용사 사망 검사
		else if (hero.IsDead())
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

		int offset = battleAct - 1 - monAttack;
		switch (offset)
		{
			// 무승부 처리
		case 0:
			drawMSG = true;
			break;
			// 승리 처리
		case 1: case -2:
			monster.Damaged(1);
			winMSG = true;
			break;
			// 패배 처리
		case -1: case 2:
			hero.Damaged(1);
			defeatMSG = true;
			break;
		}
	}
}

void StructHeroGame::PrintMonster(Monster& monster)
{
	printf("==================================================================\n");
	printf("체력\t=%s=\n", PrintHP(monster.GetHP(), monster.GetMaxHP()).c_str());
	printf("[몬스터] %s\n", monster.GetName().c_str());
	printf("==================================================================\n");
}

string StructHeroGame::PrintHP(int HP, int maxHP)
{
	return IntToCharString(HP, "♥") + IntToCharString(maxHP - HP, "♡");
}

void StructHeroGame::PrintMSG(string msg)
{
	cout << " << " << msg << " >> " << endl;
}

void StructHeroGame::TileProcess(Tile tile, int noise, char heroAct)
{
	// 타일에 상점이 있을 때
	if (shop.GetCoord().x == tile.coord.x && shop.GetCoord().y == tile.coord.y)
	{
		// 상점 처리
		ShopProcess();
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
		hero.MoveBack(heroAct);
	}
}

void StructHeroGame::InputProcess()
{
	char heroAct = _getch();
	int noise = hero.Move(heroAct, map.GetSize());
	TileProcess(map.GetTile(hero.GetCoord().y, hero.GetCoord().x), noise, heroAct);
}


void StructHeroGame::PrintGameEnd()
{
	cout << "===========================================================" << endl;
	cout << "당신은 게임에서 ";
	if (hero.IsDead())
		cout << "패배했습니다." << endl << "패배한 난이도 : ";
	else
		cout << "승리했습니다!" << endl << "클리어 난이도 : ";
	cout << IntToCharString(difficulty, "★") << endl;
	cout << endl;
	cout << "전투한 턴수 : " << battleCount << endl;
	cout << "소지 골드 : " << hero.GetGold() << endl;
	cout << "===========================================================" << endl;
}

int StructHeroGame::SizeToDifficulty(Vector2Int size)
{
	int area = size.x * size.y;

	int difficulty = 1;
	while (area > pow(5 * difficulty, 2))
		difficulty++;

	return difficulty;
}
