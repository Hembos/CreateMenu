#include <Windows.h>
#include "Header.h"
///////////////////////////////////// глобальные переменные
char szClassName[] = "Window1";
HWND hWnd;
CurrentWinBut CWB;
WINDOW* Window;
///////////////////////////////////// прототипы функций
LRESULT CALLBACK WndProc(HWND, UINT, UINT, LONG);

ATOM registerMyClass(HINSTANCE hInstance);

int createMyWindow(HINSTANCE hInstance, int nCmdShow);
//////////////////////////////////////

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpszCmdParam, _In_ int nCmdShow)
{
	//Window = SystemOpen();
	Window = Reader();
	CWB.k = 1;
	CWB.NumButton = 0;
	CWB.NumWindow = 0;
	CWB.WinDraws = malloc(10 * sizeof(int));
	if (CWB.WinDraws == NULL)
	{
		printf("ERROR");
		exit(1);
	}
	CWB.WinDraws[0] = 0;
	for (int i = 1; i < 10; i++)
		CWB.WinDraws[i] = -1;

	createMyWindow(hInstance, nCmdShow);

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	SystemClose(Window);
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		DrawMenu(hdc, CWB, Window);
		EndPaint(hWnd, &ps);
	}
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_DOWN:
		{
			CWB = Down(CWB, Window);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		case VK_UP:
		{
			if (CWB.NumButton > 0)
			{
				CWB = Up(CWB, Window);
				InvalidateRect(hWnd, NULL, TRUE);
			}
			break;
		}
		case VK_RIGHT:
		{

			if (Window[CWB.NumWindow].Button[CWB.NumButton].Binding != 0)
			{
				CWB = Right(CWB, Window);
				InvalidateRect(hWnd, NULL, TRUE);
			}
			break;
		}
		case VK_LEFT:
		{

			if (CWB.NumButton == 0 && CWB.NumWindow != 0)
			{
				CWB = Left(CWB, Window);
				InvalidateRect(hWnd, NULL, TRUE);
			}
			break;
		}
		case VK_RETURN:
		{
			MessageBox(hWnd, Window[CWB.NumWindow].Button[CWB.NumButton].name, NULL, MB_OK);
			break;
		}
		default:
			break;
		}
	}
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int createMyWindow(HINSTANCE hInstance, int nCmdShow)
{
	registerMyClass(hInstance);

	hWnd = CreateWindow(szClassName, "Menu", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 900, 600, NULL, NULL, hInstance, NULL);

	if (!hWnd) { return 0; }
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
}

ATOM registerMyClass(HINSTANCE hInstance)
{
	WNDCLASS wc;
	wc.cbClsExtra = wc.cbWndExtra = 0;
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szClassName;

	return RegisterClass(&wc);
}
