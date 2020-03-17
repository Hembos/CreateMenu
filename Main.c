#include <Windows.h>
#include "Header.h"
///////////////////////////////////// глобальные переменные
char szClassName[] = "Window1";
HWND hWnd;
WINDOW* Window;
int NumWindow = 0,
	NumButtton = 0,
	k = 1;
int* WinDraws;
///////////////////////////////////// прототипы функций
LRESULT CALLBACK WndProc(HWND, UINT, UINT, LONG);

ATOM registerMyClass(HINSTANCE hInstance);

int createMyWindow(HINSTANCE hInstance, int nCmdShow);
//////////////////////////////////////

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpszCmdParam, _In_ int nCmdShow)
{
	Window = SystemOpen();
	Window = Reader(Window);
	WinDraws = malloc(10 * sizeof(int));
	if (WinDraws == NULL)
	{
		printf("ERROR");
		exit(1);
	}
	WinDraws[0] = 0;
	for (int i = 1; i < 10; i++)
		WinDraws[i] = -1;

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
		HPEN OldPen, BlackPen, BluePen;
		HBRUSH Brush;

		BlackPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
		BluePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
		OldPen = (HPEN)SelectObject(hdc, BlackPen);
		for (int i = 0; i <= k; i++)
		{
			for (int j = 0; WinDraws[i] != -1 && j < Window[WinDraws[i]].CountButton; j++)
			{
				Brush = CreateSolidBrush(RGB(Window[WinDraws[i]].Button[j].color.R, Window[WinDraws[i]].Button[j].color.G, Window[WinDraws[i]].Button[j].color.B));
				SelectObject(hdc, Brush);
				//OldPen = (HPEN)SelectObject(hdc, BlackPen);
				if (NumWindow == WinDraws[i] && j == NumButtton)
				{
					
					Brush = CreateSolidBrush(RGB(Window[WinDraws[i]].Button[j].HighlightColor.R, Window[WinDraws[i]].Button[j].HighlightColor.G, Window[WinDraws[i]].Button[j].HighlightColor.B));
					SelectObject(hdc, Brush);
					Rectangle(hdc, Window[WinDraws[i]].Button[j].position.x, Window[WinDraws[i]].Button[j].position.y, Window[WinDraws[i]].Button[j].position.x + 100, Window[WinDraws[i]].Button[j].position.y + 30);
					SetBkColor(hdc, RGB(Window[WinDraws[i]].Button[j].HighlightColor.R, Window[WinDraws[i]].Button[j].HighlightColor.G, Window[WinDraws[i]].Button[j].HighlightColor.B));
					TextOutA(hdc, Window[WinDraws[i]].Button[j].position.x + 2, Window[WinDraws[i]].Button[j].position.y + 2, Window[WinDraws[i]].Button[j].name, strlen(Window[WinDraws[i]].Button[j].name));
					DeleteObject(Brush);
					continue;
				}
				Rectangle(hdc, Window[WinDraws[i]].Button[j].position.x, Window[WinDraws[i]].Button[j].position.y, Window[WinDraws[i]].Button[j].position.x + 100, Window[WinDraws[i]].Button[j].position.y + 30);
				SetBkColor(hdc, RGB(Window[WinDraws[i]].Button[j].color.R, Window[WinDraws[i]].Button[j].color.G, Window[WinDraws[i]].Button[j].color.B));
				TextOutA(hdc, Window[WinDraws[i]].Button[j].position.x + 2, Window[WinDraws[i]].Button[j].position.y + 2, Window[WinDraws[i]].Button[j].name, strlen(Window[WinDraws[i]].Button[j].name));
				DeleteObject(Brush);
				
			}
		}

		EndPaint(hWnd, &ps);
	}
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_DOWN:
		{
			if (NumButtton < Window[NumWindow].CountButton - 1)
			{
				NumButtton++;
				if (Window[NumWindow].Button[NumButtton].Binding != 0)
				{
					WinDraws[k] = Window[NumWindow].Button[NumButtton].Binding;
				}
				else
				{
					WinDraws[k] = -1;
				}
				InvalidateRect(hWnd, NULL, TRUE);
			}
			
			break;
		}
		case VK_UP:
		{

			if (NumButtton > 0)
			{
				NumButtton--;
				if (Window[NumWindow].Button[NumButtton].Binding != 0)
				{
					WinDraws[k] = Window[NumWindow].Button[NumButtton].Binding;
				}
				else
				{
					WinDraws[k] = -1;
				}
				InvalidateRect(hWnd, NULL, TRUE);
			}
			break;
		}
		case VK_RIGHT:
		{

			if (Window[NumWindow].Button[NumButtton].Binding != 0)
			{
				WinDraws[k] = Window[NumWindow].Button[NumButtton].Binding;
				NumWindow = Window[NumWindow].Button[NumButtton].Binding;
				NumButtton = 0;
				k++;
				if (Window[NumWindow].Button[NumButtton].Binding != 0)
				{
					WinDraws[k] = Window[NumWindow].Button[NumButtton].Binding;
				}
				else
				{
					WinDraws[k] = -1;
				}
				InvalidateRect(hWnd, NULL, TRUE);
			}


			break;
		}
		case VK_LEFT:
		{

			if (NumButtton == 0 && NumWindow != 0)
			{
				WinDraws[k - 1] = -1;
				NumButtton = 0;
				for (int i = 0; Window[WinDraws[k - 2]].Button[i].Binding != NumWindow; i++)
					NumButtton++;
				NumWindow = WinDraws[k - 2];
				k--;
				if (Window[NumWindow].Button[NumButtton].Binding != 0)
				{
					WinDraws[k] = Window[NumWindow].Button[NumButtton].Binding;
				}
				else
				{
					WinDraws[k] = -1;
				}
				InvalidateRect(hWnd, NULL, TRUE);
			}
			break;
		}
		case VK_RETURN:
		{
			MessageBox(hWnd, Window[NumWindow].Button[NumButtton].name, NULL, MB_OK);
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
