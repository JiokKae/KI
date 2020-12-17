#include "NoticeManager.h"

HRESULT NoticeManager::Init()
{
	return S_OK;
}

void NoticeManager::Release()
{
}

void NoticeManager::Update()
{
}

void NoticeManager::Render(HDC hdc)
{
	for (int i = 0; i < queNotice.size(); i++)
	{
		queNotice[i];
	}
}
