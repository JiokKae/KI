#include "MissileManager.h"
#include "Missile.h"

HRESULT MissileManager::Init()
{
	missileMax = 20;
	vecMissiles.reserve(missileMax);
	
    return S_OK;
}

void MissileManager::Release()
{
	for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
	{
		(*itMissiles)->Release();
		delete (*itMissiles);
	}
}

void MissileManager::Update()
{
	for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
	{
		(*itMissiles)->Update();
	}
}

void MissileManager::Render(HDC hdc)
{
	for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
	{
		(*itMissiles)->Render(hdc);
	}
}

void MissileManager::AddMissile(float posX, float posY)
{
	if (missileMax <= vecMissiles.size())
		return;

	Missile* missile = new Missile();
	vecMissiles.push_back(missile);
	missile->Init();
	missile->SetPos({ posX, posY });
	missile->SetAngle(3.141592f * 1.5f);
	missile->SetIsFire(true);
}
