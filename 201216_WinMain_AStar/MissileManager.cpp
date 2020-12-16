#include "MissileManager.h"
#include "Missile.h"

HRESULT MissileManager::Init()
{
	missileCount = 20;
	vecMissiles.resize(missileCount);
	for (int i = 0; i < missileCount; i++)
	{
		vecMissiles[i] = new Missile();
		vecMissiles[i]->Init();
	}

	return S_OK;
}

void MissileManager::Release()
{
	for (itMissiles = vecMissiles.begin();
		itMissiles != vecMissiles.end(); itMissiles++)
	{
		(*itMissiles)->Release();
		delete (*itMissiles);
	}
	vecMissiles.clear();
}

void MissileManager::Update()
{
	for (itMissiles = vecMissiles.begin();
		itMissiles != vecMissiles.end(); itMissiles++)
	{
		(*itMissiles)->Update();
	}
}

void MissileManager::Render(HDC hdc)
{
	for (itMissiles = vecMissiles.begin();
		itMissiles != vecMissiles.end(); itMissiles++)
	{
		(*itMissiles)->Render(hdc);
	}
}

void MissileManager::SetOwner(Enemy* owner)
{
	this->owner = owner;

	for (itMissiles = vecMissiles.begin();
		itMissiles != vecMissiles.end(); itMissiles++)
	{
		(*itMissiles)->SetOwner(owner);
	}
}

void MissileManager::Fire()
{
	for (itMissiles = vecMissiles.begin();
		itMissiles != vecMissiles.end(); itMissiles++)
	{
		if ((*itMissiles)->GetIsFire() == false)
		{
			(*itMissiles)->SetIsFire(true);
			break;
		}
	}
}
