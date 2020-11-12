#include "TimerManager.h"
#include "Timer.h"

HRESULT TimerManager::Init()
{
	timer = new Timer();
	timer->Init();

	return S_OK;
}

void TimerManager::Release()
{
	delete timer;
}

void TimerManager::Update()
{
	timer->Tick();
}

void TimerManager::Render(HDC hdc)
{
	wsprintf(szText, "FPS : %d", timer->GetFpsFrameCount());
	TextOut(hdc, WINSIZE_X - 100, 20, szText, strlen(szText));
}
