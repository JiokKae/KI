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
	findRoot = nullptr;
	findRoot2 = nullptr;
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

	// ���� Ÿ�� ���� �� ���� Ȯ��
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
	wsprintf(text, "C");
	TextOut(hdc, currTile->GetIndex().x * TILE_WIDTH + TILE_WIDTH - 10, currTile->GetIndex().y * TILE_HEIGHT, text, strlen(text));
}

bool AStar::FindPath()
{
	for (int i = 0; findRoot != startTile || findRoot2 != startTile; i++)
	{
		FindPathOneStep();
	}

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
	// ���� ���۵��� �ʾҴٸ� ��ü�� �ʱ�ȭ �Ѵ�.
	if (startTile->IsClosed() == false)
	{
		this->Init();

		openList.clear(); 
		openList.push_back(startTile);
	}
	// ���� �����ߴٸ� �θ� Ÿ�� ��Ʈ�� ã�´�.
	if (currTile == destTile)
	{
		if (findRoot == startTile && findRoot2 != startTile)
		{
			float minCost = FLT_MAX;
			AStarTile* minTile = nullptr;

			// �ֺ� Ÿ���� ���� ���� ��ŸƮ�κ����� �Ÿ��� ��带 ã�´�.
			for (int y = findRoot2->GetIndex().y - 1; y <= findRoot2->GetIndex().y + 1; y++)
			{
				for (int x = findRoot2->GetIndex().x - 1; x <= findRoot2->GetIndex().x + 1; x++)
				{
					AStarTile* tile = &map[y][x];
					if (IsMapIn({ x, y }) && tile->IsPassable() && tile->IsOpened())
					{
						if (minCost > tile->GetCostFromStart())
						{
							minCost = tile->GetCostFromStart();
							minTile = tile;
						}
					}
				}
			}

			findRoot2 = minTile;
			if (findRoot2 != startTile)
				findRoot2->SetColor(RGB(255, 255, 0));
		}

		if (findRoot == startTile)
			return;

		// ��ŸƮŸ���� ĥ������
		if(findRoot->GetParent() != startTile)
			findRoot->GetParent()->SetColor(RGB(255,0,0));

		findRoot = findRoot->GetParent();
		return;
	}

	//���� ���¸���Ʈ�� ����ִٸ� �۵��� ���Ѵ�.
	if (openList.empty()) return;

	list<AStarTile*>::iterator it;
	list<AStarTile*>::iterator MinIt;
	float MinTotalCost = FLT_MAX;

	// ���¸���Ʈ���� �ڽ�Ʈ�� ���� ���� ��� ã��
	for (it = openList.begin(); it != openList.end(); it++)
	{
		if (MinTotalCost > (*it)->GetTotalCost())
		{
			MinTotalCost = (*it)->GetTotalCost();
			MinIt = it;
		}
	}
 
 	currTile = *MinIt; 
	currTile->SetOpened(true);
	currTile->SetClosed(true);
	if(currTile != startTile && currTile != destTile)
		currTile->SetColor(RGB(50, 50, 50));
	openList.erase(MinIt);

	// ���� ��������� �ֺ� ��带 �˻��ؼ� ���¸���Ʈ�� �ֱ�
	for (int y = currTile->GetIndex().y - 1; y <= currTile->GetIndex().y + 1; y++)
	{
		for (int x = currTile->GetIndex().x - 1; x <= currTile->GetIndex().x + 1; x++)
		{
			AStarTile* tile = &map[y][x];
			if (IsMapIn({ x, y }) && tile->IsPassable() && tile != startTile)
			{
				if (tile->IsOpened() && !tile->IsClosed())
				{
					tile->Open(currTile, destTile, ImageManager::GetSingleton()->FindImage("parent"), x + 1 - currTile->GetIndex().x, y + 1 - currTile->GetIndex().y);
				}
				else
				{
					if (bool result = tile->Open(currTile, destTile, ImageManager::GetSingleton()->FindImage("parent"), x + 1 - currTile->GetIndex().x, y + 1 - currTile->GetIndex().y))
					{
						if (tile != startTile && tile != destTile)
							tile->SetColor(RGB(255, 255, 255));

						openList.push_back(tile);
					}
				}
				
			}
		}
	}

	// �����ߴٸ� ��ã�� ���μ��� ����
	if (currTile == destTile)
	{
		findRoot = destTile;
		findRoot2 = destTile;
	}

	// ����
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

	costFromStart = 0.0f;	// g : ���������� ���� �������� ���
	costToGoal = 0.0f;		// h : ���� ������ ������������ ���� ���
	totalCost = 0.0f;		// f : g + h
	
	isClosed = false;
	isPassable = true;

	parentTile = nullptr;	// g���� ������ ���� ��带 ����
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
		wsprintf(str, "%d", int(costFromStart));
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
	bool reval = false;

	if (abs(parent->GetIndex().x - idX) + abs(parent->GetIndex().y - idY) == 1)
		newCostFromStart = parent->GetCostFromStart() + 10;
	else
		newCostFromStart = parent->GetCostFromStart() + 14;

	newCostToGoal = (abs(goal->GetIndex().x - idX) + abs(goal->GetIndex().y - idY)) * 10;
	//newCostToGoal *= newCostToGoal;

	newTotalCost = newCostFromStart + newCostToGoal;
	
	//if (isClosed)
	//	return false;
	// ���ο� �ڽ�Ʈ�� ������ �ڽ�Ʈ���� ũ�� Ż��; (���̿��ߴ�)
	//if (isOpened && costToGoal < newCostToGoal)
	if (isOpened && totalCost < newTotalCost)
		return false;

	if (this->isClosed)
	{
		if (this->costFromStart > newCostFromStart)
		{
			this->costFromStart = newCostFromStart;
			this->isClosed = false;
			reval = true;
		}
	}
	else if (this->isOpened)
	{
		if (this->costFromStart > newCostFromStart)
		{
			this->costFromStart = newCostFromStart;
			reval = false;
		}
	}
	else
	{
		this->costFromStart = newCostFromStart;
		reval = true;
	}

	this->costToGoal = newCostToGoal;
	this->totalCost = newTotalCost;
	this->parentTile = parent;
	this->parentImage = parentImage;
	this->currFrame.x = currFrameX;
	this->currFrame.y = currFrameY;
 	this->isOpened = true;
	
	return reval;
}

void AStarTile::UnOpen()
{
	costFromStart = 0.0f;	// g : ���������� ���� �������� ���
	costToGoal = 0.0f;		// h : ���� ������ ������������ ���� ���
	totalCost = 0.0f;		// f : g + h
	isOpened = false;
	isClosed = false;
	parentTile = nullptr;
	parentImage = nullptr;
	SetColor(RGB(220, 220, 220));
}
