#include "Tank.h"
#include "Missile.h"


HRESULT Tank::Init()
{
	// 몸통
	pos.x = WINSIZE_X / 2;
	pos.y = WINSIZE_Y;
	size = 100;
	speed = 3;

	// 포신
	barrelSize = 130;
	barrelEnd.x = WINSIZE_X / 2;
	barrelEnd.y = pos.y - barrelSize;
	barrelAngle = 90.0f;	// degree : 0 ~ 360 / radian : 0 ~ 6.28
	cooltime = 20;
	shootFrame = 0;		/*
		90 : 360 = x : 6.28
		360 * x = 6.28 * 90

		x = 90 * 6.28 / 360
		x = 90 * PI / 180
	*/
	

	// 미사일
	numOfMissile = 50;
	currentMissileCount = 0;
	missile = new Missile[numOfMissile];
	for (int i = 0; i < numOfMissile; i++)
		missile[i].Init();

	return S_OK;
}

void Tank::Release()
{
	for (int i = 0; i < numOfMissile; i++)
		missile[i].Release();
	delete[] missile;
}

void Tank::Update(FPOINT enemyPos, int enemySize)
{
	if (missile)
	{
		for (int i = 0; i < numOfMissile; i++)
			missile[i].Update(enemyPos, enemySize);
	}
}

void Tank::Render(HDC hdc)
{
	// 몸통
	//Rectangle(hdc, pos.x - (size / 2), pos.y - (size / 2),
	//	pos.x + (size / 2), pos.y + (size / 2));
	Ellipse(hdc, pos.x - (size / 2), pos.y - (size / 2), pos.x + (size / 2), pos.y + (size / 2));

	// 포신
	MoveToEx(hdc, pos.x, pos.y, NULL);
	LineTo(hdc, barrelEnd.x, barrelEnd.y);

	// 미사일
	if (missile)
	{
		for (int i = 0; i < numOfMissile; i++)
			missile[i].Render(hdc);
	}
}

void Tank::Fire(FPOINT enemyPos)
{
	if (missile)
	{
		if (missile[currentMissileCount].GetIsFire() == false && shootFrame + cooltime < g_Frame)
		{
			// 위치
			missile[currentMissileCount].SetPos(barrelEnd);
			// 각도
			missile[currentMissileCount].SetAngle(barrelAngle);
			// 상태
			missile[currentMissileCount].SetIsFire(true);
			currentMissileCount++;
			if (currentMissileCount > numOfMissile - 1)
				currentMissileCount = 0;
			shootFrame = g_Frame;
		}
	
	}
}

void Tank::RotateBarrel(float angle)
{
	barrelAngle += angle;

	barrelEnd.x = pos.x	+ cosf(DegreeToRadian(barrelAngle)) * barrelSize;
	barrelEnd.y = pos.y	- sinf(DegreeToRadian(barrelAngle)) * barrelSize;
}

void Tank::Move(FPOINT delta)
{
	pos.x += delta.x * speed;
	pos.y += delta.y * speed;
	RotateBarrel(0);
}

Tank::Tank()
{
}


Tank::~Tank()
{
}
