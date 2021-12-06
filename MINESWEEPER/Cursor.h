#ifndef CURSOR_H
#define CURSOR_H

#include<utility>
#include "Utility.h"
#include "Table.h"

class Cursor {
public : 
	int x, y; //coordinate
	bool specialStop = false; //quickly skip the game

public :
	Cursor();
	bool changePos(int x, int y, Table &gameBoard);
	void leftClick(Table &gameBoard);
	void rightClick(Table &gameBoard);
	void cursorAction(Table &gameBoard);
	bool conti(); //get the value of special stop
	void SaveGame(Table& gameBoard); /*Save the Game*/
	std::pair<int, int> getPos();
};

#endif