// setting.h

/*
	���� ���ÿ� �ʿ��� ���������� �̸� �־����.
	Ű�Է� ����
	W A S D

	���̵��� ���� �� ������
	1 - 5, 2 - 10, 3 - 15

	�÷��̾� ���� ��ġ
	0, 0
*/

#pragma once

/*
	#define �ڵ�1 �ڵ�2
	������ �ܰ迡�� �ڵ� 1�� �ڵ�2�� ��ü�Ѵ�.
*/

//const int Player_INIT_X = 0;

#define PLAYER_INIT_X	0
#define PLAYER_INIT_Y	0

#define INPUT_KEY_UP	'w'
#define INPUT_KEY_DOWN	's'
#define INPUT_KEY_LEFT	'a'
#define INPUT_KEY_RIGHT	'd'

/*
	enum �ڷ���
	: ����Ʈ ������ �����͸� ǥ���� �� ����ϴ� �ڷ���

	enum { ���1, ���2, ���3, ... };
*/

enum BLOODTYPE { BT_A, BT_B, BT_O, BT_AB };
enum TileType
{
	FOREST = 5,
	EARTH,
	SWAMP = 10,
	WATER
};