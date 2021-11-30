#pragma once
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <wincon.h>
#include"Variables.h"

CONSOLE_SCREEN_BUFFER_INFO info;

void Warning(const char content[50])
{
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
	printf("%s\n", content);
	SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void SinkMsg(const char content[50])
{
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	printf("%s\n", content);
	SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void SplitLine(char text[10])
{
	char combined[86];
	sprintf(combined, "------------------------------------- %s -------------------------------------", text);
	while (strlen(combined)<84)
		strcat(combined, "-");
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	printf("%s\n", combined);
	SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void ClearLine(char ch[])
{
	GetConsoleScreenBufferInfo(handle, &info);
	short y = info.dwCursorPosition.Y;
	COORD startPos = { 0,y };
	SetConsoleCursorPosition(handle, startPos);
	for (int i = 0; i <= 50; i++)
	{
		printf(" ");
	}
	SetConsoleCursorPosition(handle, startPos);
	if (ch != NULL)
		printf("%c", ch);
}

void SetSize(int sizeOfX)
{
	if (sizeOfX == NULL)
		sizeOfX = 8;
	CONSOLE_FONT_INFOEX font;
	font.cbSize = sizeof(font);
	GetCurrentConsoleFontEx(handle, false, &font);
	font.dwFontSize.X = sizeOfX;
	font.dwFontSize.Y = sizeOfX * 2;
	SetCurrentConsoleFontEx(handle, false, &font);
}

void StdDisplay(int player, int index, int i, int j)
{
	switch (board[player][index][i][j])
	{
	case -1:
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED);
		printf("-");
		SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		break;
	case 0:
		printf("-");
		break;
	case 3:
	case 4:
	case 5:
	case 6:
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
		printf("#");
		SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		break;
	case 2:
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED);
		printf("#");
		SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		break;
	default:
		break;
	}
}

void CDisplay(int player, int index, int i, int j)
{
	switch (board[player][index][i][j])
	{
	case -1:
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED);
		printf("[-]");
		SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		break;
	case 0:
		printf("---");
		break;
	case 3:
	case 4:
	case 5:
	case 6:
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
		printf("[#]");
		SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		break;
	case 2:
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED);
		printf("[#]");
		SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		break;
	default:
		break;
	}
}

void EndDisplay(int player, int index, int i, int j)
{
	switch (board[player][index][i][j])
	{
	case -1:
		SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_RED);
		printf("[-]");
		SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		break;
	case 0:
		printf("---");
		break;
	case 3:
	case 4:
	case 5:
	case 6:
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
		printf("[#]");
		SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		break;
	case 2:
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED);
		printf("[#]");
		SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		break;
	default:
		break;
	}
}

void SmlDisplayBoard(int player, int index)
{
	printf("\n");
	printf("  A B C D E F G H I\n");
	for (i = 0; i < 9; i++)
	{
		printf("%d ", i + 1);
		for (j = 0; j < 9; j++)
		{
			StdDisplay(player, index, i, j);
			printf(" ");
		}
		printf("\n");
	}
}

void StdDisplayBoard(int player, int index)
{
	printf("\n");
	printf("   A   B   C   D   E   F   G   H   I\n");
	for (i = 0; i < 9; i++)
	{
		printf("%d ", i + 1);
		for (j = 0; j < 9; j++)
		{
			CDisplay(player, index, i, j);
			printf(" ");
		}
		printf("\n\n");
	}
}

void EndDisplayBoard(int player, int index)
{
	printf("\n");
	printf("   A   B   C   D   E   F   G   H   I\n");
	for (i = 0; i < 9; i++)
	{
		printf("%d ", i + 1);
		for (j = 0; j < 9; j++)
		{
			EndDisplay(player, index, i, j);
			printf(" ");
		}
		printf("\n\n");
	}
}

void CPDisplayBoard(int player, int index, int x, int y)
{
	printf("\n");
	printf("   A   B   C   D   E   F   G   H   I\n");
	for (i = 0; i < 9; i++)
	{
		printf("%d ", i + 1);
		for (j = 0; j < 9; j++)
		{
			if (j == x && i == y)
			{
				SetConsoleTextAttribute(handle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			}
			else
			{
				if (j == x || i == y)
				{
					SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
				}
			}
			CDisplay(player, index, i, j);
			SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			printf(" ");
		}
		printf("\n\n");
	}
}

void CODisplayBoard(int player, int index, int ax, int bx, int ay, int by)
{
	printf("\n");
	printf("   A   B   C   D   E   F   G   H   I\n");
	for (i = 0; i < 9; i++)
	{
		printf("%d ", i + 1);
		for (j = 0; j < 9; j++)
		{
			if ((j >= ax && j <= bx) && (i >= ay && i <= by))
			{
				SetConsoleTextAttribute(handle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			}
			CDisplay(player, index, i, j);
			SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			printf(" ");
		}
		printf("\n\n");
	}
}

void DisplayBoards(int player)
{
	printf("\n");
	printf("   Your Battlefield");
	printf("                ");
	printf("Opponent's Battlefield\n");
	printf("  A B C D E F G H I");
	printf("                ");
	printf("   A B C D E F G H I\n");
	for (i = 0; i < 9; i++)
	{
		printf("%d ", i + 1);
		for (j = 0; j < 9; j++)
		{
			StdDisplay(player, 1, i, j);
			printf(" ");
		}

		printf("                ");
		printf("%d ", i + 1);
		for (j = 0; j < 9; j++)
		{
			StdDisplay(1 - player, 0, i, j);
			printf(" ");
		}
		printf("\n");
	}
}

int GetDefaultOri(int player, int index, int cx, int cy, int length)
{
	int table[4][2] = {
		{ 1,1 },
		{ 2,1 },
		{ 3,1 },
		{ 4,1 }
	};

	if (cx - length + 1 > 0)
	{
		for (i = 1; i < length; i++)
		{
			if (board[player][index][cy][cx - i] != 0)
			{
				table[3][1] = 0;
			}
		}
	}
	else
		table[3][1] = 0;

	if (cx + length - 1 < 9)
	{
		for (i = 1; i < length; i++)
		{
			if (board[player][index][cy][cx + i] != 0)
			{
				table[1][1] = 0;
			}
		}
	}
	else
		table[1][1] = 0;

	if (cy - length + 1 > 0)
	{
		for (i = 1; i < length; i++)
		{
			if (board[player][index][cy - i][cx] != 0)
			{
				table[0][1] = 0;
			}
		}
	}
	else
		table[0][1] = 0;

	if (cy + length - 1 < 9)
	{
		for (i = 1; i < length; i++)
		{
			if (board[player][index][cy + i][cx] != 0)
			{
				table[2][1] = 0;
			}
		}
	}
	else
		table[2][1] = 0;

	for (i = 0; i <= 3; i++)
	{
		if (table[i][1] == 1)
			return table[i][0];
	}
	return -1;
}

void GetDefaultPos(int player, int index, int *cx, int *cy)
{
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			if (board[player][index][i][j] == 0)
			{
				*cx = j;
				*cy = i;
				return;
			}
		}
	}
	return;
}

bool CheckOri(int player, int index, int cx, int cy, int length)
{
	int ori = GetDefaultOri(player, index, cx, cy, length);
	if (ori == -1)
		return false;
	else
		return true;
}

void DisplayShipSurvive(int shipIndex)
{
	switch (shipIndex)
	{
	case 2:
		SinkMsg("Your Destroyer(length: 2) has sunk!");
		break;
	case 3:
		SinkMsg("Your Cruiser(length: 3) has sunk!");
		break;
	case 4:
		SinkMsg("Your Battleship(length: 4) has sunk!");
		break;
	case 5:
		SinkMsg("Your Carrier(length: 5) has sunk!");
		break;
	default:
		break;
	}
	return;
}

COORD ChoosePosition(int player, int index, int *tx, int *ty)
{
	GetConsoleScreenBufferInfo(handle, &info);
	short x = info.dwCursorPosition.X;
	short y = info.dwCursorPosition.Y;
	COORD pos = { x,y };
	int cx = 0, cy = 0;
	char lx;
	int input;
	bool isValid;
	GetDefaultPos(player, index, &cx, &cy);
	do {
		//SetConsoleCursorPosition(handle, pos);
		//printf("\n");
		//printf("  A B C D E F G H I\n");
		//int i, j;
		//for (i = 0; i < 9; i++)
		//{
		//	printf("%d ", i + 1);
		//	for (j = 0; j < 9; j++)
		//	{
		//		if (j == cx && i == cy)
		//		{
		//			SetConsoleTextAttribute(handle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		//		}
		//		else
		//		{
		//			if (j == cx || i == cy)
		//			{
		//				SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
		//			}
		//		}
		//		Display(player, index, i, j);
		//		SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		//		printf(" ");
		//	}
		//	printf("\n");
		//}
		isValid = true;
		lx = cx + 'A';

		SetConsoleCursorPosition(handle, pos);
		CPDisplayBoard(player, index, cx, cy);
		printf("Current Position : %c%d\n", lx, cy + 1);
		if (board[player][index][cy][cx] != 0)
		{
			isValid = false;
			Warning("You have already attacked that position");
		}
		else
			ClearLine(NULL);

		input = getch();
		if (input == 0xe0)
		{
			int a = getch();
			switch (a)
			{
			case 0x48:
				if (cy > 0)
					cy--;
				break;
			case 0x50:
				if (cy < 8)
					cy++;
				break;
			case 0x4b:
				if (cx > 0)
					cx--;
				break;
			case 0x4d:
				if (cx < 8)
					cx++;
				break;
			default:
				break;
			}
		}
		else
		{
			switch (input)
			{
			case 13:
				if (isValid)
				{
					*tx = cx;
					*ty = cy;
					return pos;
				}
				break;
			case 'a':
			case 'b':
			case 'c':
			case 'd':
			case 'e':
			case 'f':
			case 'g':
			case 'h':
			case 'i':
				cx = input - 'a';
				break;
			case 'A':
			case 'B':
			case 'C':
			case 'D':
			case 'E':
			case 'F':
			case 'G':
			case 'H':
			case 'I':
				cx = input - 'A';
				break;
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				cy = input - '1';
				break;
			default:
				break;
			}
		}
	} while (true);
}

COORD ChoosePosOri(int player, int index, int *tx, int *ty, int *ori, int length)
{
	GetConsoleScreenBufferInfo(handle, &info);
	short x = info.dwCursorPosition.X;
	short y = info.dwCursorPosition.Y;
	COORD pos = { x,y };
	int input;
	int cx = 0, cy = 0;
	bool unable;

	GetDefaultPos(player, index, &cx, &cy);
	do
	{	
		bool haveSetPos, overlap;
		do {
			haveSetPos = false;
			overlap = false;
			unable = !CheckOri(player, index, cx, cy, length);
			if (board[player][index][cy][cx] != 0)
			{
				overlap = true;
			}
			SetConsoleCursorPosition(handle, pos);
			//printf("\n");
			//printf("   A   B   C   D   E   F   G   H   I\n");
			//int i, j;
			//for (i = 0; i < 9; i++)
			//{
			//	printf("%d ", i + 1);
			//	for (j = 0; j < 9; j++)
			//	{
			//		if (j == cx && i == cy)
			//		{
			//			SetConsoleTextAttribute(handle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			//		}
			//		else
			//		{
			//			if (j == cx || i == cy)
			//			{
			//				SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
			//			}
			//		}
			//		Display(player, index, i, j);
			//		Display(player, index, i, j);
			//		Display(player, index, i, j);
			//		SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			//		printf(" ");
			//	}
			//	printf("\n  ");
			//	for (j = 0; j < 9; j++)
			//	{
			//		if (j == cx && i == cy)
			//		{
			//			SetConsoleTextAttribute(handle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			//		}
			//		else
			//		{
			//			if (j == cx || i == cy)
			//			{
			//				SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
			//			}
			//		}
			//		Display(player, index, i, j);
			//		Display(player, index, i, j);
			//		Display(player, index, i, j);
			//		SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			//		printf(" ");
			//	}
			//	printf("\n");
			//}
			CPDisplayBoard(player, index, cx, cy);
			if (unable && !overlap)
			{
				ClearLine(NULL);
				Warning("Unable to place ship in any orientation");
			}
			else
				ClearLine('\n');
			if (overlap)
				Warning("Current input position overlaps with previous ships");
			else
				ClearLine(NULL);

			input = getch();
			if (input == 0xe0)
			{
				int a = getch(); 
				switch (a)
				{
				case 0x48:
					if (cy > 0)
						cy--;
					break;
				case 0x50:
					if (cy < 8)
						cy++;
					break;
				case 0x4b:
					if (cx > 0)
						cx--;
					break;
				case 0x4d:
					if (cx < 8)
						cx++;
					break;
				default:
					break;
				}
			}
			else
			{
				switch (input)
				{
				case 13:
					if (!overlap && !unable)
						haveSetPos = true;
					break;
				case 'a':
				case 'b':
				case 'c':
				case 'd':
				case 'e':
				case 'f':
				case 'g':
				case 'h':
				case 'i':				
					cx = input - 'a';
					break;
				case 'A':
				case 'B':
				case 'C':
				case 'D':
				case 'E':
				case 'F':
				case 'G':
				case 'H':
				case 'I':
					cx = input - 'A';
					break;
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					cy = input - '1';
					break;
				default:
					break;
				}
			}
		} while (!haveSetPos);

		int orien;
		bool isValid, reset, outOfRange = false;
		int ax, bx, ay, by;
		/*if (cx - length + 1 > 0)
		{
			ax = cx - length + 1;
			bx = cx;
			ay = cy;
			by = cy;
			orien = 4;
		}
		else
		{
			if (cx + length - 1 < 8)
			{
				bx = cx + length - 1;
				ax = cx;
				ay = cy;
				by = cy;
				orien = 2;
			}
			else
			{
				if (cy - length + 1 > 0)
				{
					ay = cy - length + 1;
					by = cy;
					ax = cx;
					bx = cx;
					orien = 1;
				}
				else
				{
					by = cy + length - 1;
					ay = cy;
					ax = cx;
					bx = cx;
					orien = 3;
				}
			}
		}*/
		orien = GetDefaultOri(player, index, cx, cy, length);
		switch (orien)
		{
		case 1:
			ay = cy - length + 1;
			by = cy;
			ax = cx;
			bx = cx;
			break;
		case 2:
			bx = cx + length - 1;
			ax = cx;
			ay = cy;
			by = cy;
			break;
		case 3:
			by = cy + length - 1;
			ay = cy;
			ax = cx;
			bx = cx;
			break;
		case 4:
			ax = cx - length + 1;
			bx = cx;
			ay = cy;
			by = cy;
			break;
		default:
			Warning("Unable to place ship in any orientation");
			unable++;
			continue;
		}

		do {
			reset = false;
			overlap = false;
			outOfRange = false;
			isValid = true;
			switch (orien)
			{
			case 1:
				for (i = 0; i < length; i++)
				{
					if (board[player][1][cy - i][cx] != 0)
					{
						isValid = false;
						overlap = true;
						break;
					}
				}
				break;
			case 2:
				for (i = 0; i < length; i++)
				{
					if (board[player][1][cy][cx + i] != 0)
					{
						isValid = false;
						overlap = true;
						break;
					}
				}
				break;
			case 3:
				for (i = 0; i < length; i++)
				{
					if (board[player][1][cy + i][cx] != 0)
					{
						isValid = false;
						overlap = true;
						break;
					}
				}
				break;
			case 4:
				for (i = 0; i < length; i++)
				{
					if (board[player][1][cy][cx - i] != 0)
					{
						isValid = false;
						overlap = true;
						break;
					}
				}
				break;
			default:
				break;
			}
			if (ax < 0 || bx>8 || ay < 0 || by>8)
			{
				isValid = false;
				outOfRange = true;
			}

			SetConsoleCursorPosition(handle, pos);
			CODisplayBoard(player, index, ax, bx, ay, by);
			if (outOfRange&&overlap)
			{
				ClearLine(NULL);
				Warning("Position out of range!");
				ClearLine(NULL);
				Warning("Current input position overlaps with previous ships");
			}
			else
			{
				if (outOfRange || overlap)
				{
					if (outOfRange)
					{
						ClearLine(NULL);
						Warning("Position out of range!");
						ClearLine(NULL);
					}		
					else
					{
						ClearLine(NULL);
						Warning("Current input position overlaps with previous ships");
						ClearLine(NULL);
					}
						
				}
				else
				{
					ClearLine('\n');
					ClearLine(NULL);
				}
			}


			input = getch();
			if (input == 0xe0)
			{
				int a = getch();
				switch (a)
				{
				case 0x48:
					ay = cy - length + 1;
					by = cy;
					ax = cx;
					bx = cx;
					orien = 1;
					break;
				case 0x50:
					by = cy + length - 1;
					ay = cy;
					ax = cx;
					bx = cx;
					orien = 3;
					break;
				case 0x4b:
					ax = cx - length + 1;
					bx = cx;
					ay = cy;
					by = cy;
					orien = 4;
					break;
				case 0x4d:
					bx = cx + length - 1;
					ax = cx;
					ay = cy;
					by = cy;
					orien = 2;
					break;
				default:
					break;
				}
			}
			else
			{
				switch (input)
				{
				case 8:
					reset = true;
					break;
				case 13:
					if (isValid)
					{
						switch (orien)
						{
						case 1:
							*tx = ax;
							*ty = ay;
							*ori = 1;
							return pos;
						case 3:
							*tx = bx;
							*ty = ay;
							*ori = 1;
							return pos;
						case 2:
							*tx = ax;
							*ty = ay;
							*ori = 0;
							return pos;
						case 4:
							*tx = ax;
							*ty = by;
							*ori = 0;
							return pos;
						default:
							break;
						}
					}
				default:
					break;
				}
			}
		} while (!reset);
	} while (true);
}

int StartMenu()
{
	//system("mode con: cols=30");
	//SetSize(10);

	int pointer = 1;
	int input;
	char texts[4][10] = {
		"PVP",
		"PVC",
		"CVC",
		"IO Test"
	};
	do {
		system("cls");
		printf("BATTLESHIP!\n\n");
		printf("Total battles : %d\n", datai[0]);
		printf("Game mode : \n");

		char prefix[4][15] = {
			"    ",
			"    ",
			"    ",
			"    "
		};
		strcpy(prefix[pointer - 1], "=>  ");
		for (int i = 0; i < 4; i++)
		{
			strcat(prefix[i], texts[i]);
			printf("%s\n", prefix[i]);
		}

		input = getch();
		if (input == 0xe0)
		{
			int a = getch();
			switch (a)
			{
			case 0x48:
				if (pointer == 1)
					pointer = 4;
				else
					pointer--;
				break;
			case 0x50:
				if (pointer == 4)
					pointer = 1;
				else
					pointer++;
				break;
			default:
				break;
			}
		}
		else
		{
			if (input == 13)
			{
				//SetSize(NULL);
				//system("mode con: cols=84");		
				return pointer;
			}
		}
	} while (true);
}

int Menu(char list[][15], int length, char text[])
{
	int pointer = 1;
	int input;
	do {
		system("cls");
		printf("%s\n\n", text);

		//char prefix[4][15] = {
		//	"    ",
		//	"    ",
		//	"    ",
		//	"    "
		//};
		char prefix[10][20];
		for (i = 0; i < 10; i++)
		{
			strcpy(prefix[i], "    ");
		}
		strcpy(prefix[pointer - 1], "=>  ");
		for (int i = 0; i < length; i++)
		{
			strcat(prefix[i], list[i]);
			printf("%s\n", prefix[i]);
		}

		input = getch();
		if (input == 0xe0)
		{
			int a = getch();
			switch (a)
			{
			case 0x48:
				if (pointer == 1)
					pointer = length;
				else
					pointer--;
				break;
			case 0x50:
				if (pointer == length)
					pointer = 1;
				else
					pointer++;
				break;
			default:
				break;
			}
		}
		else
		{
			if (input == 13)	
				return pointer;
			if (input == 8)
				return -1;
		}
	} while (true);
}