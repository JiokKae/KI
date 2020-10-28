#pragma once
#include "pch.h"

class Circle
{
	POINTFLOAT pos;
	float radius;

public:
	HRESULT Init();				// 멤버 변수 초기화, 메모리 할당
	void Release();				// 메모리 해제
	void Update();				// 프레임 단위 게임 로직 실행 (데이터 변경)
	void Render(HDC hdc);		// 프레임 단위 출력 (이미지, 텍스트 등)

	POINTFLOAT GetPos() { return pos; }
	void SetPos(POINTFLOAT pos) { this->pos = pos; }
};

