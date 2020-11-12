/*
	Win32 API
	: Application Programming Interface
	�ü���� �������α׷� ������ ���� �����ϴ� �Լ��� ����

	�ϵ���� --------�ü�� (Windows)--------- �������α׷�
						(API �Լ�)

	�ڵ�(Handle) : �����츦 �����ϴ� �� ��ü�� �����ϴ� �ε��� (����)
	�޼���(Message) : �����쿡�� �߻��� �̺�Ʈ�� �ü���� ���� �����쿡�� �����ϴ� ������ ����
*/

/*
	1. �簢���� ����Ѵ�. * 10
	2. �簢���� �����Ѵ�. (Point Rect �浹 Ȯ��)
	3. �巡�� ��� ���� (�簢���� �����ؼ� �̵���Ų��)
	4. �巡�� �� ��� ���Ŀ� �簢���� �� ������� ���
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

// ��������
HINSTANCE	g_hInstance;
HWND		g_hWnd;

void MakeRectangle(HDC hdc, int x, int y, int size);
void MakeStar(HDC hdc, int x, int y);

// �ʱ�ȭ�ϴ� �Լ�
void Init(Object* pObject)
{
	for (size_t i = 0; i < NEMO_MAX_COUNT; i++)
	{
		pObject[i].pos.x = 50 + (i * 150); /* 200; 350;*/
		pObject[i].pos.y = 500;
		pObject[i].shape = NEMO_SHAPE::NEMO;
	}
}

// ��� ���� �Լ�
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

// ����Ʈ�� ��Ʈ�� �浹 Ȯ��
bool IsInRect(RECT rc, POINT pt)
{
	//if (pt.x < rc.left || pt.x > rc.right || pt.y < rc.top || pt.y > rc.bottom)
	//{
	//	return false;
	//}
	//
	//return true;


	// ���콺 x��ǥ�� left���� ũ�� &&
	// ���콺 x��ǥ�� right���� �۴� &&
	// ���콺 y��ǥ�� top���� ũ�� &&
	// ���콺 y��ǥ�� bottom���� �۴�
	if (rc.left < pt.x && pt.x < rc.right && rc.top < pt.y && pt.y < rc.bottom)
	{
		return true;
	}

	return false;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

// �����츦 �����ϱ� ���� �Լ�
int APIENTRY WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpszCmdParam, int nCmdShow) {

	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;

	// ������ ���
	ShowWindow(g_hWnd, nCmdShow);
}

// ������ �޼����� ó���ϴ� �Լ� (�ݹ� �Լ�)
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

		// ����Լ�
		Render(hdc, mouseData, object, selectedRectId);
		break;

	}
}