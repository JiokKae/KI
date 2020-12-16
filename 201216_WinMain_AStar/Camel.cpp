#include "Camel.h"
#include "Animation.h"
#include "Image.h"

HRESULT Camel::Init(float posX, float posY)
{
	pos.x = posX;
	pos.y = posY;

	//img = ImageManager::GetSingleton()->AddImage("Camel", "Image/camel.bmp", 
	//	300, 267, 4, 3, true, RGB(255, 0, 255));
	img = ImageManager::GetSingleton()->AddImage("TestCamel", "Image/testcamel.bmp",
		300, 267, 4, 3, true, RGB(255, 0, 255));

	ani1 = new Animation();
	ani1->Init(img->GetWidth(), img->GetHeight(), img->GetFrameWidth(), img->GetFrameHeight());
	ani1->SetPlayFrame(true, true);

	ani2 = new Animation();
	ani2->Init(img->GetWidth(), img->GetHeight(), img->GetFrameWidth(), img->GetFrameHeight());
	int aniArray[8] = { 4, 8, 1, 5, 10, 2, 3, 3 };		// 0 ~ 11
	ani2->SetPlayFrame(aniArray, 8);

	ani3 = new Animation();
	ani3->Init(img->GetWidth(), img->GetHeight(), img->GetFrameWidth(), img->GetFrameHeight());
	ani3->SetPlayFrame(7, 2, false, true);

	playAni = ani3;

	playAni->SetKeyFrameUpdateTime(2.0f);
	playAni->Start();

	return S_OK;
}

void Camel::Release()
{
	SAFE_DELETE(ani1);
	SAFE_DELETE(ani2);
	SAFE_DELETE(ani3);
	//if (ani1)
	//{
	//	delete ani1;
	//	ani1 = nullptr;
	//}
}

void Camel::Update()
{
	if (playAni)
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
		{
			playAni->Start();
		}

		playAni->UpdateFrame();
	}
}

void Camel::Render(HDC hdc)
{
	//img->FrameRender(hdc, pos.x, pos.y, )
	img->AnimationRender(hdc, pos.x, pos.y, playAni);
}
