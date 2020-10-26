#include "Enemy.h"



HRESULT Enemy::Init()
{
	size = 60;
	pos = { 100.0f, 100.0f };
	speed = 15.0f;
	isDead = false;

	return S_OK;
}

void Enemy::Release()
{
}

void Enemy::Update()
{
	AutoMove();
}

void Enemy::Render(HDC hdc)
{
	Ellipse(hdc, pos.x - (size / 2), pos.y - (size / 2), pos.x + (size / 2), pos.y + (size / 2));
}

void Enemy::AutoMove()
{
	pos.x += speed;

	if ( pos.x + (size / 2) >= WINSIZE_X || pos.x - (size / 2) <= 0 )
	{
		speed *= -1;
	}
}

Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}
