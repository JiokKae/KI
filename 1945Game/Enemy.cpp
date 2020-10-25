#include "Enemy.h"
#include "Missile.h"

HPEN Enemy::hPenOutline = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
HBRUSH Enemy::hBrushInside = CreateSolidBrush(RGB(255, 150, 150));
int Enemy::currentEnemyCount = 0;

HRESULT Enemy::Init(POINTFLOAT tankPos)
{
	pos.x = rand() % (1920 - 600);
	pos.y = rand() % (1000 - 600);	
	if (pos.x > tankPos.x - 300)
		pos.x += 600;
	if (pos.y > tankPos.y - 300)
		pos.y += 600;

	size = 100;
	direction.x = 0;
	direction.y = 0;
	speed = 1.0f;
	isAlive = true;
	aliies = Allies::ENEMY;

	cooltime = 60 + rand() % 40;

	return S_OK;
}

void Enemy::Release()
{
	
}

void Enemy::Update(POINTFLOAT tankPos)
{
	if (this == nullptr)
		return;
	if (!isAlive)
		return;

	if (isAlive)
	{
		POINTFLOAT vector = { tankPos.x - pos.x , tankPos.y - pos.y };
		POINTFLOAT nomalVector = Normalize(vector);

		direction.x = nomalVector.x;
		direction.y = nomalVector.y;

		pos.x += direction.x * speed;
		pos.y += direction.y * speed;
	}

	if (GetRect().left < 0 || GetRect().right > WINDOW_SIZE_X)
		direction.x = -direction.x;
}

void Enemy::Render(HDC hdc)
{
	if (this == nullptr)
		return;
	if (!isAlive)
		return;

	HPEN hPenOld = (HPEN)SelectObject(hdc, hPenOutline);
	HPEN hBrushOld = (HPEN)SelectObject(hdc, hBrushInside);

	Ellipse(hdc, pos.x - (size / 2), pos.y - (size / 2),
		pos.x + (size / 2), pos.y + (size / 2));

	SelectObject(hdc, hPenOld);
	SelectObject(hdc, hBrushOld);
}

void Enemy::Fire(POINTFLOAT tankPos, Missile* missile, Pattern pattern)
{
	if (missile == nullptr)
		return;
	if (!isAlive)
		return;

	if (missile[Missile::currentMissileCount].GetIsFire() == false && shootFrame + cooltime < g_Frame)
	{
		POINTFLOAT v;
		v.x = tankPos.x - pos.x;
		v.y = tankPos.y - pos.y;
		float angle = 360 - DEGREE(atan2f(tankPos.y - pos.y, tankPos.x - pos.x));
		// ป๓ลย
		missile[Missile::currentMissileCount].Fired(Allies::ENEMY, pos, angle, pattern);
		Missile::currentMissileCount++;
		if (Missile::currentMissileCount > Missile::numOfMissile - 1)
			Missile::currentMissileCount = 0;
		shootFrame = g_Frame;
	}
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

POINTFLOAT Enemy::GetPos()
{
	return pos;
}

int Enemy::GetSize()
{
	return size;
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
		currentEnemyCount--;
	}
}