#pragma once

#include <Windows.h>
#include <math.h>
#include <vector>
#include <map>
#include <string>
using namespace std;
#include "KeyManager.h"
#include "ImageManager.h"
#include "MissileManager.h"
#include "SceneManager.h"
#include "TimerManager.h"
#include "SoundManager.h"

#define WINSIZE_X	1600
#define WINSIZE_Y	900
#define WINSIZE_TILE_MAP_X	1600
#define WINSIZE_TILE_MAP_Y	900
#define EPSILON		0.00001f
#define PI			3.141592f
#define RADIAN(x)	(x * PI / 180.0f)
#define DEGREE(x)	(x * 180.0f / PI)
#define SAFE_DELETE(p) 		{if (p) delete p, p = nullptr; }
#define SAFE_ARR_DELETE(p) 	{if (p) delete[] p, p = nullptr; }
#define SAFE_RELEASE(p) 	{if (p) p->Release(), delete p, p = nullptr; }

enum class Allies {
	PLAYER,
	ENEMY,
	END
};

enum class Pattern {
	NONE,
	FIREWORK,
	ARROW,
	SHOTGUN,
	NEWS,
	HURRICANE,
	STOP,
	STOPSHOTGUN,
	RANDOM,
	END
};

struct Argument {
	string a;
	string b;
};

struct Argument2 {
	void* arg[2];
};


extern HWND			g_hWnd;
extern HINSTANCE	g_hInstance;
extern float		g_time;
extern float		g_mousezDelta;
extern POINT		g_ptMouse;

inline void SetWindowSize(int startX, int startY, int sizeX, int sizeY)
{
	// ������ �۾����� ����
	RECT rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = sizeX;
	rc.bottom = sizeY;

	// ���� ������ ũ�� �޾ƿ���
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

	// �̵�
	MoveWindow(g_hWnd, startX, startY, rc.right - rc.left, rc.bottom - rc.top, true);
}

template <typename T>
inline T Clamp(T value, T min, T max)
{
	if (value > max) return max;
	else if (value < min) return min;
	return value;
}

inline RECT GetWindowRect()
{
	RECT rc;
	POINT lt, rb;
	GetClientRect(g_hWnd, &rc);
	// Ŭ���̾�Ʈ ũ�⸦ �޾ƿ�
	lt.x = rc.left;
	lt.y = rc.top;
	rb.x = rc.right;
	rb.y = rc.bottom;
	// �޾ƿ� Ŭ���̾�Ʈ ũ�⸦��ǥ�� �Է�
	ClientToScreen(g_hWnd, &lt);
	ClientToScreen(g_hWnd, &rb);
	// Ŭ���̾�Ʈ �� ��ǥ�� ������� ��ǥ�� ��ȯ
	rc.left = lt.x;
	rc.top = lt.y;
	rc.right = rb.x;
	rc.bottom = rb.y;

	return rc;
}
