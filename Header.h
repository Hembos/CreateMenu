#pragma once
#include <string.h>

typedef enum
{
	MENUBEGIN,
	WINDOWBEGIN,
	WINDOWEND,
	MENUEND
} MENU;

typedef struct
{
	int x;
	int y;
} POSITION;

typedef struct
{
	int R;
	int G;
	int B;
} COLOR;

typedef struct
{
	POSITION position;
	char* name;
	COLOR color;
	COLOR HighlightColor;
	int Binding;
} BUTTON;

typedef struct
{
	BUTTON* Button;
	int CountWindow;
	int CountButton;
} WINDOW;

WINDOW* SystemOpen();
void SystemClose(WINDOW* Window);
WINDOW* Reader(WINDOW* Window);
