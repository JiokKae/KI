#pragma once

#include "GameNode.h"

class Image;
class MainGame : public GameNode
{
private:
	struct MOUSE_DATA
	{
		int mousePosX, mousePosY;
		int clickedPosX, clickedPosY;
	};

	HDC hdc;
	PAINTSTRUCT ps;
	MOUSE_DATA mouseData;
	bool isInit;

	Image* backBuffer;
	Image* backGround;

	// Scene 추가
	GameNode* titleScene;
	GameNode* battleScene;
	GameNode* loadingScene1;

public:
	HRESULT Init();				// 멤버 변수 초기화, 메모리 할당
	void Release();				// 메모리 해제
	void Update();				// 프레임 단위 게임 로직 실행 (데이터 변경)
	void Render();				// 프레임 단위 출력 (이미지, 텍스트 등)

	LRESULT MainProc(HWND hWnd, UINT iMessage,
		WPARAM wParam, LPARAM lParam);

};
