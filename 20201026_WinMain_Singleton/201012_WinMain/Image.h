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
		DWORD	resID;		// 리소스의 고유한 아이디
		HDC		hMemDC;		// 그리기를 주관하는 객체의 핸들
		HBITMAP	hBitmap;	// 이미지 정보
		HBITMAP hOldBit;	// 기존 이미지 정보
		int		width;		// 이미지 가로 크기
		int		height;		// 이미지 세로 크기
		BYTE	loadType;	// 로드 타입

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
	LPIMAGE_INFO imageInfo;		// 이미지 정보 구조체 포인터
	//LPIMAGE_INFO imageInfo;

	char filenName;			// 파일 경로 + 이름
	bool isTrans;			// 투명화 여부
	COLORREF transColor;	// 투명화할 색
	bool isAnimateSheet;
	int sheetNum;
public:
	// 빈 비트맵 이미지를 만든다
	HRESULT Init(int width, int height);

	// 리소스로부터 데이터를 읽어서 비트맵을 만든다
	HRESULT Init(const DWORD resID, int width, int height, bool isTrans = FALSE, COLORREF transColor = FALSE, bool isAnimateSheet = false, int sheetNum = 1);

	// 파일로부터 데이터를 읽어서 비트맵을 만든다
	HRESULT Init(const char* fileName, int width, int height, bool isTrans = FALSE, COLORREF transColor = FALSE, bool isAnimateSheet = false, int sheetNum = 1);

	// 메모리 해제
	void Release();

	// 화면에 출력
	void Render(HDC hdc, int x, int y, int zoom = 1, int sheetNum = 0);

	HDC GetHMemDC() { return imageInfo->hMemDC; }
};

