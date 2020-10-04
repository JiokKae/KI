#pragma once

#include <iostream>
#include <string>

#define WALL	0
#define GRASS	1
#define MUD		2
#define FOREST	3

// 2���� int ����ü
struct Vector2Int
{
	int y, x;
};

// ���� ������ ������ ������ ��ȯ�ϴ� �Լ�
int RandomInRange(int start, int end);

// ���ڿ� �Էµ� ������ ���ڿ��� ��ȯ�ϴ� �Լ�
std::string IntToCharString(int num, std::string ch);

// ���͸� �Է¹޴� �Լ�
void GetEnter();
