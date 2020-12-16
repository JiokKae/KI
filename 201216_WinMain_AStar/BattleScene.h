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
	virtual HRESULT Init() override;			// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release() override;			// �޸� ����
	virtual void Update() override;				// ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc) override;		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	bool CheckCollision(Missile* m1, Missile* m2);
	float GetDistance(FPOINT pos1, FPOINT pos2);
	float GetAngle(FPOINT pos1, FPOINT pos2);

	BattleScene() {};
	virtual ~BattleScene() {};

};

