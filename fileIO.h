#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

char data[3][16];

void DecToBin(int index, int ini)
{
	for (j = 0; j < 15; j++)
	{
		data[index][j] = '0';
	}
	data[index][15] = '\0';

	int i = 0;
	int r;
	do
	{
		r = ini % 2;  
		//printf("%d\t", r);
		ini = ini / 2;
		//printf("%d\t", ini);
		data[index][i] = '0' + r;
		//printf("%c\t", data[index][15-i]);
		i++;
		//printf("%d\n", i);
	} while (ini != 0);
}

int BinToDec(char no[])
{
	int t = 0;
	for (int j = 0; j < 15; j++)
	{
		t = (pow(2,j))*(no[j] - '0') + t;
	}
	return t;
}

void SetLength(char *content[], int num)
{
	if (num < 10)
		sprintf(content, "0%d", num);
	else
		itoa(num, content, 10);
}

void Openbsdt()
{
	FILE *fp = fopen("BattleShipSaves.bsdt", "wb");
	fclose(fp);
}

void Writebsdt()
{
	FILE *fp = fopen("BattleShipSaves.bsdt", "wb");

	for (i = 0; i < 3; i++)
	{
		DecToBin(i, datai[i]);
		fputs(data[i], fp);
	}

	fclose(fp);
}

int Readbsdt()
{
	FILE *fp = fopen("BattleShipSaves.bsdt", "rb");
	if (fp == NULL)
		return -1;
	for (int i = 0; i < 3; i++)
	{
		fgets(data[i], 16, fp);
		datai[i] = BinToDec(data[i]);
	}
	fclose(fp);
	return 0;
}

void ReadData()
{
	if (Readbsdt() == -1)
		Writebsdt();
}

void UpdateData(int item)
{
	datai[item]++;
	Writebsdt();
}

void WriteLog(char mode[5], int turn)
{
	time_t timep;
	struct tm *cTime;
	time(&timep);
	cTime = gmtime(&timep);

	char txtName[27];
	char cmon[3], cday[3], chour[3], cmin[3], csec[3];
	SetLength(cmon, 1 + cTime->tm_mon);
	SetLength(cday, cTime->tm_mday);
	SetLength(chour, 8 + cTime->tm_hour);
	SetLength(cmin, cTime->tm_min);
	SetLength(csec, cTime->tm_sec);
	sprintf(txtName, "%d%s%s_%s%s%s_%s.txt", 1900 + cTime->tm_year, cmon, cday, chour, cmin, csec, mode);
	if (_access("BattleShip_Data", 0) == -1)
	{
		_mkdir("BattleShip_Data");
	}
	char location[43] = "BattleShip_Data/";
	strcat(location, txtName);
	FILE *fp = fopen(location, "w");
	if (fp == NULL)
	{
		fclose(fp);
		return;
	}
	
	fprintf(fp, "Total Round : %d\n", turn);
	for (k = 0; k <= 1; k++)
	{
		fprintf(fp, "Player %d -----------------------------------------------------------------\n", k + 1);
		fprintf(fp, "Player %d attack : \t\t\tPlayer %d ships : \n", k + 1, 2 - k);
		
		fputs("  |A |B |C |D |E |F |G |H |I \t\t  |A |B |C |D |E |F |G |H |I \n", fp);
		for (i = 0; i < 9; i++)
		{
			fputs("--+--+--+--+--+--+--+--+--+--\t\t--+--+--+--+--+--+--+--+--+--\n", fp);
			fprintf(fp, "%d ", i + 1);
			for (j = 0; j < 9; j++)
			{
				fputc('|', fp);
				int v = book[1 - k][i][j];
				if (v != 0)
				{
					char temp[3];
					itoa(v, temp, 10);
					if (strlen(temp) == 1)
					{
						char t[3] = "0";
						strcat(t, temp);
						fputs(t, fp);
					}
					else
						fputs(temp, fp);
				}
				else
					fputs("  ", fp);
			}
			fputs("\t\t", fp);

			fprintf(fp, "%d ", i + 1);
			for (j = 0; j < 9; j++)
			{
				fputc('|', fp);
				int v = board[1 - k][2][i][j];
				switch (v)
				{
				case 3:
					fputs("Dt", fp);
					break;
				case 4:
					fputs("Cs", fp);
					break;
				case 5:
					fputs("Bs", fp);
					break;
				case 6:
					fputs("Cr", fp);
					break;
				default:
					fputs("  ", fp);
					break;
				}
			}
			fputc('\n', fp);
		}
		fputs("\n\n\n", fp);
	}

	fclose(fp);
}