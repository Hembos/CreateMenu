#include "Header.h"

void DrawMenu(HDC hdc, CurrentWinBut CWB, WINDOW* Window)
{
	HPEN OldPen, BlackPen, BluePen;
	HBRUSH Brush;

	BlackPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	BluePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	OldPen = (HPEN)SelectObject(hdc, BlackPen);
	for (int i = 0; i <= CWB.k; i++)
	{
		for (int j = 0; CWB.WinDraws[i] != -1 && j < Window[CWB.WinDraws[i]].CountButton; j++)
		{
			Brush = CreateSolidBrush(RGB(Window[CWB.WinDraws[i]].Button[j].color.R, Window[CWB.WinDraws[i]].Button[j].color.G, Window[CWB.WinDraws[i]].Button[j].color.B));
			SelectObject(hdc, Brush);
			if (CWB.NumWindow == CWB.WinDraws[i] && j == CWB.NumButton)
			{

				Brush = CreateSolidBrush(RGB(Window[CWB.WinDraws[i]].Button[j].HighlightColor.R, Window[CWB.WinDraws[i]].Button[j].HighlightColor.G, Window[CWB.WinDraws[i]].Button[j].HighlightColor.B));
				SelectObject(hdc, Brush);
				Rectangle(hdc, Window[CWB.WinDraws[i]].Button[j].position.x, Window[CWB.WinDraws[i]].Button[j].position.y, Window[CWB.WinDraws[i]].Button[j].position.x + 100, Window[CWB.WinDraws[i]].Button[j].position.y + 30);
				SetBkColor(hdc, RGB(Window[CWB.WinDraws[i]].Button[j].HighlightColor.R, Window[CWB.WinDraws[i]].Button[j].HighlightColor.G, Window[CWB.WinDraws[i]].Button[j].HighlightColor.B));
				TextOutA(hdc, Window[CWB.WinDraws[i]].Button[j].position.x + 2, Window[CWB.WinDraws[i]].Button[j].position.y + 2, Window[CWB.WinDraws[i]].Button[j].name, strlen(Window[CWB.WinDraws[i]].Button[j].name));
				DeleteObject(Brush);
				continue;
			}
			Rectangle(hdc, Window[CWB.WinDraws[i]].Button[j].position.x, Window[CWB.WinDraws[i]].Button[j].position.y, Window[CWB.WinDraws[i]].Button[j].position.x + 100, Window[CWB.WinDraws[i]].Button[j].position.y + 30);
			SetBkColor(hdc, RGB(Window[CWB.WinDraws[i]].Button[j].color.R, Window[CWB.WinDraws[i]].Button[j].color.G, Window[CWB.WinDraws[i]].Button[j].color.B));
			TextOutA(hdc, Window[CWB.WinDraws[i]].Button[j].position.x + 2, Window[CWB.WinDraws[i]].Button[j].position.y + 2, Window[CWB.WinDraws[i]].Button[j].name, strlen(Window[CWB.WinDraws[i]].Button[j].name));
			DeleteObject(Brush);

		}
	}
}

CurrentWinBut Down(CurrentWinBut CWB, WINDOW* Window)
{
	if (CWB.NumButton < Window[CWB.NumWindow].CountButton - 1)
	{
		CWB.NumButton++;
		if (Window[CWB.NumWindow].Button[CWB.NumButton].Binding != 0)
		{
			CWB.WinDraws[CWB.k] = Window[CWB.NumWindow].Button[CWB.NumButton].Binding;
		}
		else
		{
			CWB.WinDraws[CWB.k] = -1;
		}
	}
	return CWB;
}

CurrentWinBut Up(CurrentWinBut CWB, WINDOW* Window)
{
	CWB.NumButton--;
	if (Window[CWB.NumWindow].Button[CWB.NumButton].Binding != 0)
	{
		CWB.WinDraws[CWB.k] = Window[CWB.NumWindow].Button[CWB.NumButton].Binding;
	}
	else
	{
		CWB.WinDraws[CWB.k] = -1;
	}
	return CWB;
}

CurrentWinBut Right(CurrentWinBut CWB, WINDOW* Window)
{
	CWB.WinDraws[CWB.k] = Window[CWB.NumWindow].Button[CWB.NumButton].Binding;
	CWB.NumWindow = Window[CWB.NumWindow].Button[CWB.NumButton].Binding;
	CWB.NumButton = 0;
	CWB.k++;
	if (Window[CWB.NumWindow].Button[CWB.NumButton].Binding != 0)
	{
		CWB.WinDraws[CWB.k] = Window[CWB.NumWindow].Button[CWB.NumButton].Binding;
	}
	else
	{
		CWB.WinDraws[CWB.k] = -1;
	}
	return CWB;
}

CurrentWinBut Left(CurrentWinBut CWB, WINDOW* Window)
{
	CWB.WinDraws[CWB.k - 1] = -1;
	CWB.NumButton = 0;
	for (int i = 0; Window[CWB.WinDraws[CWB.k - 2]].Button[i].Binding != CWB.NumWindow; i++)
		CWB.NumButton++;
	CWB.NumWindow = CWB.WinDraws[CWB.k - 2];
	CWB.k--;
	if (Window[CWB.NumWindow].Button[CWB.NumButton].Binding != 0)
	{
		CWB.WinDraws[CWB.k] = Window[CWB.NumWindow].Button[CWB.NumButton].Binding;
	}
	else
	{
		CWB.WinDraws[CWB.k] = -1;
	}
	return CWB;
}
