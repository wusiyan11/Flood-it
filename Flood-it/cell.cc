#include "cell.h"
#include <cassert>
using namespace std;

TextDisplay* Cell::display;

void Cell::notifyNeighbours() {
	for (int i=0; i < numNeighbours ; i++) {

		//cout << "row: " << row << " col: " << col << endl;
		//cout << "state: " << state << " prevState: " << prevState << endl;
		neighbours[i]->notify(state,prevState);
	}
}

void Cell::notifyDisplay() {
	char temp = state + '0';
	Cell::display->notify(row, col, temp);
}

Cell::Cell() : neighbours() {
	state = prevState = numNeighbours = row = col = 0;
	inProgress = false;
}

int Cell::getState() {
	inProgress = false;
	return state;
}

void Cell::setState(int change) {
	prevState = state;
	state = change;
}

void Cell::setCoords(int row, int col) {
	this->row = row;
	this->col = col;
}

void Cell::addNeighbour(Cell* neighbour) {
	assert(neighbour != NULL);
	for (int i=0; i<MAX_NEIGHBOURS; i++) {
		if (neighbours[i] == NULL) {
			neighbours[i] = neighbour;
			numNeighbours += 1;
			break;
		}
	}
}

void Cell::addDisplay(TextDisplay* display) {
	Cell::display = display;
}

void Cell::notify(int current, int previous) {
	if (previous == state || previous == -1) {
		//cout << "previous is " << previous << endl;
		if (inProgress == true) {
			return;
		}
		inProgress = true;
		this->prevState = state;
		state = current;
		notifyNeighbours();
		notifyDisplay();
	}
}
