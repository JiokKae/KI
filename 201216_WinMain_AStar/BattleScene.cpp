#include "BattleScene.h"
#include "Tank.h"
#include "Enemy.h"
#include "Missile.h"
#include "EnemyManager.h"
#include "SpaceShip.h"
#include "Camel.h"

HRESULT BattleScene::Init()
{
	camel1 = new Camel();
	camel1->Init(WINSIZE_X / 2, WINSIZE_Y / 2);

	spaceShip = new SpaceShip();
	spaceShip->Init();

	enemyMgr = new EnemyManager();
	enemyMgr->Init();

	tank1 = new Tank();
	tank1->Init();

	enemy1 = new Enemy();
	enemy1->Init();
	tank1->SetTarget(enemy1);

	return S_OK;
}

void BattleScene::Release()
{
	SAFE_RELEASE(camel1);
	SAFE_RELEASE(spaceShip);
	SAFE_RELEASE(enemyMgr);
	SAFE_RELEASE(tank1);
	SAFE_RELEASE(enemy1);
}

void BattleScene::Update()
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_ESCAPE))
	{
		SceneManager::GetSingleton()->ChangeScene("타이틀");
		return;
	}

	if (camel1)
		camel1->Update();

	//if (spaceShip)
	//	spaceShip->Update();

	//if (enemyMgr)
	//	enemyMgr->Update();

	//tank1->Update();
	//enemy1->Update();

#pragma region 미사일 간 충돌처리
	//Missile *m1, *m2;

	//int missileCount = tank1->GetMissileCount();
	//for (int i = 0; i < missileCount - 1; i++)
	//{
	//	m1 = &(tank1->GetMissile()[i]);
	//	if (!m1->GetIsFire())	continue;

	//	for (int j = i + 1; j < missileCount; j++)
	//	{
	//		m2 = &(tank1->GetMissile()[j]);
	//		if (!m2->GetIsFire())	continue;

	//		if (CheckCollision(m1, m2))
	//		{
	//			// 충돌 시 처리
	//			float angle1 = GetAngle(m1->GetPos(), m2->GetPos());
	//			float angle2 = GetAngle(m2->GetPos(), m1->GetPos());

	//			m2->SetAngle(angle1);
	//			m1->SetAngle(angle2);

	//			//m1->SetSpeed(0.0f);
	//			//m2->SetSpeed(0.0f);
	//		}
	//	}
	//}
#pragma endregion
}

void BattleScene::Render(HDC hdc)
{
	if (camel1)
		camel1->Render(hdc);

	//if (enemyMgr)
	//	enemyMgr->Render(hdc);

	//if (spaceShip)
	//	spaceShip->Render(hdc);

	//tank1->Render(hdc);
	//enemy1->Render(hdc);
}


bool BattleScene::CheckCollision(Missile* m1, Missile* m2)
{
	// m1의 반지름 + m2의 반지름 >= m1과 m2사이 거리 (->충돌)
	float halfSize1 = m1->GetSize() / 2.0f;
	float halfSize2 = m2->GetSize() / 2.0f;
	FPOINT pos1 = m1->GetPos();
	FPOINT pos2 = m2->GetPos();

	if (GetDistance(pos1, pos2) <= halfSize1 + halfSize2)
	{
		return true;
	}
	return false;
}

float BattleScene::GetDistance(FPOINT pos1, FPOINT pos2)
{
	float dist = sqrtf((pos2.x - pos1.x) * (pos2.x - pos1.x)
		+ (pos2.y - pos1.y) * (pos2.y - pos1.y));

	return dist;
}

float BattleScene::GetAngle(FPOINT pos1, FPOINT pos2)
{
	float x = pos2.x - pos1.x;
	float y = pos2.y - pos1.y;

	float angle = atan2f(-y, x);

	return angle;
}