#include "Missile.h"



HRESULT Missile::Init()
{
	pos.x = 0;
	pos.y = 0;
	speed = 10.0f;
	size = 30;
	isFire = false;
	angle = 0.0f;

	return S_OK;
}

void Missile::Release()
{
}

FPOINT Normalize(FPOINT vector) {
	float distance = sqrt(pow(vector.x, 2) + pow(vector.y, 2));
	vector.x /= distance;
	vector.y /= distance;
	return vector;
}

float Lerp(float a, float b, float t)
{
	return a + (b - a) * t;
}
void Missile::Update(FPOINT enemyPos, int enemySize)
{
	if (isFire)
	{
		float distance = sqrt(pow(enemyPos.x - pos.x, 2) + pow(enemyPos.y - pos.y, 2));

		if (distance < size / 2 + enemySize / 2)
			;//isFire = false;
		else if (distance < 3000)
		{
			FPOINT v;
			//v.x = enemyPos.x - pos.x;
			//v.y = enemyPos.y - pos.y;
			//
			//v = Normalize(v);

			float radian = atan2(enemyPos.y - pos.y, enemyPos.x - pos.x);
			//if (radian < 0)
			//	radian += 2 * PI;
			v.x = cos(radian);
			v.y = sin(radian);

			//			v = Normalize(v);

			direction.x = Lerp(direction.x, v.x, 0.01f);
			direction.y = Lerp(direction.y, v.y, 0.01f);

			//direction = Normalize(direction);

		}

		pos.x += direction.x * speed;
		pos.y += direction.y * speed;



		//if (pos.x > enemyPos.x)
		//	angle++;
		//else if (pos.x < enemyPos.x)
		//	angle--;
		//if (angle > 180)
		//	angle = 180;
		//else if (angle < 0)
		//	angle = 0;

	}
}

void Missile::Render(HDC hdc)
{
	if (isFire)
	{
		Ellipse(hdc, pos.x - (size / 2), pos.y - (size / 2), pos.x + (size / 2), pos.y + (size / 2));

	}
}

Missile::Missile()
{
}


Missile::~Missile()
{
}
