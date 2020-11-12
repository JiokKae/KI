#include "pch.h"
#include "Missile.h"
#include "Enemy.h"

void RainbowCircle(HDC hdc, RECT pos, int _size, int num = 72, int T = 0, int sizeT = 0, int dir = 1);

HRESULT Missile::Init()
{
	pos.x = 0;
	pos.y = 0;
	baseSpeed = 10.0f;
	speed.x = 0;
	speed.y = 0;
	size = 40;
	isFire = false;

	return S_OK;
}

void Missile::Release()
{
}

void Missile::Update(Enemy* enemys, int numOfEnemy)
{
	if (isFire)
	{
		pos.y += speed.y;
		pos.x += speed.x;

		if (pos.y < 0 || pos.x < 0 || pos.x > WIN_SIZE_X || pos.y > WIN_SIZE_Y)
			isFire = false;
	}
}

void Missile::Render(HDC hdc)
{
	if (isFire) 
	{
		
		RainbowCircle(hdc, { (LONG)(pos.x - (size / 5)), (LONG)(pos.y - (size / 5)), (LONG)(pos.x + (size / 5)), (LONG)(pos.y + (size / 5)) }, size / 5, 72);
		//Ellipse(hdc, (int)(pos.x - (size / 2)), (int)(pos.y - (size / 2)), (int)(pos.x + (size / 2)), (int)(pos.y + (size / 2)));
	}
		
}

void RainbowCircle(HDC hdc, RECT pos, int _size, int num, int T, int sizeT, int dir)
{
	double radian = 360 / 72 * (3.141592 / 180);
	double size = _size;
	//double size = sin(frame / 40.0 + sizeT) * 20 + _size;

	for (int i = 0; i < num; i++)
	{
		RECT rect = { pos.left + (LONG)(sin(g_Frame * dir / 20.0 + i * radian) * size),
			pos.top + (LONG)(cos(g_Frame * dir / 20.0 + i * radian) * size),
			pos.right + (LONG)(sin(g_Frame * dir / 20.0 + i * radian) * size),
			pos.bottom + (LONG)(cos(g_Frame * dir / 20.0 + i * radian) * size) };

		HBRUSH brush = CreateSolidBrush(
			RGB(
				cos(g_Frame * dir / 15.0 + (i + T) * radian) * 127 + 128,
				sin(g_Frame * dir / 15.0 + (i + T) * radian) * 127 + 128,
				sin(g_Frame * dir / 15.0 + ((i + T) + 50) * radian) * 127 + 128
			)
		);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);

		HPEN pen = CreatePen(PS_NULL, 1, RGB(0, 0, 0));
		HBRUSH oldPen = (HBRUSH)SelectObject(hdc, pen);

		//FillRect(hdc, &rect, brush);
		Ellipse(hdc, rect.left, rect.top, rect.right, rect.bottom);

		DeleteObject(SelectObject(hdc, oldBrush));
		DeleteObject(SelectObject(hdc, oldPen));

	}
}