#include "TitleScene.h"
#include "Image.h"
#include "Button.h"
#include "ButtonFunction.h"

void GotoBattleScene()
{
    SceneManager::GetSingleton()->ChangeScene("����");
}

HRESULT TitleScene::Init()
{
    img = ImageManager::GetSingleton()->AddImage("Ÿ��Ʋ ����", "Image/bin.bmp", WINSIZE_X, WINSIZE_Y);
    ImageManager::GetSingleton()->AddImage("������ �̵�", "Image/button.bmp", 122, 62, 1, 2);

    bf = new ButtonFunction();

    POINT ptUpFrame = { 0, 0 };
    POINT ptDownFrame = { 0, 1 };

    button1 = new Button();
    button1->Init("������ �̵�", 150, 150, ptDownFrame, ptUpFrame);

    Argument argument1;
    argument1.sceneName = "����";
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
        SceneManager::GetSingleton()->ChangeScene("����");// , "�ε�1");
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
