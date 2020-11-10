#include "Missile.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "Image.h"

HRESULT Missile::Init()
{
	size = 30;
	pos.x = 0;
	pos.y = 0;
	speed = 5.0f;
	isFire = false;
	angle = 0.0f;
	destAngle = 0.0f;
	followRatio = 0.1f;
	time = 0;
	
	img = new Image();
	if (FAILED(img->Init("Image/구슬.bmp", 30, 30,
		true, RGB(255, 0, 255))))
	{
		// 예외처리
		MessageBox(g_hWnd, "파일로부터 비트맵 생성에 실패했습니다.",
			"실패", MB_OK);
	}
	return S_OK;
}

void Missile::Release()
{
	img->Release();
	delete img;
}

void Missile::Update()
{
	if (isFire)
	{
		
#pragma region 유도
		//float tempAngle;
		//if (target)
		//{
		//	followRatio += 0.2f;
		//	if (followRatio > 10.0f)
		//	{
		//		followRatio = 10.0f;
		//	}

		//	destAngle = atan2f(-(target->GetPos().y - pos.y),
		//		(target->GetPos().x - pos.x));

		//	tempAngle = DegreeToRadian(angle);
		//	tempAngle +=
		//		(destAngle - DegreeToRadian(angle)) / (10.0f / followRatio);

		//	angle = RadianToDegree(tempAngle);
		//}

		//pos.x += cosf(tempAngle) * speed;
		//pos.y -= sinf(tempAngle) * speed;
#pragma endregion

		//speed = (sin(pos.y/60) + 1.2f) * 1.5f + (sin(pos.x / 60) + 1.2f) * 1.5f;
		//angle -= speed/ 100.0f;

		pos.x += cosf(angle) * speed;
		pos.y -= sinf(angle) * speed;
		
		// 벽에 부딪혔는지
		// 왼쪽, 오른쪽
		if (pos.x - (size / 2) <= 0)
		{
			pos.x = size / 2;
			angle = PI - angle;
		}
		if(pos.x + (size / 2) >= WINSIZE_X)
		{
			pos.x = WINSIZE_X - (size / 2);
			angle = PI - angle;
		}
		// 위, 아래
		if (pos.y - (size / 2) <= 0)
		{
			pos.y = (size / 2);
			angle = PI * 2.0f - angle;
		}
		if(pos.y + (size / 2) >= WINSIZE_Y)
		{
			pos.y = WINSIZE_Y - (size / 2);
			angle = PI * 2.0f - angle;
		}
	}
}

void Missile::Render(HDC hdc)
{
	if (isFire)
	{
		img->Render(hdc, pos.x - (size / 2), pos.y - (size / 2));
		//Ellipse(hdc, pos.x - (size / 2), pos.y - (size / 2),pos.x + (size / 2), pos.y + (size / 2));
	}
}

Missile::Missile()
{
}


Missile::~Missile()
{
}
