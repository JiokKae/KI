#pragma once

#include <iostream>
#include <string>

#define WALL	0
#define GRASS	1
#define MUD		2
#define FOREST	3

// 2차원 int 구조체
struct Vector2Int
{
	int y, x;
};

// 범위 내에서 무작위 정수를 반환하는 함수
int RandomInRange(int start, int end);

// 문자와 입력된 길이의 문자열로 반환하는 함수
std::string IntToCharString(int num, std::string ch);

// 엔터를 입력받는 함수
void GetEnter();
