#ifndef __GAME_H__
#define __GAME_H__
#include <iostream>
#include "cell.h"
#include "textdisplay.h"
#include "PRNG.h"
using namespace std;

class Game {
	Cell** grid;  				 // The actual grid.
	const int gridSize;    // Size of the grid.
	int turns;						 // Number of turns remaining
	TextDisplay* display;  // The text display.
	//	int seed;

public:
	Game(int size, int turns);
	~Game();

	int getTurns();
	bool isWon();
	void change(int state);  // Changes (0,0) and all appropriate neighbours to state

	void print();
};

#endif
