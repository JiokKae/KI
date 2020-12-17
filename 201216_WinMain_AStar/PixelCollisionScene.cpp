#include "PixelCollisionScene.h"
#include "Image.h"

#define G (9.8f/2)

HRESULT PixelCollisionScene::Init()
{
	imgMountain = ImageManager::GetSingleton()->AddImage("ÇÈ¼¿ Ãæµ¹ ¹è°æ", "Image/mountain.bmp", WINSIZE_X, WINSIZE_Y, true, RGB(255, 0, 255));
	imgMountain2 = ImageManager::GetSingleton()->AddImage("ÇÈ¼¿ Ãæµ¹ ¹è°æ2", "Image/mountain.bmp", WINSIZE_X, WINSIZE_Y, true, RGB(255, 0, 255));
	imgBall = ImageManager::GetSingleton()->AddImage("ÇÈ¼¿ °ø", "Image/ball.bmp", 60, 60, true, RGB(255, 0, 255));
	
	ballPos.x = WINSIZE_X / 2;
	ballPos.y = WINSIZE_Y / 6;
	ballAcceleration = {0, 0};
	ballForce = {};
	ballVelocity = {};
	ballWeight = 1;
	ballElasticity = 1.01f;

	return S_OK;
}

void PixelCollisionScene::Release()
{
}

void PixelCollisionScene::Update()
{
	float limit = 1300;
	if (ballVelocity.x > limit)
		ballVelocity.x = limit;
	if (ballVelocity.y > limit)
		ballVelocity.y = limit;
	if (ballVelocity.x < -limit)
		ballVelocity.x = -limit;
	if (ballVelocity.y < -limit)
		ballVelocity.y = -limit;
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F5))
	{
		ballPos.x = WINSIZE_X / 2;
		ballPos.y = WINSIZE_Y / 6;
		ballAcceleration = { 0, 0 };
		ballForce = {};
		ballVelocity = {};
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_F6))
	{
		BitBlt(imgMountain->GetMemDC(), 0, 0, imgMountain->GetWidth(), imgMountain->GetHeight(), imgMountain2->GetMemDC(), 0, 0, SRCCOPY);

	}

	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
	{
		ballPos.x += -1;
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
	{
		ballPos.x += 1;
	}

	if (ballPos.x > WINSIZE_X - imgBall->GetWidth() / 2) 
	{
		ballPos.x = WINSIZE_X - imgBall->GetWidth() / 2;
		ballVelocity.x = -ballVelocity.x;
	}
	else if (ballPos.x < 0 + imgBall->GetWidth() / 2)
	{
		ballPos.x = 0 + imgBall->GetWidth() / 2;
		ballVelocity.x = -ballVelocity.x;
	}
	
	if (ballPos.y > WINSIZE_Y - imgBall->GetHeight() / 2)
	{
		ballPos.y = WINSIZE_Y - imgBall->GetHeight() / 2;
		ballVelocity.y = -ballVelocity.y;
	}
	else if (ballPos.y < 0 + imgBall->GetHeight() / 2)
	{
		ballPos.y = 0 + imgBall->GetHeight() / 2;
		ballVelocity.y = -ballVelocity.y;
	}


	COLORREF color = GetPixel(imgMountain->GetMemDC(), ballPos.x, ballPos.y + imgBall->GetHeight()/2);

	int dir = 72;
	int collisionCount = 0;
	float rad = 0;
	for (int i = 0; i < dir; i++)
	{
		float rad = DegreeToRadian(i * 360.0 / dir);
		COLORREF color = GetPixel(imgMountain->GetMemDC(), ballPos.x + cos(rad) * imgBall->GetWidth() / 2, ballPos.y + sin(rad) * imgBall->GetHeight() / 2);
		WORD r = GetRValue(color);
		WORD g = GetGValue(color);
		WORD b = GetBValue(color);
		if (!(r == 255 && g == 0 && b == 255))
		{
			FPOINT newVelocity;
			newVelocity.x = ballVelocity.x * cos(rad * 2) - ballVelocity.y * sin(rad * 2) * ballElasticity;
			newVelocity.y = ballVelocity.y * cos(rad * 2) + ballVelocity.x * sin(rad * 2) * ballElasticity;
			ballVelocity.x = newVelocity.x;
			ballVelocity.y = newVelocity.y;
			ballForce.y = -G * ballWeight - 10;

			HBRUSH oldBrush = (HBRUSH)SelectObject(imgMountain->GetMemDC(), CreateSolidBrush(RGB(255, 0, 255)));
			HPEN oldPen = (HPEN)SelectObject(imgMountain->GetMemDC(), CreatePen(PS_SOLID, 1, RGB(255, 0, 255)));
			Ellipse(imgMountain->GetMemDC(), 
				ballPos.x - imgBall->GetWidth() / 1.f,
				ballPos.y - imgBall->GetHeight() / 1.f,
				ballPos.x + imgBall->GetWidth() / 1.f,
				ballPos.y + imgBall->GetHeight() / 1.f
			);
			DeleteObject(SelectObject(imgMountain->GetMemDC(), oldBrush));
			DeleteObject(SelectObject(imgMountain->GetMemDC(), oldPen));

			vector<Effect*>::iterator it;
			for (it = explosions.begin(); it != explosions.end(); it++)
			{
				if ((*it)->IsActive() == false)
					break;
			}
			if (it == explosions.end())
			{
				explosions.push_back(new Effect());
				explosions.back()->Init();
				explosions.back()->Active(ballPos);
			}
			else
			{
				(*it)->Init();
				(*it)->Active(ballPos);
			}
			
			//ballPos.x -= cos(rad) * imgBall->GetWidth() / 2/ 10;
			//ballPos.y -= sin(rad) * imgBall->GetHeight() / 2/ 10;
			break;
		}
	}
	if (collisionCount < 4 && collisionCount > 0)
	{
		
	}
	else
	{
		ballForce.y = 0;
	}

	float scale = 10.f;
	ballAcceleration.x = ballForce.x / ballWeight;
	ballAcceleration.y = (ballForce.y + ballWeight * G) / ballWeight;

	ballVelocity.x += ballAcceleration.x * TimerManager::GetSingleton()->GetElapsedTime() * scale;
	ballVelocity.y += ballAcceleration.y * TimerManager::GetSingleton()->GetElapsedTime() * scale;

	ballPos.x += ballVelocity.x * TimerManager::GetSingleton()->GetElapsedTime() * scale;
	ballPos.y += ballVelocity.y * TimerManager::GetSingleton()->GetElapsedTime() * scale;

	for (int i = 0; i < explosions.size(); i++)
	{
		explosions[i]->Update();
	}

}

void PixelCollisionScene::Render(HDC hdc)
{


	imgMountain->Render(hdc, 0, 0);
	imgBall->Render(hdc, ballPos.x - imgBall->GetWidth() / 2, ballPos.y - imgBall->GetHeight() / 2);


	for (int i = 0; i < explosions.size(); i++)
	{
		explosions[i]->Render(hdc);
	}
	/*
	int dir = 72;
	for (int i = 0; i < dir; i++)
	{
		float rad = DegreeToRadian(i * 360.0 / dir);
		Ellipse(hdc,
			ballPos.x + cos(rad) * imgBall->GetWidth() / 2 - 2,
			ballPos.y + sin(rad) * imgBall->GetHeight() / 2 - 2,
			ballPos.x + cos(rad) * imgBall->GetWidth() / 2 + 2,
			ballPos.y + sin(rad) * imgBall->GetHeight() / 2 + 2
		);
	}
	*/
}

PixelCollisionScene::~PixelCollisionScene()
{
}

PixelCollisionScene::PixelCollisionScene()
{
}

HRESULT Effect::Init()
{
	imgExplosion = ImageManager::GetSingleton()->AddImage("Æø¹ß", "Image/explosion.bmp", 832 * 3, 62 * 3, 26, 1, true, RGB(255, 0, 255));
	currFrame = 0;
	time = 0;

	return S_OK;
}

void Effect::Release()
{
}

void Effect::Update()
{
	if (!isActive)
		return;
	time += TimerManager::GetSingleton()->GetElapsedTime();
	if (time > 0.07f)
	{
		currFrame++;
		time -= 0.07f;
	}

	if (currFrame > 25)
		isActive = false;
}

void Effect::Render(HDC hdc)
{
	if (!isActive)
		return;

	imgExplosion->FrameRender(hdc, pos.x, pos.y, currFrame, 0);
}

void Effect::Active(FPOINT pos)
{
	this->pos = pos;
	currFrame = 0;
	time = 0;
	isActive = true;
}
