#include "Missile.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "Image.h"

HRESULT Missile::Init()
{
	size = 30;
	pos.x = 0;
	pos.y = 0;
	speed = 100.0f;
	isFire = false;
	angle = 0.0f;
	
	

	return S_OK;
}

void Missile::Release()
{

}

void Missile::Update()
{
	if (!isFire)
		return;
		
	//speed = (sin(pos.y/60) + 1.2f) * 1.5f + (sin(pos.x / 60) + 1.2f) * 1.5f;
	//angle -= speed/ 100.0f;

	
	// 적탄환 밖으로 나갈 경우
	if (pos.x < 0 || pos.x > WINSIZE_X || pos.y < 0 || pos.y > WINSIZE_Y)
		isFire = false;

	pos.x += direction.x * speed * TimerManager::GetSingleton()->GetTimeElapsed();
	pos.y += direction.y * speed * TimerManager::GetSingleton()->GetTimeElapsed();

	AdditionalMissile();
}

void Missile::Render(HDC hdc)
{
	if (isFire)
	{
		img->Render(hdc, pos.x - (size / 2), pos.y - (size / 2), size, size);
		//Ellipse(hdc, pos.x - (size / 2), pos.y - (size / 2),pos.x + (size / 2), pos.y + (size / 2));
	}
}

void Missile::Fired(Allies allies, POINTFLOAT pos, float angle, Pattern pattern, float size, float speed)
{
	if (size < 10)
		return;

	this->isFire = true;
	this->allies = allies;
	string strKey;
	if (allies == Allies::PLAYER) strKey = "Missile1";
	if (allies == Allies::ENEMY) strKey = "Missile2";
	img = ImageManager::GetSingleton()->FineImage(strKey);
	this->pos = pos;
	this->size = size;
	this->speed = speed;

	this->shootTime = g_time;
	SetAngle(angle);
	SetPattern(pattern);
}

void Missile::SetPattern(Pattern pattern)
{
	this->pattern = pattern;
	switch (pattern)
	{
	case Pattern::FIREWORK:
		cooltime = 0.625f;
		break;
	case Pattern::ARROW:
		speed *= 10;
		cooltime = 0.08f;
		break;
	case Pattern::SHOTGUN:
		speed *= 0.8f;
		cooltime = 0.3125f;
		break;
	case Pattern::NEWS:
		shootTime = g_time - 300.0f;
		cooltime = 150.0f;
		break;
	case Pattern::HURRICANE:
		speed *= 3.0f;
		cooltime = 0.05f;
		break;
	case Pattern::STOP:
		speed = 0;
		cooltime = 2.f;
		break;
	case Pattern::STOPSHOTGUN:
		speed *= 0.8f;
		cooltime = 0.6f;
		break;
	case Pattern::RANDOM:
		cooltime = 0;
		break;
	}
}

void Missile::AdditionalMissile()
{
	if (shootTime + cooltime > g_time)
		return;

	switch (pattern)
	{
		//	1 to 8 end
	case Pattern::FIREWORK:
		for (int i = 0; i < 8; i++)
			MissileManager::GetSingleton()->AddMissile(allies, pos, i * 45 + angle, Pattern::SHOTGUN, size * 0.66f, speed / 4);
		this->isFire = false;
		break;

		// 1 to 3
	case Pattern::ARROW:
		for (int i = -1; i < 2; i++)
			MissileManager::GetSingleton()->AddMissile(allies, pos, angle - 180 + i * 10, Pattern::NONE, size * 0.8f, speed / 2);
		break;

		// 1 to 3 end
	case Pattern::SHOTGUN:
		for (int i = -1; i < 2; i++)
			MissileManager::GetSingleton()->AddMissile(allies, pos, angle + i * 10, Pattern::NONE, size * 0.66f, speed * 1.5f);
		this->isFire = false;
		break;

		// 1 to 4 end
	case Pattern::NEWS:
		for (int i = 0; i < 4; i++)
			MissileManager::GetSingleton()->AddMissile(allies, pos, angle + i * 90, Pattern::ARROW, size, speed * 0.8f);
		this->isFire = false;
		break;

		// 1 to 1
	case Pattern::HURRICANE:
		angle += 45;
		MissileManager::GetSingleton()->AddMissile(allies, pos, angle, Pattern::SHOTGUN, size * 0.8f, speed * 0.2f);
		break;

		// 1 to 4 end
	case Pattern::STOP:
		for (int i = -1; i < 2; i++)
			MissileManager::GetSingleton()->AddMissile(allies, pos, i * 10 + angle, Pattern::RANDOM, size * 0.66f, 100.0f / 4);
		this->isFire = false;
		break;

		// 1 to 3 end
	case Pattern::STOPSHOTGUN:
		for (int i = -1; i < 2; i++)
			MissileManager::GetSingleton()->AddMissile(allies, pos, angle + i * 10, Pattern::STOP, size * 1.f, speed * 1.5f);
		this->isFire = false;
		break;

		// 1 to 1 end
	case Pattern::RANDOM:
		MissileManager::GetSingleton()->AddMissile(allies, pos, angle, (Pattern)(rand() % (int)Pattern::END), size * 0.8f, speed * 1.5f);
		this->isFire = false;
		break;
	}
	shootTime = g_time;
}
