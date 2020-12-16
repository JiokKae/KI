#pragma once
#include "GameNode.h"
#include <vector>

class Enemy;
class EnemyManager : public GameNode
{
private:
	vector<Enemy*>	vecEnemys;
	vector<Enemy*>::iterator itEnemys;

public:
	HRESULT Init();		
	void Release();		
	void Update();		
	void Render(HDC hdc);

	void AddEnemy(float posX, float posY);

};

