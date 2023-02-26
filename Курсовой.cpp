// Подключение заголовочного файла с функциями.
#include "Header.h"
// Точка входа программы.
int main()
{
	short Enter;
		Menu();
		Enter = Options();
		if (Enter == 1)
		{
			return 0;
		}
		if (Enter == 2)
		{
			system("cls");
			SetupSystem();
			Initialise1();

			do
			{
				Render();
				Update();

			} while (isGameActive);

			Initialise2();
			isGameActive = true;
			do
			{
				Render();
				Update();
				if (cardsOnLevel == cardsNumber) //открываем дверь, если герой собрал все кристаллы
				{
					for (int r = 0; r < rowsCount; r++)
					{
						for (int c = 0; c < columnsCount; c++)
						{
							unsigned char symbol = LevelData1[r][c];

							switch (symbol)
							{
							case '2':
							{
								LevelData[r][c] = symbolExitOn;
								break;
							}
							}
						}
					}
				}


			} while (isGameActive);
			Shutdown();
		
		
	}
	return 0;
}