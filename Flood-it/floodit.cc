#if _WIN32
// This is Windows-Only
inline int getpid() {
        return 42;
}
#else

#include <sys/types.h>
#include <unistd.h>
#include "game.h"
#include "textdisplay.h"
#include "cell.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <limits>
#include <climits>
#include "PRNG.h"

using namespace std;


//Handles usage error;
void usage(char *argv[]) {
        cerr << "Usage: " << argv[0] << " [ -size N (width and height of game ) >= 2) ] |"
        << " [ -moves M (number of moves until game is over) >= 1) ] | [ -seed S (seed for"
        << " random-number generator (1..INT_MAX)) ]" << endl;
        exit(EXIT_FAILURE);
}

int seed;// Global use

// void change_option(char * first, char * second, int &moves, int &size, int &seed, char* argv[])
//   changes defualt options and return usage error if options are used wrong.
void change_option(char * first, char * second, int &moves, int &size, int &seed, char* argv[]) {
        string option = string(first);
        int num;
        stringstream ss(second);
        ss >> num;
        if (ss.fail()) {
                usage (argv);
        }
        if (option == "-moves") {
                if (num < 1) {
                        usage (argv);
                }
                moves = num;
                return;
        }
        if (option == "-size") {
                if (num < 2) {
                        usage (argv);
                }
                size = atoi(second);
                return;
        }
        if (option == "-seed") {
                if (num > INT_MAX) {
                        usage (argv);
                }
                seed = atoi(second);
                return;
        }
        usage(argv);
}

int main (int argc, char * argv[]) {
        istream * infile = &cin;
        int size = 10, moves = 20;
        seed = getpid();

        switch (argc) {
                case 7: {
                        change_option(argv[5],argv[6],moves,size,seed,argv);
                }
                case 5: {
                        change_option(argv[3],argv[4],moves,size,seed,argv);
                }
                case 3: {
                        change_option(argv[1],argv[2],moves,size,seed,argv);
                        break;
                }
                case 1: {
                        break;
                }
                default: {
                        usage(argv); //Usage Error
                }
        }

        Game g(size,moves);
        int imove;
        int movesleft = g.getTurns();
        g.print();
        cout << movesleft << " moves left" << endl;


        while (!cin.eof()) {
                *infile >> imove;
                if (cin.eof()) {
                        break;
                }
                if (movesleft == 0) {
                        cout << "Lost" << endl;
                        return 0;
                }
                if (cin.fail()) {
                        cerr << "Invalid move" << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<int>::max(),'\n');
                } else {
                        g.change(imove);
                        g.print();
                        movesleft = g.getTurns();
                        if (movesleft == 1) {
                                cout << movesleft << " move left" << endl;
                        } else {
                                cout << movesleft << " moves left" << endl;
                        }
                        if (g.isWon()) {
                                cout << "Won" << endl;
                                return 0;
                        }
                }
        }
}
#endif
