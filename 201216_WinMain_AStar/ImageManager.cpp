#include "ImageManager.h"
#include "Image.h"

HRESULT ImageManager::Init()
{
	return S_OK;
}

void ImageManager::Release()
{
}

Image* ImageManager::AddImage(string strKey, const char* fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	// 맵에 키에 해당하는 데이터가 있는지 확인해서
	// 있으면 추가 없이 리턴
	Image* image = nullptr;
	image = FindImage(strKey);
	if (image)
	{
		return image;
	}

	// 없으면 추가
	image = new Image();
	if (FAILED(image->Init(fileName, width, height, isTrans, transColor)))
	{
		image->Release();
		delete image;

		return nullptr;
	}

	mapImageDatas.insert(make_pair(strKey, image));

	return image;
}

Image* ImageManager::AddImage(string strKey, const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
	Image* image = nullptr;
	image = FindImage(strKey);
	if (image)
	{
		return image;
	}

	image = new Image();
	if (FAILED(image->Init(fileName, width, height, 
		maxFrameX, maxFrameY, isTrans, transColor)))
	{
		image->Release();
		delete image;

		return nullptr;
	}

	mapImageDatas.insert(make_pair(strKey, image));

	return image;
}

void ImageManager::DeleteImage(string strKey)
{
	map<string, Image*>::iterator it = mapImageDatas.find(strKey);
	if (it != mapImageDatas.end())
	{
		(it->second)->Release();
		delete (it->second);

		mapImageDatas.erase(it);
	}
}

Image* ImageManager::FindImage(string strKey)
{
	map<string, Image*>::iterator it = mapImageDatas.find(strKey);
	if (it != mapImageDatas.end())
	{
		return it->second;
	}

	return nullptr;
}
