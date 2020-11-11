#pragma once
#include "pch.h"
#include "GameNode.h"

class Missile;
class Enemy;
class Image;
class Ship : public GameNode
{
private:
	RECT rc;
	Allies allies;
	POINTFLOAT pos;
	POINTFLOAT size;
	float speed;

	Image* image;
	

public:
	HRESULT Init();				// 멤버 변수 초기화, 메모리 할당
	void Release();				// 메모리 해제
	void Update();				// 프레임 단위 게임 로직 실행 (데이터 변경)
	void Render(HDC hdc);		// 프레임 단위 출력 (이미지, 텍스트 등)

	POINTFLOAT GetPos() { return pos; }

	void Fire();
	void Move();
	void Dead();

	
};

