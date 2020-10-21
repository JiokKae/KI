#pragma once
#include "pch.h"

class Missile;

inline double Distance(POINTFLOAT pos1, POINTFLOAT pos2)
{
	return sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2));
}

