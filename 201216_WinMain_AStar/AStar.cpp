#include "AStar.h"
#include "Image.h"

HRESULT AStar::Init()
{
	for (int y = 0; y < TILE_NUM_Y; y++)
	{
		for (int x = 0; x < TILE_NUM_X; x++)
		{
			if (startTile == nullptr)
				map[y][x].Init(x, y);
			else
				map[y][x].UnOpen();

			if(map[y][x].IsPassable() == false)
				map[y][x].SetColor(RGB(0, 0, 0));
		}
	}

	if(startTile == nullptr)
		startTile = &map[0][0];
	startTile->SetColor(RGB(0, 255, 255));

	if (destTile == nullptr)
		destTile = &map[15][8];
	destTile->SetColor(RGB(255, 255, 0));

	currTile = startTile;

	return S_OK;
}

void AStar::Release()
{
}

void AStar::Update()
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown('X'))
	{
		this->FindPathOneStep();
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_SPACE))
	{
		this->FindPathOneStep();
	}
	if (KeyManager::GetSingleton()->IsOnceKeyDown('F'))
	{
		this->FindPath();
	}
	if (KeyManager::GetSingleton()->IsOnceKeyDown('I'))
	{
		this->Init();
	}

	// 샘플 타일 영역 안 인지 확인
	RECT rcMap;
	rcMap.left = 0;
	rcMap.top = 0;
	rcMap.right = rcMap.left + TILE_NUM_X * TILE_WIDTH;
	rcMap.bottom = rcMap.top + TILE_NUM_Y * TILE_HEIGHT;

	if (PtInRect(&rcMap, g_ptMouse))
	{
		if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
		{
			int posX = g_ptMouse.x - rcMap.left, posY = g_ptMouse.y - rcMap.top;
			int idX = posX / TILE_WIDTH;
			int idY = posY / TILE_HEIGHT;

			startTile = &map[idY][idX];
			startTile->SetColor(RGB(0, 255, 255));
			Init();
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RBUTTON))
		{
			int posX = g_ptMouse.x - rcMap.left, posY = g_ptMouse.y - rcMap.top;
			int idX = posX / TILE_WIDTH;
			int idY = posY / TILE_HEIGHT;

			destTile = &map[idY][idX];
			destTile->SetColor(RGB(255, 255, 0));
			Init();
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_MBUTTON))
		{
			int posX = g_ptMouse.x - rcMap.left, posY = g_ptMouse.y - rcMap.top;
			int idX = posX / TILE_WIDTH;
			int idY = posY / TILE_HEIGHT;
			
			setPassableValue = !map[idY][idX].IsPassable();
		}
		if (KeyManager::GetSingleton()->IsStayKeyDown(VK_MBUTTON))
		{
			int posX = g_ptMouse.x - rcMap.left, posY = g_ptMouse.y - rcMap.top;
			int idX = posX / TILE_WIDTH;
			int idY = posY / TILE_HEIGHT;

			map[idY][idX].SetPassable(setPassableValue);
			Init();
		}
	}

}

void AStar::Render(HDC hdc)
{
	for (int y = 0; y < TILE_NUM_Y; y++)
	{
		for (int x = 0; x < TILE_NUM_X; x++)
		{
			map[y][x].Render(hdc);
		}
	}

	char text[50];
	wsprintf(text, "커렌");
	TextOut(hdc, currTile->GetIndex().x * TILE_WIDTH, currTile->GetIndex().y * TILE_HEIGHT, text, strlen(text));
}

bool AStar::FindPath()
{
	this->Init();

	openList.clear();
	openList.push_back(startTile);
	while (currTile != destTile)
	{
		// 실패
		if (openList.empty()) return false;

		list<AStarTile*>::iterator it;
		list<AStarTile*>::iterator MinIt;
		float MinTotalCost = FLT_MAX;

		// 가장 작은 노드 찾기
		for (it = openList.begin(); it != openList.end(); it++)
		{
			if (MinTotalCost > (*it)->GetTotalCost())
			{
				MinTotalCost = (*it)->GetTotalCost();
				MinIt = it;
			}
		}

		currTile = *MinIt;
		currTile->SetClosed(true);
		if (currTile != startTile && currTile != destTile)
			currTile->SetColor(RGB(50, 50, 50));
		openList.erase(MinIt);

		// 주변 
		for (int y = currTile->GetIndex().y - 1; y <= currTile->GetIndex().y + 1; y++)
		{
			for (int x = currTile->GetIndex().x - 1; x <= currTile->GetIndex().x + 1; x++)
			{
				AStarTile* tile = &map[y][x];
				if (IsMapIn({ x, y }) && tile->IsClosed() == false && tile->IsPassable() && tile->IsOpened() == false)
				{
					tile->Open(currTile, destTile,ImageManager::GetSingleton()->FindImage("parent"),0,0);
					if (tile != startTile && tile != destTile)
						tile->SetColor(RGB(255, 255, 255));
					tile->SetOpened(true);
					openList.push_back(tile);
				}
			}
		}
	}

	// 성공
	return true;
}

bool AStar::IsMapIn(POINT index)
{
	if (index.x < 0 || index.x > TILE_NUM_X - 1
		|| index.y < 0 || index.y > TILE_NUM_Y - 1)
		return false;
	else
		return true;
}

void AStar::FindPathOneStep()
{
	// 만약 시작되지 않았다면 전체를 초기화 한다.
	if (startTile->IsClosed() == false)
	{
		this->Init();

		openList.clear(); 
		openList.push_back(startTile);
	}
	// 만약 도착했다면 부모를 타고가 루트를 찾는다.
 	if (currTile == destTile)
	{
		if (findRoot == startTile)
			return;

		// 스타트타일은 칠하지마
		if(findRoot->GetParent() != startTile)
			findRoot->GetParent()->SetColor(RGB(255,0,0));

		findRoot = findRoot->GetParent();
		return;
	}

	//만약 오픈리스트가 비어있다면 작동을 안한다.
	if (openList.empty()) return;

	list<AStarTile*>::iterator it;
	list<AStarTile*>::iterator MinIt;
	float MinTotalCost = FLT_MAX;

	// 오픈리스트에서 코스트가 가장 작은 노드 찾기
	for (it = openList.begin(); it != openList.end(); it++)
	{
		if (MinTotalCost > (*it)->GetTotalCost())
		{
			MinTotalCost = (*it)->GetTotalCost();
			MinIt = it;
		}
	}

 	currTile = *MinIt; 
	currTile->SetClosed(true);
	if(currTile != startTile && currTile != destTile)
		currTile->SetColor(RGB(50, 50, 50));
	openList.erase(MinIt);

	// 가장 작은노드의 주변 노드를 검사해서 오픈리스트에 넣기
	for (int y = currTile->GetIndex().y - 1; y <= currTile->GetIndex().y + 1; y++)
	{
		for (int x = currTile->GetIndex().x - 1; x <= currTile->GetIndex().x + 1; x++)
		{
			AStarTile* tile = &map[y][x];
			if (IsMapIn({ x, y }) && tile->IsPassable())
			{
				if (bool result = tile->Open(currTile, destTile, ImageManager::GetSingleton()->FindImage("parent"), x + 1 - currTile->GetIndex().x, y + 1 - currTile->GetIndex().y))
				{
					if (tile->IsOpened() == false && tile->IsClosed() == false)
					{
						tile->SetOpened(true);
						if (tile != startTile && tile != destTile)
							tile->SetColor(RGB(255, 255, 255));
						openList.push_back(tile);
					}		
				}
			}
		}
	}

	// 도착했다면 길찾기 프로세스 시작
	if (currTile == destTile)
	{
		findRoot = destTile;
	}

	// 성공
	return;
}

HRESULT AStarTile::Init()
{
	return E_NOTIMPL;
}

HRESULT AStarTile::Init(int idx, int idy)
{
	this->idX = idx;
	this->idY = idy;

	center.x = idX * TILE_WIDTH + (TILE_WIDTH / 2);
	center.y = idY * TILE_HEIGHT + (TILE_HEIGHT / 2);

	rc.left = idX * TILE_WIDTH;
	rc.right = rc.left + TILE_WIDTH;
	rc.top = idY * TILE_HEIGHT;
	rc.bottom = rc.top + TILE_HEIGHT;

	costFromStart = 0.0f;	// g : 시작점부터 현재 노드까지의 비용
	costToGoal = 0.0f;		// h : 현재 노드부터 목적지까지의 예상 비용
	totalCost = 0.0f;		// f : g + h
	
	isClosed = false;
	isPassable = true;

	parentTile = nullptr;	// g갱신 때마다 이전 노드를 저장
	parentImage = nullptr;
	SetColor(RGB(220, 220, 220));
	
	return S_OK;
}

void AStarTile::Release()
{
	DeleteObject(hBrush);
}

void AStarTile::Update()
{
}

void AStarTile::Render(HDC hdc)
{
	SelectObject(hdc, hBrush);
	FillRect(hdc, &rc, hBrush);

	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	if (parentImage)
	{
		parentImage->FrameRender(hdc, center.x, center.y, currFrame.x, currFrame.y);
	}
	if (0 && totalCost != 0)
	{
		char str[50];
		wsprintf(str, "%d", int(totalCost));
		TextOut(hdc, rc.left, rc.top, str, strlen(str));
	}
}

void AStarTile::SetColor(COLORREF color)
{
	this->color = color;
	if(hBrush != nullptr)
		DeleteObject(hBrush);
	hBrush = CreateSolidBrush(this->color);
}

void AStarTile::SetPassable(bool passable)
{
	this->isPassable = passable;
	if (passable == false)
	{
		SetColor(RGB(0, 0, 0));
	}
	else
		SetColor(RGB(220, 220, 220));
}

bool AStarTile::Open(AStarTile* parent, AStarTile* goal, Image* parentImage, int currFrameX, int currFrameY)
{
	float newCostFromStart;
	float newCostToGoal;
	float newTotalCost;

	if (abs(parent->GetIndex().x - idX) + abs(parent->GetIndex().y - idY) == 1)
		newCostFromStart = parent->GetCostFromStart() + 10;
	else
		newCostFromStart = parent->GetCostFromStart() + 14;

	newCostToGoal = (abs(goal->GetIndex().x - idX) + abs(goal->GetIndex().y - idY)) * 10;
	newCostToGoal *= newCostToGoal;

	newTotalCost = newCostFromStart + newCostToGoal;
	
	if (isClosed)
		return false;
	// 새로운 코스트가 기존의 코스트보다 크면 탈출; (골이여야댐)
	//if (isOpened && costToGoal < newCostToGoal)
	if (isOpened && totalCost < newTotalCost)
		return false;

	this->costFromStart = newCostFromStart;
	this->costToGoal = newCostToGoal;
	this->totalCost = newTotalCost;
	this->parentTile = parent;
	this->parentImage = parentImage;
	this->currFrame.x = currFrameX;
	this->currFrame.y = currFrameY;

	return true;
}

void AStarTile::UnOpen()
{
	costFromStart = 0.0f;	// g : 시작점부터 현재 노드까지의 비용
	costToGoal = 0.0f;		// h : 현재 노드부터 목적지까지의 예상 비용
	totalCost = 0.0f;		// f : g + h
	isOpened = false;
	isClosed = false;
	parentTile = nullptr;
	parentImage = nullptr;
	SetColor(RGB(220, 220, 220));
}
