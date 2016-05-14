#include "textdisplay.h"
using namespace std;

//Initializer 
TextDisplay::TextDisplay(int n) : gridSize((unsigned int)n) {
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
	for (unsigned int i=0; i < gridSize; ++i) {
		delete [] theDisplay[i];
	}
	delete [] theDisplay; 
	theDisplay = NULL;
}

void TextDisplay::notify(int r, int c, char ch) {
	//int colour = theDisplay[r][c] - '0';
	//int x = ch - '0';
	//cout << "delete" <<endl;
	//cout << "colours[0] = " << colours[0] <<endl;
	//colours[colour] -= 1;
	//colours[0] += 1;
	//colours[x] += 1;
	theDisplay[r][c] = ch;
}

//It checks whether all the cells in the board are of the same state or not. 
bool TextDisplay::filled() {
	/*for (unsigned int i=0; i < 5; i++) {
		//cout << "gridSize: " << gridSize << endl;
		cout << "colours [" << i << "] = " << colours[i] << endl;
		if (colours[i]==(gridSize * gridSize)) {
			return true;
		}
	}*/
		for (unsigned int i=0;i < gridSize; i++) {
			for (unsigned int j=0;j < gridSize; j++) {
				if (theDisplay[i][j] != theDisplay[0][0]) {
					return false;
				}
			}
		}
	return true;
}

void TextDisplay::print() {
	for (unsigned int i=0; i < gridSize; i++) {
		for (unsigned int j=0; j < gridSize; j++) {
			cout << theDisplay[i][j];
		}
		cout << endl;
	}
}
