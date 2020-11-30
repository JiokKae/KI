#include "Camel.h"
#include "Image.h"
#include "Animation.h"

HRESULT Camel::Init(float posX, float posY)
{
	pos.x = posX;
	pos.y = posY;

	img = ImageManager::GetSingleton()->AddImage("Camel", "Image/camel.bmp", 300, 267, 4, 3, TRUE, RGB(255, 0, 255));

	ani1 = new Animation();
	ani1->Init(img->GetWidth(), img->GetHeight(), img->GetFrameWidth(), img->GetFrameHeight());
	ani1->SetPlayFrame(true, true);

	ani2 = new Animation();
	ani2->Init(img->GetWidth(), img->GetHeight(), img->GetFrameWidth(), img->GetFrameHeight());
	int arr[8] = { 1, 3, 5, 7, 6, 5, 4, 3 };
	ani2->SetPlayFrame(arr, 8, true);

	ani3 = new Animation();
	ani3->Init(img->GetWidth(), img->GetHeight(), img->GetFrameWidth(), img->GetFrameHeight());
	ani3->SetPlayFrame(7, 3, false, true);
	
	playAni = ani3;
	playAni->SetKeyFrameUpdateTime(0.2f);
	playAni->Start();

	return S_OK;
}

void Camel::Release()
{
	SAFE_DELETE(ani1);
	SAFE_DELETE(ani2);
	SAFE_DELETE(ani3);
}

void Camel::Update()
{
	if (playAni)
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
		{
			playAni->Start();
		}
		playAni->UpdateFrmae();
	}
}

void Camel::Render(HDC hdc)
{
	img->AnimationRender(hdc, pos.x, pos.y, playAni);
}
