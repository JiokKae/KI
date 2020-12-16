#include "ButtonFunction.h"

void ButtonFunction::ChangeScene(const char* scenename, const char* loadingSceneName)
{
	if (loadingSceneName)
	{
		SceneManager::GetSingleton()->ChangeScene(scenename, loadingSceneName);
	}
	else
	{
		SceneManager::GetSingleton()->ChangeScene(scenename);
	}
}

void ButtonFunction::QuitProgram(void)
{
	if (MessageBox(g_hWnd, "게임을 종료하시겠습니까?", "종료확인", MB_OKCANCEL) == IDOK)
	{
		PostQuitMessage(0);
	}
}
