#pragma once
#include "GameNode.h"

#define TILE_SIZE		32		// Ÿ�� �ϳ��� ������
#define SAMPLE_TILE_X	20		// ���� Ÿ���� X ����
#define SAMPLE_TILE_Y	9		// ���� Ÿ���� Y ����

#define TILE_X			20
#define TILE_Y			20

enum TERRAIN { WALL, GRASS, EARTH, WATER, CEMENT, END };

typedef struct tagTile
{
	TERRAIN terrain;
	RECT rc;
	int frameX;
	int frameY;
} TILE_INFO;

typedef struct tagSampleTile
{
	RECT rc;
	int frameX;
	int frameY;
} SAMPLE_TILE_INFO;

typedef struct tagSelectTile
{
	int frameX;
	int frameY;
} SELECT_TILE_INFO;

class Image;
class TileMapToolScene : public GameNode
{
private:
	Image* sampleTile;

	// ���� Ÿ���� ����
	TILE_INFO tileInfo[TILE_X * TILE_Y];

	// ���� Ÿ���� ����
	SAMPLE_TILE_INFO sampleTileInfo[SAMPLE_TILE_X * SAMPLE_TILE_Y];

	// ���õ� Ÿ���� ����
	SELECT_TILE_INFO selectTileInfo;

	// ���̺�, �ε� ��ư
	RECT rcSave;
	RECT rcLoad;

public:
	virtual HRESULT Init() override;	
	virtual void Release() override;	
	virtual void Update() override;		
	virtual void Render(HDC hdc) override;

	void Save();
	void Load();

	TileMapToolScene();
	virtual ~TileMapToolScene() {};
};

