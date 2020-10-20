#pragma once

#include <Windows.h>
#include <cmath>
#include "resource.h"

#define WIN_SIZE_X	1200
#define WIN_SIZE_Y	900
#define RADIAN(x)	((x - 90) / 180.0 * 3.141592)

extern HWND g_hWnd;
extern int g_Frame;