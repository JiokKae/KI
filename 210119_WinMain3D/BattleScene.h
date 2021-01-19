#pragma once
#include "pch.h"
#include "GameNode.h"

class Ship;
class Camel;
class EnemyManager;
class BattleScene :	public GameNode
{
private:
	EnemyManager* enemyMgr;
	Camel* camel1;
	Ship* player;

public:
	virtual HRESULT Init() override;	
	virtual void Release() override;	
	virtual void Update() override;		
	virtual void Render(HDC hdc) override;		

	bool CheckCollision(Missile* m1, Missile* m2);	// 미사일끼리 충돌확인
	float GetDistance(POINTFLOAT pos1, POINTFLOAT pos2);
	float GetAngle(POINTFLOAT pos1, POINTFLOAT pos2);

	BattleScene() {}
	virtual ~BattleScene() {}

};

