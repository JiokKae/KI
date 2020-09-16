#include <iostream>
#include <ctime>
//#include <iomanip>
#include <string>
using namespace std;

int main()
{
	//int num;

	//cout << "숫자 입력 : ";
	//cin >> num;

	//if (num % 10 == 0 || num > 100 && num < 200)
	//{
	//	cout << "실행" << endl;
	//}

	// rand() => 일정한 수열을 반환하는 함수
	// 0, 1, 2, 3, 4, 5, 6, 7, 8, ..., 32767
	// srand() => rand()에서 사용하는 수열을 바꿔주는
	// 함수, 랜덤시드를 초가화하는 함수
	// time(NULL) => 1970.01.01 ~ 지난 시간 초를 반환

	//int random;
	//int input;

	//while (true)
	//{
	//	srand(time((time_t)NULL));
	//	random = rand() % 10 + 1;

	//	cout << "임의의 숫자가 정해졌습니다." << endl;
	//	cin >> input; 

	//	if (random > input)
	//	{
	//		cout << "정답은 " << input << "보다 큽니다" << endl;
	//	}
	//	else if (random < input)
	//	{
	//		cout << "정답은 " << input << "보다 작습니다" << endl;
	//	}
	//	else
	//	{
	//		cout << "정답입니다." << endl;
	//	}
	//	cout << "정답은 " << random << "입니다." << endl << endl;
	//}
	//
/*
	int num;

	cin >> num;

	switch (num)
	{
	case 1:
		cout << "1입니다." << endl;
		break;

	case 2:
		cout << "2입니다." << endl;
		break;

	case 3:
		cout << "3입니다." << endl;
		break;

	default:
		cout << "else입니다." << endl;
		break;
	}

	[반복문]
	1. while문
	=>조건문이 만족하지 않을 때까지(참이 아닐때까지) 반복
	while(조건식)
	{
		실행 코드
	}

	2. do while문
	=>먼저 반복시킬 코드 실행 후 조건 검사
	do
	{
		실행 코드
	}while(조건식);

	3. for문
	for(초기식; 조건식; 증감식)
	{
		실행문
	}

	초기식 -> (조건식 -> 실행문 -> 증감식) -> (조건식 -> 실행문 -> 증감식) -> ....

	초기식 : 조건체크를 위한 변수의 선언 및 초기화
	조건식 : 해당 조건이 참이면 반복, 아니면 break;
	증감식 : 중괄호 안의 실행문이 실행된 뒤에 초기식에 선언한 변수값을 증가, 감소 시킨다.
*/
	/*int i = 10;
	while (i > 0)
	{
		cout << i-- << endl;
	}

	i = 1;
	do
	{
		if (i % 3 == 0)
			cout << i << endl;
		i++;
	} while (i < 100);

	int src = 2;
	for (int i = 1; i < 1000; i++)
	{
		if (i == src)
		{
			cout << i << endl;
			src *= 2;
		}
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

	for (int i = 2; i < 10; i += 3)
	{
		for (int j = 1; j < 10 ; j++)
		{
			for (int k = i; k < i + 3; k++)
			{
				if (k < 10)
					cout << k << " * " << j << " = " << setw(2) << k * j;
				if (k != i + 2)
					cout << "\t";
				else
					cout << endl;
			}
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
	for (int i = -29; i < 30; i++)
	{
		for (int j = -29; j < 30; j++)
		{
			if (abs(i) + abs(j) < 30 && abs(i) + abs(j) > 10 || abs(i-20) + abs(j-20) < 5 || abs(i - 20) + abs(j + 20) < 5 || abs(i + 20) + abs(j - 20) < 5 || abs(i + 20) + abs(j + 20) < 5)
				cout << "*";
			else
				cout << " ";
		}
		cout << endl;
	}

	int order;
	int com;
	bool gameEnd = false;
	int offset;
	
	while (!gameEnd)
	{
		srand(time(NULL));
		com = rand() % 3;

		cout << "0(가위), 1(바위), 2(보) : ";
		cin >> order;

		cout << "컴퓨터 : " << com << endl;
		offset = order - com;
		switch (offset)
		{
		case 0:
			cout << "무승부! 다시!" << endl;
			break;
		case 1: case -2:
			cout << "승리했습니다!" << endl;
			gameEnd = true;
			break;
		case -1: case 2:
			cout << "패배했습니다!" << endl;
			gameEnd = true;
			break;
		default:
			cout << "잘못된 입력" << endl;
			break;
		}
	}*/

	/*

	// 영웅은 절차적!

	1. 텍스트로 진행되는 게임
	2. 게임이 시작되면 영웅의 이름과 난이도를 입력받는다.
	3. 입력된 난이도에 따라서 영웅의 HP / 만나게 되는 몬스터의 숫자가 변동
	4. 게임이 시작되면 마지막 몬스터를 잡을 때까지 전투가 진행되는 방식
	5. 몬스터를 잡으면 랜덤하게 돈을 획득한다. ( 0 ~ 100 )
	6. 몬스터를 잡으면 던전을 계속 탐험할 지 상점을 들를지 결정한다.
	7. 상점을 들르면 돈을 소모해서 HP를 회복할 수 있다.
	8. 전투는 가위바위보로 이루어진다. (비기면 승패가 정해질 때까지 반복, 지면 HP가 소모( 몬스터는 한번지면 사망))
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
	int heroAct;

	// option
	int difficulty = 0;
	bool battleEnd = false;
	bool outShop = false;
	int battleCount = 0;

	// monster
	int numOfMonster;
	int monAttack;

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
	maxHp = hp = 4 + difficulty;
	numOfMonster = 3 + difficulty * difficulty;

	do
	{
		// 전투
		if (!battleEnd) 
		{
			battleCount++;
			cout << "몬스터와 조우했습니다! 전투 개시" << endl;
		}
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

			case 1: case -2:
			{
				cout << "-----------------------------" << endl;
				cout << "승리했습니다!" << endl;
				numOfMonster--;
				int gotGold = rand() % 100;
				gold += gotGold;
				cout << "몬스터 처치! " << gotGold << "골드 획득!! " << endl;
				cout << "-----------------------------" << endl;
				battleEnd = true;
				break;
			}
			case -1: case 2:
				cout << "-----------------------------" << endl;
				cout << "패배했습니다! HP 1 감소!" << endl;
				hp--;
				cout << "-----------------------------" << endl;
				battleEnd = true;
				break;

			default:
				cout << "잘못된 입력" << endl;
				break;
			}
		}

		// 사망 검사
		if (hp == 0 || numOfMonster == 0)
			break;

		// 행동
		cout << endl;
		cout << "-----------------------------------------------------------" << endl;
		cout << name << " 용사의 HP : " << hp << "/" << maxHp << " 용사의 소지 골드 : " << gold << endl;
		cout << " 던전에 남은 적 : " << numOfMonster << "마리" << endl;
		cout << "용사의 행동 : (1) 탐색을 계속한다. (2) 상점에 방문한다. " << endl;
		cout << "-----------------------------------------------------------" << endl;
		cin >> heroAct;
		switch (heroAct)
		{
		case 1:
			battleEnd = false;
			break;
		case 2:
			// 상점
			while (!outShop)
			{
				cout << "-----------------------------------------------------------" << endl;
				cout << " 용사의 HP : " << hp << "/" << maxHp << " 용사의 소지 골드 : " << gold << endl;
				cout << "(1) 3HP 회복 100Gold (2) 완전 회복 250Gold (3) 나가기" << endl;
				cout << "-----------------------------------------------------------" << endl;
				cin >> heroAct;
				switch (heroAct)
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
					cout << "잘못된 입력" << endl;
					break;
				}
			}
			outShop = false;
			battleEnd = false;
		default:
			cout << "Error : 잘못된 입력" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			break;
		} 
	}while (true);

	if (hp == 0)
	{
		cout << "-----------------------------------------------------------" << endl;
		cout << "당신은 게임에서 패배했습니다." << endl;
		cout << "패배한 난이도 : " << difficulty << endl;
		cout << "전투한 턴수 : " << battleCount << endl;
		cout << "소지 골드 : " << gold << endl;
		cout << "-----------------------------------------------------------" << endl;
	}
	else
	{
		cout << "-----------------------------------------------------------" << endl;
		cout << "당신은 게임에서 승리했습니다!" << endl;
		cout << "클리어 난이도 : " << difficulty << endl;
		cout << "전투한 턴수 : " << battleCount << endl;
		cout << "소지 골드 : " << gold << endl;
		cout << "-----------------------------------------------------------" << endl;
	}
		
}
