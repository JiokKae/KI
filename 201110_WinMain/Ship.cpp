#include "Ship.h"
#include "MissileManager.h"
#include "Enemy.h"
#include "Image.h"

HRESULT Ship::Init()
{
	size = {52, 64};
	speed = 5.0f;
	pos = { WINSIZE_X / 2, WINSIZE_Y - 100 };
	image = new Image();
	if (FAILED(image->Init("Image/rocket.bmp", 52, 64,
		true, RGB(255, 0, 255))))
	{
		// ����ó��
		MessageBox(g_hWnd, "���Ϸκ��� ��Ʈ�� ������ �����߽��ϴ�.",
			"����", MB_OK);
	}

	return S_OK;
}

void Ship::Release()
{
	image->Release();
	delete image;
}

void Ship::Update()
{
	// �̻��� �߻� Ű�Է�
	if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_SPACE))
	{
		Fire();
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
	{
		pos.x -= speed;
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
	{
		pos.x += speed;
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
	{
		pos.y -= speed;
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
	{
		pos.y += speed;
	}
}

void Ship::Render(HDC hdc)
{
	image->Render(hdc, int(pos.x - size.x / 2), int(pos.y - size.y / 2), int(size.x), int(size.y));
}

void Ship::Fire()
{
	MissileManager::GetSingleton()->AddMissile(allies, { pos.x, pos.y}, 90, Pattern::NONE);
}

void Ship::Move()
{
}

void Ship::Dead()
{
}

