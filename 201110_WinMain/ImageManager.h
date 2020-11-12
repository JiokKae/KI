#pragma once
#include "pch.h"
#include "Singleton.h"
#include <map>
using namespace std;

class Image;
class ImageManager : public Singleton<ImageManager>
{
private:
	map<string, Image*> mapImageDatas;
public:
	HRESULT Init();
	void Release();

	void AddImage(string strKey, const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = 0UL);
	void AddImage(string strKey, const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor);

	void DeleteImage(string strKey);
	Image* FineImage(string strKey);
};

