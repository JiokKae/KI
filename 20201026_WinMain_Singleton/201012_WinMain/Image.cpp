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
		hdc,				// ���� ������ DC
		x, y,				// ���簡 ���۵� ��ġ
		imageInfo->width,	// �������� ����� ���� ũ��
		imageInfo->height,	// �������� ����� ���� ũ��
		imageInfo->hMemDC,	// ���� DC
		0, 0,				// �������� ���� ���� ��ġ
		SRCCOPY				// ���� �ɼ�
	);

}
