#include "Missile.h"

void RainbowCircle(HDC hdc, RECT pos, int _size, int num = 72, int T = 0, int sizeT = 0, int dir = 1);

HRESULT Missile::Init()
{
	pos.x = 0;
	pos.y = 0;
	baseSpeed = 40.0f;
	speed.x = 0;
	speed.y = 0;
	size = 20;
	isFire = false;

	return S_OK;
}

void Missile::Release()
{
}

void Missile::Update()
{
	if (isFire)
	{
		pos.y += speed.y;
		pos.x += speed.x;
		if (pos.y < 0)
		{
			speed.y = -speed.y;
		}
		if (pos.x < 0)
		{
			speed.x = -speed.x;
		}
		if(pos.x > WIN_SIZE_X)
		{
			speed.x = -speed.x;
		}
		if (pos.y > WIN_SIZE_Y)
		{
			speed.y = -speed.y;
		}
			
	}
}

void Missile::Render(HDC hdc)
{
	if (isFire) 
	{
		//Ellipse(hdc, pos.x - (size / 2), pos.y - (size / 2), pos.x + (size / 2), pos.y + (size / 2));
		RainbowCircle(hdc, { pos.x - (size / 2), pos.y - (size / 2), pos.x + (size / 2), pos.y + (size / 2) }, 20, 72);
	}
		
}

void RainbowCircle(HDC hdc, RECT pos, int _size, int num, int T, int sizeT, int dir)
{
	double radian = 360 / 72 * (3.141592 / 180);
	double size = _size;
	//double size = sin(frame / 40.0 + sizeT) * 20 + _size;

	for (int i = 0; i < num; i++)
	{
		RECT rect = { pos.left + sin(g_Frame * dir / 20.0 + i * radian) * size,
			pos.top + cos(g_Frame * dir / 20.0 + i * radian) * size,
			pos.right + sin(g_Frame * dir / 20.0 + i * radian) * size,
			pos.bottom + cos(g_Frame * dir / 20.0 + i * radian) * size };

		HBRUSH brush = CreateSolidBrush(
			RGB(
				cos(g_Frame * dir / 15.0 + (i + T) * radian) * 127 + 128,
				sin(g_Frame * dir / 15.0 + (i + T) * radian) * 127 + 128,
				sin(g_Frame * dir / 15.0 + ((i + T) + 50) * radian) * 127 + 128)
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