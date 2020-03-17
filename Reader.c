#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <ctype.h>
#include "Header.h"

int length = 0;

WINDOW* SystemOpen()
{
	WINDOW* Window;

	Window = malloc(10 * sizeof(WINDOW));
	if (Window == NULL)
	{
		printf("ERROR");
		exit(1);
	}
	for (int i = 0; i < 10; i++)
	{
		Window[i].CountButton = 0;
		Window[i].Button = malloc(10 * sizeof(BUTTON));
		if (Window[i].Button == NULL)
		{
			printf("ERROR");
			exit(1);
		}
		for (int j = 0; j < 10; j++)
		{
			Window[i].Button[j].name = malloc(100 * sizeof(char));
			if (Window[i].Button[j].name == NULL)
			{
				printf("ERROR");
				exit(1);
			}
		}
	}
	Window->CountWindow = 0;
	return Window;
}

void SystemClose(WINDOW* Window)
{
	for (int i = 0; i < 10; i++)
	{
		free(Window[i].Button);
	}
	free(Window);
}

int CommandName(char* str)
{
	if (!strcmp(str, "MenuBegin"))
		return MENUBEGIN;
	if (!strcmp(str, "MenuEnd"))
		return MENUEND;
	if (!strcmp(str, "WindowBegin"))
		return WINDOWBEGIN;
	if (!strcmp(str, "WindowEnd"))
		return WINDOWEND;
	return -1;
}

char* DeleteSpace(char* str)
{
	char* tmp;
	int index = 0;
	tmp = malloc(1024 * sizeof(char));
	if (tmp == NULL)
	{
		printf("ERROR");
		exit(1);
	}
	for (unsigned int i = 0; i < strlen(str); i++)
	{
		if (!isspace(str[i]))
		{
			tmp[index++] = str[i];
		}
	}
	tmp[index] = '\0';
	str = tmp;
	return str;
}

int Numbers(char* str)
{
	int Num = -1;

	for (; *str != '\n';)
	{
		if (isdigit(*str))
		{
			Num = atoi(str);
			while (isdigit(*str))
				str++;
			break;
		}
		str++;
	}

	return Num;
}

char* Name(char* str)
{
	char* Name;
	int i;
	Name = malloc(100 * sizeof(char));
	for (; *str != '(';)
		str++;
	str++;
	for (i = 0; *str != ','; i++)
	{
		Name[i] = *str;
		str++;
	}
	Name[i] = '\0';
	return Name;
}

char* ShiftPointer(char* str)
{
	str++;
	for (; *str != ',' && *str != ')';)
	{
		str++;
		length++;
	}

	return str;
}

char* ReverseShift(char* str)
{
	for (int i = 0; i < length; i++)
	{
		str--;
	}
	length = 0;
	return str;
}

WINDOW* Reader(WINDOW* Window)
{
	FILE* fp;
	int kindCom;
	char* str;
	str = malloc(1024 * sizeof(char));
	if (str == NULL)
	{
		printf("ERROR");
		exit(1);
	}
	fopen_s(&fp, "Text.txt", "r");
	if (fp == NULL)
	{
		printf("ERROR");
		exit(1);
	}

	fgets(str, 1024, fp);
	str = DeleteSpace(str);
	kindCom = CommandName(str);
	if (kindCom == 0)
	{
		while (kindCom != 3)
		{
			fgets(str, 1024, fp);
			str = DeleteSpace(str);
			kindCom = CommandName(str);
			if (kindCom == 3)
				break;
			while (kindCom != 2)
			{
				fgets(str, 1024, fp);
				str = DeleteSpace(str);
				kindCom = CommandName(str);
				if (kindCom != 2)
				{
					Window[Window->CountWindow].Button[Window[Window->CountWindow].CountButton].name = Name(str);
					str = ShiftPointer(str);

					Window[Window->CountWindow].Button[Window[Window->CountWindow].CountButton].color.R = Numbers(str);
					str = ShiftPointer(str);
					Window[Window->CountWindow].Button[Window[Window->CountWindow].CountButton].color.G = Numbers(str);
					str = ShiftPointer(str);
					Window[Window->CountWindow].Button[Window[Window->CountWindow].CountButton].color.B = Numbers(str);
					str = ShiftPointer(str);

					Window[Window->CountWindow].Button[Window[Window->CountWindow].CountButton].HighlightColor.R = Numbers(str);
					str = ShiftPointer(str);
					Window[Window->CountWindow].Button[Window[Window->CountWindow].CountButton].HighlightColor.G = Numbers(str);
					str = ShiftPointer(str);
					Window[Window->CountWindow].Button[Window[Window->CountWindow].CountButton].HighlightColor.B = Numbers(str);
					str = ShiftPointer(str);

					Window[Window->CountWindow].Button[Window[Window->CountWindow].CountButton].position.x = Numbers(str);
					str = ShiftPointer(str);
					Window[Window->CountWindow].Button[Window[Window->CountWindow].CountButton].position.y = Numbers(str);
					str = ShiftPointer(str);

					Window[Window->CountWindow].Button[Window[Window->CountWindow].CountButton].Binding = Numbers(str);
					str = ReverseShift(str);

					Window[Window->CountWindow].CountButton++;
				}
			}
			Window->CountWindow++;
		}
	}
	else
	{
		printf("ERROR");
		exit(1);
	}

	free(str);
	fclose(fp);
	return Window;
}
