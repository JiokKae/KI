#include "Enemy.h"
#include "Image.h"

HRESULT Enemy::Init(float posX, float posY)
{
	size = 60;
	direction = { 0, 0 };
	pos = { posX,  posY };
	speed = 3.0f;
	isAlive = true;
	aliies = Allies::ENEMY;

	cooltime = 3.0f;// + (float)(rand() % 40)/60.f;
	shootTime = -cooltime;
	updateCount = 0;
	currFrameX = 0;
	currFrameY = 0;
	
	

	img = ImageManager::GetSingleton()->FineImage("UFO");

	return S_OK;
}

void Enemy::Release()
{
}

void Enemy::Update()
{
	if (isAlive) {
		currFrameX = updateCount / 5 % img->GetMaxFrameX();
		currFrameY = updateCount / 2 % 2;
		updateCount++;

		AutoMove();
	}
	
}

void Enemy::Render(HDC hdc)
{
	if(isAlive)
		img->FrameRender(hdc, pos.x, pos.y, currFrameX, currFrameY);

	//Ellipse(hdc, pos.x - (size / 2), pos.y - (size / 2)
	//	, pos.x + (size / 2), pos.y + (size / 2));
}

void Enemy::AutoMove()
{
	pos.x += speed;

	if (pos.x + (size / 2) >= WINSIZE_X ||
		pos.x - (size / 2) <= 0)
	{
		speed *= -1;
	}
}

void Enemy::Fire(POINTFLOAT targetPos, Pattern pattern)
{
	if (!isAlive)
		return;
	
	if (shootTime + cooltime < g_time)
	{
		POINTFLOAT v;
		v.x = targetPos.x - pos.x;
		v.y = targetPos.y - pos.y;
		float angle = 360 - DEGREE(atan2f(targetPos.y - pos.y, targetPos.x - pos.x));
		// ป๓ลย
		MissileManager::GetSingleton()->AddMissile(Allies::ENEMY, pos, angle, pattern);
		shootTime = g_time;
	}
}