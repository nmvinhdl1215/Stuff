#include<iostream>
#include<vector>
#include<utility>
#include<queue>
#ifdef _WIN32
	#include <windows.h>
#endif

#include "Utility.h"
#include "Table.h"
#include "Tile.h"

#ifdef __unix__
static const char* c_red		= "\033[1;31m";
static const char* c_green 		= "\033[1;32m";
static const char* c_yellow		= "\033[1;33m";
static const char* c_blue		= "\033[1;34m";
static const char* c_magenta	= "\033[1;35m";
static const char* c_cyan		= "\033[1;36m";
static const char* c_reset		= "\033[0m";
#endif /* not __unix__ */
#ifdef __GNUC__
	__attribute__((always_inline))
#endif /*not __GNUC__ */
inline void Table::changeColor(int x) {
#ifdef __unix__
	switch(x)
	{
		case 1:
			puts(c_red);
			break;
		case 2:
			puts(c_green);
			break;
		case 3:
			puts(c_yellow);
			break;
		case 4:
			puts(c_blue);
			break;
		case 5:
			puts(c_magenta);
			break;
		case 6:
			puts(c_cyan);
			break;
		default:
			puts(c_reset);
			break;
	}
#elif defined _WIN32
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
#endif

}

Table::Table() {
	this->rows = 0;
	this->columns = 0;
	this->flags = 0;
};

Table::Table(int rows, int columns, int bombs) {
	this->rows = rows;
	this->columns = columns;
	this->flags = bombs;
	this->Tiles.resize(rows * columns);

	this->genTile(bombs);
}

void Table::drawTable() {
	std::cout << "    ";
	for (int i = 0; i < this->columns; i++) {
		std::cout << i << ' ';
	}
	std::cout << "\n\n";
	for (int i = 0; i < this->rows; i++) {
		std::cout << i << "  ";
		if (i < 10) { std::cout << ' '; }
		for (int j = 0; j < this->columns; j++) {
			int pos = i * columns + j;


			if (this->Tiles[pos].getMark()) {
				this->changeColor(2); //green
				std::cout << "? ";
				this->changeColor(7); //back to normal
				continue;
			}
			else if (this->Tiles[pos].getVeiledState()) {
				std::cout << "# ";
				continue;
			}

			if (this->Tiles[pos].isBomb()) { 
				this->changeColor(4); //red
				std::cout << "B "; 
				this->changeColor(7);
			}
			else { 
				if (this->Tiles[pos].getAdjVal() > 0) std::cout << this->Tiles[pos].getAdjVal() << " ";
				else std::cout << "  ";
			}
		}
		std::cout << '\n';
	}
	for (int i = 0; i < 3; i++) {
		std::cout << '\n';
	}
}

bool Table::checkBomb(int x, int y) {
	return this->Tiles[x * this->columns + y].isBomb();
}

void Table::genTile(int bombs) {
	while (bombs) {
		int x = getRand(0, this->rows - 1);
		int y = getRand(0, this->columns - 1);
		//std::cerr << x << ' ' << y << '\n';
		int pos = x * columns + y;
		if (!this->Tiles[pos].isBomb()) {
			this->Tiles[pos] = Tile(x, y, true);
			--bombs;
		}
	}

	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < this->columns; j++) {
			int pos = i * columns + j;
			if (!this->Tiles[pos].isBomb()) {
				this->Tiles[pos] = Tile(i, j);
				this->getAdj(i, j);
			}
		}
	}
}

std::pair<int, int> Table::getDimension() {
	return std::pair<int, int>(this->rows, this->columns);
}

void Table::openVeiled(int x, int y) {
	int pos = x * this->columns + y;
	this->Tiles[pos].changeVeiledState();
	if (this->Tiles[pos].getMark()) {
		this->changeMarkState(x, y);
	}
}

void Table::changeMarkState(int x, int y) {
	int pos = x * this->columns + y;
	if (this->Tiles[pos].getMark()) {
		this->flags++;
	}
	else {
		this->flags--;
	}
	if (this->flags < 0) {
		this->flags = 0;
		return;
	}
	this->Tiles[pos].changeMark();
}

bool Table::checkVeiled(int x, int y) {
	int pos = x * this->columns + y;
	return this->Tiles[pos].getVeiledState();
}

bool Table::checkMarked(int x, int y) {
	int pos = x * this->columns + y;
	return this->Tiles[pos].getMark();
}

int Table::getAdj(int x, int y) {
	int ans = 0;
	int ori = x * this->columns + y;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (x + i < 0 || x + i >= this->rows || y + j < 0 || y + j >= this->columns) {
				continue;
			}
			int pos = (x + i) * this->columns + (y + j);
			ans += this->Tiles[pos].isBomb();
		}
	}
	this->Tiles[ori].getAdj(ans);
	return ans;
}

void Table::bfs(int x, int y) {
	std::queue<std::pair<int, int> > hold;
	hold.push(std::pair<int, int>(x, y));
	while (!hold.empty()) {
		std::pair<int, int> cur = hold.front();
		hold.pop();
		int pos = cur.first * this->columns + cur.second;
		if (!this->Tiles[pos].getVeiledState()) {
			continue;
		}
		this->openVeiled(cur.first, cur.second);

		if (this->Tiles[pos].getAdjVal() == 0 && !this->Tiles[pos].isBomb()) {
			for (int i = -1; i <= 1; i++) {
				for (int j = -1; j <= 1; j++) {
					if (cur.first + i < 0 || cur.first + i >= this->rows || cur.second + j < 0 || cur.second + j >= this->columns) {
						continue;
					}
					hold.push(std::pair<int, int>(cur.first + i, cur.second + j));
				}
			}
		}
	}
}

int Table::checkWinState() {
	int winState = 1;
	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < this->columns; j++) {
			int pos = i * columns + j;
			if (this->Tiles[pos].isBomb() && !this->Tiles[pos].getVeiledState()) {
				return -1;
			}
			if (!this->Tiles[pos].isBomb() && this->Tiles[pos].getVeiledState()) {
				winState = 0;
			}
			if (this->Tiles[pos].isBomb() && !this->Tiles[pos].getMark()) {
				winState = 0;
			}
		}
	}

	//system("pause");
	return winState;
}

int Table::getFlags() {
	return this->flags;
}

void Table::setUpTile(int x, int y, int adj, bool veil, bool mark, bool bomb) {
	int pos = x * this->columns + y;
	this->Tiles[pos] = Tile(x, y, bomb);
	this->Tiles[pos].reAdjValue(adj);
	if (!veil) {
		this->openVeiled(x, y);
	}
	if (mark) {
		this->Tiles[pos].changeMark();
	}
}

void Table::unveiledAll() {
	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < this->columns; j++) {
			int pos = i * this->columns + j;
			if (this->Tiles[pos].getVeiledState()) {
				this->openVeiled(i, j);
			}
		}
	}
}
