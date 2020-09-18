#include <iostream>
#include <string>
#include <ctime>
#include <conio.h>
using namespace std;

#define MAP_SIZE_X 40
#define MAP_SIZE_Y 12
#define GROUND 0
#define WALL 1
#define SHOP 2
#define MONSTER 3

int main()
{
	// 영웅은 절차적!
	/*
	1. 텍스트로 진행되는 게임
		2. 게임이 시작되면 영웅의 이름과 난이도를 입력받는다.
		3. 입력된 난이도에 따라서 영웅의 HP / 만나게 되는 몬스터의 숫자가 변동
		4. 게임이 시작되면 마지막 몬스터를 잡을 때까지 전투가 진행되는 방식
		5. 몬스터를 잡으면 랜덤하게 돈을 획득한다. (0 ~100)
		6. 몬스터를 잡으면 던전을 계속 탐험할 지 상점을 들를지 결정한다.
		7. 상점을 들르면 돈을 소모해서 HP를 회복할 수 있다.
		8. 전투는 가위바위보로 이루어진다. (비기면 승패가 정해질 때까지 반복, 지면 HP가 소모(몬스터는 한번지면 사망))
		9. 몬스터를 다 잡으면 클리어 / HP가 0이 되면 게임오버
		10. 클리어 시 엔딩멘트 출력
		11. 종료

	*/

	// hero
	string name;
	int maxHp;
	int hp;
	int gold = 0;
	int heroAttack;
	int heroAct, shopAct;
	int hx, hy;
	int gotGold = 0;

	// shop
	int sx, sy;

	// option
	int difficulty = 0;
	bool battleEnd = false;
	bool outShop = false;
	bool defeatMSG = false;
	bool winMSG = false;
	int battleCount = 0;
	

	// monster
	int numOfMonster;
	int monAttack;

	// map
	int map[MAP_SIZE_Y][MAP_SIZE_X];

	cout << "GAME : 영웅은 절차적 실행" << endl;
	cout << "영웅의 이름을 입력하시오 : " << endl;
	cin >> name;

	while (difficulty < 1 || difficulty > 5)
	{
		cout << "게임의 난이도 입력 ★(1) ★★(2) ★★★(3) ★★★★(4) ★★★★★(5)" << endl;
		cin >> difficulty;
		if (cin.fail() || difficulty < 1 || difficulty > 5)
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Error : 잘못된 입력" << endl;
		}
	}

	//setting 
	maxHp = hp = 5 + difficulty / 2;
	numOfMonster = 3 + difficulty * difficulty;
	
	for (int i = 0; i < MAP_SIZE_Y; i++)
		for (int j = 0; j < MAP_SIZE_X; j++)
			map[i][j] = GROUND;
	
	srand(time(NULL));
	sx = rand() % MAP_SIZE_X;
	sy = rand() % MAP_SIZE_Y;
	map[sy][sx] = SHOP;

	// 몬스터 랜덤 배치
	for (int i = 0; i < numOfMonster; i++)
	{
		int x = rand() % MAP_SIZE_X;
		int y = rand() % MAP_SIZE_Y;
		if (map[y][x] == GROUND)
			map[y][x] = MONSTER;
		else
			i--;
	}

	hx = rand() % MAP_SIZE_X;
	hy = rand() % MAP_SIZE_Y;

	do
	{
		// 사망 검사
		if (hp == 0 || numOfMonster == 0)
			break;

		system("cls");
		// 행동
		for (int i = 0; i < MAP_SIZE_Y; i++)
		{
			for (int j = 0; j < MAP_SIZE_X; j++)
			{
				if (hx == j && hy == i)
					cout << 'H';
				else if (map[i][j] == SHOP)
					cout << 'S';
				else if (map[i][j] == MONSTER)
					cout << 'M';
				else if(map[i][j] == GROUND)
					cout << '_';

			}
			cout << endl;
		}
		cout << endl;
		cout << "-----------------------------------------------------------" << endl;
		cout << name << " 용사의 HP : " << hp << "/" << maxHp << " 용사의 소지 골드 : " << gold << endl;
		cout << " 던전에 남은 적 : " << numOfMonster << "마리" << endl;
		cout << "(H)용사 (M)몬스터 (S)상점 " << endl;
		cout << "-----------------------------------------------------------" << endl;

		if (winMSG)
		{
			cout << "-----------------------------" << endl;
			cout << "승리했습니다!" << endl;
			cout << "몬스터 처치! " << gotGold << "골드 획득!! " << endl;
			cout << "-----------------------------" << endl;
			winMSG = false;
		}
		if (defeatMSG)
		{
			cout << "-----------------------------" << endl;
			cout << "패배했습니다! HP 1 감소!" << endl;
			cout << "-----------------------------" << endl;
			defeatMSG = false;
		}

		heroAct = _getch();
		switch (heroAct)
		{
		case 'w':
		case 'W':
			if (hy > 0)
				hy--;
			break;
		case 'a':
		case 'A':
			if (hx > 0)
				hx--;
			break;
		case 's':
		case 'S':
			if (hy < MAP_SIZE_Y - 1 )
				hy++;
			break;
		case 'd':
		case 'D':
			if (hx < MAP_SIZE_X - 1)
				hx++;
			break;

		default:
			cout << "Error : 잘못된 입력" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			break;
		}
		//Enter Shop
		if (sx == hx && sy == hy)
		{
			while (!outShop)
			{
				cout << "-----------------------------------------------------------" << endl;
				cout << " 용사의 HP : " << hp << "/" << maxHp << " 용사의 소지 골드 : " << gold << endl;
				cout << "(1) 3HP 회복 100Gold (2) 완전 회복 250Gold (3) 나가기" << endl;
				cout << "-----------------------------------------------------------" << endl;
				cin >> shopAct;
				switch (shopAct)
				{
				case 1:
					if (gold > 100)
					{
						gold -= 100;
						hp += 3;
						if (hp > maxHp)
							hp = maxHp;
						cout << "<체력을 3 회복했습니다>" << endl << endl;
					}
					else
						cout << "<골드가 부족합니다>" << endl << endl;
					break;

				case 2:
					if (gold > 250)
					{
						gold -= 250;
						hp = maxHp;
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
			// 히어로 위치 롤백
			switch (heroAct)
			{
			case 'w': case 'W':
				hy++;
				break;
			case 'a': case 'A':
				hx++;
				break;
			case 's': case 'S':
				hy--;
				break;
			case 'd': case 'D':
				hx--;
				break;
			}
			outShop = false;
			battleEnd = false;
		}
		
		// 전투
		if (map[hy][hx] == MONSTER)
		{
			battleCount++;
			cout << "몬스터와 조우했습니다! 전투 개시" << endl;

			while (!battleEnd)
			{
				srand(time(NULL));
				monAttack = rand() % 3;

				cout << "<공격 선택> 0(가위), 1(바위), 2(보) : ";
				cin >> heroAttack;
				if (heroAttack > 2 || heroAttack < 0 || cin.fail())
				{
					cin.clear();
					cin.ignore(256, '\n');
					cout << "Error : 잘못된 입력" << endl;
					continue;
				}
				cout << "몬스터의 공격 : ";
				switch (monAttack)
				{
				case 0:
					cout << "가위" << endl;
					break;
				case 1:
					cout << "바위" << endl;
					break;
				case 2:
					cout << "보" << endl;
					break;
				}

				int offset = heroAttack - monAttack;
				switch (offset)
				{
				case 0:
					cout << "무승부! 다시!" << endl << endl;
					break;

				// 승리 처리
				case 1: case -2:
				{
					numOfMonster--;
					gotGold = rand() % 100;
					gold += gotGold;
					map[hy][hx] = GROUND;
					winMSG = true;
					battleEnd = true;
					break;
				}
				// 패배 처리
				case -1: case 2:
					hp--;
					// 히어로 위치 롤백
					switch (heroAct)
					{
					case 'w': case 'W':
							hy++;
						break;
					case 'a': case 'A':
							hx++;
						break;
					case 's': case 'S':
							hy--;
						break;
					case 'd': case 'D':
							hx--;
						break;
					}
					defeatMSG = true;
					battleEnd = true;
					break;

				default:
					//cout << "잘못된 입력" << endl;
					break;
				}
			}
			battleEnd = false;
		}
		
	} while (true);

	if (hp == 0)
	{
		cout << "-----------------------------------------------------------" << endl;
		cout << "당신은 게임에서 패배했습니다." << endl;
		cout << "패배한 난이도 : ";
		for (int i = 0; i < difficulty; i++) 
			cout << "★";
		cout << endl;
		cout << "전투한 턴수 : " << battleCount << endl;
		cout << "소지 골드 : " << gold << endl;
		cout << "-----------------------------------------------------------" << endl;
	}
	else
	{
		cout << "-----------------------------------------------------------" << endl;
		cout << "당신은 게임에서 승리했습니다!" << endl;
		cout << "클리어 난이도 : ";
		for (int i = 0; i < difficulty; i++)
			cout << "★";
		cout << endl;
		cout << "전투한 턴수 : " << battleCount << endl;
		cout << "소지 골드 : " << gold << endl;
		cout << "-----------------------------------------------------------" << endl;
	}

}