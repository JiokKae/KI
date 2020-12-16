#pragma once
#include "pch.h"

class ButtonFunction
{
public:
	void ChangeScene(const char* scenename, const char* loadingSceneName = nullptr);
	void QuitProgram(void);

	ButtonFunction() {};
	~ButtonFunction() {};
};

