#pragma once
#include "GameNode.h"
#include "pch.h"

class Missile;
class Enemy : public GameNode
{
private:
	// 몸체
	POINTFLOAT pos;
	POINTFLOAT direction;
	float speed;
	float size;
	bool isAlive;
	Allies aliies;
	
	// 발사
	int cooltime;
	int shootFrame;

public:
	static HPEN hPenOutline;
	static HBRUSH hBrushInside;
	static int currentEnemyCount;

	HRESULT Init(POINTFLOAT tankPos);	// 멤버 변수 초기화, 메모리 할당
	void Release();						// 메모리 해제
	void Update(POINTFLOAT tankPos);	// 프레임 단위 게임 로직 실행 (데이터 변경)
	void Render(HDC hdc);				// 프레임 단위 출력 (이미지, 텍스트 등)

	void Fire(POINTFLOAT tankPos, Missile* missile, Pattern pattern);
	RECT GetRect();
	POINTFLOAT GetPos();
	int GetSize();
	bool IsAlive() { return isAlive; }
	void Appear();
	void Dead();

	
};

