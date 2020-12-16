#pragma once
#include "GameNode.h"
#include <vector>

class Missile;
class Enemy;
class MissileManager : public GameNode
{
private:
	int missileCount;
	vector<Missile*> vecMissiles;
	vector<Missile*>::iterator itMissiles;

	Enemy* owner;

public:
	HRESULT Init();		
	void Release();		
	void Update();		
	void Render(HDC hdc);

	void SetOwner(Enemy* owner);

	void Fire();
};

