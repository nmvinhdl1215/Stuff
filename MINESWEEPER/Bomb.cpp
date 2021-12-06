#include "Bomb.h"

Bomb::Bomb(){
	this->x = -1; this->y = -1;
};

Bomb::Bomb(int x, int y) {
	this->x = x;
	this->y = y;
}

bool Bomb::checkViable() { //current tile is not assigned as a bomb tile
	return (x <= -1 || y <= -1);
}

bool Bomb::getVeiledState() {
	return this->veiled;
}

bool Bomb::getMark() {
	return this->mark;
}

void Bomb::swapVeiledState() {
	this->veiled = !this->veiled;
}

void Bomb::changeMark() {
	this->mark = !this->mark;
}