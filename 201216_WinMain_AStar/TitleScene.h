#pragma once
#include "GameNode.h"

class Image;
class Button;
class ButtonFunction;
class TitleScene : public GameNode
{
private:
	Image* img;
	Button* button1;
	ButtonFunction* bf;

public:
	virtual HRESULT Init() override;			// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release() override;			// �޸� ����
	virtual void Update() override;				// ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc) override;		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	TitleScene() {};
	virtual ~TitleScene() {};

};

