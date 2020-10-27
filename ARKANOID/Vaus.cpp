#include "Vaus.h"
#include "Missile.h"
#include "Block.h"

HRESULT Vaus::Init()
{
	pos = { WINSIZE_X / 2 ,WINSIZE_Y - 100 };
	width = 100;
	height = 50;
	speed = 5.0f;

	// 미사일
	numOfMissile = 20;
	currentMissileCount = 0;
	missile = new Missile[numOfMissile];
	for (int i = 0; i < numOfMissile; i++)
		missile[i].Init();
	

	return S_OK;
}

void Vaus::Release()
{
	for (int i = 0; i < numOfMissile; i++)
		missile[i].Release();
	delete[] missile;
}

void Vaus::Update()
{
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
	{
		Move(-1.0f);
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
	{
		Move(1.0f);
	}

	if(missile)
		for (int i = 0; i < numOfMissile; i++)
			missile[i].Update();

	LatedUpdate();
}

void Vaus::LatedUpdate()
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
					float jangle = DEGREE(atan2f(missile[j].GetPos().y - missile[i].GetPos().y, missile[j].GetPos().x - missile[i].GetPos().x));

					missile[i].SetAngle(iangle);
					missile[j].SetAngle(jangle);

				}
			}
			
		}
	}
	
}

void Vaus::Render(HDC hdc)
{
	Rectangle(hdc, pos.x, pos.y, pos.x + width, pos.y + height);
	
	// 미사일
	for (int i = 0; i < numOfMissile; i++)
		missile[i].Render(hdc);
}

void Vaus::Move(float dir)
{
	pos.x += dir * speed;
}
