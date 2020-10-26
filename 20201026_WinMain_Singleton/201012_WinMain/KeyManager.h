#pragma once
#include "pch.h"
#include "Singleton.h"
#include <bitset>

using namespace std;
#define KEY_MAX_COUNT	256
class KeyManager : public Singleton<KeyManager>
{
private:
	bitset<KEY_MAX_COUNT> keyUp;
	bitset<KEY_MAX_COUNT> keyDown;
public:
	HRESULT Init();
	void Release();

	bool IsOnceKeyDown(int key);	// 키값 처음 눌렸을 때 판단
	bool IsOnceKeyUp(int key);		// 키가 처음 눌렸다가 떼졌는지 판단
	bool IsStayKeyDown(int key);	// 키가 눌려져 있는지 판단

	void SetKeyDown(int key, bool state) { keyDown.set(key, state); }
	void SetKeyUp(int key, bool state) { keyUp.set(key, state); }

	bitset<KEY_MAX_COUNT> GetKeyDown() { return keyDown; }
	bitset<KEY_MAX_COUNT> GetKeyUp() { return keyUp; }
};

