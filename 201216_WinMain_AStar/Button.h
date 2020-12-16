#pragma once
#include "GameNode.h"
//#include "ButtonFunction.h"

/*
	함수포인터 (함수의 메모리주소를 담는 변수)
	(변수)포인터 (변수의 메모리주소를 담는 변수)
	int a = 10;
	int* pA = &a;

	void func(void);	// 함수의 원형
	int sum(int, int);

	void (*funcPointer)(void);	// 함수포인터(변수)를 선언
	funcPointer = func;			// 함수포인터에 함수의 주소를 대입

	int (*pFunc)(int, int);
	pFunc = sum;

	func();
	funcPointer();
*/

enum BUTTON_STATE
{
	NONE,
	UP,
	DOWN
};

//typedef int __jungsu;
//
//void (*buttonFunc)(void);

class ButtonFunction;

typedef void (*func_t1)(void);
typedef void (ButtonFunction::*func_t2)(const char*, const char*);

class Image;
class Button : public GameNode
{
private:
	BUTTON_STATE state;
	Image* img;
	RECT rc;
	POINT pos;

	POINT ptDownFrame;
	POINT ptUpFrame;

	// 버튼 기능 (함수포인터)
	//void (*buttonFunc)(void);
	//void (*buttonFunc2)(const char*, const char*);

	ButtonFunction* bf;
	func_t1 buttonFunc1;
	func_t2 buttonFunc2;
	Argument arg;


public:
	HRESULT Init(const char* fileName, int posX, int posY, POINT downFramePoint, POINT upFramePoint);
	virtual HRESULT Init() override;	
	virtual void Release() override;	
	virtual void Update() override;		
	virtual void Render(HDC hdc) override;

	//void SetButtonFunc(void (*buttonFunc)(void)) { this->buttonFunc = buttonFunc; }
	//void SetButtonFunc(void (*buttonFunc)(const char*, const char*)) { this->buttonFunc2 = buttonFunc; }
	void SetButtonFunc(func_t2 buttonFunc, ButtonFunction* bf, Argument arg) {
		this->buttonFunc2 = buttonFunc; this->bf = bf; this->arg = arg; }

	Button();
	virtual ~Button() {};

};

