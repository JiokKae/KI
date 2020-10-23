#include "Enemy.h"

HRESULT Enemy::Init()
{
	pos.x = 500;
	pos.y = 350;
	size = 110;
	speed.x = 0.0f;
	speed.y = 0;

	return S_OK;
}

void Enemy::Release()
{
}

void Enemy::Update()
{
	pos.x += speed.x;
	pos.y += speed.y;

	if (GetRect().left < 0 || GetRect().right > WINSIZE_X)
		speed.x = -speed.x;
}

void Enemy::Render(HDC hdc)
{
	Ellipse(hdc, pos.x - (size / 2), pos.y - (size / 2),
		pos.x + (size / 2), pos.y + (size / 2));
}

RECT Enemy::GetRect()
{
	RECT rect;
	rect.left = pos.x - size / 2.0f;
	rect.top = pos.y - size / 2.0f;
	rect.right = pos.x + size / 2.0f;
	rect.bottom = pos.y + size / 2.0f;
	return rect;
}

FPOINT Enemy::GetPos()
{
	return pos;
}

int Enemy::GetSize()
{
	return size;
}
