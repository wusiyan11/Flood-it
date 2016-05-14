#include "game.h"
#include "textdisplay.h"
#include "cell.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include "PRNG.h"

using namespace std;

int seed;

void change_option(char * first, char * second, int &moves, int &size, int &seed) {
	string option = string(first);
	int num = atoi(second);

	if (option == "-moves" && num >= 2) {
		moves = num;
	}
	if (option == "-size" && num >= 1) {
		size = atoi(second);
	}
	if (option == "-seed") {
		seed = atoi(second);
	}
}

int main (int argc, char * argv[]) {
	istream * infile = &cin;
	int size = 10, moves = 20;
	seed = getpid();

	switch (argc) {
		case 7: {
			change_option(argv[5],argv[6],moves,size,seed);
		}
		case 5: {
			change_option(argv[3],argv[4],moves,size,seed);
		}
		case 3: {
			change_option(argv[1],argv[2],moves,size,seed);
			break;
		}
		default: {
			//Usage Error
		}
	}

	Game g(size,moves);
	int move;
	int movesleft = g.getTurns();

	while (movesleft) {
	
	g.print();
	cout << movesleft << " moves left" << endl;
		if (infile->eof()) {
			break;
		}
		*infile >> move;
		g.change(move);
		if (g.isWon()) {
			g.print();
			movesleft = g.getTurns();
			cout << movesleft << " moves left" << endl;
			cout << "Won" << endl;
			return 0;
		}
		movesleft = g.getTurns();
	}
	cout << "Lost" << endl;
}
