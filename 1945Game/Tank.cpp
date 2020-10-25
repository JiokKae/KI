#include "Tank.h"
#include "Missile.h"

int Tank::hitCount = 0;

HRESULT Tank::Init()
{
	// ¸öÅë
	pos.x = WINDOW_SIZE_X / 2;
	pos.y = WINDOW_SIZE_Y;
	size = 60;
	speed = 6;
	hPenOutline = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
	hBrushInside = CreateSolidBrush(RGB(200, 200, 255));
	aliies = Allies::PLAYER;

	// Æ÷½Å
	barrelSize = 60;
	
	barrelAngle += 90.0f * barrelSpeed;
	barrelEnd.x = pos.x + cosf(RADIAN(barrelAngle)) * barrelSize;
	barrelEnd.y = pos.y - sinf(RADIAN(barrelAngle)) * barrelSize;

	barrelSpeed = 2.0f;
	cooltime = 5;
	shootFrame = 0;

	return S_OK;
}

void Tank::Release()
{
	// ¸öÅë
	DeleteObject(hPenOutline);
	DeleteObject(hBrushInside);
}

void Tank::Update()
{
	if (this == nullptr)
		return;

	if (GetAsyncKeyState(KEY_W))
	{
		Move({ 0,-1 });
	}
	if (GetAsyncKeyState(KEY_S))
	{
		Move({ 0,1 });
	}
	if (GetAsyncKeyState(KEY_A))
	{
		Move({ -1,0 });
	}
	if (GetAsyncKeyState(KEY_D))
	{
		Move({ 1,0 });
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		RotateBarrel(1);
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		RotateBarrel(-1);
	}
	
}

void Tank::Render(HDC hdc)
{
	if (this == nullptr)
		return;

	// ¸öÅë
	HPEN hPenOld = (HPEN)SelectObject(hdc, hPenOutline);
	HPEN hBrushOld = (HPEN)SelectObject(hdc, hBrushInside);
	Ellipse(hdc, (int)(pos.x - (size / 2)), (int)(pos.y - (size / 2)), (int)(pos.x + (size / 2)), (int)(pos.y + (size / 2)));

	// Æ÷½Å
	MoveToEx(hdc, (int)pos.x, (int)pos.y, NULL);
	LineTo(hdc, (int)barrelEnd.x, (int)barrelEnd.y);

	SelectObject(hdc, hPenOld);
	SelectObject(hdc, hBrushOld);
}

void Tank::Fire(POINTFLOAT enemyPos, Missile* missile)
{
	if (missile)
	{
		if (missile[Missile::currentMissileCount].GetIsFire() == false && shootFrame + cooltime < g_Frame)
		{
			missile[Missile::currentMissileCount].Fired(Allies::PLAYER, barrelEnd, barrelAngle, Pattern::NONE);
			Missile::currentMissileCount++;
			if (Missile::currentMissileCount > Missile::numOfMissile - 1)
				Missile::currentMissileCount = 0;
			shootFrame = g_Frame;
		}
	}
}

void Tank::RotateBarrel(float angle)
{
	barrelAngle += angle * barrelSpeed;

	barrelEnd.x = pos.x + cosf(RADIAN(barrelAngle)) * barrelSize;
	barrelEnd.y = pos.y - sinf(RADIAN(barrelAngle)) * barrelSize;
}

void Tank::Move(POINTFLOAT delta)
{
	pos.x += delta.x * speed;
	pos.y += delta.y * speed;

	if (pos.x < size / 2)
		pos.x = size / 2;
	else if (pos.x > WINDOW_SIZE_X - size / 2)
		pos.x = WINDOW_SIZE_X - size / 2;

	if (pos.y < size / 2)
		pos.y = size / 2;
	else if (pos.y > WINDOW_SIZE_Y - size / 2)
		pos.y = WINDOW_SIZE_Y - size / 2;

	RotateBarrel(0);
}

POINTFLOAT Tank::GetPos()
{
	return pos;
}