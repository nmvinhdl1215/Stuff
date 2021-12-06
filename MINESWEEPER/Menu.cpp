#include "Menu.h"
#include "main.h"
#include "screen.h"

void	Menu::Start(int &GAMEMODE)
{
	int MenuSelection = 0;
	do
	{
		clear_screen();
		cout << "***WELCOME TO MINESWEEPER***\n" << endl;
		cout << "1. New game" << endl;
		cout << "2. Continue" << endl;
		cout << "3. Settings" << endl;
		cout << "4. Exit" << endl << endl;

		cout << "Please type a number to continue: ";
		cin >> MenuSelection;
		switch (MenuSelection)
		{
		case 1:
			GAMEMODE = CHOOSE_DIFFICULTY;
			StartNewGame(GAMEMODE);
			break;
		case 2:
			GAMEMODE = IN_GAME;
			LaunchGame(0, 0, 0, "GameSave.txt");
			break;
		case 3:
			break;
		case 4:
			exit(0);
			break;
		default:
			break;
		}
	} while ((MenuSelection != 4) || (GAMEMODE == IN_MENU));
}

void	Menu::StartNewGame(int &GAMEMODE)
{
	int LevelSelection = 0;
	while ((LevelSelection != 5) || (GAMEMODE == CHOOSE_DIFFICULTY))
	{
		clear_screen();
		cout << "***CHOOSE A DIFFICULTY***" << endl << endl;
		cout << "1. Easy" << endl;
		cout << "2. Medium" << endl;
		cout << "3. Hard" << endl;
		cout << "4. Custom" << endl;
		cout << "5. Back to Main Menu" << endl << endl;
		cout << "Please type a number to continue: ";
		cin >> LevelSelection;
		switch (LevelSelection)
		{
		case 1:
		{
			GAMEMODE = IN_GAME;
			int Row = 9;
			int Column = 9;
			int Bomb = 9;
			LaunchGame(Row, Column, Bomb);
			break;
		}
		case 2:
		{
			GAMEMODE = IN_GAME;
			int Row = 16;
			int Column = 16;
			int Bomb = 40;
			LaunchGame(Row, Column, Bomb);
			break;
		}
		case 3:
		{
			GAMEMODE = IN_GAME;
			int Row = 24;
			int Column = 24;
			int Bomb = 99;
			LaunchGame(Row, Column, Bomb);
			break;
		}
		case 4:
		{
			char response = 'n';
			int Row, Column, Bomb;
			while (response != 'y')
			{

				clear_screen();
				// Ask the player to customize their Map
				cout << "***CUSTOME GAME***" << endl << endl;
				cout << "Please enter the number of Rows: ";
				cin >> Row;
				cout << "Please enter the number of Columns: ";
				cin >> Column;
				cout << "Please enter the number of Bombs: ";
				cin >> Bomb;
				// Confirmation
				cout << "Your Gameboard is " << Row << " x " << Column << " with " << Bomb << " Bombs.\n";
				cout << "Please type 'y' to confirm and play or 'n' to recustomize your game.\n";
				cout << "Your response --> ";
				cin >> response;
			}
			GAMEMODE = IN_GAME;
			LaunchGame(Row, Column, Bomb);
			break;
		}
		case 5:
		{
			GAMEMODE = IN_MENU;
			Menu::Start(GAMEMODE);
			break;
		}
		default:
			break;
		}
	}
}
