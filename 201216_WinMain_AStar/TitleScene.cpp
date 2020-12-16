#include "TitleScene.h"
#include "Image.h"
#include "Button.h"
#include "ButtonFunction.h"

void GotoBattleScene()
{
    SceneManager::GetSingleton()->ChangeScene("전투");
}

HRESULT TitleScene::Init()
{
    img = ImageManager::GetSingleton()->AddImage("타이틀 원빈", "Image/bin.bmp", WINSIZE_X, WINSIZE_Y);
    ImageManager::GetSingleton()->AddImage("전투씬 이동", "Image/button.bmp", 122, 62, 1, 2);

    bf = new ButtonFunction();

    POINT ptUpFrame = { 0, 0 };
    POINT ptDownFrame = { 0, 1 };

    button1 = new Button();
    button1->Init("전투씬 이동", 150, 150, ptDownFrame, ptUpFrame);

    Argument argument1;
    argument1.sceneName = "전투";
    argument1.loadingSceneName = "";
    button1->SetButtonFunc(&ButtonFunction::ChangeScene, bf, argument1);

    return S_OK;
}

void TitleScene::Release()
{
    SAFE_RELEASE(button1);
    SAFE_DELETE(bf);
}

void TitleScene::Update()
{
    if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RETURN))
    {
        SceneManager::GetSingleton()->ChangeScene("전투");// , "로딩1");
        return;
    }

    if (button1)
        button1->Update();
}

void TitleScene::Render(HDC hdc)
{
    if (img)
        img->Render(hdc, 0, 0);
    if (button1)
        button1->Render(hdc);
}
