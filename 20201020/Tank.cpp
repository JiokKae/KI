#include "Tank.h"
#include "Missile.h"

HRESULT Tank::Init()
{
	pos.x = WIN_SIZE_X / 2;
	pos.y = WIN_SIZE_Y;
	size = 100;

	// ����
	barrelSize = 130;

	// �̻���
	numOfMissile = 5000;
	missile = new Missile[numOfMissile];
	for (int i = 0; i < numOfMissile; i++)
		missile[i].Init();

	return S_OK;
}

void Tank::Release()
{
	for (int i = 0; i < numOfMissile; i++)
		missile->Release();
	
	delete[] missile;
}

void Tank::Update()
{
	for (int i = 0; i < numOfMissile; i++)
		missile[i].Update();
}

void Tank::Render(HDC hdc)
{
	// ��ü
	Ellipse(hdc, pos.x - (size / 2), pos.y - (size / 2), pos.x + (size / 2), pos.y + (size / 2));
	
	// ����
	MoveToEx(hdc, pos.x, pos.y, NULL);

	LineTo(hdc, GetBarrelEnd().x, GetBarrelEnd().y);

	// �̻���
	for (int i = 0; i < numOfMissile; i++)
		missile[i].Render(hdc);
	
	char szText[128];
	wsprintf(szText, "Angle : %d", angle);
	TextOut(hdc, 5, 60, szText, strlen(szText));
}

void Tank::Fire()
{
	if (missile)
	{
		if (missile[currentMissileIndex].IsFire() == false)
		{
			for (int i = -1; i < 2; i++)
			{
				missile[currentMissileIndex+i].SetPos(GetBarrelEnd());

				missile[currentMissileIndex+i].SetSpeed(angle + i * 20);
				missile[currentMissileIndex+i].SetIsFire(true);
			}
			
			currentMissileIndex += 3;
			if (currentMissileIndex + 90 > numOfMissile - 1)
				currentMissileIndex = 0;
		}
	}
}

void Tank::SetAngle(int angle) { this->angle = angle; }

void Tank::RotateBarrel(int delta)
{
	angle += delta;
	if (angle < -90)
		angle = -90;
	else if (angle > 90)
		angle = 90;
}

POINT Tank::GetBarrelEnd()
{
	POINT p = { pos.x + cos(RADIAN(angle)) * barrelSize , pos.y + sin(RADIAN(angle)) * barrelSize };
	return p;
}
