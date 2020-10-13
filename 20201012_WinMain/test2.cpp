#include <Windows.h>

HINSTANCE g_hinstance;
HWND g_hWnd;
LPSTR g_lpszClass = (LPSTR)TEXT("гоюл");

//LRESULT CALLBACK WinProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

//int APIENTRY WinMain(HINSTANCE _hinstance, HINSTANCE _hPrevInstance, LPSTR lpszCmdClass, int nCmdShow)
int APIENTRY WinMain(HINSTANCE _hinstance, HINSTANCE _hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	g_hinstance = _hinstance;

	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = g_hinstance;
	//wndClass.lpfnWndProc = WinProc;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = g_lpszClass;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_VREDRAW | CS_HREDRAW;
	RegisterClass(&wndClass);

	g_hWnd = CreateWindow(g_lpszClass, g_lpszClass, WS_OVERLAPPEDWINDOW, 50, 50, 1200, 900, NULL, NULL, g_hinstance, NULL);

	ShowWindow(g_hWnd, nCmdShow);

	MSG message;
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return message.wParam;
}

//LRESULT CALLBACK WinProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) 
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) 
{
	switch (iMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}