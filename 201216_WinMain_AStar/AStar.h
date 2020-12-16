#pragma once
#include "GameNode.h"

class Image;
class AStarTile 
{
	int idX, idY;
	POINT center;
	RECT rc;

	float costFromStart;	// g : ���������� ���� �������� ���
	float costToGoal;		// h : ���� ������ ������������ ���� ���
	float totalCost;		// f : g + h
	bool isOpened;
	bool isClosed;
	bool isPassable;

	AStarTile* parentTile;	// g���� ������ ���� ��带 ����
	Image* parentImage;
	POINT currFrame;

	COLORREF color;
	HBRUSH hBrush;

public:
	virtual HRESULT Init();
	HRESULT Init(int idx, int idy);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	POINT GetIndex()			{ return POINT{ idX, idY }; }
	POINT GetCenter()			{ return center; }
	float GetTotalCost()		{ return totalCost; }
	AStarTile* GetParent()		{ return parentTile; }
	float GetCostFromStart()	{ return costFromStart; }
	bool IsOpened()				{ return isOpened; }
	bool IsClosed()				{ return isClosed; }
	bool IsPassable()			{ return isPassable; }

	void SetOpened(bool opened) { this->isOpened = opened; }
	void SetClosed(bool closed) { this->isClosed = closed; }
	void SetPassable(bool passable);
	void SetColor(COLORREF color);

	void UnOpen();
	bool Open(AStarTile* parent, AStarTile* start, Image* parentImage, int currFrameX, int currFrameY);

	AStarTile()
		: hBrush(nullptr) 
		, parentImage(nullptr)
	{}
};

#define TILE_WIDTH	32
#define TILE_HEIGHT	32

#define TILE_NUM_X	((int)(WINSIZE_X/TILE_WIDTH))
#define TILE_NUM_Y	((int)(WINSIZE_Y/TILE_HEIGHT))


class AStar : public GameNode
{
private:
	AStarTile map[TILE_NUM_Y][TILE_NUM_X];
	
	list<AStarTile*> openList;

	AStarTile* startTile;
	AStarTile* destTile;
	AStarTile* currTile;
	AStarTile* findRoot;

	bool setPassableValue;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	bool IsMapIn(POINT index);
	bool FindPath();
	void FindPathOneStep();
	
};
