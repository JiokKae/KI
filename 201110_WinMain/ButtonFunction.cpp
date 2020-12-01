#include "ButtonFunction.h"

void ButtonFunction::ChangeScene(void* arg)
{
	Argument* argu = (Argument*)arg;

	SceneManager::GetSingleton()->ChangeScene(argu->a.c_str(), argu->b.c_str());
}

void ButtonFunction::QuitProgram(void* arg)
{
	//int* point = (int*)arg;
	//if (MessageBox(g_hWnd, string("������ �����Ͻðڽ��ϱ�?" + to_string(*point)).c_str(), "���� Ȯ��", MB_OKCANCEL) == IDOK)
	if (MessageBox(g_hWnd, "������ �����Ͻðڽ��ϱ�?", "���� Ȯ��", MB_OKCANCEL) == IDOK)
	{
		PostQuitMessage(0);
	}
}
