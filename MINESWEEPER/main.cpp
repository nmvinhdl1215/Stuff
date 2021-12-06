#include <stdio.h>    
#include<iostream>
#include<stdlib.h>
#include<time.h>

#include "Table.h"
#include "Cursor.h"

int main() {
	srand(time(NULL));
	std::cout << "Minesweeper game\n";
	std::cout << "Enter the rows : ";
	int rows, colums;
	std::cin >> rows;
	std::cout << "Enter the columns : ";
	std::cin >> colums;
	std::cout << "Enter the ammount of bombs : ";
	int bombs;
	std::cin >> bombs;
	Table gameBoard = Table(rows, colums, bombs);
	Cursor cursor = Cursor();

	system("cls");

	while (cursor.conti()) {
		gameBoard.drawTable();
		cursor.cursorAction(gameBoard);
		system("cls");
	}

	return 0;
}