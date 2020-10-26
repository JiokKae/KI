#pragma once

#include <Windows.h>
#include <math.h>
#include "KeyManager.h"

#define WINSIZE_X	1600	
#define WINSIZE_Y	900
#define PI			3.141592f
#define RADIAN(x)	(x * PI / 180.0f)
#define DEGREE(x)	(x * 180.0f / PI)

extern HWND g_hWnd;