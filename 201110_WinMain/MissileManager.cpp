#include "MissileManager.h"
#include "Missile.h"
#include "Image.h"

HRESULT MissileManager::Init()
{
	vecMissiles.clear();

	maxMissileCount = 3000;
	vecMissiles.reserve(maxMissileCount);
	for (int i = 0; i < maxMissileCount; i++)
	{
		vecMissiles.push_back(new Missile());
		vecMissiles[i]->Init();
	}

    return S_OK;
}

void MissileManager::Release()
{
	for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
	{
		(*itMissiles)->Release();
		delete (*itMissiles);
	}
	vecMissiles.clear();
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

int MissileManager::GetMissileCount()
{
	int count = currentMissileCount++;
	if (currentMissileCount > maxMissileCount - 1)
		currentMissileCount = 0;
	return count;
}

void MissileManager::AddMissile(Allies allies, POINTFLOAT pos, float angle, Pattern pattern, float size, float speed)
{
	int count;
	do {
		count = GetMissileCount();
	} while (vecMissiles[count]->GetIsFire() != false);

	vecMissiles[count]->Fired(allies, pos, angle, pattern, size, speed);
}
