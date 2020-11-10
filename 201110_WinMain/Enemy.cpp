#include "Enemy.h"
#include "Image.h"
#include "MissileManager.h"

HRESULT Enemy::Init(float posX, float posY)
{
	size = 60;
	pos = { posX,  posY };
	speed = 3.0f;
	isDead = false;
	updateCount = 0;
	currFrameX = 0;
	currFrameY = 0;

	missileMgr = new MissileManager;
	missileMgr->Init();

	img = new Image();
	if (FAILED(img->Init("Image/ufo.bmp", 530, 32, 10, 1,
		true, RGB(255, 0, 255))))
	{
		// 예외처리
		MessageBox(g_hWnd, "파일로부터 비트맵 생성에 실패했습니다.",
			"실패", MB_OK);
	}

	return S_OK;
}

void Enemy::Release()
{
	missileMgr->Release();
	delete missileMgr;

	img->Release();
	delete img;
}

void Enemy::Update()
{
	if (updateCount % 10 == 0)
		missileMgr->AddMissile(pos.x, pos.y);

	missileMgr->Update();

	updateCount++;
	
	currFrameX = updateCount / 5 % img->GetMaxFrameX();
	
	AutoMove();
}

void Enemy::Render(HDC hdc)
{
	missileMgr->Render(hdc);

	img->FrameRender(hdc, pos.x, pos.y, currFrameX, currFrameY);

	//Ellipse(hdc, pos.x - (size / 2), pos.y - (size / 2)
	//	, pos.x + (size / 2), pos.y + (size / 2));
}

void Enemy::AutoMove()
{
	pos.x += speed;

	if (pos.x + (size / 2) >= WINSIZE_X ||
		pos.x - (size / 2) <= 0)
	{
		speed *= -1;
	}
}

Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}
