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
		END
	};

	typedef struct tagImageInfo
	{
		DWORD	resID;		// ���ҽ��� ������ ���̵�
		HDC		hMemDC;		// �׸��⸦ �ְ��ϴ� �ڵ� (�޸� ����)
		HBITMAP	hBitmap;	// �̹��� ����
		HBITMAP hOldBit;	// ���� �̹��� ����
		int		width;		// �̹��� ���� ũ��
		int		height;		// �̹��� ���� ũ��
		BYTE	loadType;	// �ε� Ÿ��

		// Animation�� �ʿ��� ����
		int maxFrameX;		// �ִ� ������ �ε���
		int maxFrameY;		
		int currFrameX;		// ���� ������ �ε���
		int currFrameY;
		int frameWidth;		// �����Ӻ� ũ��
		int frameHeight;

		// Animation ����� ��ġ
		float x;
		float y;

		tagImageInfo() {
			resID = 0;
			hMemDC = NULL;
			hBitmap = NULL;
			hOldBit = NULL;
			width = 0;
			height = 0;
			loadType = IMAGE_LOAD_KIND::EMPTY;

			maxFrameX = 0;
			maxFrameY = 0;
			currFrameX = 0;
			currFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			x = y = 0;
		};

	} IMAGE_INFO, *LPIMAGE_INFO;

private:
	IMAGE_INFO*	imageInfo;		// �̹��� ���� ����ü ������
	//LPIMAGE_INFO imageInfo;

	char* fileName;				// ���� ��� + �̸�
	bool isTrans;				// ����ȭ ����
	COLORREF transColor;		// ����ȭ�� ��

public:	
	//�� ��Ʈ�� �̹����� �����.
	HRESULT Init(int width, int height);

	// ���ҽ��κ��� �����͸� �о ��Ʈ���� �����.
	HRESULT Init(const DWORD resID, int width, int height,
		bool isTrans = FALSE, COLORREF transColor = FALSE);

	// ���Ϸκ��� �����͸� �о ��Ʈ���� �����.
	HRESULT Init(const char* fileName, int width, int height,
		bool isTrans = FALSE, COLORREF transColor = FALSE);

	// ���Ϸκ��� �����͸� �о ��Ʈ���� �����. (�ִϸ��̼�)
	HRESULT Init(const char* fileName, int width, int height,
		int maxFrameX, int maxFrameY,
		bool isTrans = FALSE, COLORREF transColor = FALSE);

	// �޸� ����
	void Release();

	void Render(HDC hdc, int destX, int destY, int sizeX, int sizeY);
	void FrameRender(HDC hdc, int destX, int destY, int currFrameX, int currFrameY);

	HDC GetMemDC() { return imageInfo->hMemDC; }
	int GetMaxFrameX() { return imageInfo->maxFrameX; }

	Image();
	~Image();
};
