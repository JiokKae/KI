#include "Enemy.h"
#include <cmath>

POINTFLOAT Normalize(POINTFLOAT pos) {
	 float deno = pow(pos.x, 2) + pow(pos.y, 2);
	 pos.x /= sqrt(deno);
	 pos.y /= sqrt(deno);

	 return pos;
}

HRESULT Enemy::Init()
{
	pos.x = (FLOAT)(rand() % 1200);
	pos.y = (FLOAT)(rand() % 300);
	speed = 2;
	size = 50;

	return S_OK;
}

void Enemy::Release()
{
}

void Enemy::Update(POINTFLOAT tankPos)
{
	if (isAlive)
	{
		POINTFLOAT vector = { tankPos.x - pos.x , tankPos.y - pos.y };
		POINTFLOAT nomalVector = Normalize(vector);

		pos.x += nomalVector.x * speed;
		pos.y += nomalVector.y * speed;
	}
}

void Enemy::Render(HDC hdc)
{
	if(isAlive)
		Ellipse(hdc, pos.x - (size / 2.0), pos.y - (size / 2.0), pos.x + (size / 2.0), pos.y + (size / 2.0));
}

void Enemy::Appear()
{
	if (!isAlive)
	{
		isAlive = true;
	}
}

void Enemy::Dead()
{
	if (isAlive)
	{
		isAlive = false;
	}
}

int Enemy::GetSize()
{
	return size;
}

POINTFLOAT Enemy::GetPos()
{
	return pos;
}
