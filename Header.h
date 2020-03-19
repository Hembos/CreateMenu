#pragma once
#include <string.h>
#include <Windows.h>

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
	int CountButton;
} WINDOW;

typedef struct
{
	int NumWindow, //=0
		NumButton,//=0
		k;//=1
	int* WinDraws;
} CurrentWinBut;

CurrentWinBut CWB;

WINDOW* Window;

//WINDOW* SystemOpen();
void SystemClose();
WINDOW* Reader();
void DrawMenu(HDC hdc);
void Down();
void Up();
void Right();
void Left();
