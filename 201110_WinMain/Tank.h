#pragma once
#include "pch.h"
#include "GameNode.h"

class Missile;
class Enemy;
class Tank : public GameNode
{
private:
	// 속성 : 멤버변수
	RECT rc;
	int size;
	float speed;

	// 포신
	// 포신의 시작점
	// 포신의 끝점
	FPOINT barrelEnd;
	int barrelSize;
	float barrelAngle;

	// 미사일
	Missile* missile;
	int missileCount;

	// 적 (타겟)
	Enemy* target;

public:
	// 기능 : 멤버함수
	HRESULT Init();				// 멤버 변수 초기화, 메모리 할당
	void Release();				// 메모리 해제
	void Update();				// 프레임 단위 게임 로직 실행 (데이터 변경)
	void Render(HDC hdc);		// 프레임 단위 출력 (이미지, 텍스트 등)

	void Fire();
	void Move();
	void Dead();
	void RotateBarrel(float angle);

	Missile* GetMissile() { return missile; }
	int GetMissileCount() { return missileCount; }

	Tank();
	~Tank();
};

