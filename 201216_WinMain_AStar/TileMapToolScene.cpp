#include "TileMapToolScene.h"
#include "Image.h"

/*
	�ǽ� 1. ���� Ÿ���� �巡�׷� �����ϰ� Ŭ������ ����Ÿ�Ͽ� ����
	�ǽ� 2. ������ ��ư�� Button Ŭ������ �̿��ؼ� ����
	�ǽ� 2_1. �Լ� �����ͷ� ��ư ��� �߰�

	extra. ��ü ���� Ÿ�� ���� �� ����
*/

HRESULT TileMapToolScene::Init()
{
	SetWindowSize(0, 0, WINSIZE_TILE_MAP_X, WINSIZE_TILE_MAP_Y);

	sampleTile = ImageManager::GetSingleton()->AddImage("����Ÿ��", "Image/maptiles.bmp", 640, 288, SAMPLE_TILE_X, SAMPLE_TILE_Y);

	// ���̺�, �ε� ��ư
	SetRect(&rcSave, WINSIZE_TILE_MAP_X - sampleTile->GetWidth(), sampleTile->GetHeight() + 200,
		WINSIZE_TILE_MAP_X - sampleTile->GetWidth() + 150, sampleTile->GetHeight() + 270);

	SetRect(&rcLoad, WINSIZE_TILE_MAP_X - sampleTile->GetWidth() + 200, sampleTile->GetHeight() + 200,
		WINSIZE_TILE_MAP_X - sampleTile->GetWidth() + 350, sampleTile->GetHeight() + 270);

	// ���õ� Ÿ�� ����
	selectTileInfo.frameX = 0;
	selectTileInfo.frameY = 0;

	// ������ ���� Ÿ���� ������ ����
	for (int i = 0; i < SAMPLE_TILE_Y; i++)
	{
		for (int j = 0; j < SAMPLE_TILE_X; j++)
		{
			SetRect(&sampleTileInfo[i * SAMPLE_TILE_X + j].rc,
				(WINSIZE_TILE_MAP_X - sampleTile->GetWidth()) + (j * TILE_SIZE),
				/*0 + */i * TILE_SIZE,
				(WINSIZE_TILE_MAP_X - sampleTile->GetWidth()) + (j * TILE_SIZE + TILE_SIZE),
				i * TILE_SIZE + TILE_SIZE);

			sampleTileInfo[i * SAMPLE_TILE_X + j].frameX = j;
			sampleTileInfo[i * SAMPLE_TILE_X + j].frameY = i;
		}
	}


	// ���� ��ܿ� ���� Ÿ���� ������ ����
	for (int i = 0; i < TILE_Y; i++)
	{
		for (int j = 0; j < TILE_X; j++)
		{
			SetRect(&tileInfo[i * TILE_X + j].rc,
				j * TILE_SIZE, i * TILE_SIZE, 
				j * TILE_SIZE + TILE_SIZE,	i * TILE_SIZE + TILE_SIZE);

			tileInfo[i * TILE_X + j].terrain = TERRAIN::GRASS;
			tileInfo[i * TILE_X + j].frameX = 0;
			tileInfo[i * TILE_X + j].frameY = 1;
		}
	}

	return S_OK;
}

void TileMapToolScene::Release()
{
}

void TileMapToolScene::Update()
{
	// ���� Ÿ�� ���� �� ���� Ȯ��
	RECT rcSample;
	rcSample.left = WINSIZE_TILE_MAP_X - sampleTile->GetWidth();
	rcSample.top = 0;
	rcSample.right = WINSIZE_TILE_MAP_X;
	rcSample.bottom = sampleTile->GetHeight();
	if (PtInRect(&rcSample, g_ptMouse))
	{
		if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON))
		{
			int posX = g_ptMouse.x - rcSample.left, posY = g_ptMouse.y - rcSample.top;
			int idX = posX / TILE_SIZE;
			int idY = posY / TILE_SIZE;

			selectTileInfo.frameX = sampleTileInfo[idY * SAMPLE_TILE_X + idX].frameX;
			selectTileInfo.frameY = sampleTileInfo[idX + idY * SAMPLE_TILE_X].frameY;
		}
	}

	// ����Ÿ���� ������ ����
	RECT rcMain;
	rcMain.left = 0;
	rcMain.top = 0;
	rcMain.right = rcMain.left + (TILE_SIZE * TILE_X);
	rcMain.bottom = rcMain.top + (TILE_SIZE * TILE_Y);
	if (PtInRect(&rcMain, g_ptMouse))
	{
		if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON) || 
			KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
		{
			int posX = g_ptMouse.x - rcMain.left, posY = g_ptMouse.y - rcMain.top;
			int idX = posX / TILE_SIZE;
			int idY = posY / TILE_SIZE;

			tileInfo[idY * TILE_X + idX].frameX = selectTileInfo.frameX;
			tileInfo[idX + idY * TILE_X].frameY = selectTileInfo.frameY;
		}
	}

	// ��ư ó��
	if (PtInRect(&rcSave, g_ptMouse) && KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON))
	{
		Save();
	}
	if (PtInRect(&rcLoad, g_ptMouse) && KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON))
	{
		Load();
	}
}

void TileMapToolScene::Render(HDC hdc)
{
	PatBlt(hdc, 0, 0, WINSIZE_TILE_MAP_X, WINSIZE_TILE_MAP_Y, WHITENESS);

	if (sampleTile)
	{
		// ���� Ÿ��
		sampleTile->Render(hdc, WINSIZE_TILE_MAP_X - sampleTile->GetWidth(), 0);

		// ���� Ÿ��
		for (int i = 0; i < TILE_X * TILE_Y; i++)
		{
			sampleTile->FrameRender(hdc, tileInfo[i].rc.left + (TILE_SIZE / 2), tileInfo[i].rc.top + (TILE_SIZE / 2),
				tileInfo[i].frameX, tileInfo[i].frameY);

			//Rectangle(hdc, tileInfo[i].rc.left, tileInfo[i].rc.top, tileInfo[i].rc.right, tileInfo[i].rc.bottom);
		}

		// ���õ� Ÿ��
		sampleTile->FrameRender(hdc, WINSIZE_TILE_MAP_X - sampleTile->GetWidth(), sampleTile->GetHeight() + 100,
			selectTileInfo.frameX, selectTileInfo.frameY);
	}

	// ���̺�, �ε� ��ư
	Rectangle(hdc, rcSave.left, rcSave.top, rcSave.right, rcSave.bottom);
	Rectangle(hdc, rcLoad.left, rcLoad.top, rcLoad.right, rcLoad.bottom);
}

void TileMapToolScene::Save()
{
	DWORD writtenByte;
	HANDLE hFile = CreateFile("Save/saveMapData.map", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(hFile, tileInfo, sizeof(TILE_INFO) * TILE_X * TILE_Y, &writtenByte, NULL);

	CloseHandle(hFile);
}

void TileMapToolScene::Load()
{
	DWORD readByte;
	HANDLE hFile = CreateFile("Save/saveMapData.map", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(hFile, tileInfo, sizeof(TILE_INFO) * TILE_X * TILE_Y, &readByte, NULL);

	CloseHandle(hFile);
}

TileMapToolScene::TileMapToolScene()
{
}
