#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>
using namespace std;
/*
	객체

*/

class Rectangle1 {
public:	// 접근 지정자가 기본적으로 private
	int width;
	int height;
	int posX, posY;

	// +
	int CalcArea() {
		return width * height;
	}
};

struct Rectangle2 {
public:		// 접근 지정자가 기본적으로 public
	int width;
	int height;
	int posX, posY;
};

class Car {
public:
	int speed;
	int maxSpeed;
	int xSpeed;
	int xMaxSpeed;
	int gear;
	string color;
	RECT rc;

	void Init() {
		color = "빨간색";
		gear = 0;
		maxSpeed = 10;
		rc = { 100,150,150,200 };
		speed = 0;
		xSpeed = 0;
		xMaxSpeed = 10;
	}

	void Run() {
		//cout << color << "차가 " << speed << "km/h로 달리고 있다." << endl;

		rc.top += xSpeed;
		rc.bottom += xSpeed;
		rc.left += speed;
		rc.right += speed;
	}
	void SpeedUp(int addSpeed) {
		speed += addSpeed;
		if (speed > maxSpeed)
			speed = maxSpeed;
	}
	void SpeedDown(int addSpeed) {
		speed -= addSpeed;
		if (speed < -maxSpeed)
			speed = -maxSpeed;
	}
	void XSpeedUp(int addSpeed) {
		xSpeed += addSpeed;
		if (xSpeed > xMaxSpeed)
			xSpeed = xMaxSpeed;
	}
	void XSpeedDown(int addSpeed) {
		xSpeed -= addSpeed;
		if (xSpeed < -xMaxSpeed)
			xSpeed = -xMaxSpeed;
	}
	void Draw() {
		HDC hdc = GetWindowDC(GetForegroundWindow());
		Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);
		
		//HDC mem_dc = CreateCompatibleDC()
	}
};

int main()
{
	Rectangle2 structRect;
	structRect.height = 10;
	structRect.width = 5;

	Rectangle1 classRect;
	classRect.CalcArea();

	Car myCar;
	myCar.Init();
	while (true)
	{
		if (_kbhit())
		{
			switch (_getch())
			{
			case 'w': case 'W':
				myCar.SpeedUp(1);
				break;
			case 's': case 'S':
				myCar.SpeedDown(1);
				break;
			case 'a': case 'A':
				myCar.XSpeedDown(1);
				break;
			case 'd': case 'D':
				myCar.XSpeedUp(1);
				break;
			case 'r':
				myCar.Init();
			default:
				break;
			}
		}
		
		//system("cls");

		myCar.Run();
		myCar.Draw();

		Sleep(33);
	}
}