#include "Missile.h"
#include <iostream>
using namespace std;

void NormalMissile::Move()
{
	cout << "발사 시점 각도로 직선으로 날아간다~" << endl;
}

void NormalMissile::Notice()
{
	cout << "일반 미사일이 생성되었다." << endl;
}

NormalMissile::~NormalMissile()
{
	cout << "일반 미사일이 소멸되었다." << endl;
}

void HomingMissile::Move()
{
	cout << "타겟을 향해 날아간다~~" << endl;
}

void HomingMissile::Notice()
{
	cout << "유도 미사일이 생성되었다." << endl;
}

HomingMissile::~HomingMissile()
{
	cout << "유도 미사일이 소멸되었다." << endl;
}

void LazerMissile::Move()
{
	cout << "레이저가 발사되었다~!!" << endl;
}

void LazerMissile::Notice()
{
	cout << "레이저 미사일이 생성되었다." << endl;
}

LazerMissile::~LazerMissile()
{
	cout << "레이저 미사일이 소멸되었다." << endl;
}
