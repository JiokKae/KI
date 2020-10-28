#pragma once
#include "GameNode.h"

class Circle;
class MainGame : public GameNode
{
private:
	POINT mouse;
	POINT clickedMouse;
	HANDLE hTimer, hTimer2;

	// ������ ����
	HWND hWnd;
	HINSTANCE hInstance;

	// �� ����
	int zoomStart;
	int zooming;

	// ������ ����
	int frame;
	int checkFrame;
	int FPS;
	float zoom = 1.0f;

	// ���� ����
	HBITMAP hbmMem, hbmMemOld;
	HDC hdc, hdcMem;
	HDC hdc_BackGround;

	// �巡�� ����
	bool isDragging;
	bool isMDragging;

	Circle* circle;

public:
	HRESULT Init(HWND hWnd, HINSTANCE hInst);
	void Release();
	void Update();
	void Render(HDC hdc);

	void PrintCos(float degree, float zoom);
	void PrintSin(float degree, float zoom);
	void PrintDegree(float degree, float zoom);
	void PrintAtan2(float a, float b, float zoom);
	

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};