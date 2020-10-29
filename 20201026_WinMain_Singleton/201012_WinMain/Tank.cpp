#include "Tank.h"
#include "Missile.h"
#include "Enemy.h"

Tank::Tank()
{
}


Tank::~Tank()
{
}

HRESULT Tank::Init()
{
	target = nullptr;
	size = 100;
	rc = {	(WINSIZE_X / 2) - (size / 2), (WINSIZE_Y) - (size / 2),
			(WINSIZE_X / 2) + (size / 2), (WINSIZE_Y) + (size / 2) };
	speed = 5.0f;

	// 포신
	barrelSize = 150;
	barrelEnd.x = WINSIZE_X / 2;
	barrelEnd.y = WINSIZE_Y - barrelSize;
	barrelAngle = -90.0f;		// 단위 : degree(0 ~ 360), radian(0 ~ 6.28)

	//90 : 360 = x : 6.28

	//	360 * x = 90 * 6.28
	//	x = DegreeToRadian(90);

	// 미사일
	numOfMissile = 500;
	currentMissileCount = 0;
	missile = new Missile[numOfMissile];
	for (int i = 0; i < numOfMissile; i++)
		missile[i].Init();
	

	return S_OK;
}

void Tank::Release()
{
	for (int i = 0; i < numOfMissile; i++)
		missile[i].Release();
	delete[] missile;
}

void Tank::Update()
{
	if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_UP))
	{
		Fire();
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
	{
		RotateBarrel(1.0f);
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
	{
		RotateBarrel(-1.0f);
	}

	if(missile)
		for (int i = 0; i < numOfMissile; i++)
			missile[i].Update();

	LatedUpdate();
}

void Tank::LatedUpdate()
{
	if (missile)
	{
		for (int i = 0; i < numOfMissile - 1; i++)
		{
			if (!missile[i].GetIsFire())
				continue;

			for (int j = i + 1; j < numOfMissile; j++)
			{
				if (!missile[j].GetIsFire())
					continue;

				int distance = sqrtf(powf(missile[i].GetPos().x - missile[j].GetPos().x, 2) + powf(missile[i].GetPos().y - missile[j].GetPos().y, 2));
				if (distance < missile[i].GetSize() / 2 + missile[j].GetSize() / 2)
				{
					float iangle = DEGREE(atan2f(missile[i].GetPos().y - missile[j].GetPos().y, missile[i].GetPos().x - missile[j].GetPos().x));
					//missile[i].Move(iangle, (missile[i].GetSize() / 2 + missile[j].GetSize() / 2 - distance));
					//if (iangle < 0)
					//	iangle += 360;
					float jangle = DEGREE(atan2f(missile[j].GetPos().y - missile[i].GetPos().y, missile[j].GetPos().x - missile[i].GetPos().x));
					//missile[i].Move(jangle, (missile[i].GetSize() / 2 + missile[j].GetSize() / 2 - distance));
					//if (jangle < 0)
					//	jangle += 360;
					//missile[i].SetAngle((iangle + missile[i].GetAngle()) / 2);
					//missile[j].SetAngle((jangle + missile[j].GetAngle()) / 2);

					missile[i].SetAngle(iangle);
					missile[j].SetAngle(jangle);

				}
			}
			
		}
	}
	
}

void Tank::Render(HDC hdc)
{
	//Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);

	// 포신
	MoveToEx(hdc, WINSIZE_X / 2, WINSIZE_Y, NULL);
	LineTo(hdc, barrelEnd.x, barrelEnd.y);

	// 미사일
	for (int i = 0; i < numOfMissile; i++)
		missile[i].Render(hdc);
}

void Tank::Fire()
{
	if (missile)
	{
		if (missile[currentMissileCount].GetIsFire() == false)
		{
			missile[currentMissileCount].SetPos(barrelEnd);
			missile[currentMissileCount].SetAngle(barrelAngle);
			missile[currentMissileCount].SetIsFire(true);
			currentMissileCount++;
			if (currentMissileCount > numOfMissile - 1)
				currentMissileCount = 0;
		}
	}
}

void Tank::Move()
{
}

void Tank::Dead()
{
}

void Tank::RotateBarrel(float angle)
{
	barrelAngle -= angle;
	barrelEnd.x = WINSIZE_X / 2
		+ cosf(RADIAN(barrelAngle)) * barrelSize;
	barrelEnd.y = WINSIZE_Y
		+ sinf(RADIAN(barrelAngle)) * barrelSize;
}

void Tank::SetTarget(Enemy * target)
{
	this->target = target;
	if (missile)
	{
		missile->SetTarget(target);
	}
}
