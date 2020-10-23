#include "framework.h"
#include "MainGame.h"
#include "Resource.h"
#include <string>

HRESULT MainGame::Init(HWND hWnd, HINSTANCE hInst)
{
	this->hWnd = hWnd;

	return S_OK;
}


LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_TIMER:
		switch (wParam)
		{
		case 0:
			InvalidateRect(hWnd, NULL, false);
			break;

		case 1:
			FPS = frame - checkFrame;
			checkFrame = frame;
			break;
		}

		break;

	case WM_CREATE:
		hTimer = (HANDLE)SetTimer(hWnd, 0, 1000 / 70, NULL);
		hTimer2 = (HANDLE)SetTimer(hWnd, 1, 1000, NULL);

		// ´õºí ¹öÆÛ
		hdc = GetDC(hWnd);
		hdc_BackGround = CreateCompatibleDC(hdc);
		ReleaseDC(hWnd, hdc);
		HBITMAP bitBackGround;
		bitBackGround = LoadBitmap(g_hInstance, MAKEINTRESOURCE(IDB_BITMAP1));
		SelectObject(hdc_BackGround, bitBackGround);
		DeleteObject(bitBackGround);

		break;
	case WM_MOUSEMOVE:
		mouse.x = LOWORD(lParam);
		mouse.y = HIWORD(lParam);
		if (isDragging)
		{
			clickedMouse.x = LOWORD(lParam);
			clickedMouse.y = HIWORD(lParam);
		}
		if (isMDragging)
		{
			zooming = mouse.y;
			zoom += ((float)zooming - (float)zoomStart) / 200;
			if (zoom < 0.005)
				zoom = 0.005;
			zoomStart = zooming;
		}
		break;

	case WM_LBUTTONDOWN:
		if (isDragging == false)
		{
			isDragging = true;
			clickedMouse.x = LOWORD(lParam);
			clickedMouse.y = HIWORD(lParam);
		}
		break;

	case WM_LBUTTONUP:
		if (isDragging == true)
			isDragging = false;
		break;

	case WM_MBUTTONDOWN:
		if (isMDragging == false)
		{
			zoomStart = mouse.y;
			isMDragging = true;
		}
		break;

	case WM_MBUTTONUP:
		if (isMDragging == true)
			isMDragging = false;
		break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc;
		hdc = BeginPaint(hWnd, &ps);

		hdcMem = CreateCompatibleDC(hdc); //2
		hbmMem = CreateCompatibleBitmap(hdc, WINDOW_SIZE_X, WINDOW_SIZE_Y);//3
		hbmMemOld = (HBITMAP)SelectObject(hdcMem, hbmMem);//4

		BitBlt(hdcMem, 0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y, hdc_BackGround, 0, 0, SRCCOPY);


		Ellipse(hdcMem, 960, 508, 500 * zoom);

		for (int i = 0; i < 20; i++)
		{
			if (i == 9)
			{
				HPEN hpen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
				HPEN hpenOld = (HPEN)SelectObject(hdcMem, hpen);

				MoveToEx(hdcMem, i * 100 + 60, 0, NULL);
				LineTo(hdcMem, i * 100 + 60, WINDOW_SIZE_Y);

				DeleteObject(SelectObject(hdcMem, hpenOld));

			}
			MoveToEx(hdcMem, i * 100 + 60, 0, NULL);
			LineTo(hdcMem, i * 100 + 60, WINDOW_SIZE_Y);

		}
		for (int i = 0; i < 11; i++)
		{
			if (i == 5)
			{
				HPEN hpen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
				HPEN hpenOld = (HPEN)SelectObject(hdcMem, hpen);

				MoveToEx(hdcMem, 0, i * 100 + 8, NULL);
				LineTo(hdcMem, WINDOW_SIZE_X, i * 100 + 8);

				DeleteObject(SelectObject(hdcMem, hpenOld));

			}

			MoveToEx(hdcMem, 0, i * 100 + 8, NULL);
			LineTo(hdcMem, WINDOW_SIZE_X, i * 100 + 8);
		}

		PrintCos((frame / 4) % 360, zoom);
		PrintSin((frame / 4) % 360, zoom);
		PrintDegree((frame / 4) % 360, zoom);
		POINTFLOAT p = CoordToPlain(clickedMouse.x, clickedMouse.y, zoom);

		PrintAtan2(p.x, p.y, zoom);

		char buf[50];
		wsprintf(buf, "%d", frame);
		TextOut(hdcMem, 0, 0, buf, strlen(buf));

		wsprintf(buf, "X : %d, Y : %d", mouse.x, mouse.y);
		TextOut(hdcMem, 10, 30, buf, strlen(buf));



		wsprintf(buf, "0, 0");
		TextOut(hdcMem, 960 + 2, 508 + 2, buf, strlen(buf));

		wsprintf(buf, "FPS : %d", FPS);
		TextOut(hdcMem, 0, 50, buf, strlen(buf));

		std::string s = "Zoom : " + std::to_string(zoom);
		TextOut(hdcMem, 0, 70, s.c_str(), strlen(s.c_str()));

		BitBlt(hdc, 0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y, hdcMem, 0, 0, SRCCOPY);

		SelectObject(hdcMem, hbmMemOld); //-4
		DeleteObject(hbmMem); //-3
		DeleteDC(hdcMem); //-2

		EndPaint(hWnd, &ps);
		frame++;
	}
	break;
	case WM_DESTROY:
		KillTimer(hWnd, 0);
		DeleteDC(hdcMem); //-2
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, iMessage, wParam, lParam);
	}
	return 0;
}

void MainGame::PrintCos(float degree, float zoom)
{
	HPEN hpen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	HPEN hpenOld = (HPEN)SelectObject(hdcMem, hpen);
	HFONT hFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, _T("±Ã¼­"));
	HFONT hFontOld = (HFONT)SelectObject(hdcMem, hFont);
	SetTextColor(hdcMem, RGB(255, 0, 0));
	SetBkMode(hdcMem, TRANSPARENT);

	MoveToEx(hdcMem, 960, 500 + 8, NULL);
	LineTo(hdcMem, cos(RADIAN(degree)) * 500 * zoom + 960, 500 + 8);

	std::string s = "cos(" + std::to_string(degree).substr(0, 4) + ") : " + std::to_string(cos(RADIAN(degree))).substr(0, 5) + ", 0";
	TextOut(hdcMem, cos(RADIAN(degree)) * 500 * zoom + 960 + 2, 508 + 2, s.c_str(), strlen(s.c_str()));

	SetTextColor(hdcMem, RGB(0, 0, 0));
	DeleteObject(SelectObject(hdcMem, hpenOld));
	DeleteObject(SelectObject(hdcMem, hFontOld));
}

void MainGame::PrintSin(float degree, float zoom)
{
	HPEN hpen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
	HPEN hpenOld = (HPEN)SelectObject(hdcMem, hpen);
	HFONT hFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, _T("±Ã¼­"));
	HFONT hFontOld = (HFONT)SelectObject(hdcMem, hFont);
	SetTextColor(hdcMem, RGB(0, 0, 255));
	SetBkMode(hdcMem, TRANSPARENT);

	MoveToEx(hdcMem, 960, 500 + 8, NULL);
	LineTo(hdcMem, 960, -sin(RADIAN(degree)) * 500 * zoom + 500 + 8);

	std::string s = +"sin(" + std::to_string(degree).substr(0, 4) + ") : 0, " + std::to_string(sin(RADIAN(degree))).substr(0, 5);
	TextOut(hdcMem, 960 + 2, -sin(RADIAN(degree)) * 500 * zoom + 508 + 2, s.c_str(), strlen(s.c_str()));

	SetTextColor(hdcMem, RGB(0, 0, 0));
	DeleteObject(SelectObject(hdcMem, hpenOld));
	DeleteObject(SelectObject(hdcMem, hFontOld));
}

void MainGame::PrintDegree(float degree, float zoom)
{
	HPEN hpen = CreatePen(PS_SOLID, 3, RGB(255, 0, 255));
	HPEN hpenOld = (HPEN)SelectObject(hdcMem, hpen);
	HFONT hFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, _T("±Ã¼­"));
	HFONT hFontOld = (HFONT)SelectObject(hdcMem, hFont);
	SetTextColor(hdcMem, RGB(255, 0, 255));
	SetBkMode(hdcMem, TRANSPARENT);

	MoveToEx(hdcMem, 960, 500 + 8, NULL);
	LineTo(hdcMem, cos(RADIAN(degree)) * 500 * zoom + 960, -sin(RADIAN(degree)) * 500 * zoom + 500 + 8);

	DeleteObject(SelectObject(hdcMem, hpenOld));

	MoveToEx(hdcMem, cos(RADIAN(degree)) * 500 * zoom + 960, 500 + 8, NULL);
	LineTo(hdcMem, cos(RADIAN(degree)) * 500 * zoom + 960, -sin(RADIAN(degree)) * 500 * zoom + 500 + 8);

	MoveToEx(hdcMem, 960, -sin(RADIAN(degree)) * 500 * zoom + 500 + 8, NULL);
	LineTo(hdcMem, cos(RADIAN(degree)) * 500 * zoom + 960, -sin(RADIAN(degree)) * 500 * zoom + 500 + 8);

	std::string s = std::to_string(cos(RADIAN(degree))).substr(0, 5) + ", " + std::to_string(sin(RADIAN(degree))).substr(0, 5) + "(°¢µµ : " + std::to_string(degree).substr(0, 4) + ")";
	TextOut(hdcMem, cos(RADIAN(degree)) * 500 * zoom + 960 + 2, -sin(RADIAN(degree)) * 500 * zoom + 508 + 2 + 30, s.c_str(), strlen(s.c_str()));

	SetTextColor(hdcMem, RGB(0, 0, 0));

	DeleteObject(SelectObject(hdcMem, hFontOld));
}

void MainGame::PrintAtan2(float a, float b, float zoom)
{
	HPEN hpen = CreatePen(PS_SOLID, 3, RGB(0, 180, 0));
	HPEN hpenOld = (HPEN)SelectObject(hdcMem, hpen);
	HFONT hFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, _T("±Ã¼­"));
	HFONT hFontOld = (HFONT)SelectObject(hdcMem, hFont);
	SetTextColor(hdcMem, RGB(0, 180, 0));
	SetBkMode(hdcMem, TRANSPARENT);

	MoveToEx(hdcMem, 960, 500 + 8, NULL);
	LineTo(hdcMem, a * 500 * zoom + 960, -b * 500 * zoom + 500 + 8);

	std::string s = std::to_string(a).substr(0, 5) + ", " + std::to_string(b).substr(0, 5) + "(°¢µµ(atan2) : " + std::to_string(DEGREE(atan2(-b, a))) + ")";
	//std::string s = std::to_string(a).substr(0, 5) + ", " + std::to_string(b).substr(0, 5) + "(°¢µµ(atan2) : " + std::to_string(DEGREE(atan(-b/a))) + ")";

	TextOut(hdcMem, a * 500 * zoom + 960 + 2, -b * 500 * zoom + 508 + 2, s.c_str(), strlen(s.c_str()));

	SetTextColor(hdcMem, RGB(0, 0, 0));
	DeleteObject(SelectObject(hdcMem, hpenOld));
	DeleteObject(SelectObject(hdcMem, hFontOld));
}

