#pragma once
#include "Singleton.h"
#include "pch.h"

class NoticeManager : public Singleton<NoticeManager>
{
	deque<string*> queNotice;
	deque<string*>::iterator it;
	
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
};

