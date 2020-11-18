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
	cout << "부모 미사일 팩토리가 소멸되었다." << endl;
}

Missile * NormalMissileFactory::CreateMissile()
{
	return new NormalMissile();
}

NormalMissileFactory::~NormalMissileFactory()
{
	cout << "일반 미사일 팩토리가 소멸된다" << endl;
}

Missile * LazerMissileFactory::CreateMissile()
{
	return new LazerMissile();
}

LazerMissileFactory::~LazerMissileFactory()
{
	cout << "레이저 미사일 팩토리가 소멸되었다." << endl;
}

Missile * HomingMissileFactory::CreateMissile()
{
	return new HomingMissile();
}

HomingMissileFactory::~HomingMissileFactory()
{
	cout << "유도 미사일 팩토리가 소멸되었다." << endl;
}
