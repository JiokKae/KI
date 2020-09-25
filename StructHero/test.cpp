#include <iostream>
#include <ctime>
#include <string>
#include <conio.h>

using namespace std;

string** mapAll(int mapArray)
{
	string** mapXY = new string*[mapArray];		// 기준할당

	// 할당된 각 방(?)에 각각 할당
	for (int i = 0; i < mapArray; i++)
	{
		mapXY[i] = new string[mapArray];
	}
	// 랜덤 함수 정의
	int mapRandam;

	// 맵 초기화
	for (int i = 0; i < mapArray; i++)
	{
		for (int j = 0; j < mapArray; j++)
		{
			mapRandam = rand() % 3;
			switch (mapRandam)
			{
			case 0:
			{
				mapXY[i][j] = "숲";		// 숲으로 초기화
			}
			break;
			case 1:
			{
				mapXY[i][j] = "늪";		// 늪으로 초기화
			}
			break;
			case 2:
			{
				mapXY[i][j] = "땅";		// 땅으로 초기화
			}
			break;
			}
		}
	}

	// 상점 초기화

	int storeX = (rand() % mapArray);
	int storeY = (rand() % mapArray);

	mapXY[storeY][storeX] = "＄";

	return mapXY;
}

// 용사 관련 정의
string playerName;
string mapTemp = "땅";
int playerHp;
int playerExperience;
int playerMaxHp;
int playerGold;
int playerX = 0;
int playerY = 0;


// 난이도
int level;
int mapLevel;


// 플레이어 이동

void playerMove(string** mapAddress)
{
	mapAddress[playerY][playerX] = mapTemp;

	char WASD = _getch();

	if (WASD == 'W' || WASD == 'w')
	{
		if (playerY > 0 && playerY < mapLevel)
		{
			mapTemp = mapAddress[playerY - 1][playerX];
			playerY -= 1;
		}
	}
	else if (WASD == 'A' || WASD == 'a')
	{
		if (playerX > 0 && playerX <= mapLevel)
		{
			mapTemp = mapAddress[playerY][playerX - 1];
			playerX -= 1;
		}
	}
	else if (WASD == 'S' || WASD == 's')
	{
		if (playerY < mapLevel - 1 && playerY >= 0)
		{
			mapTemp = mapAddress[playerY + 1][playerX];
			playerY += 1;
		}
	}
	else if (WASD == 'D' || WASD == 'd')
	{
		if (playerX < mapLevel && playerX >= 0)
		{
			mapTemp = mapAddress[playerY][playerX + 1];
			playerX += 1;
		}
	}
	mapAddress[playerY][playerX] = "ρ";

}

// 맵 출력
void mapOpen(string** mapAddress)
{
	for (int i = 0; i < mapLevel; i++)
	{
		for (int j = 0; j < mapLevel; j++)
		{
			cout << mapAddress[i][j];
		}
		cout << endl;
	}
}


int main()
{
	string** mapAddress = NULL;

	srand(time(NULL));

	// 시작
	cout << "==============" << endl;
	cout << "영웅은 절차적!" << endl;
	cout << "==============" << endl;
	cout << endl;

	// 용사 이름
	cout << "용사의 이름을 입력하세요 : ";
	cin >> playerName;
	cout << endl;
	system("cls");


	// 난이도 설정

	while (level != 1 && level != 2 && level != 3)
	{
		cout << "난이도를 설정하세요." << endl;
		cout << "1. 쉬움, 2. 보통, 3. 어려움" << endl;
		cin >> level;

		if (level == 1 || level == 2 || level == 3)
		{
			system("cls");
			switch (level)
			{
			case 1:
			{
				mapLevel = 5;
				mapAddress = mapAll(5);
			}
			break;
			case 2:
			{
				mapLevel = 10;
				mapAddress = mapAll(10);
			}
			break;
			case 3:
			{
				mapLevel = 25;
				mapAddress = mapAll(25);
			}
			break;
			}
		}
		else
		{
			system("cls");
			cout << "잘못입력하셨습니다." << endl;
			cout << "다시입력하셨습니다." << endl;
		}
	}
	mapAddress[playerY][playerX] = "ρ";
	mapOpen(mapAddress);

	while (1)
	{
		playerMove(mapAddress);
		system("cls");
		mapOpen(mapAddress);
	}
}