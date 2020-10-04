#include "Map.h"

Map::~Map()
{
	Delete();
}

void Map::Delete()
{
	if (tiles != nullptr)
	{
		for (int i = 0; i < size.y; i++)
			delete[] tiles[i];
		delete[] tiles;
		tiles = nullptr;
	}
}

void Map::Init(int y, int x)
{
	if (tiles != nullptr) {
		Delete();
	}
}

bool Map::GetAroundEightTiles(Vector2Int coord, AroundTiles& aroundTiles)
{
	if (coord.x == 0 || coord.y == 0 || coord.x == size.x + 1 || coord.y == size.y + 1)
		return false;

	aroundTiles.tiles[0] = &tiles[coord.y - 1][coord.x - 1];
	aroundTiles.tiles[1] = &tiles[coord.y - 1][coord.x];
	aroundTiles.tiles[2] = &tiles[coord.y - 1][coord.x + 1];
	aroundTiles.tiles[3] = &tiles[coord.y][coord.x - 1];
	aroundTiles.tiles[4] = &tiles[coord.y][coord.x + 1];
	aroundTiles.tiles[5] = &tiles[coord.y + 1][coord.x + 1];
	aroundTiles.tiles[6] = &tiles[coord.y + 1][coord.x];
	aroundTiles.tiles[7] = &tiles[coord.y + 1][coord.x - 1];

	return true;
}

Tile Map::GetRandomTile()
{
	int y = RandomInRange(1, size.y);
	int x = RandomInRange(1, size.x);

	return tiles[y][x];
}

void Map::PlaceTile(Tile origin, Vector2Int coord, int power)
{
	Tile& currentTile = tiles[coord.y][coord.x];
	if (currentTile.type != origin.type && currentTile.type != WALL && power >= RandomInRange(0, 100))
	{
		currentTile.encounterPercent = origin.encounterPercent;
		currentTile.shape = origin.shape;
		currentTile.type = origin.type;

		for (int i = 0; i < 8; i++)
		{
			AroundTiles aroundTiles;
			if (GetAroundEightTiles(coord, aroundTiles))
			{
				PlaceTile(origin, aroundTiles.tiles[i]->coord, power - 30);
			}
		}

	}
	else
		return;
}

Tile Map::DecideTile(Vector2Int coord)
{
	Tile Wall = { {}, WALL	, 0		, false	, "  " };
	Tile Grass = { {}, GRASS	, 10	, true	, "§¤" }; // ¢Æ
	Tile Mud = { {}, MUD	, 30	, true	, "~~" };
	Tile Forest = { {}, FOREST, 20	, true	, "¢¿" };
	Tile newTile;
	if (coord.x == 0 || coord.y == 0 || coord.x == size.x + 1 || coord.y == size.y + 1)
	{
		newTile = Wall;
	}
	else
	{
		newTile = Grass;
	}

	newTile.coord = coord;

	return newTile;
}
void Map::CreateMap(int difficulty)
{
	srand((unsigned int)time(NULL));
	int mudSeed = difficulty;
	int forestSeed = difficulty - 1;
	tiles = new Tile * [size.y + 2];
	for (int y = 0; y < size.y + 2; y++)
	{
		tiles[y] = new Tile[size.x + 2];
		for (int x = 0; x < size.x + 2; x++)
		{
			tiles[y][x] = DecideTile({ y, x });
		}
	}
	Tile Mud = { {}, MUD, 30, true, "~~" };
	Tile Forest = { {}, FOREST, 20, true, "¢¿" };
	Vector2Int coord;
	while (mudSeed > 0)
	{
		coord.x = RandomInRange(1, size.x);
		coord.y = RandomInRange(1, size.y);
		cout << "mudSeed" << mudSeed << endl;
		PlaceTile(Mud, coord, 80 + mudSeed * 20);
		mudSeed--;

	}
	while (forestSeed > 0)
	{
		coord.x = RandomInRange(1, size.x);
		coord.y = RandomInRange(1, size.y);
		cout << "forestSeed" << forestSeed << endl;
		PlaceTile(Forest, coord, 80 + forestSeed * 20);
		forestSeed--;

	}
}
