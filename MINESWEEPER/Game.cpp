#include <SFML/Graphics.hpp>
#include <string>
#include "main.h"
#include "screen.h"
#include "TileMap.h"

/* Game.cpp - main game file
 */
/**
 * LaunchGame - launch new minesweeper session
 * @Row:	Number of rows
 * @Column:	Number of column
 * @Bomb:	Number of Bomb
 * @fSave:	Game session file
 *
 * Launch a new minsweeper session (windows) with given settings
 */
void LaunchGame(int Row, int Column, int Bomb, string fSave)
{

	// Timer Initiatives
	EngineUtils::Timer* timer = EngineUtils::Timer::Instance();
	bool isRunning = true;
	float frameRate = 60.0f;
	float elapsedTime = 0.0f;
	float TotalTime = 0.0f;

	// Game Initiatives
	Table table;

	if (fSave != "") {
		ifstream Save(fSave);
		Save >> Row >> Column >> Bomb;
		table = Table(Row, Column, Bomb);
		for (int i = 0; i < Row; i++) {
			for (int j = 0; j < Column; j++) {
				int a;
				bool b, c, d;
				Save >> a >> b >> c >> d;
				table.setUpTile(i, j, a, b, c, d);
			}
		}
	}
	else {
		table = Table(Row, Column, Bomb);
	}

	sf::RenderWindow window(sf::VideoMode(50 * Column, 46 * Row), "Tilemap");

	Cursor cursor = Cursor();
	int winState = 0;

	TileMap map;
#ifdef __unix__
	if (!map.load("Images/TileSet.png", sf::Vector2u(50, 46), table)) {
#elif defined  _WIN32
	if (!map.load("Images\\TileSet.png", sf::Vector2u(50, 46), table)) {
#endif
		return;
	}

	while (window.isOpen() && cursor.conti() && (winState == 0)) {
		sf::Event event;
		while (window.pollEvent(event)) {
#ifdef __unix__
			if (!map.load("Images/TileSet.png", sf::Vector2u(50, 46), table)) {
#elif defined _WIN32
			if (!map.load("Images\\TileSet.png", sf::Vector2u(50, 46), table)) {
#endif
				return;
			}

			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::MouseButtonReleased) {
				cursor.changePos(event.mouseButton.y / 46, event.mouseButton.x / 50, table);
				if (event.mouseButton.button == sf::Mouse::Left) {
					std::cout << "Left click in : " << event.mouseButton.x << ' ' << event.mouseButton.y << '\n';
					cursor.leftClick(table);
				}
				if (event.mouseButton.button == sf::Mouse::Right) {
					std::cout << "Right click in : " << event.mouseButton.x << ' ' << event.mouseButton.y << '\n';
					cursor.rightClick(table);
				}
			}

			window.clear(sf::Color::Black);
			window.draw(map);
			window.display();

			winState = table.checkWinState();
		}

		//cursor.cursorAction(table);
	}

	if (winState == 0) {
		return;
	}
	
	clear_screen();

	if (winState == 1) {
		table.drawTable();
		cout << "YOU WIN HURRAYYYY!!!\n";
	}
	else if (winState == -1) {
		table.unveiledAll();
		table.drawTable();
		cout << "YOU LOSE, NOOB. GO BACK WHEN YOU GETTIN BETTER.\n";
	}
	getchar();	// On wait. Replace system("pause")
}

