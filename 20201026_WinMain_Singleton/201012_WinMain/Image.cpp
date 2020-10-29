#include "Image.h"

HRESULT Image::Init(int width, int height)
{
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO;
	imageInfo->resID = 0;
	imageInfo->loadType = IMAGE_LOAD_KIND::EMPTY;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
	imageInfo->width = width;
	imageInfo->height = height;

	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL)
	{
		Release();
		return E_FAIL;
	}

	return S_OK;
}

HRESULT Image::Init(const DWORD resID, int width, int height, bool isTrans, COLORREF transColor, bool isAnimateSheet, int sheedNum)
{
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO;
	imageInfo->resID = 0;
	imageInfo->loadType = IMAGE_LOAD_KIND::EMPTY;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
	imageInfo->width = width;
	imageInfo->height = height;

	this->isTrans = isTrans;
	this->transColor = transColor;
	this->isAnimateSheet = isAnimateSheet;
	this->sheetNum = sheetNum;

	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL)
	{
		Release();
		return E_FAIL;
	}

	return S_OK;
}

HRESULT Image::Init(const char* fileName, int width, int height, bool isTrans, COLORREF transColor, bool isAnimateSheet, int sheetNum)
{
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO;
	imageInfo->resID = 0;
	imageInfo->loadType = IMAGE_LOAD_KIND::FILE;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
	imageInfo->width = width;
	imageInfo->height = height;

	this->isTrans = isTrans;
	this->transColor = transColor;
	this->isAnimateSheet = isAnimateSheet;
	this->sheetNum = sheetNum;

	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL)
	{
		Release();
		return E_FAIL;
	}

	return S_OK;
}

void Image::Release()
{
	if (imageInfo)
	{
		SelectObject(imageInfo->hMemDC, imageInfo->hOldBit);
		DeleteObject(imageInfo->hBitmap);
		DeleteDC(imageInfo->hMemDC);
		delete imageInfo;
		imageInfo = nullptr;
	}
}
/*
class GameNode;
class Singleton : GameNode;
class Image;
class Character : GameNode; { iori, kyo }
class Scene : GameNode; { battleScene{HPbar, Time, } }
class AnimationState;
class AnimationRelation;
class

*/
void Image::Render(HDC hdc, int x, int y, int zoom, int currentSheetNum)
{
	if (isTrans)
	{
		GdiTransparentBlt(
			hdc, 
			x, y, 
			imageInfo->width / sheetNum * zoom, imageInfo->height * zoom,	// 출력되는 크기
			imageInfo->hMemDC, 
			imageInfo->width / sheetNum * currentSheetNum, 0,				// 원본이미지에서 출력될 시작 좌표
			imageInfo->width / sheetNum, imageInfo->height,					// 원본 이미지에서 출력할 크기
			transColor);
	}
	else 
	{
		BitBlt(
			hdc,				// 복사 목적지 DC
			x, y,				// 복사가 시작될 위치
			imageInfo->width,	// 원본에서 복사될 가로 크기
			imageInfo->height,	// 원본에서 복사될 세로 크기
			imageInfo->hMemDC,	// 원본 DC
			0, 0,				// 원본에서 복사 시작 위치
			SRCCOPY				// 복사 옵션
		);
	}
	

}
