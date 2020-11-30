#include "TitleScene.h"
#include "Image.h"

HRESULT TitleScene::Init()
{
	img = ImageManager::GetSingleton()->AddImage("Title Scene Image", "Image/bin.bmp", WINSIZE_X, WINSIZE_Y);

	float a = 0;
	for (int i = 0; i < 1000000; i++)
	{
		a += 100.0f;
	}
	//Sleep(500);
	return S_OK;
}

void TitleScene::Release()
{
}

void TitleScene::Update()
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RETURN))
	{
		SceneManager::GetSingleton()->ChangeScene("Battle Scene", "Loading Scene 1");
		return;
	}
}

void TitleScene::Render(HDC hdc)
{
	if (img)
		img->Render(hdc, 0, 0, WINSIZE_X, WINSIZE_Y);
}
