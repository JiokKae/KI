#pragma once

#include <Windows.h>
#include <math.h>

#define WINSIZE_X	1920
#define WINSIZE_Y	1000
#define PI			3.141592f
#define DegreeToRadian(x)	(x * PI / 180.0f)

struct FPOINT
{
	float x;
	float y;
};

extern HWND g_hWnd;
extern int g_Frame;