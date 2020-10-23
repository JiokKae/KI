#pragma once

#include <Windows.h>
#include <math.h>

#define WINDOW_SIZE_X 1920
#define WINDOW_SIZE_Y 1080
#define RADIAN(x)	(x / 180.0 * 3.141592)
#define DEGREE(x)	(x / 3.141592 * 180.0)

extern HINSTANCE g_hInstance;
extern int g_Frame;

inline POINTFLOAT CoordToPlain(int x, int y, float zoom) {
	POINTFLOAT p;
	p.x = (float)(x - 960) / (500.0 * zoom);
	p.y = (float)-(y - 508) / (500.0 * zoom);
	return p;
}

inline void Ellipse(HDC hdc, float x, float y, float r) {
	Ellipse(hdc, x - r, y - r, x + r, y + r);
}

