#include "ButtonFunction.h"

void ButtonFunction::ChangeScene(void* arg)
{
	Argument* argu = (Argument*)arg;

	SceneManager::GetSingleton()->ChangeScene(argu->a.c_str(), argu->b.c_str());
}

void ButtonFunction::QuitProgram(void* arg)
{
	//int* point = (int*)arg;
	//if (MessageBox(g_hWnd, string("게임을 종료하시겠습니까?" + to_string(*point)).c_str(), "종료 확인", MB_OKCANCEL) == IDOK)
	if (MessageBox(g_hWnd, "게임을 종료하시겠습니까?", "종료 확인", MB_OKCANCEL) == IDOK)
	{
		PostQuitMessage(0);
	}
}
