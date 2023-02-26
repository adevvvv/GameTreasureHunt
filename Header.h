// Защита от многочисленного подключения заголовка.
#pragma once
// Подключение заголовочного файла, который позволяет работать с потоками ввода/вывода.
#include <iostream>
// Подключение заголовочного файла для работы со временем.
#include <ctime>
// Подключаем заголовочный файл, в котором содержатся прототипы функции SetConsoleCP(кодовая таблица) и SetConsoleOutputCP(кодовая таблица).
#include <Windows.h>
// Подключаем заголовочный файл для getch.
#include <conio.h>
// Нужно для того, чтоб не было конфиликтов повторяющихся переменных.
using namespace std;
// Количество строк в массиве.
const int rowsCount = 20;
// Количество столбцов в массиве.
const int columnsCount = 40;
// Герой. ASCII - символ 220.
const unsigned char symbolHero = 220;
// Стена. ASCII - символ 177.
const unsigned char symbolWall = 177;
// Ящик. ASCII - символ 254.
const unsigned char symbolBox = 254;
// Выход. ASCII - символ 178.
const unsigned char symbolExitOn = 178;
// Мина. ASCII - символ 42.
const unsigned char symbolMine = 42;
// Карточки. ASCII - символ 36.
const unsigned char symbolCard = 15;
// Выход. ASCII - символ 176.
const unsigned char symbolExitOff = 176;
// Двумерный массив для лабиринта 1 уровня.
const unsigned char LevelData1[rowsCount][columnsCount + 1] = 
{
	// Герой - 1, выход - 2, стена - #, ящик - х.
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
// Двумерный массив для лабиринта 2 уровня.
const unsigned char LevelData2[rowsCount][columnsCount + 1] =
{
	// Герой - 1, выход - 2, стена - #, ящик - х, карточки - !, * - мина. 
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
// Дискриптор вывода консоли.
HANDLE consoleHandle = 0;
// Переменная, которая будет отвечать за то, нужно ли продолжать игру после очередного ввода.
bool isGameActive = true;
// Двумерный массив.
unsigned char LevelData[rowsCount][columnsCount];
// Для слежения за координатами перемещения героя. Ряд.
int heroRow = 0;
// Для слежения за координатами перемещения героя. Колонка.
int heroColumn = 0;
// Счетчик карт.
int cardsNumber = 0;
// Карточки для уровня 2. 
int cardsOnLevel;
// Функция меню.
void Menu()
{
	cout << "1. Exit" << endl << "2. Start." << endl;
}
// Функция работы с меню.
short Options()
{
	SetConsoleOutputCP(1251);
	while (true)
	{
		short Enter;
		cin >> Enter;
		// cin.fail() - Определяет, соответствует ли определенное значение значению, определенному в переменной.
		if (cin.fail() || Enter < 1 || 2 < Enter)
		{
			// Востанавливает поток, если что-то пошло не так.
			cin.clear();
			// cin.ignore - функция, которая считывает символ и игнорирует его; 
			// cin.rdbuf - буфер чтения, в котором он хранит символы; in_avail - сколько кол-во символов в нем содержится
			cin.ignore(cin.rdbuf()->in_avail());
			cout << endl << "Ошибка! Повторите." << endl;
		}
		else if ((Enter == 1) || (Enter == 2))
		{
			SetConsoleOutputCP(437);
			cin.ignore(cin.rdbuf()->in_avail());
			return Enter;
		}
	}
}
// Задание зерна генератору псевдослучайных чисел.
void SetupSystem()
{
	srand(time(0));
	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
}
// Задаем начальные значения для логики игры 1.
void Initialise1()
{
	cardsOnLevel = 0;
	// Внешний for, который будет двигаться счетчиком r по строкам массива.
	for (int r = 0; r < rowsCount; r++)
	{
		// Внутренний for, который будет двигаться счетчиком с по столбцам массива.
		for (int c = 0; c < columnsCount; c++)
		{
			// Для получения текущего символа на r-строке и в с-столбце.
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
// Задаем начальные значения для логики игры 2.
void Initialise2()
{
	cardsOnLevel = 44;
	// Внешний for, который будет двигаться счетчиком r по строкам массива.
	for (int r = 0; r < rowsCount; r++)
	{
		// Внутренний for, который будет двигаться счетчиком с по столбцам массива.
		for (int c = 0; c < columnsCount; c++)
		{
			// Для получения текущего символа на r-строке и в с-столбце.
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
// Весь графический вывод основного цикла игры на экран.
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
	cout << "\n\tИспользуйте WASD для перемещения ";
	SetConsoleTextAttribute(consoleHandle, 10);
	cout << "Героя";
	SetConsoleTextAttribute(consoleHandle, 7);
	cout << ".Будьте осторожны, во втором уровне будут ";
	SetConsoleTextAttribute(consoleHandle, 13);
	cout << "мины";
	SetConsoleTextAttribute(consoleHandle, 7);
	cout << ".\n\tДля того, чтобы пройти уровень 2 вам нужно собрать все ";
	SetConsoleTextAttribute(consoleHandle, 11);
	cout << "карточки.";
	SetConsoleTextAttribute(consoleHandle, 7);
	cout << "\n\tИх должно быть 44 для того чтобы открыть ";
	SetConsoleTextAttribute(consoleHandle, 12);
	cout << "дверь";
	SetConsoleTextAttribute(consoleHandle, 7);
	cout << ".\n\tR - заново.";
	cout << "\n\n\tВы собрали карточек = " << cardsNumber << " | ";
	SetConsoleOutputCP(437);


}
// Перемещение героя.
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
		// Проверяем, есть ли пустое место за коробкой.
		if (LevelData[row + heroDirectionR][column + heroDirectionC] == ' ')
		{
			canMoveToCell = true;
			// Ставим коробку на новые координаты.
			LevelData[row + heroDirectionR][column + heroDirectionC] = symbolBox;
		}
	}
	case symbolCard:
	{
		int heroDirectionR = row - heroRow;
		int heroDirectionC = column - heroColumn;
		// Проверям, есть ли объект в радиусе одной клетки от героя.
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
		// Стираем предыдущий значок героя.
		LevelData[heroRow][heroColumn] = ' ';
		// Записываем новые координаты.
		heroRow = row;
		heroColumn = column;

		LevelData[heroRow][heroColumn] = symbolHero;
	}
}
// Совершаем ввод и осуществляем основную логику игры.
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
// Прощаемся с пользователем после окончания игры.
void Shutdown()
{
	SetConsoleOutputCP(1251);
	system("cls");
	cout << "Поздравляю! \nНажмите любую клавишу, чтобы продолжить..."  << endl;
	_getch();
	SetConsoleOutputCP(437);
}
