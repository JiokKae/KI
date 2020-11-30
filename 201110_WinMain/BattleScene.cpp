#include "BattleScene.h"
#include "EnemyManager.h"
#include "Missile.h"
#include "Camel.h"
#include "Ship.h"

HRESULT BattleScene::Init()
{
	player = new Ship;
	player->Init();

	enemyMgr = new EnemyManager();
	enemyMgr->Init();
	enemyMgr->AddEnemy(100, 100);

	camel1 = new Camel();
	camel1->Init(200, 200);

	MissileManager::GetSingleton()->Init();
	//Sleep(1000);
	return S_OK;
}

void BattleScene::Release()
{
	SAFE_RELEASE(player);
	SAFE_RELEASE(enemyMgr);
	SAFE_RELEASE(camel1);

	MissileManager::GetSingleton()->Release();
}

void BattleScene::Update()
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_ESCAPE))
	{
		SceneManager::GetSingleton()->ChangeScene("Title Scene", "Loading Scene 1");
		return;
	}

	enemyMgr->Update(player->GetPos());
	camel1->Update();
	player->Update();

	MissileManager::GetSingleton()->Update();
}

void BattleScene::Render(HDC hdc)
{
	enemyMgr->Render(hdc);
	camel1->Render(hdc);
	MissileManager::GetSingleton()->Render(hdc);

	player->Render(hdc);

}

bool BattleScene::CheckCollision(Missile * m1, Missile * m2)
{
	// m1의 반지름 + m2의 반지름 >= m1과 m2사이 거리 (->충돌)
	float halfSize1 = m1->GetSize() / 2.0f;
	float halfSize2 = m2->GetSize() / 2.0f;
	POINTFLOAT pos1 = m1->GetPos();
	POINTFLOAT pos2 = m2->GetPos();

	if (GetDistance(pos1, pos2) <= halfSize1 + halfSize2)
	{
		return true;
	}
	return false;
}

float BattleScene::GetDistance(POINTFLOAT pos1, POINTFLOAT pos2)
{
	float dist = sqrtf((pos2.x - pos1.x) * (pos2.x - pos1.x)
		+ (pos2.y - pos1.y) * (pos2.y - pos1.y));

	return dist;
}

float BattleScene::GetAngle(POINTFLOAT pos1, POINTFLOAT pos2)
{
	float x = pos2.x - pos1.x;
	float y = pos2.y - pos1.y;

	float angle = atan2f(-y, x);

	return angle;
}
