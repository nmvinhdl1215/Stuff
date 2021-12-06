#include<vector>

#include "Tile.h"

Tile::Tile() {
	this->x = -1; this->y = -1; this->adjacent = 0;
};

Tile::Tile(int x, int y, bool bomb) {
	this->x = x;
	this->y = y;
	this->bomb = bomb;
	this->adjacent = 0;
}

void Tile::reAdjValue(int adj) {
	this->adjacent = adj;
}

bool Tile::getVeiledState() {
	return this->veiled;
}

bool Tile::getMark() {
	return this->mark;
}

void Tile::changeVeiledState() {
	this->veiled = !this->veiled;
}

void Tile::changeMark() {
	this->mark = !this->mark;
}

bool Tile::isBomb() {
	return this->bomb;
}

void Tile::getAdj(int val) {
	this->adjacent = val;
}

int Tile::getAdjVal() {
	return this->adjacent;
}