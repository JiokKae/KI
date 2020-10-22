#pragma once
#include "pch.h"
#include "GameNode.h"

class Missile : public GameNode
{
private:
	// 속도, 좌표, 크기, 발사여부
	float speed;
	FPOINT pos;
	int size;
	bool isFire;
	float angle;
	FPOINT direction;
	
public:
	HRESULT Init();
	void Release();
	void Update(FPOINT enemyPos, int enemySize);
	void Render(HDC hdc);

	bool GetIsFire() { return isFire; }
	void SetIsFire(bool isFire) { this->isFire = isFire; }

	void SetPos(FPOINT pos) { this->pos = pos; }

	void SetAngle(float angle) 
	{ 
		this->angle = angle; 
		direction.x = cosf(DegreeToRadian(angle));
		direction.y = -sinf(DegreeToRadian(angle));
	}

	Missile();
	~Missile();
};

