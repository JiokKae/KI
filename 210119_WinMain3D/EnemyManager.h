#pragma once
#include "GameNode.h"
#include <vector>

class Enemy;
class EnemyManager : public GameNode
{
	vector<Enemy*> vecEnemys;
	vector<Enemy*> ::iterator itEnemys;
	
	int enemyMax;
public:
	HRESULT Init();
	void Release();
	void Update(POINTFLOAT targetPos);
	void Render(HDC hdc);

	void AddEnemy(float posX, float posY);
	void AddFullEnemy();
};

