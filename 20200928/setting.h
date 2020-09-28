// setting.h

/*
	게임 세팅에 필요한 설정값들을 미리 넣어두자.
	키입력 관련
	W A S D

	난이도에 따른 맵 사이즈
	1 - 5, 2 - 10, 3 - 15

	플레이어 시작 위치
	0, 0
*/

#pragma once

/*
	#define 코드1 코드2
	컴파일 단계에서 코드 1을 코드2로 대체한다.
*/

//const int Player_INIT_X = 0;

#define PLAYER_INIT_X	0
#define PLAYER_INIT_Y	0

#define INPUT_KEY_UP	'w'
#define INPUT_KEY_DOWN	's'
#define INPUT_KEY_LEFT	'a'
#define INPUT_KEY_RIGHT	'd'

/*
	enum 자료형
	: 리스트 형태의 데이터를 표현할 때 사용하는 자료형

	enum { 멤버1, 멤버2, 멤버3, ... };
*/

enum BLOODTYPE { BT_A, BT_B, BT_O, BT_AB };
enum TileType
{
	FOREST = 5,
	EARTH,
	SWAMP = 10,
	WATER
};