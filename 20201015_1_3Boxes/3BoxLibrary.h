#pragma once

#define WINDOW_SIZE_X		1920
#define WINDOW_SIZE_Y		1000
#define BIGBOX_SPEED		10
#define BIGBOX_SIZE			50
#define BIGBOX_MARGIN		40

#define BIGBOX_COL			(WINDOW_SIZE_X / (BIGBOX_MARGIN + BIGBOX_SIZE)) 
#define BIGBOX_ROW			(WINDOW_SIZE_Y / (BIGBOX_MARGIN + BIGBOX_SIZE)) 
#define BIGBOX_MAX_COUNT	(BIGBOX_COL * BIGBOX_ROW)

#define WORLDBOX_SIZE_X		((BIGBOX_COL- 1) * (BIGBOX_SIZE + BIGBOX_MARGIN) + BIGBOX_MARGIN)
#define WORLDBOX_SIZE_Y		((BIGBOX_ROW - 1) * (BIGBOX_SIZE + BIGBOX_MARGIN) + BIGBOX_MARGIN)
#define LIMIT_TIME			30

// 게임모드 스위치
#define SPECIAL_SWITCH		0x0001
#define AUTO_WALL_SWITCH	0x0002
#define VELOCITY			0x0004
#define SHOOT_MODE			0x0008
#define BOX_COLLISION		0x0010
#define BOX_CHANGE			0x0030

#define MAZE_GAME			(SPECIAL_SWITCH | AUTO_WALL_SWITCH | BOX_CHANGE)
#define SHOOT_GAME			(SHOOT_MODE | VELOCITY | SPECIAL_SWITCH)

#define GAMEMODE			(SHOOT_GAME)


#define KEY_ENTER	0x0D
#define KEY_LEFT	0x25
#define KEY_RIGHT	0x27
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
