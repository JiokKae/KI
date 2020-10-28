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

HRESULT Image::Init(const DWORD resID, int width, int height, bool isTrans, COLORREF transColor)
{
	return E_NOTIMPL;
}

HRESULT Image::Init(const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	return E_NOTIMPL;
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

void Image::Render(HDC hdc, int x, int y)
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
