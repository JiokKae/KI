#pragma once
#include "GameNode.h"

class Effect
{
	Image* imgExplosion;
	FPOINT pos;
	bool isActive;
	float time;
	int currFrame;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	bool IsActive() { return isActive; }
	void Active(FPOINT pos);
};

class Image;
class PixelCollisionScene : public GameNode
{
private:
	Image* imgMountain;
	Image* imgMountain2;
	Image* imgBall;
	
	vector<Effect*> explosions;

	FPOINT ballForce;
	FPOINT ballAcceleration;
	FPOINT ballVelocity;
	FPOINT ballPos;
	float ballWeight;
	float ballElasticity;
	bool isCollision;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	
	~PixelCollisionScene();
	PixelCollisionScene();
};