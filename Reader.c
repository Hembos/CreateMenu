#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <ctype.h>
#include "Header.h"

WINDOW* Window;
int length = 0;
int CountWindow = 0;

typedef enum
{
	MENUBEGIN,
	WINDOWBEGIN,
	WINDOWEND,
	MENUEND
} MENU;

void SystemClose()
{
	for (int i = 0; i < CountWindow; i++)
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
	Name = malloc(sizeof(char));
	if (Name == NULL)
	{
		printf("ERROR");
		exit(1);
	}
	for (; *str != '(';)
		str++;
	str++;
	for (i = 0; *str != ','; i++)
	{
		Name = realloc(Name, (i + 1) * sizeof(char));
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

WINDOW* Reader()
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

	Window = malloc(sizeof(WINDOW));
	if (Window == NULL)
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
			Window = realloc(Window, (CountWindow + 1) * sizeof(WINDOW));
			if (Window == NULL)
			{
				printf("ERROR");
				exit(1);
			}
			Window[CountWindow].Button = malloc(sizeof(BUTTON));
			if (Window[CountWindow].Button == NULL)
			{
				printf("ERROR");
				exit(1);
			}
			Window[CountWindow].CountButton = 0;
			while (kindCom != 2)
			{
				
				fgets(str, 1024, fp);
				str = DeleteSpace(str);
				kindCom = CommandName(str);
				Window[CountWindow].Button = realloc(Window[CountWindow].Button, (Window[CountWindow].CountButton + 1) * sizeof(BUTTON));
				if (Window[CountWindow].Button == NULL)
				{
					printf("ERROR");
					exit(1);
				}

				if (kindCom != 2)
				{
					Window[CountWindow].Button[Window[CountWindow].CountButton].name = Name(str);
					str = ShiftPointer(str);

					Window[CountWindow].Button[Window[CountWindow].CountButton].color.R = Numbers(str);
					str = ShiftPointer(str);
					Window[CountWindow].Button[Window[CountWindow].CountButton].color.G = Numbers(str);
					str = ShiftPointer(str);
					Window[CountWindow].Button[Window[CountWindow].CountButton].color.B = Numbers(str);
					str = ShiftPointer(str);

					Window[CountWindow].Button[Window[CountWindow].CountButton].HighlightColor.R = Numbers(str);
					str = ShiftPointer(str);
					Window[CountWindow].Button[Window[CountWindow].CountButton].HighlightColor.G = Numbers(str);
					str = ShiftPointer(str);
					Window[CountWindow].Button[Window[CountWindow].CountButton].HighlightColor.B = Numbers(str);
					str = ShiftPointer(str);

					Window[CountWindow].Button[Window[CountWindow].CountButton].position.x = Numbers(str);
					str = ShiftPointer(str);
					Window[CountWindow].Button[Window[CountWindow].CountButton].position.y = Numbers(str);
					str = ShiftPointer(str);

					Window[CountWindow].Button[Window[CountWindow].CountButton].Binding = Numbers(str);
					str = ReverseShift(str);

					Window[CountWindow].CountButton++;
				}
			}
			CountWindow++;

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
