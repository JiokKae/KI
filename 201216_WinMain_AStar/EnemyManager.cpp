#include "EnemyManager.h"
#include "Enemy.h"

HRESULT EnemyManager::Init()
{
	// 1) �迭 ���
	Enemy* enemys = new Enemy[10];
	for (int i = 0; i < 10; i++)
	{
		enemys[i].Init();
	}

	//// 2) vector push_back()�Լ� ���
	//for (int i = 0; i < 10; i++)
	//{
	//	vecEnemys.push_back(new Enemy());
	//	vecEnemys[i]->Init();
	//}

	//// 3) vector resize()�Լ� ���
	//vecEnemys.resize(10);
	//for (int i = 0; i < 10; i++)
	//{
	//	vecEnemys[i] = new Enemy();
	//	vecEnemys[i]->Init();
	//}

	// 4) vector reserve()�Լ� ���
	vecEnemys.reserve(10);
	for (int i = 0; i < 10; i++)
	{
		vecEnemys.push_back(new Enemy());
		vecEnemys[i]->Init(80 + (i % 5) * 100, 100 + (i / 5) * 100);
	}

	return S_OK;
}

void EnemyManager::Release()
{
	for (itEnemys = vecEnemys.begin();
		itEnemys != vecEnemys.end(); itEnemys++)
	{
		(*itEnemys)->Release();
		delete (*itEnemys);
	}
	vecEnemys.clear();
}

void EnemyManager::Update()
{
	for (itEnemys = vecEnemys.begin();
		itEnemys != vecEnemys.end(); itEnemys++)
	{
		(*itEnemys)->Update();
	}
}

void EnemyManager::Render(HDC hdc)
{
	for (itEnemys = vecEnemys.begin();
		itEnemys != vecEnemys.end(); itEnemys++)
	{
		(*itEnemys)->Render(hdc);
	}
}

void EnemyManager::AddEnemy(float posX, float posY)
{
}
