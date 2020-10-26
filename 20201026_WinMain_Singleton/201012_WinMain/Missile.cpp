#include "Missile.h"
#include "Enemy.h"


HRESULT Missile::Init()
{
	size = 100;
	pos.x = 0;
	pos.y = 0;
	speed = 5.0f;
	isFire = false;
	angle = 0.0f;
	target = nullptr;
	followRatio = 0.1f;

	// 포신
	barrelSize = 100;
	barrelEnd.x = pos.x;
	barrelEnd.y = pos.y;
	barrelAngle = angle;		// 단위 : degree(0 ~ 360), radian(0 ~ 6.28)

	barrelSize2 = 80;
	barrelEnd2.x = pos.x;
	barrelEnd2.y = pos.y;
	barrelAngle2 = angle;
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
		pos.y += sinf(RADIAN(angle)) * speed;

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
		barrelEnd.y = pos.y	+ sinf(RADIAN(angle)) * barrelSize;

		barrelEnd2.x = pos.x + cosf(RADIAN(angle2)) * barrelSize;
		barrelEnd2.y = pos.y + sinf(RADIAN(angle2)) * barrelSize;
	}
}

void Missile::Render(HDC hdc)
{
	if (isFire)
	{
		Ellipse(hdc, pos.x - (size / 2), pos.y - (size / 2),
			pos.x + (size / 2), pos.y + (size / 2));

		HPEN hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
		HPEN hPenOld = (HPEN)SelectObject(hdc, hPen);

		MoveToEx(hdc, pos.x, pos.y, NULL);
		LineTo(hdc, barrelEnd.x, barrelEnd.y);

		DeleteObject(SelectObject(hdc, hPenOld));

		MoveToEx(hdc, pos.x, pos.y, NULL);
		LineTo(hdc, barrelEnd2.x, barrelEnd2.y);
	}
}

void Missile::Move(float angle, float distance)
{
	pos.x += cosf(RADIAN(angle)) * distance;
	pos.y += sinf(RADIAN(angle)) * distance;
}

Missile::Missile()
{
}


Missile::~Missile()
{
}
