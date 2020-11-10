#pragma once

#include <Windows.h>
#include <math.h>
#include "KeyManager.h"

#define WINSIZE_X	600
#define WINSIZE_Y	800
#define PI			3.141592f
#define DegreeToRadian(x)	(x * PI / 180.0f)
#define RadianToDegree(x)	(x * 180.0f / PI)

struct FPOINT
{
	float x;
	float y;
};

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;