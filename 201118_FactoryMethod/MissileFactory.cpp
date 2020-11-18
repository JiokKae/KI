#include "MissileFactory.h"
#include "Missile.h"
#include <iostream>
using namespace std;

void MissileFactory::NewMissile()
{
	Missile* m = CreateMissile();
	missileDatas.push_back(m);
	m->Notice();
}

MissileFactory::~MissileFactory()
{
	cout << "�θ� �̻��� ���丮�� �Ҹ�Ǿ���." << endl;
}

Missile * NormalMissileFactory::CreateMissile()
{
	return new NormalMissile();
}

NormalMissileFactory::~NormalMissileFactory()
{
	cout << "�Ϲ� �̻��� ���丮�� �Ҹ�ȴ�" << endl;
}

Missile * LazerMissileFactory::CreateMissile()
{
	return new LazerMissile();
}

LazerMissileFactory::~LazerMissileFactory()
{
	cout << "������ �̻��� ���丮�� �Ҹ�Ǿ���." << endl;
}

Missile * HomingMissileFactory::CreateMissile()
{
	return new HomingMissile();
}

HomingMissileFactory::~HomingMissileFactory()
{
	cout << "���� �̻��� ���丮�� �Ҹ�Ǿ���." << endl;
}
