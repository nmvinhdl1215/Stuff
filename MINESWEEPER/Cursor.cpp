#include <fstream>
#include<iostream>
#include<ios>

#include "Utility.h"
#include "Cursor.h"
#include "Table.h"

Cursor::Cursor() {
	this->x = 0; this->y = 0;
}

std::pair<int, int> Cursor::getPos() {
	return std::pair<int, int>(this->x, this->y);
}

bool Cursor::changePos(int x, int y, Table &gameBoard) {
	std::pair<int, int> dimension = gameBoard.getDimension();
	if (x < 0 || x >= dimension.first || y < 0 || y >= dimension.second) {
		return false;
	}
	this->x = x; this->y = y;
	return true;
}

void Cursor::cursorAction(Table &gameBoard) {
	std::cout << "Current cursor location : (" << this->x << ", " << this->y << ")\n";
	std::cout << "1/ Change cursor location\n";
	std::cout << "2/ Left click to open current tile\n";
	std::cout << "3/ Right click to mark current tile\n";
	std::cout << "4/ Save the game\n";
	std::cout << "5/ End the game\n";
	std::cout << "Choose your action : ";
	int action;
	std::cin >> action;

	switch(action) {
	case 1 : 
		int a, b;
		do {
			bool check = true;
			std::cout << "Enter new cursor position : ";
			std::cin >> a >> b;
			check = this->changePos(a, b, gameBoard);
			if (!check) {
				std::cout << errMessage;
			}
		} while (!this->changePos(a, b, gameBoard));
		break;
	case 2:
		this->leftClick(gameBoard);
		break;
	case 3:
		this->rightClick(gameBoard);
		break;
	case 4:
		this->SaveGame(gameBoard);
		break;
	case 5:
		this->specialStop = true;
		break;
	default :
		std::cout << errMessage;
		system("pause");
		break;
	}
}

bool Cursor::conti() {
	return !this->specialStop;
}

void Cursor::leftClick(Table &gameBoard) {
	if (gameBoard.checkVeiled(this->x, this->y) && !gameBoard.checkMarked(this->x, this->y)) {
		//std::cout << "THIS IS NOT UNVEILED YET\n";
		//system("pause");
		gameBoard.bfs(this->x, this->y);
	}
}

void Cursor::rightClick(Table& gameBoard) {
	if (gameBoard.checkVeiled(this->x, this->y)) {
		gameBoard.changeMarkState(this->x, this->y);
	}
}

void Cursor::SaveGame(Table& gameBoard)
{
	{
		std::ofstream SaveFile;
		SaveFile.open("GameSave.txt", std::ofstream::out | std::ofstream::trunc); // Clear save file's content to save new content

		SaveFile << gameBoard.getDimension().first << ' ' << gameBoard.getDimension().second << ' ' << gameBoard.getFlags() << "\n";

		int rows = gameBoard.getDimension().first;
		int columns = gameBoard.getDimension().second;

		for (int i = 0; i < rows; i++)
			for (int j = 0; j < columns; j++)
			{
				//Save the (i,j) Tile's data
				int pos = i * columns + j;
				SaveFile << gameBoard.getAdj(i, j) << " " << gameBoard.checkVeiled(i, j) << " " << gameBoard.checkMarked(i, j) << " " << gameBoard.checkBomb(i, j) << "\n";
			}

		SaveFile.close();
	}
}