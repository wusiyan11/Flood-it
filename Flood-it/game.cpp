#include "game.h"
using namespace std;

extern int seed;

Game::Game(int size, int turns) : grid(NULL), gridSize(size), turns(turns),
    display(NULL){
    myseed = seed;
	display = new TextDisplay(size);
	grid = new Cell* [size];

	int ranum;
	PRNG prng(myseed);	

	for (int i=0;i<size;i++) {
		grid[i] = new Cell[size];
	}
    grid[0][0].addDisplay(display);
	for (int i=0;i<size;i++) {
		for (int j=0;j<size;j++) {
			ranum = prng(4);
			grid[i][j].setState(ranum);
			grid[i][j].setCoords(i,j);

			char color = ranum + '0';
			display->notify(i,j,color);

			if (i != 0) {
				grid[i][j].addNeighbour(&grid[i-1][j]);
			}
			if (i != (size - 1)) {
				grid[i][j].addNeighbour(&grid[i+1][j]);
			}
			if (j != 0) {
				grid[i][j].addNeighbour(&grid[i][j-1]);
			}
			if (j != (size - 1)) {
				grid[i][j].addNeighbour(&grid[i][j+1]);	
			}
		}
	}
}

Game::~Game() {
	for (int i = 0; i<turns; i++) {
		delete [] grid[i];
	}
	delete [] grid;
	delete display;
}

int Game::getTurns(){
	return turns;
}

bool Game::isWon(){
	if (turns >= 0 && display->filled()) {
		return true;
	}
	return false;
}

void Game::change(int state) {
	grid[0][0].notify(state);
	turns -= 1;
}

void Game::print() {
	display->print();
	for (int i=0;i<gridSize;i++) {
		for (int j=0;j<gridSize;j++) {
			grid[i][j].getState();
		}
	}
}


