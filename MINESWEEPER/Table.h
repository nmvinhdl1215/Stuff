#ifndef __TABLE_H
#define __TABLE_H


#include<vector>
#include<utility>

#include "Bomb.h"
#include "Tile.h"

class Table { //settings up the table 
private:
	int rows, columns, flags;
	std::vector<Tile> Tiles;

public:
	Table();
	Table(int rows, int columns, int bombs);
	void genTile(int bombs); //randomly generating the bombs and setup the number tiles
	int getAdj(int x, int y); /* Find and return the number of adj bombs to Tile(x,y) of the Table. */
	int checkWinState();
	void drawTable(); //draw the game board
	std::pair<int, int> getDimension();
	bool checkBomb(int x, int y); //check if there is a bomb in that position 
	bool checkVeiled(int x, int y);
	bool checkMarked(int x, int y);
	void openVeiled(int x, int y); //after left clicking 
	void changeMarkState(int x, int y);
	int getFlags();
	void bfs(int x, int y); //handle case where the tile's adjacent variable = 0
	void setUpTile(int x, int y, int adj, bool veil, bool mark, bool bomb);
	void changeColor(int x);
	void unveiledAll(); //for endgame 
};

#endif 