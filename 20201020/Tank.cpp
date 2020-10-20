#include "Tank.h"
#include "Missile.h"

HRESULT Tank::Init()
{
	pos.x = WIN_SIZE_X / 2;
	pos.y = WIN_SIZE_Y;
	size = 100;

	// 포신
	barrelSize = 130;
	cooltime = 10;
	

	return S_OK;
}

void Tank::Release()
{
	
}

void Tank::Update()
{
	
}

void Tank::Render(HDC hdc)
{
	// 몸체
	Ellipse(hdc, (int)(pos.x - (size / 2)), (int)(pos.y - (size / 2)), (int)(pos.x + (size / 2)), (int)(pos.y + (size / 2)));
	
	// 포신
	MoveToEx(hdc, (int)pos.x, (int)pos.y, NULL);

	LineTo(hdc, (int)GetBarrelEnd().x, (int)GetBarrelEnd().y);
	
	char szText[128];
	wsprintf(szText, "Angle : %d", angle);
	TextOut(hdc, 5, 60, szText, strlen(szText));
}

void Tank::Fire(Missile * missile, int &index, int numOfMissile)
{
	if (missile)
	{
		if (missile[index].IsFire() == false && shootFrame + cooltime < g_Frame)
		{
			int num = 1;
			for (int i = 0; i < num; i++)
			{
				missile[index + i].SetPos(GetBarrelEnd());
				missile[index + i].SetSpeed(angle + i * 20);
				missile[index + i].SetIsFire(true);
			}
			
			index += num;
			if (index + num > numOfMissile - 1)
				index = 0;
			shootFrame = g_Frame;
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

POINTFLOAT Tank::GetBarrelEnd()
{
	POINTFLOAT p = { pos.x + cos(RADIAN(angle)) * barrelSize , pos.y + sin(RADIAN(angle)) * barrelSize };
	return p;
}

POINTFLOAT Tank::GetPos()
{
	return pos;
}
