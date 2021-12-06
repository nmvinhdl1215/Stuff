#ifndef BOMB_H
#define BOMB_H


class Bomb {
private:
	int x = -1, y = -1; //coordinate;
	bool veiled = true; //haven't beeing press
	bool mark = false; //right click thinggy

public:
	Bomb();
	Bomb(int x, int y);
	bool checkViable();
	bool getVeiledState();
	bool getMark(); //being marked or not ? 
	void swapVeiledState();
	void changeMark(); //mark or unmark that tile 
};

#endif 