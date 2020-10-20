#pragma once
#include "pch.h"
#include "GameNode.h"

class Enemy;
class Missile : public GameNode
{
private:
	float baseSpeed;
	POINTFLOAT speed;
	POINTFLOAT pos;
	int size;
	bool isFire;

public:
	HRESULT Init();								// 멤버 변수 초기화, 메모리 할당
	void Release();								// 메모리 해제
	void Update(Enemy* enemys, int numOfEnemy);	// 프레임 단위 게임 로직 실행 (데이터 변경)
	void Render(HDC hdc);						// 프레임 단위 출력 (이미지, 텍스트 등)

	bool IsFire() { return isFire; }
	POINTFLOAT GetPos() { return pos; }
	int GetSize() { return size; }

	void SetIsFire(bool isFire) { this->isFire = isFire; }
	void SetPos(POINTFLOAT pos) { this->pos = pos; }
	void SetSpeed(int angle) { 
		this->speed.x = (float)cos(RADIAN(angle)) * baseSpeed;
		this->speed.y = (float)sin(RADIAN(angle)) * baseSpeed;
	}
};

