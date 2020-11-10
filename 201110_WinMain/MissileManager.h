#pragma once
#include "GameNode.h"
#include <vector>

class Missile;
class MissileManager : public GameNode
{
	vector<Missile*> vecMissiles;
	vector<Missile*> ::iterator itMissiles;
	int missileMax;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void AddMissile(float posX, float posY);
};
