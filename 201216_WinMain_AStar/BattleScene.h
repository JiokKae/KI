#pragma once
#include "GameNode.h"

class Camel;
class Tank;
class Enemy;
class Missile;
class EnemyManager;
class SpaceShip;
class BattleScene : public GameNode
{
private:
	SpaceShip* spaceShip;
	Tank* tank1;
	Enemy* enemy1;
	EnemyManager* enemyMgr;
	Camel* camel1;

public:
	virtual HRESULT Init() override;			// 멤버 변수 초기화, 메모리 할당
	virtual void Release() override;			// 메모리 해제
	virtual void Update() override;				// 프레임 단위 게임 로직 실행 (데이터 변경)
	virtual void Render(HDC hdc) override;		// 프레임 단위 출력 (이미지, 텍스트 등)

	bool CheckCollision(Missile* m1, Missile* m2);
	float GetDistance(FPOINT pos1, FPOINT pos2);
	float GetAngle(FPOINT pos1, FPOINT pos2);

	BattleScene() {};
	virtual ~BattleScene() {};

};

