#pragma once
#include "pch.h"

class Image
{
public:
	enum IMAGE_LOAD_KIND
	{
		RESOURCE,
		FILE,
		EMPTY,
		END,
	};

	typedef struct tagImageInfo
	{
		DWORD	resID;		// ���ҽ��� ������ ���̵�
		HDC		hMemDC;		// �׸��⸦ �ְ��ϴ� ��ü�� �ڵ�
		HBITMAP	hBitmap;	// �̹��� ����
		HBITMAP hOldBit;	// ���� �̹��� ����
		int		width;		// �̹��� ���� ũ��
		int		height;		// �̹��� ���� ũ��
		BYTE	loadType;	// �ε� Ÿ��

		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBitmap = NULL;
			hOldBit = NULL;
			width = 0;
			height = 0;
			loadType = IMAGE_LOAD_KIND::EMPTY;
		}
		
	} IMAGE_INFO, *LPIMAGE_INFO;

private:
	//tagImageInfo imageInfo;
	LPIMAGE_INFO imageInfo;		// �̹��� ���� ����ü ������
	//LPIMAGE_INFO imageInfo;

	char filenName;			// ���� ��� + �̸�
	bool isTrans;			// ����ȭ ����
	COLORREF transColor;	// ����ȭ�� ��

public:
	// �� ��Ʈ�� �̹����� �����
	HRESULT Init(int width, int height);

	// ���ҽ��κ��� �����͸� �о ��Ʈ���� �����
	HRESULT Init(const DWORD resID, int width, int height, bool isTrans = FALSE, COLORREF transColor = FALSE);

	// ���Ϸκ��� �����͸� �о ��Ʈ���� �����
	HRESULT Init(const char* fileName, int width, int height, bool isTrans = FALSE, COLORREF transColor = FALSE);

	// �޸� ����
	void Release();

	// ȭ�鿡 ���
	void Render(HDC hdc, int x, int y);
};

