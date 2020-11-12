/*
	Win32 API
	: Application Programming Interface
	운영체제가 응용프로그램 개발을 위해 제공하는 함수의 집합

	하드웨어 --------운영체제 (Windows)--------- 응용프로그램
						(API 함수)

	핸들(Handle) : 윈도우를 구성하는 각 객체를 구분하는 인덱스 (정수)
	메세지(Message) : 윈도우에서 발생한 이벤트를 운영체제를 통해 윈도우에게 전달하는 데이터 모음
*/

/*
	1. 사각형을 출력한다. * 10
	2. 사각형을 선택한다. (Point Rect 충돌 확인)
	3. 드래그 기능 구현 (사각형을 선택해서 이동시킨다)
	4. 드래그 앤 드랍 이후에 사각형을 별 모양으로 출력
*/
#include <Windows.h>

#define NEMO_MAX_COUNT	10
#define NEMO_SIZE		80

enum NEMO_SHAPE 
{
	NEMO,
	STAR,
};

struct MouseData 
{
	int posX, posY;
	int clickedPosX, clickedPosY;
};

struct Object
{
	POINT pos;
	NEMO_SHAPE shape;	// 0 : rect, 1 : star
};

// 전역변수
HINSTANCE	g_hInstance;
HWND		g_hWnd;

void MakeRectangle(HDC hdc, int x, int y, int size);
void MakeStar(HDC hdc, int x, int y);

// 초기화하는 함수
void Init(Object* pObject)
{
	for (size_t i = 0; i < NEMO_MAX_COUNT; i++)
	{
		pObject[i].pos.x = 50 + (i * 150); /* 200; 350;*/
		pObject[i].pos.y = 500;
		pObject[i].shape = NEMO_SHAPE::NEMO;
	}
}

// 출력 관련 함수
void Render(HDC hdc, MouseData mouseData, Object* pObject, int selectedRectId)
{
	char szText[128] = "";
	wsprintf(szText, "X : %d, Y : %d", mouseData.posX, mouseData.posY);
	TextOut(hdc, mouseData.posX, mouseData.posY, szText, strlen(szText));

	wsprintf(szText, "Clicked X : %d, Y : %d", mouseData.posX, mouseData.posY);
	TextOut(hdc, 10, 30, szText, strlen(szText));

	wsprintf(szText, "Selected ID : %d", selectedRectId);
	TextOut(hdc, 100, 5, szText, strlen(szText));

	for (int i = 0; i < NEMO_MAX_COUNT; i++)
	{
		switch (pObject[i].shape)
		{
		case NEMO_SHAPE::NEMO:
			MakeRectangle(hdc, pObject[i].pos.x, pObject[i].pos.y, NEMO_SIZE);
			break;
		case NEMO_SHAPE::STAR:
			MakeStar(hdc, pObject[i].pos.x, pObject[i].pos.y);
			break;
		}
	}
}

void MakeRectangle(HDC hdc, int x, int y, int size)
{

}

void MakeStar(HDC hdc, int x, int y) 
{
	MoveToEx(hdc, x, y, NULL);
	LineTo(hdc, x + 30, y);
	LineTo(hdc, x + 5, y + 20);
	LineTo(hdc, x + 15, y - 10);
	LineTo(hdc, x + 25, y + 20);
	LineTo(hdc, x, y);
}

// 포인트와 렉트의 충돌 확인
bool IsInRect(RECT rc, POINT pt)
{
	//if (pt.x < rc.left || pt.x > rc.right || pt.y < rc.top || pt.y > rc.bottom)
	//{
	//	return false;
	//}
	//
	//return true;


	// 마우스 x좌표가 left보다 크다 &&
	// 마우스 x좌표가 right보다 작다 &&
	// 마우스 y좌표가 top보다 크다 &&
	// 마우스 y좌표가 bottom보다 작다
	if (rc.left < pt.x && pt.x < rc.right && rc.top < pt.y && pt.y < rc.bottom)
	{
		return true;
	}

	return false;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

// 윈도우를 생성하기 위한 함수
int APIENTRY WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpszCmdParam, int nCmdShow) {

	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;

	// 윈도우 출력
	ShowWindow(g_hWnd, nCmdShow);
}

// 윈도우 메세지를 처리하는 함수 (콜백 함수)
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage)
{
	PAINTSTRUCT ps;

	static MouseData mouseData;
	static Object object[NEMO_MAX_COUNT];
	static int selectedRectId = -1;

	switch (iMessage)
	{
	case WM_CREATE:
		Init(object);
		break;
	case WM_MOUSEMOVE:
		mouseData.posX = LOWORD(lParam);
		mouseData.posY = HIWORD(lParam);

		if (selectedRectId != -1)
		{
			object[selectedRectId].pos.x = mouseData.posX - (NEMO_SIZE / 2);
			object[selectedRectId].pos.y = mouseData.posY - (NEMO_SIZE / 2);
		}
		
		InvalidateRect(g_hWnd, NULL, true);
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_LBUTTONUP:
		object[selectedRectId].shape = NEMO_SHAPE::STAR;

		selectedRectId = -1;
		InvalidateRect(g_hWnd, NULL, true);
		break;
	case WM_LBUTTONDOWN:
		mouseData.clickedPosX = LOWORD(lParam);
		mouseData.clickedPosY = HIWORD(lParam);
		POINT pt;
		pt = { mouseData.clickedPosX , mouseData.clickedPosY };
		RECT rc;
		for (int i = 0; i < NEMO_MAX_COUNT; i++)
		{
			rc.left = object[i].pos.x;
			rc.top = object[i].pos.y;
			rc.right = object[i].pos.x + NEMO_SIZE;
			rc.bottom = object[i].pos.y + NEMO_SIZE;
			if (IsInRect(rc, pt))
			{
				selectedRectId = i;
				break;
			}
		}

		InvalidateRect(g_hWnd, NULL, true);
	}
	case WM_PAINT:
		HDC hdc;
		hdc = BeginPaint(g_hWnd, &ps);

		// 출력함수
		Render(hdc, mouseData, object, selectedRectId);
		break;

	}
}