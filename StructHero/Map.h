#pragma once
#include "StructHeroLibrary.h"
#include <ctime>

using namespace std;

// 타일 : (Vector2Int) 좌표 / (int) 타입 / (int) 인카운터 확률 / (bool) 통과가능여부 / (string) 모양
struct Tile 
{
	Vector2Int coord;
	int type;
	int encounterPercent;
	bool passable;
	string shape;
};

// 주변 타일 : 주변 타일을 저장하는 배열
struct AroundTiles 
{
	Tile* tiles[8];
};

class Map
{
private:
	Tile** tiles = nullptr;
	Vector2Int size;			// 맵의 크기
public:
	// 맵을 삭제하는 함수 (동적할당 해제)
	~Map();	
	
	// getter
	Tile GetTile(int y, int x)		{ return tiles[y][x]; }
	Tile& GetTileRef(int y, int x)	{ return tiles[y][x]; }
	Vector2Int GetSize()			{ return size; }

	// setter
	void SetSize(Vector2Int size) { this->size = size; }

	void Delete();
	void Init(int y, int x);

	// 주변 타일을 받아오는 함수
	bool GetAroundEightTiles(Vector2Int coord, AroundTiles& aroundTiles);

	// 무작위로 타일을 가져오는 함수
	Tile GetRandomTile();

	// 타일을 랜덤으로 생성하는 함수
	void PlaceTile(Tile origin, Vector2Int coord, int power);

	// 맵의 타일을 결정해주는 함수
	Tile DecideTile(Vector2Int coord);
	
	// 맵을 생성하는 함수 (동적할당 사용)
	void CreateMap(int difficulty);
	
};

