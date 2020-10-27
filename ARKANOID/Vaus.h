#pragma once
#include "pch.h"
#include "GameNode.h"

class Missile;
class Block;
class Vaus : public GameNode
{
private:
	POINT pos;
	int width, height;
	float speed;

	// 미사일
	int numOfMissile;
	int currentMissileCount;
	Missile* missile;

public:
	// 기능 : 멤버함수
	HRESULT Init();				// 멤버 변수 초기화, 메모리 할당
	void Release();				// 메모리 해제
	void Update();				// 프레임 단위 게임 로직 실행 (데이터 변경)
	void LatedUpdate();
	void Render(HDC hdc);		// 프레임 단위 출력 (이미지, 텍스트 등)

	void Fire();

	void Move(float dir);

};

