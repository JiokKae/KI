#include "EnemyManager.h"
#include "Enemy.h"
HRESULT EnemyManager::Init()
{
	//// 1) �迭���
	//Enemy* enemys = new Enemy[10];
	//for (int i = 0; i < 10; i++)
	//{
	//	enemys[i].Init();
	//}
	//
	//// 2) vector push_back() �Լ� ���
	//for (int i = 0; i < 10; i++)
	//{
	//	vecEnemys.push_back(new Enemy());
	//	vecEnemys[i]->Init();
	//}
	//
	//// 3) vector resize() �Լ� ���
	//vecEnemys.resize(10);
	//for (int i = 0; i < 10; i++)
	//{
	//	vecEnemys[i] = new Enemy();
	//	vecEnemys[i]->Init();
	//}
	//
	// 4) vector reserve() �Լ� ���
	enemyMax = 10;
	vecEnemys.reserve(enemyMax);
	
	return S_OK;
}

void EnemyManager::Release()
{
	for (itEnemys = vecEnemys.begin(); itEnemys != vecEnemys.end(); itEnemys++)
	{
		(*itEnemys)->Release();
		delete (*itEnemys);
	}
}

void EnemyManager::Update(POINTFLOAT targetPos)
{
	for (itEnemys = vecEnemys.begin(); itEnemys != vecEnemys.end(); itEnemys++)
	{
		(*itEnemys)->Update();
		(*itEnemys)->Fire(targetPos, (Pattern)(rand() % (int)Pattern::END));
	}
}

void EnemyManager::Render(HDC hdc)
{
	for (itEnemys = vecEnemys.begin(); itEnemys != vecEnemys.end(); itEnemys++)
	{
		(*itEnemys)->Render(hdc);
	}
}

void EnemyManager::AddEnemy(float posX, float posY)
{
	Enemy* enemy = new Enemy();
	vecEnemys.push_back(enemy);
	enemy->Init(posX, posY);
	
}

void EnemyManager::AddFullEnemy()
{
	for (int i = 0; i < enemyMax; i++)
	{
		vecEnemys.push_back(new Enemy());
		vecEnemys[i]->Init(500 / enemyMax + (i % 5) * 100, 500 / enemyMax + (i / 5) * 100);
	}
}
