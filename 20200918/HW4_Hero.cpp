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
	// ������ ������!
	/*
	1. �ؽ�Ʈ�� ����Ǵ� ����
		2. ������ ���۵Ǹ� ������ �̸��� ���̵��� �Է¹޴´�.
		3. �Էµ� ���̵��� ���� ������ HP / ������ �Ǵ� ������ ���ڰ� ����
		4. ������ ���۵Ǹ� ������ ���͸� ���� ������ ������ ����Ǵ� ���
		5. ���͸� ������ �����ϰ� ���� ȹ���Ѵ�. (0 ~100)
		6. ���͸� ������ ������ ��� Ž���� �� ������ �鸦�� �����Ѵ�.
		7. ������ �鸣�� ���� �Ҹ��ؼ� HP�� ȸ���� �� �ִ�.
		8. ������ ������������ �̷������. (���� ���а� ������ ������ �ݺ�, ���� HP�� �Ҹ�(���ʹ� �ѹ����� ���))
		9. ���͸� �� ������ Ŭ���� / HP�� 0�� �Ǹ� ���ӿ���
		10. Ŭ���� �� ������Ʈ ���
		11. ����

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

	cout << "GAME : ������ ������ ����" << endl;
	cout << "������ �̸��� �Է��Ͻÿ� : " << endl;
	cin >> name;

	while (difficulty < 1 || difficulty > 5)
	{
		cout << "������ ���̵� �Է� ��(1) �ڡ�(2) �ڡڡ�(3) �ڡڡڡ�(4) �ڡڡڡڡ�(5)" << endl;
		cin >> difficulty;
		if (cin.fail() || difficulty < 1 || difficulty > 5)
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Error : �߸��� �Է�" << endl;
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

	// ���� ���� ��ġ
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
		// ��� �˻�
		if (hp == 0 || numOfMonster == 0)
			break;

		system("cls");
		// �ൿ
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
		cout << name << " ����� HP : " << hp << "/" << maxHp << " ����� ���� ��� : " << gold << endl;
		cout << " ������ ���� �� : " << numOfMonster << "����" << endl;
		cout << "(H)��� (M)���� (S)���� " << endl;
		cout << "-----------------------------------------------------------" << endl;

		if (winMSG)
		{
			cout << "-----------------------------" << endl;
			cout << "�¸��߽��ϴ�!" << endl;
			cout << "���� óġ! " << gotGold << "��� ȹ��!! " << endl;
			cout << "-----------------------------" << endl;
			winMSG = false;
		}
		if (defeatMSG)
		{
			cout << "-----------------------------" << endl;
			cout << "�й��߽��ϴ�! HP 1 ����!" << endl;
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
			cout << "Error : �߸��� �Է�" << endl;
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
				cout << " ����� HP : " << hp << "/" << maxHp << " ����� ���� ��� : " << gold << endl;
				cout << "(1) 3HP ȸ�� 100Gold (2) ���� ȸ�� 250Gold (3) ������" << endl;
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
						cout << "<ü���� 3 ȸ���߽��ϴ�>" << endl << endl;
					}
					else
						cout << "<��尡 �����մϴ�>" << endl << endl;
					break;

				case 2:
					if (gold > 250)
					{
						gold -= 250;
						hp = maxHp;
						cout << "<ü���� ���� ȸ���߽��ϴ�>" << endl << endl;
					}
					else
						cout << "<��尡 �����մϴ�>" << endl << endl;
					break;

				case 3:
					outShop = true;
					break;
				default:
					//cout << "�߸��� �Է�" << endl;
					break;
				}
			}
			// ����� ��ġ �ѹ�
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
		
		// ����
		if (map[hy][hx] == MONSTER)
		{
			battleCount++;
			cout << "���Ϳ� �����߽��ϴ�! ���� ����" << endl;

			while (!battleEnd)
			{
				srand(time(NULL));
				monAttack = rand() % 3;

				cout << "<���� ����> 0(����), 1(����), 2(��) : ";
				cin >> heroAttack;
				if (heroAttack > 2 || heroAttack < 0 || cin.fail())
				{
					cin.clear();
					cin.ignore(256, '\n');
					cout << "Error : �߸��� �Է�" << endl;
					continue;
				}
				cout << "������ ���� : ";
				switch (monAttack)
				{
				case 0:
					cout << "����" << endl;
					break;
				case 1:
					cout << "����" << endl;
					break;
				case 2:
					cout << "��" << endl;
					break;
				}

				int offset = heroAttack - monAttack;
				switch (offset)
				{
				case 0:
					cout << "���º�! �ٽ�!" << endl << endl;
					break;

				// �¸� ó��
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
				// �й� ó��
				case -1: case 2:
					hp--;
					// ����� ��ġ �ѹ�
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
					//cout << "�߸��� �Է�" << endl;
					break;
				}
			}
			battleEnd = false;
		}
		
	} while (true);

	if (hp == 0)
	{
		cout << "-----------------------------------------------------------" << endl;
		cout << "����� ���ӿ��� �й��߽��ϴ�." << endl;
		cout << "�й��� ���̵� : ";
		for (int i = 0; i < difficulty; i++) 
			cout << "��";
		cout << endl;
		cout << "������ �ϼ� : " << battleCount << endl;
		cout << "���� ��� : " << gold << endl;
		cout << "-----------------------------------------------------------" << endl;
	}
	else
	{
		cout << "-----------------------------------------------------------" << endl;
		cout << "����� ���ӿ��� �¸��߽��ϴ�!" << endl;
		cout << "Ŭ���� ���̵� : ";
		for (int i = 0; i < difficulty; i++)
			cout << "��";
		cout << endl;
		cout << "������ �ϼ� : " << battleCount << endl;
		cout << "���� ��� : " << gold << endl;
		cout << "-----------------------------------------------------------" << endl;
	}

}