#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<Windows.h>
#include<stdbool.h>
#include<time.h>
#include"MainFunctions.h"
#include"Variables.h";
#include"AI.h"
#include"fileIO.h"

board[2][3][9][9] =									// [0] for public [1] for private
{
	{	{	{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }  },

		{	{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }	},

		{	{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }	}	},

	{	{	{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }	},

		{	{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }	},

		{	{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }  ,
			{ 0,0,0,0,0,0,0,0,0 }	}	}
};

sunk[2][4][3] =
{
	{	{ 2,0,0 },
		{ 3,0,0 },
		{ 4,0,0 },
		{ 5,0,0 },	},
	{	{ 2,0,0 },
		{ 3,0,0 },
		{ 4,0,0 },
		{ 5,0,0 }, }
};
sunkCount[2] = {0,0};

char texts[3][15] = {
	"Easy",
	"Difficult",
	"Unbeatable"
};
//int board[2][2][9][9] =									// [0] for public [1] for private
//{
//	{ { { 0,0,0,0,0,0,0,0,0 }  ,
//{ 0,0,0,0,0,0,0,0,0 }  ,
//{ 0,0,0,0,0,0,0,0,0 }  ,
//{ 0,0,0,0,0,0,0,0,0 }  ,
//{ 0,0,0,0,0,0,0,0,0 }  ,
//{ 0,0,0,0,0,0,0,0,0 }  ,
//{ 0,0,0,0,0,0,0,0,0 }  ,
//{ 0,0,0,0,0,0,0,0,0 }  ,
//{ 0,0,0,0,0,0,0,0,0 } },
//
//{ { 1,0,0,0,0,0,0,0,0 }  ,
//{ 0,0,0,0,0,0,0,0,0 }  ,
//{ 0,0,0,0,0,0,0,0,0 }  ,
//{ 0,0,0,0,0,0,0,0,0 }  ,
//{ 0,0,0,0,0,0,0,0,0 }  ,
//{ 0,0,0,0,0,0,0,0,0 }  ,
//{ 0,0,0,0,0,0,0,0,0 }  ,
//{ 0,0,0,0,0,0,0,0,0 }  ,
//{ 0,0,0,0,0,0,0,0,0 } } },
//
//{ { { 0,0,0,0,0,0,0,0,0 }  ,
//{ 0,0,0,0,0,0,0,0,0 }  ,
//{ 0,0,0,0,0,0,0,0,0 }  ,
//{ 0,0,0,0,0,0,0,0,0 }  ,
//{ 0,0,0,0,0,0,0,0,0 }  ,
//{ 0,0,0,0,0,0,0,0,0 }  ,
//{ 0,0,0,0,0,0,0,0,0 }  ,
//{ 0,0,0,0,0,0,0,0,0 }  ,
//{ 0,0,0,0,0,0,0,0,0 } },
//
//{ { 0,0,0,1,1,1,0,0,0 }  ,
//{ 0,0,0,0,0,0,0,0,0 }  ,
//{ 0,0,1,0,1,0,0,0,0 }  ,
//{ 0,0,1,0,1,0,0,0,0 }  ,
//{ 0,0,1,0,1,0,0,0,0 }  ,
//{ 0,0,1,0,1,0,0,0,0 }  ,
//{ 0,0,0,0,1,0,0,0,0 }  ,
//{ 0,0,0,0,0,0,0,0,0 }  ,
//{ 0,0,0,0,0,0,1,1,0 } } }
//};

void Initialize()
{
	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 3; j++)
		{
			for (k = 0; k < 9; k++)
			{
				for (l = 0; l < 9; l++)
				{
					board[i][j][k][l] = 0;
				}
			}
		}
	}

	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 4; j++)
		{
			for (k = 1; k < 3; k++)
			{
				sunk[i][j][k] = 0;
			}
		}
	}

	sunkCount[0] = 0;
	sunkCount[1] = 0;

	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 9; j++)
		{
			for (k = 0; k < 9; k++)
			{
				book[i][j][k] = 0;
			}
		}
	}
}

void PVP()
{
	int winner = -1;

	//system("cls");
	//printf("So you have chosen the PVP mode.\n");
	//Sleep(700);
	//printf("The first thing you are doing here is setting the position of your ships.\n");
	//Sleep(700);
	//printf("It's a PVP game,\n");
	//Sleep(500);
	//printf("so make sure you are the only person who knows where your ships are.\n");
	//Sleep(500);
	//printf("I will give you more instructions after deploying your ships.\n\n");
	//Sleep(1000);
	//printf("Press any key to continue...");
	//system("pause>nul");

	system("cls");
	SplitLine("Player 1");
	SetShips(0, false);

	system("cls");
	SplitLine("Player 2");
	SetShips(1, false);

	system("cls");
	printf("So both of you are going to start right?\n");
	Sleep(500);
	printf("Here's something to remind you:\n");
	Sleep(500);
	printf("If you see the heading 'Player 1' or 'Player 2',\n");
	Sleep(700);
	printf("make sure only the corresponding player is looking at the screen.\n\n");
	Sleep(700);
	printf("Have fun!");
	system("pause>nul");
	system("cls");

	int countTurn, sunkShip = 0;
	for (countTurn = 1; true; countTurn++)
	{
		sunkShip = Attack(countTurn, 0, false, sunkShip);
		if (!CheckShipsSurvive(1))
		{
			winner = 0;
			break;
		}
		sunkShip = Attack(countTurn, 1, false, sunkShip);
		if (!CheckShipsSurvive(0))
		{
			winner = 1;
			break;
		}
	}

	UpdateData(0);
	WriteLog("PVP", countTurn);
	system("cls");
	printf("Player %d wins!\n", winner + 1);
	printf("Total turns used: %d\n", countTurn);
	printf("\nPlayer  1 : ");
	EndDisplayBoard(0, 1);
	printf("\nPlayer  2 : ");
	EndDisplayBoard(1, 1);
	
}

int PVC()
{
	int winner = -1;

	system("cls");
	//printf("So you have chosen the PVP mode.\n");
	//Sleep(700);
	//printf("The first thing you are doing here is setting the position of your ships.\n");
	//Sleep(700);
	//printf("It's a PVP game,\n");
	//Sleep(500);
	//printf("so make sure you are the only person who knows where your ships are.\n");
	//Sleep(500);
	//printf("I will give you more instructions after deploying your ships.\n\n");
	//Sleep(1000);
	//printf("Press any key to continue...");
	//system("pause>nul");
	switch (Menu(texts, 3, "Please choose difficulties: "))
	{
	case -1:
		return 0;
	default:
		break;
	}


	AISetShips(0);

	system("cls");
	SplitLine("Player");
	SetShips(1, true);

	system("cls");
	//printf("So both of you are going to start right?\n");
	//Sleep(500);
	//printf("Here's something to remind you:\n");
	//Sleep(500);
	//printf("If you see the heading 'Player 1' or 'Player 2',\n");
	//Sleep(700);
	//printf("make sure only the corresponding player is looking at the screen.\n\n");
	//Sleep(700);
	//printf("Have fun!");
	//system("pause>nul");
	//system("cls");

	int countTurn;
	int sunkShip = 0;
	for (countTurn = 1; true; countTurn++)
	{
		sunkShip = Attack(countTurn, 1, true, sunkShip);
		//AIAttack(1, countTurn);
		if (!CheckShipsSurvive(0))
		{
			winner = 1;
			break;
		}
		
		sunkShip = AIAttack(0, countTurn);
		if (!CheckShipsSurvive(1))
		{
			winner = 0;
			break;
		}
	}

	UpdateData(0);
	WriteLog("PVC", countTurn);
	system("cls");
	if (winner == 0)
		printf("Computer wins!\n");
	else
		printf("Player wins!\n");
	printf("Total turns used: %d\n", countTurn);
	printf("\nComputer : ");
	EndDisplayBoard(0, 1);
	printf("\nPlayer : ");
	EndDisplayBoard(1, 1);	
	AIVarIni();
	getch();
	return 0;
}

void CVC()
{
	int winner = -1;
	system("cls");
	for (k = 0; k < 2; k++)
	{
		AISetShips(k);
		StdDisplayBoard(k, 1);	
	}
	getch();
	system("cls");

	int countTurn;
	int sunkShip = 0;
	//printf("\n#Ini hitCount[0]=%d     hitCount[1]=%d\n\n", hitCount[0], hitCount[1]);
	for (countTurn = 1; true; countTurn++)
	{
		sunkShip = AIAttack(1, countTurn);
		if (!CheckShipsSurvive(0))
		{
			winner = 1;
			break;
		}

		sunkShip = AIAttack(0, countTurn);
		if (!CheckShipsSurvive(1))
		{
			winner = 0;
			break;
		}

		//StdDisplayBoard(1, 1);
		//StdDisplayBoard(0, 1);
		//getch();
	}

	UpdateData(0);
	WriteLog("CVC", countTurn);
	system("cls");
	if (winner == 0)
		printf("Computer wins!\n");
	else
		printf("Player wins!\n");
	printf("Total turns used: %d\n", countTurn);
	printf("\nComputer : ");
	EndDisplayBoard(0, 1);
	printf("\nPlayer : ");
	EndDisplayBoard(1, 1);
	AIVarIni();
	getch();
}

int main()
{
	/*initialization*/
	system("mode con: cols=84");
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	srand(time(NULL));

	SetConsoleTitleA("BattleShip");

	//int a = getch();
	//if (a == 0xe0)   //如果是方向键
	//{
	//	a = getch();  //再获取一次按键
	//	if (a == 0x48)
	//		printf("上\n");
	//	if (a == 0x50)
	//		printf("下\n");
	//	if (a == 0x4b)
	//		printf("左\n");
	//	if (a == 0x4d)
	//		printf("右\n");
	//}
	//else
	//	printf("%c\n", a);
	//system("pause");

	while (true)
	{
		ReadData();

		switch (StartMenu())
		{
		case 1:
			PVP();
			break;
		case 2:
			PVC();
			break;
		case 3:
			CVC();
			break;
		case 4:
			switch (Menu(texts, 3, "Please choose difficulties: "))
			{
			case -1:
				continue;
			default:
				break;
			}		
			UpdateData(0);
			WriteLog("Test", 0);
			break;
		default:
			break;
		}
		Initialize();
	}
	return 0;
}