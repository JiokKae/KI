#pragma once

#include <Windows.h>
#include <math.h>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <deque>
using namespace std;

#include "KeyManager.h"
#include "ImageManager.h"
#include "TimerManager.h"
#include "SceneManager.h"

#define WINSIZE_X	1600
#define WINSIZE_Y	900
#define WINSIZE_TILE_MAP_X	1400
#define WINSIZE_TILE_MAP_Y	800
#define PI			3.141592f
#define DegreeToRadian(x)	(x * PI / 180.0f)
#define RadianToDegree(x)	(x * 180.0f / PI)
#define SAFE_DELETE(p)		{ if (p) { delete p; p = nullptr; } }
#define SAFE_ARR_DELETE(p)	{ if (p) { delete[] p; p = nullptr; } }
#define SAFE_RELEASE(p)		{ if (p) { p->Release(); delete p; p = nullptr; } }

struct FPOINT
{
	float x;
	float y;
};

struct Argument
{
	string sceneName;
	string loadingSceneName;
};

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern POINT g_ptMouse;

inline void SetWindowSize(int startX, int startY, int sizeX, int sizeY)
{
	// 윈도우 작업영역 지정
	RECT rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = sizeX;
	rc.bottom = sizeY;

	// 실제 윈도우 크기 받아오기
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

	// 이동
	MoveWindow(g_hWnd, startX, startY, rc.right - rc.left, rc.bottom - rc.top, true);
}
