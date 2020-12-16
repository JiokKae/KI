#include "Missile.h"
#include "Enemy.h"


HRESULT Missile::Init()
{
	size = 30;
	pos.x = 0;
	pos.y = 0;
	speed = 500.0f;
	goalTime = 10.0f;
	isFire = false;
	angle = -PI / 2.0f;
	destAngle = 0.0f;
	target = nullptr;
	followRatio = 0.1f;
	owner = nullptr;

	return S_OK;
}

void Missile::Release()
{
}

void Missile::Update()
{
	if (isFire)
	{
#pragma region 유도
		//float tempAngle;
		//if (target)
		//{
		//	followRatio += 0.2f;
		//	if (followRatio > 10.0f)
		//	{
		//		followRatio = 10.0f;
		//	}

		//	destAngle = atan2f(-(target->GetPos().y - pos.y),
		//		(target->GetPos().x - pos.x));

		//	tempAngle = DegreeToRadian(angle);
		//	tempAngle +=
		//		(destAngle - DegreeToRadian(angle)) / (10.0f / followRatio);

		//	angle = RadianToDegree(tempAngle);
		//}

		//pos.x += cosf(tempAngle) * speed;
		//pos.y -= sinf(tempAngle) * speed;
#pragma endregion
		pos.x += cosf(angle) * speed *
			TimerManager::GetSingleton()->GetElapsedTime() / goalTime;
		// 5초에 500pixel == 1Frame(elapsedTime)에 x
		pos.y -= sinf(angle) * speed *
			TimerManager::GetSingleton()->GetElapsedTime() / goalTime;

		//// 벽에 부딪혔는지
		//// 왼쪽, 오른쪽
		//if (pos.x - (size / 2) <= 0 || pos.x + (size / 2) >= WINSIZE_X)
		//{
		//	angle = PI - angle;
		//}
		//// 위, 아래
		//if (pos.y - (size / 2) <= 0 || pos.y + (size / 2) >= WINSIZE_Y)
		//{
		//	angle = PI * 2.0f - angle;
		//}
	}
}

void Missile::Render(HDC hdc)
{
	if (isFire)
	{
		Ellipse(hdc, pos.x - (size / 2), pos.y - (size / 2),
			pos.x + (size / 2), pos.y + (size / 2));
	}
}

void Missile::SetIsFire(bool fire)
{
	this->isFire = fire;
	if (owner && isFire)
	{
		pos.x = owner->GetPos().x;
		pos.y = owner->GetPos().y;
	}
}

Missile::Missile()
{
}


Missile::~Missile()
{
}
