#include "KeyManager.h"

HRESULT KeyManager::Init()
{
	for (int i = 0; i < KEY_MAX_COUNT; i++)
	{
		SetKeyUp(i, true);
		//keyUp[i] = true;
		SetKeyDown(i, false);
		//keyDown[i] = false;
	}

	return E_NOTIMPL;
}

void KeyManager::Release()
{
	ReleaseSingleton();
}

bool KeyManager::IsOnceKeyDown(int key)
{
	// GetAsyncKeyState(VK_...)
	/* 
	�Լ� ȣ�� ������ ����Ű(VK_...)�� � �������� Ȯ���� �����ϴ�.
	1. 0x0000 => ���� �����ӿ� �������� ���� ȣ�� �������� �������� ����
	2. 0x0001 => ���� �����ӿ� �������� �ְ� ȣ�� �������� �������� ����
	3. 0x8000 => ���� �����ӿ� �������� ���� ȣ�� ������ �����ִ� ����
	4. 0x8001 => ���� �����ӿ� �������� �ְ� ȣ��������� �����ִ� ����
	*/

	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!GetKeyDown()[key])
		{
			SetKeyDown(key, true);
			return true;
		}
	}
	else
	{
		SetKeyDown(key, false);
	}
	return false;
}

bool KeyManager::IsOnceKeyUp(int key)
{
	short test = GetAsyncKeyState(key);
	// �ǽ�2. ���� �ڵ带 �м��ؼ� �ϼ��غ���.
	if (GetAsyncKeyState(key) & 0x8000)
	{
		SetKeyUp(key, false);
	}
	else
	{
		if (!GetKeyUp()[key])
		{
			SetKeyUp(key, true);
			return true;
		}
	}
	return false;
}

bool KeyManager::IsStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
		return true;
	
	return false;
}