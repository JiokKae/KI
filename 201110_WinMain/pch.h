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

#define WINSIZE_X	600
#define WINSIZE_Y	800
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

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern float g_time;
extern POINT g_ptMouse;