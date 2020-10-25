#pragma once

#include <Windows.h>
#include <math.h>


#define WINDOW_SIZE_X 1920
#define WINDOW_SIZE_Y 1080
#define RADIAN(x)	(x / 180.0f * 3.141592f)
#define DEGREE(x)	(x / 3.141592f * 180.0f)

#define KEY_A 0x41 
#define KEY_B 0x42
#define KEY_C 0x43
#define KEY_D 0x44
#define KEY_E 0x45
#define KEY_F 0x46
#define KEY_G 0x47
#define KEY_H 0x48
#define KEY_I 0x49
#define KEY_J 0x4A
#define KEY_K 0x4B
#define KEY_L 0x4C
#define KEY_M 0x4D
#define KEY_N 0x4E
#define KEY_O 0x4F
#define KEY_P 0x50
#define KEY_Q 0x51
#define KEY_R 0x52
#define KEY_S 0x53
#define KEY_T 0x54
#define KEY_U 0x55
#define KEY_V 0x56
#define KEY_W 0x57
#define KEY_X 0x58
#define KEY_Y 0x59
#define KEY_Z 0x5A

extern HINSTANCE g_hInstance;
extern int g_Frame;

enum class Allies {
	PLAYER,
	ENEMY,
};

enum class Pattern {
	NONE,
	FIREWORK,
	ARROW,
	SHOTGUN,
	NEWS,
	HURRICANE,
};


inline POINTFLOAT CoordToPlain(int x, int y, float zoom) 
{
	POINTFLOAT p;
	p.x = (x - 960.0f) / (500.0f * zoom);
	p.y = -(y - 508.0f) / (500.0f * zoom);
	return p;
}

inline void Ellipse(HDC hdc, float x, float y, float r) 
{
	Ellipse(hdc, (int)(x - r), (int)(y - r), (int)(x + r), (int)(y + r));
}

inline float Lerp(float a, float b, float t)
{
	return a + (b - a) * t;
}

inline POINTFLOAT Normalize(POINTFLOAT vector) 
{
	float distance = sqrtf(powf(vector.x, 2) + powf(vector.y, 2));
	vector.x /= distance;
	vector.y /= distance;
	return vector;
}

inline int CampareDistance(POINTFLOAT pos1, POINTFLOAT pos2) 
{
	if (powf(pos1.x, 2) + powf(pos1.y, 2) > powf(pos2.x, 2) + powf(pos2.y, 2))
		return -1;
	else if (powf(pos1.x, 2) + powf(pos1.y, 2) < powf(pos2.x, 2) + powf(pos2.y, 2))
		return 1;
	else
		return 0;
}

inline const POINTFLOAT operator+(const POINTFLOAT& pf1, const POINTFLOAT& pf2) {
	POINTFLOAT temp;
	temp.x = pf1.x + pf2.x;
	temp.y = pf1.y + pf2.y;
	return temp;
}
inline const POINTFLOAT operator-(const POINTFLOAT& pf1, const POINTFLOAT& pf2) {
	POINTFLOAT temp;
	temp.x = pf1.x - pf2.x;
	temp.y = pf1.y - pf2.y;
	return temp;
}