// ������ �� ��������������� ����������� ���������.
#pragma once
// ����������� ������������� �����, ������� ��������� �������� � �������� �����/������.
#include <iostream>
// ����������� ������������� ����� ��� ������ �� ��������.
#include <ctime>
// ���������� ������������ ����, � ������� ���������� ��������� ������� SetConsoleCP(������� �������) � SetConsoleOutputCP(������� �������).
#include <Windows.h>
// ���������� ������������ ���� ��� getch.
#include <conio.h>
// ����� ��� ����, ���� �� ���� ����������� ������������� ����������.
using namespace std;
// ���������� ����� � �������.
const int rowsCount = 20;
// ���������� �������� � �������.
const int columnsCount = 40;
// �����. ASCII - ������ 220.
const unsigned char symbolHero = 220;
// �����. ASCII - ������ 177.
const unsigned char symbolWall = 177;
// ����. ASCII - ������ 254.
const unsigned char symbolBox = 254;
// �����. ASCII - ������ 178.
const unsigned char symbolExitOn = 178;
// ����. ASCII - ������ 42.
const unsigned char symbolMine = 42;
// ��������. ASCII - ������ 36.
const unsigned char symbolCard = 15;
// �����. ASCII - ������ 176.
const unsigned char symbolExitOff = 176;
// ��������� ������ ��� ��������� 1 ������.
const unsigned char LevelData1[rowsCount][columnsCount + 1] = 
{
	// ����� - 1, ����� - 2, ����� - #, ���� - �.
	"########################################",
	"#                  ##x ## ##      x   1#",
	"#x################  #  #     ####   ####",
	"# #2 x      x   ##  #  #x   x ##########",
	"# # x ### x  #  ##  #x   ###     x     #",
	"# #x x  x  ## x ##  #  x ############  #",
	"# # x    ##  #  ## x##  ##  #########xx#",
	"# # #####    # x##xx  ####  #     x   x#",
	"# #   x   xx #x ##  ##  x  x#  ###### x#",
	"# # xx # # x   ###  x   ##  #  ###### x#",
	"# #  x #   x x  ##  ###### x   ###### x#",
	"# ####### ########  #  x  ###########  #",
	"#       #  ##  ###  #  #   x     ####  #",
	"#########  ##       #x ########    x   #",
	"#######    ##########     x########## ##",
	"#######  ################ x##       ####",
	"####      x     ######### x    ####   ##",
	"############ x######################x ##",
	"############          x               ##",
	"########################################"
};
// ��������� ������ ��� ��������� 2 ������.
const unsigned char LevelData2[rowsCount][columnsCount + 1] =
{
	// ����� - 1, ����� - 2, ����� - #, ���� - �, �������� - !, * - ����. 
	"########################################",
	"#! #   x  ##  2#                       #",
	"# x x  # !## ##  !#*!*#### #####*!*### #",
	"#*   *  *#   ##! *######## ########### #",
	"#   # x # xxx #* !##!##### ###### #### #",
	"#  #  x ##    #! *## !#### ##### ####  #",
	"# x# x #  x x #* !##* !!!  # # #####  ##",
	"#x #x * x   * #! *################   ###",
	"# #     x ##*!#* !###!*######       # ##",
	"######  ########  #!          #######  #",
	"#####*    !!!!!   #######   ##!!!!!!!  #",
	"########################  ########### ##",
	"######*                          #### ##",
	"##!      ######################  #### ##",
	"#####           !!!*!!!!! *#####!#### ##",
	"####  !*          #######  ########## ##",
	"######### ###############* ##########x##",
	"######### ########                x    #",
	"#######!            ############  !## 1#",
	"########################################"
};
// ���������� ������ �������.
HANDLE consoleHandle = 0;
// ����������, ������� ����� �������� �� ��, ����� �� ���������� ���� ����� ���������� �����.
bool isGameActive = true;
// ��������� ������.
unsigned char LevelData[rowsCount][columnsCount];
// ��� �������� �� ������������ ����������� �����. ���.
int heroRow = 0;
// ��� �������� �� ������������ ����������� �����. �������.
int heroColumn = 0;
// ������� ����.
int cardsNumber = 0;
// �������� ��� ������ 2. 
int cardsOnLevel;
// ������� ����.
void Menu()
{
	cout << "1. Exit" << endl << "2. Start." << endl;
}
// ������� ������ � ����.
short Options()
{
	SetConsoleOutputCP(1251);
	while (true)
	{
		short Enter;
		cin >> Enter;
		// cin.fail() - ����������, ������������� �� ������������ �������� ��������, ������������� � ����������.
		if (cin.fail() || Enter < 1 || 2 < Enter)
		{
			// �������������� �����, ���� ���-�� ����� �� ���.
			cin.clear();
			// cin.ignore - �������, ������� ��������� ������ � ���������� ���; 
			// cin.rdbuf - ����� ������, � ������� �� ������ �������; in_avail - ������� ���-�� �������� � ��� ����������
			cin.ignore(cin.rdbuf()->in_avail());
			cout << endl << "������! ���������." << endl;
		}
		else if ((Enter == 1) || (Enter == 2))
		{
			SetConsoleOutputCP(437);
			cin.ignore(cin.rdbuf()->in_avail());
			return Enter;
		}
	}
}
// ������� ����� ���������� ��������������� �����.
void SetupSystem()
{
	srand(time(0));
	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
}
// ������ ��������� �������� ��� ������ ���� 1.
void Initialise1()
{
	cardsOnLevel = 0;
	// ������� for, ������� ����� ��������� ��������� r �� ������� �������.
	for (int r = 0; r < rowsCount; r++)
	{
		// ���������� for, ������� ����� ��������� ��������� � �� �������� �������.
		for (int c = 0; c < columnsCount; c++)
		{
			// ��� ��������� �������� ������� �� r-������ � � �-�������.
			unsigned char symbol = LevelData1[r][c];

			switch (symbol)
			{
			case '#':
			{
				LevelData[r][c] = symbolWall;
				break;
			}
			case '1':
			{
				LevelData[r][c] = symbolHero;

				heroRow = r;
				heroColumn = c;
				break;
			}
			case '2':
			{
				LevelData[r][c] = symbolExitOn;
				break;
			}
			case 'x':
			{
				
				LevelData[r][c] = symbolBox;
				break;
			}
			default:
				LevelData[r][c] = symbol;
				break;
			}
		}
	}
}
// ������ ��������� �������� ��� ������ ���� 2.
void Initialise2()
{
	cardsOnLevel = 44;
	// ������� for, ������� ����� ��������� ��������� r �� ������� �������.
	for (int r = 0; r < rowsCount; r++)
	{
		// ���������� for, ������� ����� ��������� ��������� � �� �������� �������.
		for (int c = 0; c < columnsCount; c++)
		{
			// ��� ��������� �������� ������� �� r-������ � � �-�������.
			unsigned char symbol = LevelData2[r][c];

			switch (symbol)
			{
			case '#':
			{
				LevelData[r][c] = symbolWall;
				break;
			}
			case '1':
			{
				LevelData[r][c] = symbolHero;

				heroRow = r;
				heroColumn = c;
				break;
			}
			case '2':
			{
				LevelData[r][c] = symbolExitOff;
				break;
			}
			case 'x':
			{
				LevelData[r][c] = symbolBox;
				break;
			}
			case '*':
			{
				LevelData[r][c] = symbolMine;
				break;
			}
			case '!':
			{
				LevelData[r][c] = symbolCard;
				break;
			}
			default:
				LevelData[r][c] = symbol;
				break;
			}
		}
	}
}
// ���� ����������� ����� ��������� ����� ���� �� �����.
void Render()
{
	COORD cursorCoord;
	cursorCoord.X = 0;
	cursorCoord.Y = 0;
	SetConsoleCursorPosition(consoleHandle, cursorCoord);

	cout << "\n\n\t";
	for (int r = 0; r < rowsCount; r++)
	{
		for (int c = 0; c < columnsCount; c++)
		{
			unsigned char symbol = LevelData[r][c];

			switch (symbol)
			{
			case symbolWall:
			{
				SetConsoleTextAttribute(consoleHandle, 15);
				break;
			}
			case symbolBox:
			{
				SetConsoleTextAttribute(consoleHandle, 14);
				break;
			}
			case symbolHero:
			{
				SetConsoleTextAttribute(consoleHandle, 10);
				break;
			}
			case symbolExitOff:
			{
				SetConsoleTextAttribute(consoleHandle, 8);
				break;
			}
			case symbolExitOn:
			{
				SetConsoleTextAttribute(consoleHandle, 12);
				break;
			}
			case symbolMine:
			{
				SetConsoleTextAttribute(consoleHandle, 13);
				break;
			}
			case symbolCard:
			{
				SetConsoleTextAttribute(consoleHandle, 11);
				break;
			}
			}
			cout << symbol;
		}
		cout << "\n\t";
	}

	SetConsoleOutputCP(1251);
	SetConsoleTextAttribute(consoleHandle, 7);
	cout << "\n\t����������� WASD ��� ����������� ";
	SetConsoleTextAttribute(consoleHandle, 10);
	cout << "�����";
	SetConsoleTextAttribute(consoleHandle, 7);
	cout << ".������ ���������, �� ������ ������ ����� ";
	SetConsoleTextAttribute(consoleHandle, 13);
	cout << "����";
	SetConsoleTextAttribute(consoleHandle, 7);
	cout << ".\n\t��� ����, ����� ������ ������� 2 ��� ����� ������� ��� ";
	SetConsoleTextAttribute(consoleHandle, 11);
	cout << "��������.";
	SetConsoleTextAttribute(consoleHandle, 7);
	cout << "\n\t�� ������ ���� 44 ��� ���� ����� ������� ";
	SetConsoleTextAttribute(consoleHandle, 12);
	cout << "�����";
	SetConsoleTextAttribute(consoleHandle, 7);
	cout << ".\n\tR - ������.";
	cout << "\n\n\t�� ������� �������� = " << cardsNumber << " | ";
	SetConsoleOutputCP(437);


}
// ����������� �����.
void MoveHeroTo(int row, int column)
{
	unsigned char destinationCell = LevelData[row][column];
	bool canMoveToCell = false;

	switch (destinationCell)
	{
	case ' ':
	{
		canMoveToCell = true;
		break;
	}
	case symbolExitOn:
	{
		isGameActive = false;
		break;
	}
	case symbolMine:
	{
		Initialise2();
		cardsNumber = 0;
		break;
	}
	case symbolBox:
	{
		int heroDirectionR = row - heroRow;
		int heroDirectionC = column - heroColumn;
		// ���������, ���� �� ������ ����� �� ��������.
		if (LevelData[row + heroDirectionR][column + heroDirectionC] == ' ')
		{
			canMoveToCell = true;
			// ������ ������� �� ����� ����������.
			LevelData[row + heroDirectionR][column + heroDirectionC] = symbolBox;
		}
	}
	case symbolCard:
	{
		int heroDirectionR = row - heroRow;
		int heroDirectionC = column - heroColumn;
		// ��������, ���� �� ������ � ������� ����� ������ �� �����.
		if (LevelData[row][column] - LevelData[heroRow][heroColumn] <= LevelData[1][1])
		{
			canMoveToCell = true;
			LevelData[row][column] = ' ';
			cardsNumber++;
		}
		break;
	}
	}

	if (canMoveToCell)
	{
		// ������� ���������� ������ �����.
		LevelData[heroRow][heroColumn] = ' ';
		// ���������� ����� ����������.
		heroRow = row;
		heroColumn = column;

		LevelData[heroRow][heroColumn] = symbolHero;
	}
}
// ��������� ���� � ������������ �������� ������ ����.
void Update()
{
	unsigned char inputChar = _getch();
	inputChar = tolower(inputChar);

	switch (inputChar)
	{
	case 'w':
	{
		MoveHeroTo(heroRow - 1, heroColumn);
		break;
	}
	case 'a':
	{
		MoveHeroTo(heroRow, heroColumn - 1);
		break;
	}
	case 's':
	{
		MoveHeroTo(heroRow + 1, heroColumn);
		break;
	}
	case 'd':
	{
		MoveHeroTo(heroRow, heroColumn + 1);
		break;
	}
	case 'r':
	{
		Initialise1();
		break;
	}
	}
}
// ��������� � ������������� ����� ��������� ����.
void Shutdown()
{
	SetConsoleOutputCP(1251);
	system("cls");
	cout << "����������! \n������� ����� �������, ����� ����������..."  << endl;
	_getch();
	SetConsoleOutputCP(437);
}
