#ifndef TILE_H
#define TILE_H

//#include "Table.h"

class Tile {
private :
	int x, y; //coordinate 
	int adjacent; //the amount of adjacent bomb
	bool veiled = true; //haven't beeing press
	bool mark = false; //right click thinggy
	bool bomb = false; //is it a bomb or not

public :
	Tile();
	Tile(int x, int y, bool bomb = 0);
	void getAdj(int val); //assign adjacent bomb
	int getAdjVal();
	bool isBomb(); 
	void reAdjValue(int adj);
	bool getVeiledState(); //being clicked or not
	bool getMark(); //being marked or not 
	void changeVeiledState(); //mostly for unveiled 
	void changeMark(); //mark or unmark that tile 
};

#endif