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
	if (MessageBox(g_hWnd, "������ �����Ͻðڽ��ϱ�?", "����Ȯ��", MB_OKCANCEL) == IDOK)
	{
		PostQuitMessage(0);
	}
}
