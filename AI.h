#pragma once
#include<stdio.h>
#include<time.h>
#include<stdbool.h>
#include<stdlib.h>
#include"Variables.h"
#include"UI.h"

struct Coor
{
	int X;
	int Y;
};
struct Coor firstHit[2];
struct Coor lastAtt[2] = { { 0,0 }, {0,0} };
struct Coor oriIndic[2] = { { 0,0 },{ 0,0 } };
int ttlHit[2] = { 0,0 };
int hitCount[2] = { 0,0 };
struct Coor hitQueue[2][14];
int head[2] = { 0,0 }, tail[2] = { 0,0 };
int ori[2];

void AIVarIni()
{
	for (i = 0; i < 2; i++)
	{
		firstHit[i].X = 0;
		firstHit[i].Y = 0;
		lastAtt[i].X = 0;
		lastAtt[i].Y = 0;
		oriIndic[i].X = 0;
		oriIndic[i].Y = 0;
		ttlHit[i] = 0;
		hitCount[i] = 0;
		head[i] = 0;
		tail[i] = 0;
		ori[i] = NULL;
		hit[i] = 0;
		for (j = 0; j < 14; j++)
		{
			hitQueue[i][j].X = 0;
			hitQueue[i][j].Y = 0;
		}
		for (j = 0; j < 4; j++)
		{
			attackOri[i][j] = 1;
		}
	}
}

bool CheckAIPos(int posX, int posY)
{
	posX++;
	posY++;
	if (posX == 3 && posY == 3)
		return false;
	if (posX == 3 && posY == 7)
		return false;
	if (posX == 7 && posY == 3)
		return false;
	if (posX == 7 && posY == 7)
		return false;
	if (posX == 5 && posY == 5)
		return false;
	return true;
}

void AISetShip(int player, int length)
{
	int posA, posB, ori;
	bool isValid;

	do
	{
		isValid = true;
		posA = rand() % 9;
		posB = rand() % 9;
		ori = rand() % 2;

		switch (ori)
		{
		case 0:
			if (posA + length > 9)
			{
				isValid = false;
			}
			for (i = 0; i < length; i++)
			{
				if (board[player][1][posB][posA + i] > 2 || !CheckAIPos(posA + i, posB))
				{
					isValid = false;
					break;
				}
			}
			break;
		case 1:
			if (posB + length > 9)
			{
				isValid = false;
			}
			for (i = 0; i < length; i++)
			{
				if (board[player][1][posB + i][posA] > 2 || !CheckAIPos(posA, posB + i))
				{
					isValid = false;
					break;
				}
			}
			break;
		default:
			break;
		}
	} while (!isValid);
	RegisterShip(player, ori, length, posA, posB);
}

void AISetShips(int player)
{
	AISetShip(player, 5);
	AISetShip(player, 4);
	AISetShip(player, 3);
	AISetShip(player, 2);
	//StdDisplayBoard(0, 1);
	//getchar();
}

void ResetBoard()
{
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			board[1][1][i][j] = 0;
		}
	}
}

int AIAttack(int player, int turnCount)
{
	int posA, posB;
	int flag;
	//printf("\nhitCount[0]=%d     hitCount[1]=%d\n", hitCount[0], hitCount[1]);
	do {
		if (hit[player] == 0 && (firstHit[player].X == 0 && firstHit[player].Y == 0))
		{		
			do
			{
				posA = rand() % 9;
				if (posA % 2 == 0)
					posB = (rand() % 5) * 2;
				else
					posB = (rand() % 4) * 2 + 1;

				flag = RegisterAttack(player, posA, posB, turnCount, true);
				//printf("\n%d attack (%d,%d), return = %d\n", player + 1, posA + 1, posB + 1, flag);
				//getch();

				if (flag == 1)
				{
					firstHit[player].X = posA;
					firstHit[player].Y = posB;
					hitCount[player]++;
					//printf("#Ran hitCount[%d] = %d\n", player, hitCount[player]);
					//getch();
					lastAtt[player].X = posA;
					lastAtt[player].Y = posB;
				}
			} while (flag == -1);
		}
		else
		{		
			if (attackOri[player][0] == -1 && attackOri[player][1] == -1 && attackOri[player][2] == -1 && attackOri[player][3] == -1 && head[player] <= tail[player])
			{
				firstHit[player].X = hitQueue[player][head[player]].X;
				firstHit[player].Y = hitQueue[player][head[player]].Y;
				head[player]++;
				hit[player] = 1;
				oriIndic[player].X = 0;
				oriIndic[player].Y = 0;
				for (i = 0; i < 4; i++)
					attackOri[player][i] = 1;
			}

			if (firstHit[player].Y - 1 < 0)
				attackOri[player][0] = -1;
			if (firstHit[player].X + 1 > 8)
				attackOri[player][1] = -1;
			if (firstHit[player].Y + 1 > 8)
				attackOri[player][2] = -1;
			if (firstHit[player].X - 1 < 0)
				attackOri[player][3] = -1;

			if (hit[player] == 1 && (oriIndic[player].X == 0 && oriIndic[player].Y == 0))
			{
				do
				{
					ori[player] = rand() % 4;
				} while (attackOri[ori[player]] == -1);
				switch (ori[player])
				{
				case 0:
					oriIndic[player].Y = -1;
					break;
				case 1:
					oriIndic[player].X = 1;
					break;
				case 2:
					oriIndic[player].Y = 1;
					break;
				case 3:
					oriIndic[player].X = -1;
					break;
				default:
					break;
				}
			}

			posA = firstHit[player].X + oriIndic[player].X*hit[player];
			posB = firstHit[player].Y + oriIndic[player].Y*hit[player];
			if (posA > 8 || posA < 0 || posB > 8 || posB < 0)
			{
				hit[player] = 1;
				oriIndic[player].X *= -1;
				oriIndic[player].Y *= -1;
				posA = firstHit[player].X + oriIndic[player].X*hit[player];
				posB = firstHit[player].Y + oriIndic[player].Y*hit[player];
			}

			flag = RegisterAttack(player, posA, posB, turnCount, true);		
			//printf("\n%d attack (%d,%d), return = %d\n", player + 1, posA + 1, posB + 1, flag);

			if (flag <= 0)
			{
				attackOri[player][ori[player]] = -1;
				oriIndic[player].X = 0;
				oriIndic[player].Y = 0;
				hit[player] = 1;
			}
			else
			{
				hitCount[player]++;
				//printf("#NR  hitCount[%d] = %d\n", player, hitCount[player]);
				//getch();
				lastAtt[player].X = posA;
				lastAtt[player].Y = posB;
				hitQueue[player][tail[player]] = lastAtt[player];
				tail[player]++;
			}

			//printf("hitcount = %d\thit = %d\t\n", hitCount[player], hit[player]);
			//getch();

			if (flag > 1)
			{
				ttlHit[player] += flag;
				//printf("ttlHit[%d] = %d\n", player, ttlHit[player]);
				//getch();
				if (hitCount[player] == ttlHit[player])
				{
					oriIndic[player].X = 0;
					oriIndic[player].Y = 0;
					hit[player] = 0;
					ttlHit[player] = 0;
					hitCount[player] = 0;
					for (i = 0; i < 4; i++)
						attackOri[player][i] = 1;
					for (i = 0; i <= tail[player]; i++)
					{
						hitQueue[player][i].X = 0;
						hitQueue[player][i].Y = 0;
					}
					head[player] = 0;
					tail[player] = 0;
					firstHit[player].X = 0;
					firstHit[player].Y = 0;
				}
				else
				{
					attackOri[player][ori[player]] = -1;
					oriIndic[player].X = 0;
					oriIndic[player].Y = 0;
					hit[player] = 1;
				}
			}
		}
	} while (flag == -1);

	return flag;
}