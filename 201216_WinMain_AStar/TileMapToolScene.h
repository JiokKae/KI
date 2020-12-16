#pragma once
#include "GameNode.h"

#define TILE_SIZE		32		// 타일 하나의 사이즈
#define SAMPLE_TILE_X	20		// 샘플 타일의 X 갯수
#define SAMPLE_TILE_Y	9		// 샘플 타일의 Y 갯수

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

	// 메인 타일의 정보
	TILE_INFO tileInfo[TILE_X * TILE_Y];

	// 샘플 타일의 정보
	SAMPLE_TILE_INFO sampleTileInfo[SAMPLE_TILE_X * SAMPLE_TILE_Y];

	// 선택된 타일의 정보
	SELECT_TILE_INFO selectTileInfo;

	// 세이브, 로드 버튼
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

