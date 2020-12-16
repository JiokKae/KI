#include "Enemy.h"
#include "Image.h"
#include "MissileManager.h"

HRESULT Enemy::Init(float posX/* = 0.0f*/, float posY/* = 0.0f*/)
{
	size = 60;
	pos = { posX, posY };
	speed = 3.0f;
	isDead = false;
	updateCount = 0;
	currFrameX = 0;
	currFrameY = 0;
	fireTime = 0.0f;

	img = ImageManager::GetSingleton()->FindImage("UFO");

	//img = new Image();
	//if (FAILED(img->Init("Image/ufo.bmp", 530, 32, 10, 1,
	//	true, RGB(255, 0, 255))))
	//{
	//	// ����ó��
	//	MessageBox(g_hWnd, "���Ϸκ��� ��Ʈ�� ������ �����߽��ϴ�.",
	//		"����", MB_OK);
	//}

	missileMgr = new MissileManager();
	missileMgr->Init();
	missileMgr->SetOwner(this);

	fireCount = 0;

	return S_OK;
}

void Enemy::Release()
{
	missileMgr->Release();
	delete missileMgr;
}

void Enemy::Update()
{
	//AutoMove();

	updateCount++;

	if (updateCount % 5 == 0)
	{
		currFrameX++;
		if (currFrameX >= img->GetMaxFrameX())
		{
			currFrameX = 0;
		}
		updateCount = 0;
	}

	fireCount++;

	//float deltaTime = TimerManager::GetSingleton()->GetElapsedTime();
	fireTime += TimerManager::GetSingleton()->GetElapsedTime();

	if (fireTime >= 3.0f/*3�ʿ� �� ��*/)
	//if (fireCount % 200 == 0/*200�����ӿ� �� ��*/)
	{
		missileMgr->Fire();
		fireCount = 0;
		fireTime = 0.0f;
	}

	// �̻��� �Ŵ���
	missileMgr->Update();
}

void Enemy::Render(HDC hdc)
{
	if (img)
	{
		img->FrameRender(hdc, pos.x, pos.y, currFrameX, currFrameY);
	}

	// �̻��� �Ŵ���
	missileMgr->Render(hdc);

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
