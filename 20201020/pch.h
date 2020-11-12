#pragma once

#include <Windows.h>
#include <cmath>
#include "resource.h"

#define WIN_SIZE_X	1200
#define WIN_SIZE_Y	900
#define RADIAN(x)	((x - 90) / 180.0 * 3.141592)

extern HWND g_hWnd;
extern int g_Frame;

inline double Distance(POINTFLOAT pos1, POINTFLOAT pos2)
{
	return sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2));
}