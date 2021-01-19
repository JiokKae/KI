#pragma once
#include "GameNode.h"
#include "pch.h"
#include <vector>

class Missile;
enum class Allies;
enum class Pattern;
class MissileManager : public Singleton<MissileManager>
{
	vector<Missile*> vecMissiles;
	vector<Missile*> ::iterator itMissiles;
	int maxMissileCount;
	int currentMissileCount;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	int GetMissileCount();

	void AddMissile(Allies allies, POINTFLOAT pos, float angle, Pattern pattern, float size = 30.0f, float speed = 100.0f);
};
