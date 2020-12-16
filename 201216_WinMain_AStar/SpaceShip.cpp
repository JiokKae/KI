#include "SpaceShip.h"
#include "Image.h"

HRESULT SpaceShip::Init()
{
	pos.x = WINSIZE_X / 2.0f;
	pos.y = WINSIZE_Y - 200.0f;

	ImageManager::GetSingleton()->AddImage("快林急",
		"Image/rocket.bmp", 52, 64, true, RGB(255, 0, 255));
	img = ImageManager::GetSingleton()->FindImage("快林急");

	speed = 150.0f;

	return S_OK;
}

void SpaceShip::Release()
{
}

void SpaceShip::Update()
{
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
	{
		pos.x -= speed * TimerManager::GetSingleton()->GetElapsedTime();
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
	{
		pos.x += speed * TimerManager::GetSingleton()->GetElapsedTime();
	}
}

void SpaceShip::Render(HDC hdc)
{
	//img->Render(hdc, pos.x, pos.y);
	img->AlphaRender(hdc, pos.x, pos.y, 50);
}
