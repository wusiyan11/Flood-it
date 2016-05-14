#include "textdisplay.h"
using namespace std;

//Initializer 
TextDisplay::TextDisplay(int n) : gridSize(n) {
	theDisplay = new char* [n];
	for (int i = 0;i < n; ++i) {
		theDisplay[i] = new char[n];
	}
	for (int i =0; i < n; ++i) {
		for (int j = 0; j < n; ++j ){
			theDisplay[i][j] = '0';
		}
	}
	for (int i = 0; i < 5 ; ++i) {
		colours[i] = 0;
		//cout << "initialized colours [" << i <<"] = " << colours[i] << endl;
	}
}


TextDisplay::~TextDisplay() {
	for (int i=0; i < gridSize; ++i) {
		delete [] theDisplay[i];
	}
	delete [] theDisplay; 
	theDisplay = NULL;
}

void TextDisplay::notify(int r, int c, char ch) {
	int colour = theDisplay[r][c] - '0';
	int x = ch - '0';
	//cout << "delete" <<endl;
	colours[colour] -= 1;
	colours[0] += 1;
	colours[x] += 1;
	theDisplay[r][c] = ch;
}

//It checks whether all the cells in the board are of the same state or not. 
bool TextDisplay::filled() {
	for (int i=0; i < 5; i++) {
		//cout << "gridSize: " << gridSize << endl;
		//cout << "colours [" << i << "] = " << colours[i] << endl;
		if (colours[i]==(gridSize * gridSize)) {
			return true;
		}
	}
	return false;
}

void TextDisplay::print() {
	for (int i=0; i < gridSize; i++) {
		for (int j=0; j < gridSize; j++) {
			cout << theDisplay[i][j];
		}
		cout << endl;
	}
}
