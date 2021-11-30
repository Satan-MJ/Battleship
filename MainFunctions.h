#pragma once
#include <stdio.h>
#include <Windows.h>
#include <stdbool.h>
#include"Variables.h"
#include"UI.h"

bool CheckShipsSurvive(int player)
{
	if (sunkCount[player] == 4)
	{
		return false;
	}
	else
	{
		return true;
	}
	
	//int i, j;
	//for (i = 0; i < 9; i++)
	//{
	//	for (j = 0; j < 9; j++)
	//	{
	//		if (board[player][0][i][j] == 0 && board[player][1][i][j] != 0)
	//		{
	//			return true;
	//		}
	//	}
	//}
	//return false;
}

//int CheckShipSurvive(int player, int sunk[])
//{
//	int i, j;
//	int count[4][2] =
//	{
//		{ 2,0 },
//		{ 3,0 },
//		{ 4,0 },
//		{ 5,0 },
//	};
//	for (i = 0; i < 9; i++)
//	{
//		for (j = 0; j < 9; j++)
//		{
//			if (board[player][0][i][j] > 2)
//			{
//				count[board[player][0][i][j] - 3][1]++;
//			}
//		}
//	}
//	for (i = 3; i <= 6; i++)
//	{
//		if (count[i][1] == 0 && sunk[i - 3] == 0)
//		{
//			return count[i][0];
//		}
//	}
//	return 0;
//}

int CheckShipSurvive(int player, int status, bool useAI)
{

	sunk[player][status - 3][1]++;
	if (sunk[player][status - 3][0] == sunk[player][status - 3][1])
	{
		sunk[player][status - 3][2] = 1;
		sunkCount[player]++;
		
		switch (sunk[player][status-3][0])
		{
		case 2:
			if (!useAI)
				SinkMsg("The Destroyer(length: 2) has sunk!");
			return 2;
			break;
		case 3:
			if (!useAI)
				SinkMsg("The Cruiser(length: 3) has sunk!");
			return 3;
			break;
		case 4:
			if (!useAI)
				SinkMsg("The Battleship(length: 4) has sunk!");
			return 4;
			break;
		case 5:
			if (!useAI)
				SinkMsg("The Carrier(length: 5) has sunk!");
			return 5;
			break;
		default:
			break;
		}
	}
	return 1;
}

bool CheckPosition(int *posA, int *posB)
{
	char pos[1024];
	bool isValid = true;

	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
	fgets(pos, 1024, stdin);
	SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

	if (strlen(pos) != 3)
	{
		//printf("%d", strlen(pos));
		Warning("Please enter 2 Characters");
		isValid = false;
	}
	else
	{
		switch (pos[0])
		{
		case 65:
		case 97:
			*posA = 1;
			break;
		case 66:
		case 98:
			*posA = 2;
			break;
		case 67:
		case 99:
			*posA = 3;
			break;
		case 68:
		case 100:
			*posA = 4;
			break;
		case 69:
		case 101:
			*posA = 5;
			break;
		case 70:
		case 102:
			*posA = 6;
			break;
		case 71:
		case 103:
			*posA = 7;
			break;
		case 72:
		case 104:
			*posA = 8;
			break;
		case 73:
		case 105:
			*posA = 9;
			break;
		default:
			//printf("%d", pos[0]);
			Warning("Please enter 1 letter for the x-axis of the position(A - I)");
			isValid = false;
			break;
		}

		if (pos[1] >= 49 && pos[1] <= 57)
		{
			*posB = pos[1] - '0';
		}
		else
		{
			//printf("%d", pos[1]);
			Warning("Please enter 1 number for the y-axis of the position(1 - 9)");
			isValid = false;
		}
	}

	if (isValid)
		return true;
	else
		return false;
}

void RegisterShip(int player, int ori, int length, int posA, int posB)
{
	switch (ori)
	{
	case 0:
		for (i = 0; i < length; i++)
		{
			board[player][1][posB][posA + i] = 1 + length;
			board[player][2][posB][posA + i] = 1 + length;
		}
		break;
	case 1:
		for (i = 0; i < length; i++)
		{
			board[player][1][posB + i][posA] = 1 + length;
			board[player][2][posB + i][posA] = 1 + length;
		}
		break;
	default:
		break;
	}
}

int RegisterAttack(int player, int posA, int posB, int turnCount, bool useAI)
{
	int sunkShip = 0;
	
	if (board[1 - player][0][posB][posA] != 0)
		return -1;

	book[1 - player][posB][posA] = turnCount;
	switch (board[1 - player][1][posB][posA])
	{
	case 0:
		board[1 - player][0][posB][posA] = -1;
		board[1 - player][1][posB][posA] = -1;
		break;
	case 3:
	case 4:
	case 5:
	case 6:
		sunkShip = CheckShipSurvive(1 - player, board[1 - player][1][posB][posA], useAI);
		board[1 - player][0][posB][posA] = 2;
		board[1 - player][1][posB][posA] = 2;
		if (useAI)
			hit[player]++;
		break;
	default:
		break;
	}
	//printf("hit[%d] = %d\t(%d,%d)\tflag = %d\n", player, hit[player], posA+1, posB+1, sunkShip);
	//getch();
	return sunkShip;
}

void SetShip(const char name[12], int length, int player, char headerText[])
{
	bool isValid = true;
	system("cls");
	SplitLine(headerText);
	printf("Set Your battleShips!");
	printf("\nYou are setting the position of the %s(length : %d).\n", name, length);

	int posA = 0;
	int posB = 0;
	//char ori[1024];
	int ori = 0;
	COORD pos = ChoosePosOri(player, 1, &posA, &posB, &ori, length);
	//do {
	//	isValid = true;
	//	do {
	//		printf("\nEnter the position(Left-most and upper-most point -eg. G2) : ");
	//		isValid = CheckPosition(&posA, &posB);
	//	} while (!isValid);
	//	ChoosePosition(player, 1, &posA, &posB);
	//	
	//	//Input(Orientaion)
	//	do {
	//		isValid = true;
	//		printf("\nEnter the orientation(0:horizontal, 1:vertical) : ");
	//		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
	//		fgets(ori, 1024, stdin);
	//		SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	//		//Validation check(Orientation)
	//		if (strlen(ori) != 2)
	//		{
	//			Warning("Please enter 1 number only");
	//		}
	//		if (ori[0] != '0'&&ori[0] != '1')
	//		{
	//			isValid = false;
	//			Warning("Please enter either 0 or 1 for orientation");
	//		}
	//	} while (!isValid);
	//	int i;
	//	switch (ori[0])
	//	{
	//	case 48:
	//		if (posA + length > 9)
	//		{
	//			isValid = false;
	//			Warning("Position out of range");
	//		}
	//		for (i = 0; i < length; i++)
	//		{
	//			if (board[player][1][posB][posA + i] != 0)
	//			{
	//				isValid = false;
	//				Warning("Current input position overlaps with previous ships");
	//				break;
	//			}
	//		}
	//		if (!isValid)
	//			break;
	//		for (i = 0; i < length; i++)
	//		{
	//			board[player][1][posB][posA + i] = 1 + length;
	//		}
	//		break;
	//	case 49:
	//		if (posB + length > 9)
	//		{
	//			isValid = false;
	//			Warning("Position out of range");
	//		}
	//		for (i = 0; i < length; i++)
	//		{
	//			if (board[player][1][posB + i][posA] != 0)
	//			{
	//				isValid = false;
	//				Warning("Current input position overlaps with previous ships");
	//				break;
	//			}
	//		}
	//		if (!isValid)
	//			break;
	//		for (i = 0; i < length; i++)
	//		{
	//			board[player][1][posB + i][posA] = 1 + length;
	//		}
	//		break;
	//	default:
	//		break;
	//	}
	//} while (!isValid);

	//printf("posA: %d, posB: %d, ori: %d", posA, posB, ori);

	RegisterShip(player, ori, length, posA, posB);
	SetConsoleCursorPosition(handle, pos);
	StdDisplayBoard(player, 1);
}

void SetShips(int player, bool useAI)
{
	char header[10];
	if (useAI)
		strcpy(header, "Player");
	else
		sprintf(header, "Player %d", player+1);

	SetShip("Carrier", 5, player, header);
	SetShip("Battleship", 4, player, header);
	SetShip("Cruiser", 3, player, header);
	SetShip("Destroyer", 2, player, header);

	system("cls");
	SplitLine(header);
	printf("\nYour Battlefield : \n");
	StdDisplayBoard(player, 1);
	system("pause>nul");
}

int Attack(int turnCount, int player, bool useAI, int sunkShipIndex)
{
	printf("Turn %d\n", turnCount);
	char format[20];
	if (useAI)
		SplitLine("Player");
	else
	{
		sprintf(format, "Player %d", player + 1);
		SplitLine(format);
		system("pause>nul");
	}

	DisplayShipSurvive(sunkShipIndex);
	printf("\n");

	printf("Your Battlefield : ");
	SmlDisplayBoard(player, 1);

	bool isValid = true;
	int posA, posB;
	//do {
	//	do {
	//		printf("\nEnter the coordinates you want to attack : ");
	//		isValid = CheckPosition(&posA, &posB);
	//	} while (!isValid);
	//	if (board[1 - player][0][posB - 1][posA - 1] != 0)
	//	{
	//		Warning("You already attacked that position");
	//		isValid = false;
	//	}
	//} while (!isValid);
	COORD pos = ChoosePosition(1 - player, 0, &posA, &posB);

	int sunkShip = RegisterAttack(player, posA, posB, turnCount, false);

	SetConsoleCursorPosition(handle, pos);
	StdDisplayBoard(1 - player, 0);
	ClearLine("\n");
	printf("\n\n");
	DisplayBoards(player);
	printf("\npress any key to continue...");
	system("pause>nul");

	system("cls");
	return sunkShip;
}