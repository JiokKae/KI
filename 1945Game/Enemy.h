#pragma once
#include "GameNode.h"
class Enemy : public GameNode
{
private:
	POINTFLOAT pos;
	int size;
	POINTFLOAT speed;
public:
	HRESULT Init();				// 멤버 변수 초기화, 메모리 할당
	void Release();				// 메모리 해제
	void Update();				// 프레임 단위 게임 로직 실행 (데이터 변경)
	void Render(HDC hdc);		// 프레임 단위 출력 (이미지, 텍스트 등)

	RECT GetRect();
	POINTFLOAT GetPos();
	int GetSize();
};

