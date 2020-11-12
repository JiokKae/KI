#pragma once

#include <Windows.h>
#include <math.h>
#include <string>
#include "KeyManager.h"
#include "ImageManager.h"
#include "MissileManager.h"
#include "TimerManager.h"

#define WINSIZE_X	600
#define WINSIZE_Y	800
#define PI			3.141592f
#define RADIAN(x)	(x * PI / 180.0f)
#define DEGREE(x)	(x * 180.0f / PI)

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

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern float g_time;