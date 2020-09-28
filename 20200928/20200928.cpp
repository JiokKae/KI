/*
	1. 소스파일의 분할
	2. 전처리문 define
	3. 열거자 enum
*/

#include <iostream>
#include <string>
#include "setting.h"
/*
	키입력 관련
	W A S D

	난이도에 따른 맵 사이즈
	1 - 5, 2 - 10, 3 - 15
*/

struct Tile
{
	std::string shape;		//콘솔에 출력될 모양
	int posX, posY;
	TileType type;
	int gold;

};


int main()
{
	Tile map[10][10];

	
	map[0][0].type = TileType::EARTH;
	map[0][0].type = TileType::EARTH; 
	map[0][0].type = TileType::EARTH;

	map[0][0].type = TileType::EARTH;

}

struct MapData {
	Tile** map;
	int mapSizeX;
	int mapSizeY;
};

void SetMap(MapData mapData)
{
	for (int i = 0; i < mapData.mapSizeY; i++)
	{
		for (int j = 0; j < mapData.mapSizeX; j++)
		{
			mapData.map[i][j].type = TileType::EARTH;
			mapData.map[i][j].shape = "ㅁ";
			mapData.map[i][j].posX = j;
			mapData.map[i][j].posY = i;
			mapData.map[i][j].gold = 0;
		}
	}
	mapData.map[PLAYER_INIT_Y][PLAYER_INIT_X].shape = "P";
}