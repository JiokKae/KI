#include "Enemy.h"
#include "Image.h"

HRESULT Enemy::Init()
{
	size = 100;
	pos = { 100.0f, 100.0f };
	speed = 5.0f;
	isDead = false;

	image = new Image();
	if (FAILED(image->Init("Image/����.bmp", size, size, true, RGB(255, 0, 255))))
	{
		// ����ó��
		MessageBox(g_hWnd, "���Ϸκ��� ��Ʈ�� ������ �����߽��ϴ�.", "����", MB_OK);
	}

	return S_OK;
}

void Enemy::Release()
{
	delete image;
}

void Enemy::Update()
{
	AutoMove();
}

void Enemy::Render(HDC hdc)
{
	if (image)
	{
		image->Render(hdc, pos.x - (size / 2), pos.y - (size / 2));
	}
//	Ellipse(hdc, pos.x - (size / 2), pos.y - (size / 2), pos.x + (size / 2), pos.y + (size / 2));
}

void Enemy::AutoMove()
{
	pos.x += speed;

	if ( pos.x + (size / 2) >= WINSIZE_X || pos.x - (size / 2) <= 0 )
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
