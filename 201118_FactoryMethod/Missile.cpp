#include "Missile.h"
#include <iostream>
using namespace std;

void NormalMissile::Move()
{
	cout << "�߻� ���� ������ �������� ���ư���~" << endl;
}

void NormalMissile::Notice()
{
	cout << "�Ϲ� �̻����� �����Ǿ���." << endl;
}

NormalMissile::~NormalMissile()
{
	cout << "�Ϲ� �̻����� �Ҹ�Ǿ���." << endl;
}

void HomingMissile::Move()
{
	cout << "Ÿ���� ���� ���ư���~~" << endl;
}

void HomingMissile::Notice()
{
	cout << "���� �̻����� �����Ǿ���." << endl;
}

HomingMissile::~HomingMissile()
{
	cout << "���� �̻����� �Ҹ�Ǿ���." << endl;
}

void LazerMissile::Move()
{
	cout << "�������� �߻�Ǿ���~!!" << endl;
}

void LazerMissile::Notice()
{
	cout << "������ �̻����� �����Ǿ���." << endl;
}

LazerMissile::~LazerMissile()
{
	cout << "������ �̻����� �Ҹ�Ǿ���." << endl;
}
