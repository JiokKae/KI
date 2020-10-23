#include "Tank.h"
#include "Missile.h"


HRESULT Tank::Init()
{
	// ����
	pos.x = WINDOW_SIZE_X / 2;
	pos.y = WINDOW_SIZE_Y;
	size = 100;
	speed = 3;

	// ����
	barrelSize = 130;
	barrelEnd.x = WINDOW_SIZE_X / 2;
	barrelEnd.y = pos.y - barrelSize;
	barrelAngle = 90.0f;	// degree : 0 ~ 360 / radian : 0 ~ 6.28
	cooltime = 5;
	shootFrame = 0;		/*
		90 : 360 = x : 6.28
		360 * x = 6.28 * 90

		x = 90 * 6.28 / 360
		x = 90 * PI / 180
	*/


	// �̻���
	numOfMissile = 5000;
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

void Tank::Update(POINTFLOAT enemyPos, int enemySize)
{
	if (missile)
	{
		for (int i = 0; i < numOfMissile; i++)
			missile[i].Update(enemyPos, enemySize);
	}
}

void Tank::Render(HDC hdc)
{
	// ����
	//Rectangle(hdc, pos.x - (size / 2), pos.y - (size / 2),
	//	pos.x + (size / 2), pos.y + (size / 2));
	Ellipse(hdc, pos.x - (size / 2), pos.y - (size / 2), pos.x + (size / 2), pos.y + (size / 2));

	// ����
	MoveToEx(hdc, pos.x, pos.y, NULL);
	LineTo(hdc, barrelEnd.x, barrelEnd.y);

	// �̻���
	if (missile)
	{
		for (int i = 0; i < numOfMissile; i++)
			missile[i].Render(hdc);
	}
}

void Tank::Fire(POINTFLOAT enemyPos)
{
	if (missile)
	{
		if (missile[currentMissileCount].GetIsFire() == false && shootFrame + cooltime < g_Frame)
		{
			// ��ġ
			missile[currentMissileCount].SetPos(barrelEnd);
			// ����
			missile[currentMissileCount].SetAngle(barrelAngle);
			// ����
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

	barrelEnd.x = pos.x + cosf(DEGREE(barrelAngle)) * barrelSize;
	barrelEnd.y = pos.y - sinf(DEGREE(barrelAngle)) * barrelSize;
}

void Tank::Move(POINTFLOAT delta)
{
	pos.x += delta.x * speed;
	pos.y += delta.y * speed;
	RotateBarrel(0);
}
