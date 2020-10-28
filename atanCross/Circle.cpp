#include "Circle.h"

HRESULT Circle::Init()
{
	pos = { 500, 500 };
	radius = 100;
	return S_OK;
}

void Circle::Release()
{
}

void Circle::Update()
{
	//if()
}

void Circle::Render(HDC hdc)
{
	Ellipse(hdc, pos.x, pos.y, radius);
	char buf[50];
	wsprintf(buf, "x: %d, y: %d", (int)pos.x, (int)pos.y);
	TextOut(hdc, pos.x, pos.y, buf, strlen(buf));
}
