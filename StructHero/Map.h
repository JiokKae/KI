#pragma once
#include "StructHeroLibrary.h"
#include <ctime>

using namespace std;

// Ÿ�� : (Vector2Int) ��ǥ / (int) Ÿ�� / (int) ��ī���� Ȯ�� / (bool) ������ɿ��� / (string) ���
struct Tile 
{
	Vector2Int coord;
	int type;
	int encounterPercent;
	bool passable;
	string shape;
};

// �ֺ� Ÿ�� : �ֺ� Ÿ���� �����ϴ� �迭
struct AroundTiles 
{
	Tile* tiles[8];
};

class Map
{
private:
	Tile** tiles = nullptr;
	Vector2Int size;			// ���� ũ��
public:
	// ���� �����ϴ� �Լ� (�����Ҵ� ����)
	~Map();	
	
	// getter
	Tile GetTile(int y, int x)		{ return tiles[y][x]; }
	Tile& GetTileRef(int y, int x)	{ return tiles[y][x]; }
	Vector2Int GetSize()			{ return size; }

	// setter
	void SetSize(Vector2Int size) { this->size = size; }

	void Delete();
	void Init(int y, int x);

	// �ֺ� Ÿ���� �޾ƿ��� �Լ�
	bool GetAroundEightTiles(Vector2Int coord, AroundTiles& aroundTiles);

	// �������� Ÿ���� �������� �Լ�
	Tile GetRandomTile();

	// Ÿ���� �������� �����ϴ� �Լ�
	void PlaceTile(Tile origin, Vector2Int coord, int power);

	// ���� Ÿ���� �������ִ� �Լ�
	Tile DecideTile(Vector2Int coord);
	
	// ���� �����ϴ� �Լ� (�����Ҵ� ���)
	void CreateMap(int difficulty);
	
};

