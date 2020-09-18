#include <iostream>	// 입출력에 관련된 함수를 모아놓은 라이브러리
#include <conio.h>	// 키입력에 관련된 함수를 모아놓은 라이브러리
#include <ctime>
#include <cmath>
using namespace std;

int main()
{
    /*
	2차원 배열 및 다차원 배열
	배열이 2중 혹은 다중으로 되어 있는 것

	1차원 배열 : studentName[10]; -> 한 반에 10명의 학생을 관리	(10명)
	2차원 배열 : studentName[3][10]; -> 세 반에 각각 10명의 학생을 관리	(30명)
	3차원 배열 : studentName[4][3][10]; -> 총 4개 학년에 각각 3개반에 각각 10명의 학생을 관리 (120명)


	키입력
	_getch();	// char형의 값 (ASCII) 으로 키보드의 입력을 처리하는 함수

	
	// 배열
	int testNumbers[2][3] = { {1, 2, 3}, {4, 5, 6} };
	//int testNumbers[2][3] = { 1, 2, 3, 4, 5, 6 };

	cout << testNumbers << endl;
	cout << (testNumbers[0][3]) << endl;
	// cout << (testNumbers[2][3]) << endl; // 허용되지 않은 메모리 접근

	int a[2][3][5];
	int set = 0;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 5; k++)
			{
				a[i][j][k] = set++;
			}
		}
	}
	
	int offset = (int)a;
	cout << "a = " << a - offset << endl;
	for (int i = 0; i < 2; i++)
	{
		cout << "a[" << i << "] = " << (int)a[i] - (int)offset << endl;
		for (int j = 0; j < 3; j++)
		{
			cout << "a[" << i << "][" << j << "] = " << (int)a[i][j] - (int)offset << endl;
			for (int k = 0; k < 5; k++)
			{
				cout << a[i][j][k] << " (" << hex <<  (int)&a[i][j][k] - (int)offset << ")" << " ";
			}
			cout << endl;
		}
		cout << endl;
	}

	char inputKey;

	while (true) 
	{
		inputKey = _getch();
		if(inputKey == 'a' || inputKey == 'A')
			cout << "입력된 키 : " << inputKey << "("<< (int)inputKey << ")" << endl;
	}
	
	// 실습 1. 입력된 키가 'a' 이거나 'A'일 때만 출력되도록 수정

	// 실습 2. 
	
	A 에서 Z 키 중에 임의의 값을 컴퓨터가 설정을 하고
	유저는 한 개의 키를 입력해서 설정된 값을 맞춘다.
	유저가 입력한 키와 설정된 키가 맞으면 승리
	틀리면 남은 기회를 보여주고, 5번 틀리면 정답을 알려주고 게임오버

	+ 틀릴때마다 정답이 입력된 알파벳에 앞에 있는지 뒤에 있는지 알려준다.
	*/
	/*
	char inputKey;
	char goal;
	int i;
	srand(time(NULL) + rand());

	goal = rand() % 26 + 'A';

	for (i = 0; i < 5; i++)
	{
		cout << "대문자 알파벳을 입력하세요! (남은 기회 : " << 5 - i << ")" << endl;
		inputKey = _getch();
		if (inputKey >= 'A' && inputKey <= 'Z')
		{
			cout << "입력된 키 : " << inputKey << " (" << (int)inputKey << ")" << endl;
			if (inputKey == goal)
			{
				cout << "정답입니다" << endl;
				break;
			}
			else 
			{
				cout << "틀렸습니다. ";
				if (inputKey > goal)
					cout << "정답은 더 앞에 있습니다." << endl;
				else
					cout << "정답은 더 뒤에 있습니다." << endl;
			}
		}
		else
		{
			cout << "잘못된 입력" << endl;
			i--;
		}
		cout << endl;
	}
	if (i == 5)
		cout << "패배 했습니다. 정답은 " << goal << endl;
	*/

	cout << endl;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5 - i; j++)
		{
			cout << "*";
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < i + 1; j++)
		{
			cout << "*";
		}
		cout << endl;
	}
	cout << endl;
	for (int i = -5; i < 5; i++)
	{
		for (int j = 0; j < 5 - abs(i); j++)
		{
			cout << "*";
		}
		cout << endl;
	}		
	cout << endl;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5 - i; j++)
		{
			cout << "*";
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < i + 1; j++)
		{
			cout << "*";
		}
		cout << endl;
	}
	cout << endl;
	for (int i = -5; i < 5; i++)
	{
		for (int j = 0; j < 5 - abs(i); j++)
		{
			cout << "*";
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout << "*";
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (4 - i <= j)
				cout << "*";
			else
				cout << " ";
		}
		cout << endl;
	}
	cout << endl;
	for (int i = -4; i < 5; i++)
	{
		for (int j = -4; j < 5; j++)
		{
			if (abs(i) + abs(j) < 5)
				cout << "*";
			else
				cout << " ";
		}
		cout << endl;
	}
	cout << endl;
	system("cls");
	for (int i = -29; i < 30; i++)
	{
		for (int j = -99; j < 100; j++)
		{
			if (abs(i) + abs(j) < 30 && abs(i) + abs(j) > 10 || abs(i - 20) + abs(j - 20) < 5 || abs(i - 20) + abs(j + 20) < 5 || abs(i + 20) + abs(j - 20) < 5 || abs(i + 20) + abs(j + 20) < 5)
			//if( i*i*4 + (j)*(j) < 1200 ^ abs(i) + abs(j) < 30 || i * i * 4 + (j)*(j) < 300)
			//if(17 * (j/2) * (j/2) +16 * abs(j/2) * i + 17 * i*i < 8000) //하트 방정식	
				cout << "*";
			else
				cout << " ";
		}
		cout << endl;
	}
	/*
	int length;
	cout << "별 높이 입력" << endl;
	cin >> length;
	for (int i = -length / 2; i < length / 2 + 1; i++)
	{
		for (int j = -length / 2; j < length / 2 + 1; j++)
		{
			if (abs(i) + abs(j) < length/2 + 1)
				cout << "#";
			else
				cout << ".";

		}
		cout << endl;
	}
	*/
	/*
	탈출 게임 
	10 * 10 크기의 맵을 만든다
	WASD 키 입력을 통해서 상하좌우 이동을 한다.
	시작 지점은 (0,0) 탈출 지점은 (0,0) 제외한 랜덤설정

	P#########
	##########
	##########
	##########
	##########
	#######E##
	##########
	##########
	##########
	##########
	*/

	int map[10][10];
	char input;
	int playerX, playerY;
	int exitX, exitY;

	srand(time(NULL));

	playerX = playerY = 0;
	exitX = rand() % 9 + 1;
	exitY = rand() % 9 + 1;

	while (1)
	{
		system("cls");
		cout << endl << endl;

		for (int i = 0; i < 10; i++)
		{
			cout << "\t";
			for (int j = 0; j < 10; j++)
			{
				if (i == playerX && j == playerY)
					cout << "P";
				//else if (i == exitX && j == exitY)
				//	cout << "E";
				else
					cout << "#";
			}
			cout << endl;
		}
		cout << "출구와의 거리 : " << sqrt((exitX - playerX) * (exitX - playerX) + (exitY - playerY) * (exitY - playerY)) << endl;
		if (playerX == exitX && playerY == exitY)
			break;

		input = _getch();
		switch (input)
		{
		case 'w':
			if (playerX > 0)
				playerX--;
			break;
		case 'a':
			if (playerY > 0)
				playerY--;
			break;
		case 's':
			if (playerX < 10 - 1)
				playerX++;
			break;
		case 'd':
			if (playerY < 10 - 1)
				playerY++;
			break;
		default:
			break;
		}
		
	}
	cout << "축하합니다! 탈출 성공!" << endl;
}
