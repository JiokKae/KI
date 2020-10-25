#include "Missile.h"
#include "Tank.h"
#include "Enemy.h"

HPEN Missile::hPenOutline[] = { CreatePen(PS_SOLID, 3, RGB(0, 0, 255)), CreatePen(PS_SOLID, 3, RGB(255, 0, 0)), };
HBRUSH Missile::hBrushInside[] = { CreateSolidBrush(RGB(100, 255, 255)), CreateSolidBrush(RGB(255, 220, 0)), };
int Missile::numOfMissile = 5000;
int Missile::currentMissileCount = 0;

int Missile::GetMissileCount()
{
	int count = currentMissileCount++;
	if (currentMissileCount > numOfMissile - 1)
		currentMissileCount = 0;
	return count;
}

HRESULT Missile::Init()
{
	pos.x = 0;
	pos.y = 0;
	speed = 10.0f;
	size = 30;
	isFire = false;
	angle = 0.0f;

	return S_OK;
}

void Missile::Update(Enemy* enemy, int numOfEnemy, Tank* tank, int numOfTank, Missile* missile)
{
	if (this == nullptr)
		return;

	if (!isFire)
		return;

	POINTFLOAT targetPos;
	float targetSize;
	float distance;

	switch (allies)
	{
	case Allies::PLAYER:

		int targetIndex;
		targetIndex = -1;

		for (int i = 0; i < numOfEnemy; i++)
		{
			if (enemy[i].IsAlive())
			{
				if (targetIndex == -1 || CampareDistance(enemy[targetIndex].GetPos() - pos, enemy[i].GetPos() - pos) == -1)
				{
					targetIndex = i;
				}
			}
		}
		if (targetIndex == -1)
			return;

		targetPos = enemy[targetIndex].GetPos();
		targetSize = enemy[targetIndex].GetSize();
		distance = sqrtf(powf(targetPos.x - pos.x, 2) + powf(targetPos.y - pos.y, 2));

		if (distance < size / 2 + targetSize / 2)
		{
			enemy[targetIndex].Dead();
			isFire = false;
		}
		else if (distance < 3000)
		{
			POINTFLOAT v;
			//v.x = enemyPos.x - pos.x;
			//v.y = enemyPos.y - pos.y;
			//v = Normalize(v);

			float radian = atan2f(targetPos.y - pos.y, targetPos.x - pos.x);
			//if (radian < 0)
			//	radian += 2 * PI;
			v.x = cosf(radian);
			v.y = sinf(radian);

			direction.x = Lerp(direction.x, v.x, 0.01f);
			direction.y = Lerp(direction.y, v.y, 0.01f);

			//direction = Normalize(direction);
		}
		break;

	case Allies::ENEMY:
		targetPos = tank->GetPos();
		targetSize = tank->GetSize();

		distance = sqrtf(powf(targetPos.x - pos.x, 2) + powf(targetPos.y - pos.y, 2));

		// 적탄환 탱크에 맞을 경우
		if (distance < size / 2 + targetSize / 2)
		{
			Tank::hitCount++;
			isFire = false;
		}
			

		// 적탄환 밖으로 나갈 경우
		if (pos.x < 0 || pos.x > WINDOW_SIZE_X || pos.y < 0 || pos.y > WINDOW_SIZE_Y)
			isFire = false;
		break;
	}

	pos.x += direction.x * speed;
	pos.y += direction.y * speed;

	AdditionalMissile(missile);
}

void Missile::Render(HDC hdc)
{
	if (this == nullptr)
		return;

	if (isFire)
	{
		HPEN hPenOld = (HPEN)SelectObject(hdc, hPenOutline[(int)allies]);
		HPEN hBrushOld = (HPEN)SelectObject(hdc, hBrushInside[(int)allies]);

		Ellipse(hdc, (int)(pos.x - (size / 2)), (int)(pos.y - (size / 2)), (int)(pos.x + (size / 2)), (int)(pos.y + (size / 2)));
		
		SelectObject(hdc, hPenOld);
		SelectObject(hdc, hBrushOld);
	}
}

void Missile::Fired(Allies allies, POINTFLOAT pos, float angle, Pattern pattern, float size, float speed)
{
	if (size < 10)
		return;
	this->isFire = true;
	this->allies = allies;
	this->pos = pos;
	this->size = size;
	this->speed = speed;

	this->shootFrame = g_Frame;
	SetAngle(angle);
	SetPattern(pattern);
}

void Missile::SetPattern(Pattern pattern)
{
	this->pattern = pattern;
	switch (pattern)
	{
	case Pattern::FIREWORK:
		cooltime = 60;
		break;
	case Pattern::ARROW:
		speed *= 2;
		cooltime = 5;
		break;
	case Pattern::SHOTGUN:
		speed *= 0.8f;
		cooltime = 20;
		break;
	case Pattern::NEWS:
		shootFrame = g_Frame - 20000;
		cooltime = 10000;
		break;
	case Pattern::HURRICANE:
		speed *= 1.5f;
		cooltime = 2;
		break;
	}
}

void Missile::AdditionalMissile(Missile* missile)
{
	if (shootFrame + cooltime > g_Frame)
		return;

	switch (pattern)
	{
	//	1 to 10 end
	case Pattern::FIREWORK:
		for (int i = 0; i < 10; i++)
			missile[GetMissileCount()].Fired(allies, pos, i * 36 + angle, Pattern::SHOTGUN, size * 0.66f , speed / 4);
		this->isFire = false;
		break;

	// 1 to 3
	case Pattern::ARROW:
		for (int i = -1; i < 2; i++)
			missile[GetMissileCount()].Fired(allies, pos, angle - 180 + i * 10, Pattern::NONE, size * 0.8f, speed / 2);
		break;

	// 1 to 5 end
	case Pattern::SHOTGUN:
		for (int i = -2; i < 3; i++)
			missile[GetMissileCount()].Fired(allies, pos, angle + i * 10, Pattern::NONE, size * 0.66f, speed * 1.5f);
		this->isFire = false;
		break;

	// 1 to 4 end
	case Pattern::NEWS:
		for (int i = 0; i < 4; i++)
			missile[GetMissileCount()].Fired(allies, pos, angle + i * 90, Pattern::ARROW, size, speed * 0.8f);
		this->isFire = false;
		break;

	// 1 to 1
	case Pattern::HURRICANE:
		angle += 45;
		missile[GetMissileCount()].Fired(allies, pos, angle, Pattern::SHOTGUN, size * 0.8f, speed * 0.2f);
		break;
	}
	shootFrame = g_Frame;
}

void Missile::Release()
{

}