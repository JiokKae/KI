#include "Missile.h"
#include "Enemy.h"


HRESULT Missile::Init()
{
	size = 100;
	pos.x = 0;
	pos.y = 0;
	speed = 15.0f;
	isFire = false;
	angle = 0.0f;
	target = nullptr;
	followRatio = 0.1f;

	// 포신
	barrelSize = 100;
	barrelEnd.x = pos.x;
	barrelEnd.y = pos.y;
	barrelAngle = angle;		// 단위 : degree(0 ~ 360), radian(0 ~ 6.28)

	return S_OK;
}

void Missile::Release()
{
}

void Missile::Update()
{
	if (isFire)
	{
		pos.x += cosf(RADIAN(angle)) * speed;
		pos.y -= sinf(RADIAN(angle)) * speed;

		if (pos.x < 0 + size / 2)
		{
			angle = 180 - angle;
			pos.x = size / 2;
		}	
		else if (pos.x > WINSIZE_X - size / 2) 
		{
			angle = 180 - angle;
			pos.x = WINSIZE_X - size / 2;
		}
		if (pos.y < 0 + size / 2) 
		{
			angle = -angle;
			pos.y = size / 2;
		}
		else if (pos.y > WINSIZE_Y - size / 2)
		{
			angle = -angle;
			pos.y = WINSIZE_Y - size / 2;
		}
			
		barrelEnd.x = pos.x + cosf(RADIAN(angle)) * barrelSize;
		barrelEnd.y = pos.y	- sinf(RADIAN(angle)) * barrelSize;
	}
}

void Missile::Render(HDC hdc)
{
	if (isFire)
	{
		Ellipse(hdc, pos.x - (size / 2), pos.y - (size / 2),
			pos.x + (size / 2), pos.y + (size / 2));

		MoveToEx(hdc, pos.x, pos.y, NULL);
		LineTo(hdc, barrelEnd.x, barrelEnd.y);
	}
}

Missile::Missile()
{
}


Missile::~Missile()
{
}
